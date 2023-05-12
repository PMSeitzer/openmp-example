#include <iostream>
#include <omp.h>
#define N 10000
#define CHUNKSIZE 100

using namespace std;

int main(int argc, char *argv[])
{
    omp_set_num_threads(137);
    #pragma omp parallel for
    for (unsigned int i = 0; i < 10; i++) {

        #pragma omp critical
        cout << "Hello from thread #" << omp_get_thread_num() << " (nthreads=" << omp_get_num_threads() << ")"<< endl;
    }

    // example from https://wvuhpc.github.io/2018-Lesson_4/03-openmp/index.html
    double a[N], b[N], c[N], d[N];

    for (unsigned int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * N;
    }
    unsigned int chunk = CHUNKSIZE;

    //for loop pattern

//    #pragma omp parallel for schedule(dynamic,chunk)
//    for (unsigned int i = 0; i < N; i++) {

//        #pragma omp critical
//        c[i] = a[i] + b[i];
//    }

//sections pattern

#pragma omp parallel
{

    #pragma omp sections nowait
    {
        #pragma omp section
        {
            printf("Thread: %d working on + section\n", omp_get_thread_num());
            for (unsigned int i = 0; i < N; i++) {

                #pragma omp critical
                c[i] = a[i] + b[i];
            }
        }

        #pragma omp section
        {
            printf("Thread: %d working on * section\n", omp_get_thread_num());
            for(unsigned int i = 0; i < N; i++) {

                #pragma omp critical
                d[i] = a[i] * b[i];
            }
        }
    }

}
    cout << "Block 1:" << endl;
    for (unsigned int i = 0; i < 10; i++){
        printf("%17.1f %17.1f %17.1f\n", a[i], b[i], c[i]);
    }
    cout << endl;

    cout << "Block 2:" << endl;
    for (int i = N-10; i < N; i++){
        printf("%17.1f %17.1f %17.1f\n", a[i], b[i], c[i]);
    }
    cout << endl;

}


