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

   int thread_num;
   pthread_cond_t  cv;
   pthread_mutex_t mutex;

   //this gets passed around through functions, so must be a pointer!
   int *flag;
};

static struct thread_data thread_data_array[NUM_THREADS];

void P(int* output_lock_array_ptr, int thread_num){

    cout << "P("
         << thread_num
         << "): data @ thread_data_array[" << *output_lock_array_ptr
         << "] flag=" << thread_data_array[*output_lock_array_ptr].flag
         << endl;

    //lock this thread in preparation for exclusive access
    pthread_mutex_lock(&thread_data_array[*output_lock_array_ptr].mutex);

    cout << "P(" << thread_num << ") locked." << endl;
    //note that while loop is only entered if this part of the array is unavailable

    //check that this coordinate in the output array is not currently being accessed
    while (*(thread_data_array[*output_lock_array_ptr].flag) == 0) {

        /* When the current thread executes this
         * pthread_cond_wait() statement, the
         * current thread will be blocked on s->cv
         * and (atomically) unlocks s->mutex !!!
         * Unlocking s->mutex will let other thread
         * in to test s->flag.... */
        pthread_cond_wait(&(thread_data_array[*output_lock_array_ptr].cv),
                &thread_data_array[*output_lock_array_ptr].mutex);

        //wait until the lock has been released by some other thread's V() call
        //cout << (*output_lock_array_ptr) << " waiting..." << endl;
    }

    /* This will cause all other threads
     * that executes a P() call to wait
     * in the (above) while-loop !!! */
    *(thread_data_array[*output_lock_array_ptr].flag) = 0;

    cout << "P(" << thread_num << ") flag set to 0." << endl;

    //release lock in preparation for access
    pthread_mutex_unlock(&thread_data_array[*output_lock_array_ptr].mutex);

    cout << "P(" << thread_num << ") unlocked." << endl;
}

void V(int* output_lock_array_ptr) {

    cout << "V(" << *output_lock_array_ptr << ")" << endl;

    //lock this thread in preparation for exclusive access
    pthread_mutex_lock(&thread_data_array[*output_lock_array_ptr].mutex);

    /* This call may restart some thread that
     * was blocked on s->cv (in the P() call)
     * if there was not thread blocked on
     * cv, this operation does absolutely
     * nothing...                          */
    pthread_cond_signal(&thread_data_array[*output_lock_array_ptr].cv);

    /* Update semaphore state to Up */
    *(thread_data_array[*output_lock_array_ptr].flag) = 1;

    //release lock in preparation for access
    pthread_mutex_unlock(&thread_data_array[*output_lock_array_ptr].mutex);
}

void count_all(int input_array_size, int *input_array, int *output_array, int *output_lock_array){

    int counter;
    for(counter = 0; counter < input_array_size; counter++) {

        assert(input_array[counter] <= MAX_VALUE);
        assert(input_array[counter] >= 0);

        //retrieve an exclusive lock to this cord in output_array
        //waiting on other threads, if necessary

        cout << "processing entry #" << counter << ", with value=" << input_array[counter] << endl;

        int thread_data_pos = output_lock_array[counter];

        cout << "Thread Data:"
             << "Thread #" << thread_data_array[thread_data_pos].thread_num
             << endl;

        //change flag state
        P(&output_lock_array[counter], thread_data_array[thread_data_pos].thread_num);

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
        thread_data_array[counter].thread_num = counter;
        thread_data_array[counter].flag = new int(1); //initialize to all access.

        pthread_mutex_unlock(&thread_data_array[counter].mutex);

        pthread_create(&threads[counter], nullptr, function_starter, static_cast<void*>(&(thread_data_array[counter])));
    }
    for(counter = 0; counter < NUM_THREADS; counter++){
        void *dummy;
        pthread_join(threads[counter], &dummy);
    }

    cout << "All Processes Successfully Completed!" << endl;
}
