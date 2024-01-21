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

# BOT MAIN
add_executable(bot_main bot_main.cpp)
target_compile_features(bot_main PUBLIC cxx_std_14)

# Set compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(bot_main PUBLIC -Wall -Wextra -pedantic)
elseif(MSVC)
    target_compile_options(bot_main PUBLIC /W4)
endif()

target_link_libraries(bot_main PUBLIC
    exLibrary
    ${CURSES_LIBRARIES}
    )

# BOT MAIN WITH TEXT RENDERER
add_executable(bot_text bot_main_with_text_renderer.cpp)
target_compile_features(bot_text PUBLIC cxx_std_14)

# Set compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(bot_text PUBLIC -Wall -Wextra -pedantic)
elseif(MSVC)
    target_compile_options(bot_text PUBLIC /W4)
endif()

target_link_libraries(bot_text PUBLIC
    exLibrary
    ${CURSES_LIBRARIES}
    )