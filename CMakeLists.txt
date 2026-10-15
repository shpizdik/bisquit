cmake_minimum_required(VERSION 3.5.2)
project(BisquitExec)

add_executable(BisquitExec main.cpp)

#third party libs
add_subdirectory(third_party/glad)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glm)

#first party libs
add_subdirectory(bisqHelloTriangle)

target_link_libraries(BisquitExec PRIVATE glad glfw glm hello_triangle)


if(APPLE)
    target_link_libraries(BisquitExec PRIVATE
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
    )
elseif(WIN32)
    target_link_libraries(BisquitExec PRIVATE opengl32 gdi32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(BisquitExec PRIVATE OpenGL::GL dl pthread)
endif()