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

# 1.
# Qt Creator shows compilation errors for
# INCLUDEPATH=/usr/local/opt/llvm/include/
# However, the command line qmake works with either INCLUDEPATH expression,
# b/c /usr/local/opt/llvm/include --> usr/local/Cellar/llvm/9.0.0_1/lib/clang/9.0.0/include/
#
# An alternative solution to use the more general /usr/local/opt/llvm/include
# would be to tell Qt Creator that these paths are the same.
#
# 2.
# It is also possible to use
# QMAKE_CXXFLAGS -I (includes)
# QMAKE_LFFLAGS -L (libs)
# Instead of setting the value of $$INCLUDEPATH and $$LIBS variables.
INCLUDEPATH=/usr/local/Cellar/llvm/15.0.7_1/lib/clang/15.0.7/include
LIBS+= -L/usr/local/opt/llvm/lib/

