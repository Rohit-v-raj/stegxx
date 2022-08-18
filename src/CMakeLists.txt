add_library(steg STATIC
    byte.cpp
    message.cpp
    PPM.cpp
    steg.cpp
)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE steg)
