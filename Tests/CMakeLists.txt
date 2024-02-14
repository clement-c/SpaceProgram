include(FetchContent)
include(CTest)

enable_testing()

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(GoogleTest)

add_executable(test_maths test_maths.cpp)
target_link_libraries(test_maths GTest::gtest_main Engine)

gtest_discover_tests(test_maths)

include(GNUInstallDirs)
install(TARGETS test_maths RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
