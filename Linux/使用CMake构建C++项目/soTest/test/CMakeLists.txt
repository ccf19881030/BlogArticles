# ./test/CMakeLists.txt
project(soTest)
set(st test.c)

# 生成可执行文件
add_executable(st test.c)
target_link_libraries(st so2 so1)
