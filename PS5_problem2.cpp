#include <iostream>

using namespace std;

struct cae_t {
    int value;
    bool isLocked = false;
    int numAttempts = 0;
};

int test_and_set(int* mem);
bool compare_and_exchange(cae_t * mem, int compare_value, int swap_value);

int main(int argc, char *argv[])
{
    cae_t mem;
    mem.value = 4;

    int compare_value = 4;
    int exchange_value = 7;

    compare_and_exchange(&(mem), compare_value, exchange_value);

    //break the lock
    mem.isLocked = false;

    compare_and_exchange(&(mem), compare_value, exchange_value);

    compare_and_exchange(&(mem), compare_value, exchange_value);
}

bool test_and_set(cae_t *mem){

    if (mem->isLocked) {

        //force break the lock after 100 attempts
        mem->numAttempts++;
        if (mem->numAttempts >= 100) {
            mem->isLocked = false;
            cout << "Breaking lock after 100 access attempts." << endl;
        }
    }

    return mem->isLocked;
}

bool compare_and_exchange(cae_t * mem, int compare_value, int swap_value){

    cout << "-----------------------" << endl;
    cout << "Starting compare_and_exchange()" << endl;

    cout << "Comparing cae_t @ " << &(mem) << ": val=" << mem->value << " to " << compare_value << endl;

    bool isSwapped = false;

    // acquire lock (spin until the lock is released)
    while(test_and_set(mem)){}

    if (compare_value == mem->value){
        mem->value = swap_value;
        isSwapped = true;
    }

    //release lock (set to true)
    mem->isLocked = true;

    cout << "result for " << "cae_t @ " << &(mem) << ": " << (isSwapped > 0 ? "swapped" : "not swapped") << endl;
    cout << "new value for " << "cae_t @ " << &(mem) << ": " << mem->value << endl;

    cout << "Finished compare_and_exchange()" << endl;
    cout << "-----------------------" << endl;
    return isSwapped;
}
