# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("cppdraw")

message("CMAKE_ANDROID_NDK=${CMAKE_ANDROID_NDK}")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        main.cpp
        BuildOutput.cpp
        Guide.cpp
        InputQuery.cpp
        MainActivity.cpp
        MessageBox.cpp
        OpenFileActivity.cpp
        ProgramActivity.cpp
        #
        imgui_markdown/imgui_markdown.h
        #imgui_md/imgui_md.cpp
        #
        ImGuiColorTextEdit/TextEditor.cpp
        # 
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_android.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/misc/cpp/imgui_stdlib.cpp
        #
        ${CMAKE_ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        android
        log
        EGL
        GLESv3)

target_include_directories(${CMAKE_PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../assets/usr/include
        ${CMAKE_ANDROID_NDK}/sources/android/native_app_glue
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui
        C:/work/imrad/src
        )
