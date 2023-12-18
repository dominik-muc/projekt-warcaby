add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_20)

target_link_libraries(main PRIVATE
    exLibrary
    ${CURSES_LIBRARIES}
    )

add_executable(test_main test_main.cpp)
target_compile_features(test_main PRIVATE cxx_std_20)

target_link_libraries(test_main PRIVATE
    exLibrary
    ${CURSES_LIBRARIES}
    )