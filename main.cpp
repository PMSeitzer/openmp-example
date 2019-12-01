#include <iostream>
#include <omp.h>
using namespace std;

int main(int argc, char *argv[])
{

    #pragma omp parallel for
    for (unsigned int i = 0; i < 10; i++) {

        #pragma omp critical
	cout << "Hello from thread #" << omp_get_thread_num() << " (nthreads=" << omp_get_num_threads() << ")"<< endl;

        //cout << "i=" << i << endl;
    }


//    QApplication a(argc, argv);
//    ExampleOpenMP w;
//    w.show();
//    return a.exec();
}
