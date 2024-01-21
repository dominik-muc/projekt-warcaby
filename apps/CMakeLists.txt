# MAIN
add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_20)
if(PDCURSES_FOUND)
    target_compile_definitions(main PRIVATE -DPDC_DLL_BUILD -DPDC_WIDE)
endif()  
target_link_libraries(main PRIVATE
    exLibrary
    ${CURSES_LIBRARIES}
    )