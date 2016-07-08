cmake_minimum_required(VERSION 2.6)
project( LibOVR )

if(APPLE)
    file( GLOB PLATFORM_FILES
        "Src/Kernel/OVR_ThreadsPthread.*"
        "Src/OVR_OSX_*.*" )
elseif(WIN32)
    file( GLOB PLATFORM_FILES
        "Src/Kernel/OVR_ThreadsWinAPI.*"
        "Src/OVR_Win32_*.*" )
else()
    # Linux
    add_definitions(-fPIC)
    file( GLOB PLATFORM_FILES 
        "Src/Kernel/OVR_ThreadsPthread.*"
        "Src/OVR_Linux_*.*" )
endif()

add_definitions(-DUNICODE -D_UNICODE)
set(LIBOVR_INC_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/Src"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
)

file(GLOB_RECURSE to-install RELATIVE ${CMAKE_SOURCE_DIR} Src/*.h Include/*.h)

foreach(file ${to-install})
    get_filename_component(dir "${file}" DIRECTORY)
    set(dir_ "${CMAKE_BINARY_DIR}/${dir}")
    file(MAKE_DIRECTORY "${dir_}")
    file(COPY ${file} DESTINATION "${dir_}")
endforeach()

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Werror=strict-aliasing -fno-strict-aliasing)
    add_definitions(-std=c++11 -Wno-write-strings)
endif()

include_directories(${CMAKE_BINARY_DIR})

file(GLOB LIBOVR_FILES
    "Src/Kernel/OVR_Alg.*"
    "Src/Kernel/OVR_Allocator.*"
    "Src/Kernel/OVR_Array.*"
    "Src/Kernel/OVR_Atomic.*"
    "Src/Kernel/OVR_Color.*"
    "Src/Kernel/OVR_ContainerAllocator.*"
    "Src/Kernel/OVR_File.*"
    "Src/Kernel/OVR_FileFILE.*"
    "Src/Kernel/OVR_Hash.*"
    "Src/Kernel/OVR_KeyCodes.*"
    "Src/Kernel/OVR_List.*"
    "Src/Kernel/OVR_Log.*"
    "Src/Kernel/OVR_Math.*"
    "Src/Kernel/OVR_RefCount.*"
    "Src/Kernel/OVR_Std.*"
    "Src/Kernel/OVR_String.*"
    "Src/Kernel/OVR_String_FormatUtil.*"
    "Src/Kernel/OVR_String_PathUtil.*"
    "Src/Kernel/OVR_StringHash.*"
    "Src/Kernel/OVR_SysFile.*"
    "Src/Kernel/OVR_System.*"
    "Src/Kernel/OVR_Threads.*"
    "Src/Kernel/OVR_Timer.*"
    "Src/Kernel/OVR_Types.*"
    "Src/Kernel/OVR_UTF8Util.*"
    "Src/OVR_Device.*"
    "Src/OVR_DeviceConstants.*"
    "Src/OVR_DeviceHandle.*"
    "Src/OVR_DeviceImpl.*"
    "Src/OVR_DeviceMessages.*"
    "Src/OVR_HIDDevice.*"
    "Src/OVR_HIDDeviceBase.*"
    "Src/OVR_HIDDeviceImpl.*"
    "Src/OVR_LatencyTestImpl.*"
    "Src/OVR_SensorFilter.*"
    "Src/OVR_SensorFusion.*"
    "Src/OVR_SensorImpl.*"
    "Src/OVR_ThreadCommandQueue.*"
    "Src/OVR_JSON.*"
    "Src/OVR_Profile.*"
    "Src/Util/Util_LatencyTest.*"
    "Src/Util/Util_Render_Stereo.*"
 )

add_library(LibOVR STATIC ${LIBOVR_FILES} ${PLATFORM_FILES})
