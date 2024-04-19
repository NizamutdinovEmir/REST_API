add_executable(cpr_example_executable main.cpp)

target_link_libraries(cpr_example_executable PRIVATE binary)
target_include_directories(cpr_example_executable PUBLIC ${PROJECT_SOURCE_DIR})
