cmake_minimum_required(VERSION 3.0.0)
project(cppTool VERSION 0.1.0)

# include(CTest)
# enable_testing()

# add_executable(cppTool main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)



#设置exe 输出路径
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

#查找当前目录下所有文件 并将名称保存到DIR_SOURCE 变量
aux_source_directory(. DIR_SRCS)

#指定生成目标
add_executable(Demo ${DIR_SRCS})