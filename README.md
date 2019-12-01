# This project serves as a basic template for developing multithreaded c++ code using
the OpenMP library.

Creating multithreaded code references the `thinkos.pdf` textbook, chapter 1.

#To build and execute:

## Plain Project
Exploring different options available in the clang++ compiler
(defers to gcc compiler)

# Create executable
clang++ main.cpp -o openmp-example -fopenmp -L/usr/local/opt/llvm/lib
./openmp-example

# Add optimization flag 
clang++ -O main.cpp -o openmp-example-O -fopenmp -L/usr/local/opt/llvm/lib
clang++ -O1 main.cpp -o openmp-example-O1 -fopenmp -L/usr/local/opt/llvm/lib
clang++ -O2 main.cpp -o openmp-example-O2 -fopenmp -L/usr/local/opt/llvm/lib
clang++ -O3 main.cpp -o openmp-example-O3 -fopenmp -L/usr/local/opt/llvm/lib

# generate object code
clang++ main.cpp -c

# generate assembly code
clang++ main.cpp -S

# execute preprocessor only
clang++ main.cpp -E > main.E

# cmake project
TODO

# qmake project
TODO

## Memory Segments
(low number memory addresses)
C --> "Code" or "Text", actual program stored in memory
C --> "Constant": string literals
G --> "Global": global variables, declared with "static" keyword
H --> "Heap" dynamic memory allocation. Grows up towards stack
S --> "Stack" auto allocation/deallocation
(high number memory addresses)

MMU = memory managament unit
TLB = translation lookaside buffer (for page number, page is chunk of memory)

given VA (virtual address), determine page # + offset --> produce PA (physical address)

MCU --> main memory

"inode" --> index node

os think of long-term memory as "blocks"

floating point numbers:
(−1)^s * c * 2^q
