file(GLOB_RECURSE SOURCE_FILES "source/*.c" "source/*.cpp" "source/*.h" "source/*.hpp")
add_library(finengine STATIC ${SOURCE_FILES})
target_include_directories(finengine PUBLIC include source)

if(FIN_PLATFORM STREQUAL "wii")
	target_compile_definitions(finengine PUBLIC FINENGINE_OS_WII)
	target_include_directories(finengine PRIVATE
		"$ENV{DEVKITPRO}/libogc/include"
		"$ENV{DEVKITPRO}/portlibs/ppc/include"
		"$ENV{DEVKITPRO}/portlibs/wii/include"
	)
endif()