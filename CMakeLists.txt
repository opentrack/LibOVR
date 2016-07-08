cmake_minimum_required(VERSION 2.6)
project( LibOVR )

add_definitions(-DUNICODE -D_UNICODE -DMINGW_HAS_SECURE_API)

file(GLOB_RECURSE to-install RELATIVE ${CMAKE_SOURCE_DIR} Src/*.h Include/*.h)

foreach(file ${to-install})
    get_filename_component(dir "${file}" DIRECTORY)
    set(dir_ "${CMAKE_BINARY_DIR}/${dir}")
    file(MAKE_DIRECTORY "${dir_}")
    file(COPY ${file} DESTINATION "${dir_}")
endforeach()

include_directories( Include Src )

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

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS " -std=c++11 ${CMAKE_CXX_FLAGS} ")
endif()
