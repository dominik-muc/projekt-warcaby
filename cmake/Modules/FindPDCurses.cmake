message("--------------------------------------find pdcurses-----------------------------")
message("---$ENV{PDCURSESDIR}")

find_path(PDCURSES_INCLUDE_DIR curses.h
    HINTS
    $ENV{PDCURSESDIR} "${PROJECT_SOURCE_DIR}/include/PDCurses"
    PATH_SUFFIXES include/pdcurses include)


find_library(PDCURSES_LIBRARY
    names libpdcurses
    HINTS
    paths "${PROJECT_SOURCE_DIR}/include/PDCurses" $ENV{PDCURSESDIR}
    PATH_SUFFIXES wincon lib64 lib)

find_library(PDCURSES_PANEL_LIBRARY
    names panel
    HINTS
    $ENV{PDCURSESDIR}
    PATH_SUFFIXES lib64 lib)

if(PDCURSES_LIBRARY)
    set(PDCURSES_LIBRARIES ${PDCURSES_LIBRARY})
    if(PDCURSES_PANEL_LIBRARY)
        set(PDCURSES_LIBRARIES ${PDCURSES_LIBRARIES} ${PDCURSES_PANEL_LIBRARY})
    endif(PDCURSES_PANEL_LIBRARY)
endif(PDCURSES_LIBRARY)

set(PDCURSES_FOUND "NO")
if(PDCURSES_INCLUDE_DIR AND PDCURSES_LIBRARY)
    set(PDCURSES_LIBRARIES ${PDCURSES_LIBRARY} CACHE STRING "Where the PDCurses Library can be found")

    set(PDCURSES_FOUND "YES")
endif(PDCURSES_INCLUDE_DIR AND PDCURSES_LIBRARY)