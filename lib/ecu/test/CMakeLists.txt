add_executable(ecu_tests)

# Allow the tests to reach inside the implementation
target_include_directories(ecu_tests
    PRIVATE
        ../src
)

target_sources(ecu_tests
    PRIVATE
        TestOutputChannel.cpp
)

target_link_libraries(ecu_tests ecu gtest gtest_main)
