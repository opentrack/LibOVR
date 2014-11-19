cmake_minimum_required(VERSION 2.6)
project( LibOVR )

add_definitions(-DUNICODE -D_UNICODE -DMINGW_HAS_SECURE_API)
set( LIBOVR_INC_DIR 
	"${CMAKE_CURRENT_SOURCE_DIR}/Src"
	"${CMAKE_CURRENT_SOURCE_DIR}/Include" )

include_directories( Include Src )

file( GLOB INTERFACE_HEADERS Include/*.h )

file( GLOB LIBOVR_FILES
	"Src/Kernel/*.cpp"
	"Src/*.cpp"
	"Src/CAPI/*.cpp"
	"Src/Util/*.cpp"
	"Src/Displays/*.cpp"
	"Src/Service/*.cpp"
	"Src/Net/*.cpp"
	"Src/Sensors/*.cpp"
	"Src/Tracking/*.cpp"
)

add_library( LibOVR STATIC ${LIBOVR_FILES} )
if(WIN32)
    target_link_libraries(LibOVR winmm setupapi ws2_32 imagehlp wbemuuid)
endif()

if( NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR) )
	set( LIBOVR_INC_DIR 
		"${CMAKE_CURRENT_SOURCE_DIR}/Include" 
		"${CMAKE_CURRENT_SOURCE_DIR}/Src"
		PARENT_SCOPE )
endif()
