#include <iostream>

using namespace std;

#define MAX_VALUE 1023
void count_all(int input_array_size, int * input_array, int * output_array){
    int counter;

    for(counter = 0; counter < input_array_size; counter++) {
        assert(input_array[counter] <= MAX_VALUE);
        assert(input_array[counter] >= 0);
        output_array[input_array[counter]]++;
    }
}

int main(int argc, char *argv[])
{
    int input_array[MAX_VALUE];
    int output_array[MAX_VALUE];

    count_all(MAX_VALUE, input_array, output_array);

    cout << "All Processes Successfully Completed!" << endl;
}
