
add_executable(tests "tests.cpp")

target_include_directories(tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(tests 
    GTest::gtest_main
    GTest::gmock_main 
)

include(GoogleTest)
gtest_discover_tests(tests)

