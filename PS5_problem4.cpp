#include <iostream>

// Assumes that the input and output arrays are created
// outside of the function.  Note that the output lock array is assumed to be
// initialized to 1 (this allows for a mutex)
#include <thread>
#include <stdlib.h>
#define MAX_VALUE 1023
#define NUM_THREADS 1//100
#define INPUT_ARRAY_ELEMENTS (1024*1024*512)  // 512 million entries

using namespace std;

struct thread_data{
   int input_array_size;

   int *input_array;
   int *output_array;
   int *output_lock_array;
};

static struct thread_data thread_data_array[NUM_THREADS];

void P(int* output_lock_array_ptr){

    //check that this coordinate in the output array is not currently being accessed
    while (*output_lock_array_ptr == 0) {
        //wait until the lock has been released by some other thread's V() call
        cout << (*output_lock_array_ptr) << " waiting..." << endl;
    }

    //lock this thread in preparation for exclusive access
    *output_lock_array_ptr = 0;
}

void V(int* output_lock_array_ptr) {
    //release lock
    *output_lock_array_ptr = 1;
}

void count_all(int input_array_size, int *input_array, int *output_array, int *output_lock_array){

    int counter;
    for(counter = 0; counter < input_array_size; counter++) {

        assert(input_array[counter] <= MAX_VALUE);
        assert(input_array[counter] >= 0);

        //retrieve an exclusive lock to this cord in output_array
        //waiting on other threads, if necessary

        cout << "processing entry #" << counter << ", with value=" << input_array[counter] << endl;

        P(&output_lock_array[counter]);

        //thread-safe work
        output_array[input_array[counter]]++;

        //release exclusive lock
        V(&output_lock_array[counter]);
    }
}

void *function_starter(void *thread_args) {
    thread_data *temp_data = static_cast<struct thread_data*>(thread_args);
    count_all(temp_data->input_array_size, temp_data->input_array, temp_data->output_array, temp_data->output_lock_array);
    pthread_exit(nullptr);
}

int main(int argc, char *argv[]){

    int counter;
    pthread_t threads[NUM_THREADS];

    int *input_array = static_cast<int*>(malloc(INPUT_ARRAY_ELEMENTS*sizeof(int)));

    // this would be a good place to read a file into input_array
    int *output_array = static_cast<int*>(malloc((MAX_VALUE + 1) * sizeof(int)));
    int *output_lock_array = static_cast<int*>(malloc((MAX_VALUE + 1) * sizeof(int)));

    for(counter = 0; counter <= MAX_VALUE; counter++){
       output_array[counter] = 0;
       output_lock_array[counter] = 1;
    }

    for(counter = 0; counter < NUM_THREADS; counter++){
        thread_data_array[counter].input_array_size = INPUT_ARRAY_ELEMENTS / NUM_THREADS;
        thread_data_array[counter].input_array = &input_array[INPUT_ARRAY_ELEMENTS / NUM_THREADS * counter];
        thread_data_array[counter].output_array = output_array;
        thread_data_array[counter].output_lock_array = output_lock_array;

        pthread_create(&threads[counter], nullptr, function_starter, static_cast<void*>(&(thread_data_array[counter])));
    }
    for(counter = 0; counter < NUM_THREADS; counter++){
        void *dummy;
        pthread_join(threads[counter], &dummy);
    }

    cout << "All Processes Successfully Completed!" << endl;
}
