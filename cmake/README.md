# cmake

## Configuration files for cmake build environment

env.cmake
Environment variables

doxygen.cmake
Template for running doxygen - not yet usable

find_package.cmake
Overall find package to use these variables in other cmake files

## Add environment variables

Open env.cmake and create a new include directory:
set(SOURCES_MYSHAREDINCLUDE ${SOURCES_SHARED}/MySharedInclude)
