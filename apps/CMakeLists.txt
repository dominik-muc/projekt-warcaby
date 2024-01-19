# MAIN
add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_20)

target_link_libraries(main PRIVATE
    exLibrary
    )

# ASCII MAIN
add_executable(ascii_main ascii_main.cpp)
target_compile_features(ascii_main PRIVATE cxx_std_20)

if(PDCURSES_FOUND)
   target_compile_definitions(ascii_main PRIVATE -DPDC_DLL_BUILD -DPDC_WIDE)
endif()  
target_link_libraries(ascii_main PRIVATE
    exLibrary
    ${CURSES_LIBRARIES}
    )

# TEXT MAIN
add_executable(text_main text_main.cpp)
target_compile_features(text_main PRIVATE cxx_std_20)
if(PDCURSES_FOUND)
    target_compile_definitions(text_main PRIVATE -DPDC_DLL_BUILD -DPDC_WIDE)
endif()  
target_link_libraries(text_main PRIVATE
    exLibrary
    ${CURSES_LIBRARIES}
    )