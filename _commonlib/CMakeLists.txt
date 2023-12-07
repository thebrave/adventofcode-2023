add_library(adventlib adventlib.hpp adventlib.cpp stringlib.cpp)
target_include_directories(adventlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(adventlibtest stringlib_test.cpp)
target_link_libraries(adventlibtest PRIVATE adventlib Catch2::Catch2WithMain)

catch_discover_tests(adventlibtest)