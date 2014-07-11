cmake_minimum_required(VERSION 2.6)
project( LibOVR )

add_definitions(-DUNICODE -D_UNICODE)
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
)

foreach(item ${LIBOVR_FILES})
    set(pat)
    if(NOT APPLE)
        set(pat "OSX")
    endif()
    if(NOT WIN32)
        set(pat "WinAPI|Win32")
    endif()
    if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(pat "Linux")
    endif()
    if(WIN32)
        set(pat "OSX|Linux|Pthread")
    endif()
    if(pat)
        string(REGEX MATCH ${pat} res ${item})
    endif()
    if(res)
        list(REMOVE_ITEM LIBOVR_FILES ${item})
    endif()
endforeach()

source_group( include FILES ${INTERFACE_HEADERS} )
source_group( src FILES ${LIBOVR_FILES} )
source_group( platform FILES ${PLATFORM_FILES} )

add_library( LibOVR STATIC ${LIBOVR_FILES} )

if( NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR) )
	set( LIBOVR_INC_DIR 
		"${CMAKE_CURRENT_SOURCE_DIR}/Include" 
		"${CMAKE_CURRENT_SOURCE_DIR}/Src"
		PARENT_SCOPE )
endif()
