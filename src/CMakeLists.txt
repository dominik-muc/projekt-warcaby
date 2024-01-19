# Collect all headers
file(GLOB_RECURSE 
	HEADER_LIST 
	CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/include/Warcaby/*.hpp"
	"${PROJECT_SOURCE_DIR}/include/Warcaby/*.h")

# Collect implementations
file(GLOB_RECURSE 
	SRC_LIST 
	CONFIGURE_DEPENDS 
	"${PROJECT_SOURCE_DIR}/src/*.cpp")


add_library(exLibrary ${SRC_LIST} ${HEADER_LIST})
target_include_directories(exLibrary PUBLIC ../include)
if(PDCURSES_FOUND)
	message("--dll--")
    target_compile_definitions(exLibrary PRIVATE -DPDC_DLL_BUILD)
endif()  

target_include_directories(exLibrary PRIVATE
	${CURSES_LIBRARIES})

target_compile_features(exLibrary PUBLIC cxx_std_20)