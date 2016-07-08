cmake_minimum_required(VERSION 2.6)
project( LibOVR )

add_definitions(-DUNICODE -D_UNICODE -DMINGW_HAS_SECURE_API -DNOMINMAX)

include_directories( LibOVR/Include LibOVR/Src ${CMAKE_SOURCE_DIR} )

file(GLOB LIBOVR_FILES
    LibOVR/Include/*.h
    LibOVR/Include/Extras/*.h
    LibOVR/Src/*.cpp
    LibOVR/Src/*.c

    LibOVRKernel/*/*/*.cpp
    LibOVRKernel/*/*/*.c
    LibOVRKernel/*/*/*.h

    Logging/src/*.cpp
    Logging/src/internal/*.cpp
    Logging/src/include/*.h
)

file(GLOB includes LibOVRKernel/Src/*/)

include_directories(${includes} LibOVRKernel/Src)

if(CMAKE_COMPILER_IS_GNUCXX OR APPLE)
    set(CMAKE_CXX_FLAGS " -std=c++11 ${CMAKE_CXX_FLAGS} -fpermissive ")
endif()

add_definitions(-DOVR_BUILD_SHIPPING)

# add_definitions(-DOVR_DLL_BUILD) # shared only
add_library( LibOVR STATIC ${LIBOVR_FILES} )

if(WIN32)
    target_link_libraries(
        LibOVR winmm setupapi ws2_32 imagehlp wbemuuid opengl32 psapi
        advapi32 version ntdll shlwapi
    )
endif()

file(GLOB_RECURSE to-install RELATIVE ${CMAKE_SOURCE_DIR} LibOVR/*.h LibOVRKernel/*.h Logging/*.h)

foreach(file ${to-install})
    get_filename_component(dir "${file}" DIRECTORY)
    set(dir_ "${CMAKE_BINARY_DIR}/${dir}")
    file(MAKE_DIRECTORY "${dir_}")
    file(COPY ${file} DESTINATION "${dir_}")
endforeach()
