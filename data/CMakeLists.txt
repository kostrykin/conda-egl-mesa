cmake_minimum_required( VERSION 3.5 )
project( test )
include( FindPackageHandleStandardArgs )

find_package( OpenGL REQUIRED COMPONENTS EGL )
include_directories( ${OPENGL_EGL_INCLUDE_DIRS} )

add_executable(
    test
    test.cpp
)

target_link_libraries(
    test
    ${OPENGL_LIBRARIES}
    OpenGL::EGL
)
