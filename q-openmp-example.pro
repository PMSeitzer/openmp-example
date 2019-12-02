TEMPLATE = app
TARGET = q-openmp-example
DESTDIR = $$PWD

QMAKE_CXX=/usr/local/opt/llvm/bin/clang++
QMAKE_LINK=/usr/local/opt/llvm/bin/clang++

QMAKE_CXXFLAGS += -fopenmp
	
QMAKE_LFLAGS += -fopenmp \
	-L/usr/local/opt/llvm/lib

SOURCES = \
   $$PWD/main.cpp

HEADERS=

INCLUDEPATH= /usr/local/Cellar/llvm/9.0.0_1/lib/clang/9.0.0/include/

LIBS+= -L/usr/local/opt/llvm/lib/

