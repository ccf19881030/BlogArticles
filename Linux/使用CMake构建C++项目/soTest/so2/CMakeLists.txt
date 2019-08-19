# ./so2/CMakeLists.txt

project(soTest)
set(so2 so2.c)
add_library(so2 SHARED ${so2})

# link
target_link_libraries(so2 so1)
