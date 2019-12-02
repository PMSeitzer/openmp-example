# Necessary fields to create the q-openmp-example executable.
TEMPLATE = app
TARGET = q-openmp-example
DESTDIR = $$PWD

# Need to specify the appropriate compiler and linker with openMP to build multithreaded applications.
QMAKE_CXX=/usr/local/opt/llvm/bin/clang++
QMAKE_LINK=/usr/local/opt/llvm/bin/clang++

# Special openMP compiler/linker flag is necessary to build multithreaded applications
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp 

# Sources and Header for project
SOURCES = \
   $$PWD/main.cpp
HEADERS=

# Note that this is easier for Qt Creator than /usr/local/llvm/lib/include
# It is also possible to use
# QMAKE_CXXFLAGS -I (includes)
# QMAKE_LFFLAGS -L (libs)
INCLUDEPATH= /usr/local/Cellar/llvm/9.0.0_1/lib/clang/9.0.0/include/
LIBS+= -L/usr/local/opt/llvm/lib/

