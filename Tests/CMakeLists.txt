include(FetchContent)
include(CTest)

set(DOWNLOAD_EXTRACT_TIMESTAMP ON)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 6910c9d9165801d8827d628cb72eb7ea9dd538c5
    )
    FetchContent_MakeAvailable(googletest)
    
enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(GoogleTest)

add_executable(test_maths test_maths.cpp)
target_link_libraries(test_maths PUBLIC Engine PRIVATE gtest gtest_main)

add_executable(test_resource_manager test_resource_manager.cpp)
target_link_libraries(test_resource_manager PUBLIC Engine PRIVATE gtest gtest_main)

# FIXME: Not working as apparently not linking correctly to Engine.dll?
# gtest_discover_tests(test_maths)
# gtest_discover_tests(test_resource_manager)

# include(GNUInstallDirs)
install(TARGETS test_maths test_resource_manager RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
