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
    #"Src/CAPI/D3D1X/*.cpp"
    #"Src/CAPI/GL/*.cpp"
	"Src/Util/*.cpp"
)

set(CRAP-O-LA
    Src/OVR_Common_HMDDevice.cpp
    Src/OVR_Linux_HMDDevice.cpp
    Src/OVR_Linux_HIDDevice.cpp
    Src/OVR_Linux_DeviceManager.cpp
    Src/OVR_OSX_HMDDevice.cpp
)

file(GLOB LIBOVR_BLACKLIST ${CRAP-O-LA})
list(REMOVE_ITEM LIBOVR_FILES ${LIBOVR_BLACKLIST})

foreach(item ${LIBOVR_FILES})
    set(pat)
    if(APPLE)
        set(pat "Linux|Win32|WinAPI")
    endif()
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(pat "Win32|WinAPI|OSX")
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

add_library( LibOVR STATIC ${LIBOVR_FILES} )
if(WIN32)
    target_link_libraries(LibOVR winmm setupapi)
endif()

if( NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR) )
	set( LIBOVR_INC_DIR 
		"${CMAKE_CURRENT_SOURCE_DIR}/Include" 
		"${CMAKE_CURRENT_SOURCE_DIR}/Src"
		PARENT_SCOPE )
endif()
