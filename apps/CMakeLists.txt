# MAIN
add_executable(main main.cpp)
target_compile_features(main PUBLIC cxx_std_14)

# Set compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(main PUBLIC -Wall -Wextra -pedantic)
elseif(MSVC)
    target_compile_options(main PUBLIC /W4)
endif()

target_link_libraries(main PUBLIC
    exLibrary
    ${CURSES_LIBRARIES}
    )

