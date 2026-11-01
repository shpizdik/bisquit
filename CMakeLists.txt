cmake_minimum_required(VERSION 3.16)
project(BisquitExec)

add_executable(BisquitExec main.cpp)

#third party libs
add_subdirectory(glad)
add_subdirectory(glfw)

#first party libs will be here
#LIBS

#library linking
target_link_libraries(BisquitExec PRIVATE 
    glad 
    glfw
)


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