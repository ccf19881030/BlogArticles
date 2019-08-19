# ./so1/CMakeLists.txt
# project name: soTest
project(soTest)

# set source files
set(so1 so1.c)

# set make to a shared library
add_library(so1 SHARED ${so1})
