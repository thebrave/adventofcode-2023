add_library(adventlib adventlib.hpp adventlib.cpp stringlib.cpp)
target_include_directories(adventlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})