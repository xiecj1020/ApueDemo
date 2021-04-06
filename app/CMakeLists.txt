# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# 指定输出的目录结构，这里我们指定到当前CMakeLists.txt同级目录的/src/main/assets/目录下，
# 根据abiFilter中指定的编译平台在细分子目录
#set(EXECUTABLE_OUTPUT_PATH      "${CMAKE_CURRENT_SOURCE_DIR}/src/main/assets/${ANDROID_ABI}")
set(EXECUTABLE_OUTPUT_PATH      "${CMAKE_CURRENT_SOURCE_DIR}/src/main/assets/")

# 指定编译的目标可执行程序名称与编译的文件，其中testcp是输出的可执行程序名称
add_executable(testcp src/main/cpp/cp/cp.c src/main/cpp/cp/setprogname.c src/main/cpp/cp/utils.c)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

add_library( # Specifies the name of the library.
             hellojni

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
        src/main/cpp/HelloJni.cpp)
add_library( # Specifies the name of the library.
        chapterOneJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterOneJni.cpp)

add_library( # Specifies the name of the library.
        chapterTwoJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterTwoJni.cpp)
add_library( # Specifies the name of the library.
        chapterThreeJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterThreeJni.cpp)
add_library( # Specifies the name of the library.
        chapterFourJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterFourJni.cpp)
add_library( # Specifies the name of the library.
        chapterFiveJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterFiveJni.cpp)

add_library( # Specifies the name of the library.
        chapterSixJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterSixJni.cpp)
add_library( # Specifies the name of the library.
        chapterSevenJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterSevenJni.cpp)

add_library( # Specifies the name of the library.
        chapterEightJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterEightJni.cpp)

add_library( # Specifies the name of the library.
        chapterNineJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterNineJni.cpp)

add_library( # Specifies the name of the library.
        chapterTenJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterTenJni.cpp)

add_library( # Specifies the name of the library.
        chapterElevenJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/ChapterEleven.cpp)

include_directories(src/main/cpp/include/)
find_library( # Defines the name of the path variable that stores the
              # location of the NDK library.
              log-lib

              # Specifies the name of the NDK library that
              # CMake needs to locate.
              log )
# Links your native library against one or more other native libraries.
target_link_libraries( # Specifies the target library.
                       hellojni
                       # Links the log library to the target library.
                       ${log-lib} )
target_link_libraries( # Specifies the target library.
                        chapterOneJni
                       # Links the log library to the target library.
                       ${log-lib} )
target_link_libraries( # Specifies the target library.
                        chapterTwoJni
                        # Links the log library to the target library.
                        ${log-lib} )
target_link_libraries( # Specifies the target library.
        chapterThreeJni
        # Links the log library to the target library.
        ${log-lib} )
target_link_libraries( # Specifies the target library.
        chapterFourJni
        # Links the log library to the target library.
        ${log-lib} )
target_link_libraries( # Specifies the target library.
        chapterFiveJni
        # Links the log library to the target library.
        ${log-lib} )
target_link_libraries( # Specifies the target library.
        chapterSixJni
        # Links the log library to the target library.
        ${log-lib} )
target_link_libraries( # Specifies the target library.
        chapterSevenJni
        # Links the log library to the target library.
        ${log-lib} )
target_link_libraries( # Specifies the target library.
        chapterEightJni
        # Links the log library to the target library.
        ${log-lib} )
target_link_libraries( # Specifies the target library.
        chapterNineJni
        # Links the log library to the target library.
        ${log-lib} )
target_link_libraries( # Specifies the target library.
        chapterTenJni
        # Links the log library to the target library.
        ${log-lib} )
target_link_libraries( # Specifies the target library.
        chapterElevenJni
        # Links the log library to the target library.
        ${log-lib} )