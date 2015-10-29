cmake_minimum_required(VERSION 2.6)
project( LibOVR )

add_definitions(-DUNICODE -D_UNICODE -DMINGW_HAS_SECURE_API)
set( LIBOVR_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Src" "${CMAKE_CURRENT_SOURCE_DIR}/Include" )

include_directories( Include Src ${CMAKE_SOURCE_DIR} )

file( GLOB INTERFACE_HEADERS Include/*.h )

file( GLOB LIBOVR_FILES
./Src/GL/CAPI_GLE.cpp
./Src/Kernel/OVR_Alg.cpp
./Src/Kernel/OVR_Allocator.cpp
./Src/Kernel/OVR_Atomic.cpp
./Src/Kernel/OVR_Callbacks.cpp
./Src/Kernel/OVR_CRC32.cpp
./Src/Kernel/OVR_DebugHelp.cpp
./Src/Kernel/OVR_File.cpp
./Src/Kernel/OVR_FileFILE.cpp
./Src/Kernel/OVR_JSON.cpp
./Src/Kernel/OVR_Lockless.cpp
./Src/Kernel/OVR_Log.cpp
./Src/Kernel/OVR_mach_exc_OSX.c
./Src/Kernel/OVR_Rand.cpp
./Src/Kernel/OVR_RefCount.cpp
./Src/Kernel/OVR_SharedMemory.cpp
./Src/Kernel/OVR_Std.cpp
./Src/Kernel/OVR_String.cpp
./Src/Kernel/OVR_String_FormatUtil.cpp
./Src/Kernel/OVR_String_PathUtil.cpp
./Src/Kernel/OVR_SysFile.cpp
./Src/Kernel/OVR_System.cpp
./Src/Kernel/OVR_ThreadCommandQueue.cpp
./Src/Kernel/OVR_ThreadsPthread.cpp
./Src/Kernel/OVR_ThreadsWinAPI.cpp
./Src/Kernel/OVR_Timer.cpp
./Src/Kernel/OVR_UTF8Util.cpp
./Src/OVR_CAPIShim.c
./Src/OVR_CAPI_Util.cpp
./Src/OVR_StereoProjection.cpp
./Src/Util/Util_D3D11_Blitter.cpp
./Src/Util/Util_Direct3D.cpp
./Src/Util/Util_GetSystemSpecs.cpp
./Src/Util/Util_GL_Blitter.cpp
./Src/Util/Util_ImageWindow.cpp
./Src/Util/Util_LongPollThread.cpp
./Src/Util/Util_SystemGUI.cpp
./Src/Util/Util_SystemInfo.cpp
./Src/Util/Util_Watchdog.cpp
)

if(CMAKE_COMPILER_IS_GNUCXX OR APPLE)
    set(CMAKE_CXX_FLAGS " -std=c++11 ${CMAKE_CXX_FLAGS} -fpermissive ")
endif()

add_library( LibOVR STATIC ${LIBOVR_FILES} )

if(WIN32)
    target_link_libraries(
        LibOVR winmm setupapi ws2_32 imagehlp wbemuuid opengl32 psapi
        advapi32 version ntdll shlwapi
    )
endif()

if(NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
        set(LIBOVR_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include" "${CMAKE_CURRENT_SOURCE_DIR}/Src" PARENT_SCOPE)
endif()
