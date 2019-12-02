# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

TEMPLATE = app
TARGET = q-openmp-example
DESTDIR = $$PWD

QMAKE_CXX=/usr/local/opt/llvm/bin/clang++
QMAKE_LINK=/usr/local/opt/llvm/bin/clang++
QMAKE_CXXFLAGS += -DOMP_PARALLEL -fopenmp -I/usr/local/opt/llvm/include/ -I/usr/local/Cellar/llvm/9.0.0_1/include/c++/v1/ -I/usr/local/Cellar/llvm/9.0.0_1/lib/clang/9.0.0/include/ -L/usr/local/opt/llvm/lib
QMAKE_LFLAGS += -DOMP_PARALLEL -fopenmp -I/usr/local/opt/llvm/include/ -I/usr/local/Cellar/llvm/9.0.0_1/include/c++/v1/ -I/usr/local/Cellar/llvm/9.0.0_1/lib/clang/9.0.0/include/ -L/usr/local/opt/llvm/lib

SOURCES = \
   $$PWD/main.cpp

HEADERS=

# LDFLAGS+= -Wl,-rpath,/usr/local/opt/llvm/lib

INCLUDEPATH=/usr/local/opt/llvm/include/ \
	/usr/local/Cellar/llvm/9.0.0_1/lib/clang/9.0.0/include/ \
	/usr/local/Cellar/llvm/9.0.0_1/include/c++/v1/

LIBS+= -L/usr/local/opt/llvm/lib/

