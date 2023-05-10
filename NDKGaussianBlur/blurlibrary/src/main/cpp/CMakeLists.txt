# 设置cmake支持最小版本
cmake_minimum_required(VERSION 3.4.1)

# 查找父目录3rd
message(STATUS "CMAKE_CURRENT_SOURCE_DIR::${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(JNI_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../.. ABSOLUTE)
message(STATUS "JNI_LIBS_DIR::${JNI_LIBS_DIR}")

# 设置动态库生成目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${JNI_LIBS_DIR}/jniLibs/${ANDROID_ABI})

#set(LOCAL_CFLAGS " -DANDROID_NDK -DDISABLE_IMPORTGL")

# 生成共享库
add_library(blurcore SHARED blurcore.cpp)

# 查找依赖库
find_library(log-lib log)
find_library(jnigraphics-lib jnigraphics)

# 连接库文件
target_link_libraries(blurcore ${log-lib} ${jnigraphics-lib})