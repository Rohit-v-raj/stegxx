find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(run_tests 
    test_coding.cpp
    main.cpp
    test_types.cpp
)
target_link_libraries(run_tests 
    PRIVATE steg
    PUBLIC gtest pthread
)
