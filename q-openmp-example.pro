TEMPLATE = app
TARGET = q-openmp-example
DESTDIR = $$PWD

QMAKE_CXX=/usr/local/opt/llvm/bin/clang++
QMAKE_LINK=/usr/local/opt/llvm/bin/clang++

QMAKE_CXXFLAGS += -fopenmp
	
QMAKE_LFLAGS += -fopenmp \
	-I/usr/local/opt/llvm/include/ \
	-I/usr/local/Cellar/llvm/9.0.0_1/lib/clang/9.0.0/include/ \
	-L/usr/local/opt/llvm/lib

SOURCES = \
   $$PWD/main.cpp

HEADERS=

INCLUDEPATH=/usr/local/opt/llvm/include/ \
	/usr/local/Cellar/llvm/9.0.0_1/lib/clang/9.0.0/include/ \
	/usr/local/Cellar/llvm/9.0.0_1/include/c++/v1/

LIBS+= -L/usr/local/opt/llvm/lib/

