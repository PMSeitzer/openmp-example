#include <iostream>

using namespace std;

typedef struct cae_t{
    int value;
    int lock;
};

int test_and_set(int* mem);
int compare_and_exchange(cae_t * mem, int compare_value, int swap_value);

int main(int argc, char *argv[])
{
    cout << "TODO: test" << endl;
}

int test_and_set(int *mem){

}
