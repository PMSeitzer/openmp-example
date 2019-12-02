TEMPLATE = app
TARGET = q-openmp-example
DESTDIR= .

# clang++ --> /usr/local/opt/llvm/bin/clang++
QMAKE_CXX = clang++
QMAKE_LINK = clang++

QMAKE_CXXFLAGS += -DOMP_PARALLEL -fopenmp

LIBS+=-fopenmp -L/usr/local/opt/llvm/lib

SOURCES=main.cpp
HEADERS=