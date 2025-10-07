# Get all the source files from source and add_executable
add_executable(funkin-wii
    source/main.cpp
    source/states/titlestate.cpp
    source/states/teststate.cpp
)

# Link with the engine
target_link_libraries(funkin-wii finengine)

if(FIN_PLATFORM STREQUAL "wii")
    # Include and lib paths for devkitPro
    target_include_directories(funkin-wii PRIVATE
        "$ENV{DEVKITPRO}/libogc/include"
        "$ENV{DEVKITPRO}/portlibs/ppc/include"
        "$ENV{DEVKITPRO}/portlibs/wii/include"
    )
    target_link_directories(funkin-wii PRIVATE
        "$ENV{DEVKITPRO}/libogc/lib/wii"
        "$ENV{DEVKITPRO}/portlibs/ppc/lib"
        "$ENV{DEVKITPRO}/portlibs/wii/lib"
    )

    # Assets (ROMFS)
    set(ROMFS_INPUT_DIR "${CMAKE_SOURCE_DIR}/assets")
    set(ROMFS_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    set(ROMFS_TAR "romfs.tar")
    set(ROMFS_OBJ "app.romfs.o")
    add_custom_command(
        OUTPUT "${ROMFS_BIN_DIR}/${ROMFS_OBJ}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${ROMFS_BIN_DIR}"
        COMMAND tar --format=ustar -cvf "${ROMFS_TAR}" -C "${ROMFS_INPUT_DIR}" .
        COMMAND "$ENV{DEVKITPPC}/bin/powerpc-eabi-ld" --relocatable --format binary --output "${ROMFS_OBJ}" "${ROMFS_TAR}"
        COMMAND ${CMAKE_COMMAND} -E rm -f "${ROMFS_TAR}"
        WORKING_DIRECTORY "${ROMFS_BIN_DIR}"
        COMMENT "Generating ${ROMFS_OBJ} from ${ROMFS_INPUT_DIR}"
        VERBATIM
    )
    add_custom_target(app_romfs DEPENDS "${ROMFS_BIN_DIR}/${ROMFS_OBJ}")
    add_dependencies(funkin-wii app_romfs)
    target_link_libraries(funkin-wii "${ROMFS_BIN_DIR}/${ROMFS_OBJ}")

    # Wii libraries
    target_link_libraries(funkin-wii
        romfs-ogc
        tinyxml2
        grrlib
        pngu
        freetype
        png
        z
        bz2
        jpeg
        fat
        wiiuse
        bte
        ogc
        m
    )

    # Produce DOL output
    ogc_create_dol(funkin-wii)
endif()