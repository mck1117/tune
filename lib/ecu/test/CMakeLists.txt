add_executable(ecu_tests)

target_sources(ecu_tests
    PRIVATE
        TestOutputChannel.cpp
)

target_link_libraries(ecu_tests ecu gtest gtest_main)
