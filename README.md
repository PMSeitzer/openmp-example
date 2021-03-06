# Introduction

This project serves as a basic template for developing multithreaded c++ code using
the OpenMP library, as well as some notes from the `thinkos.pdf` textbook.

A copy of the `thinkos.pdf` is included in this repository.

The various building option refer to the compiler options described in `thinkos.pdf` textbook, chapter 1.

# Building and Executing

The code can be built into an executable using a variety of ways.

All ways require the `clang++` compiler included with `llvm 9.0`: [llvm releases webpage](http://releases.llvm.org/download.html)

## Plain
Using the `clang++` compiler included with `llvm 9.0`.

1.  Create executable
```
clang++ main.cpp -o openmp-example -fopenmp -L/usr/local/opt/llvm/lib
./openmp-example
```

2.  Add optimization flag 
```
clang++ -O main.cpp -o openmp-example-O -fopenmp -L/usr/local/opt/llvm/lib
clang++ -O1 main.cpp -o openmp-example-O1 -fopenmp -L/usr/local/opt/llvm/lib
clang++ -O2 main.cpp -o openmp-example-O2 -fopenmp -L/usr/local/opt/llvm/lib
clang++ -O3 main.cpp -o openmp-example-O3 -fopenmp -L/usr/local/opt/llvm/lib
```

3.  Generate object code
```
clang++ main.cpp -c
```

4.  Generate assembly code
```
clang++ main.cpp -S
```

5.  Execute preprocessor only
```
clang++ main.cpp -E > main.E
```

## cmake project

Requires that cmake be installed:
[cmake download page](https://cmake.org/download/)

then, simply
```
cmake CMakeLists.txt
make -Bj16
```

If you plan on using standard library functions, Qt Creator sometimes
gets confused about which c++ lib to use. Specify this as an include flag:

```
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/opt/llvm/include/c++/v1/")
```

## qmake project
Requires that qt be installed using `homebrew` like so:
```
brew install qt5
```
or
```
brew upgrade qt5
```
Followed by
```
brew link qt5 --force
```
After that, in a command line run:
```
qmake q-openmp-example.pro
make -Bj16
q-openmp-example.app/Contents/MacOS/q-openmp-example
```

In `Qt Creator`, Need to open the `q-openmp-example.pro` file, with a kit that uses the `clang++`
compiler.

## Telling cmake about qt5

`cmake` worked smoothly here in Qt Creator, b/c no `QT` libraries were actually used.

However, Qt Creator can have a hard time finding installed `QT` libraries:
[homebrew configuration issue](https://github.com/Homebrew/homebrew-core/issues/8392)

This can be solved by creating some symbolic links in `/usr/local/`:

```
sudo ln -s /usr/local/Cellar/qt/5.13.2/mkspecs /usr/local/mkspecs
sudo ln -s /usr/local/Cellar/qt/5.13.2/plugins/ /usr/local/plugins
```

`QT` libraries could have been incorporated in the `CMakeLists.txt` file using this syntax:


```
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
```

# thinkos.pdf textbook notes

Notes from the textbook.

**Memory Segments**
```
(low number memory addresses)
C --> "Code" or "Text", actual program stored in memory
C --> "Constant": string literals
G --> "Global": global variables, declared with "static" keyword
H --> "Heap" dynamic memory allocation. Grows up towards stack
S --> "Stack" auto allocation/deallocation
(high number memory addresses)
```

**Other Definitions**
```
MMU = memory managament unit
TLB = translation lookaside buffer (for page number, page is chunk of memory)

given VA (virtual address), determine page # + offset --> produce PA (physical address)

MCU --> main memory

"inode" --> index node

os thinks of long-term memory as "blocks"
```

**floating point numbers**
```
(−1)^s * c * 2^q
```
