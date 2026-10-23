if(NOT DEFINED SOURCE_DIR OR NOT DEFINED DEST_DIR)
    message(FATAL_ERROR
        "SOURCE_DIR and DEST_DIR must be specified"
    )
endif()

if(NOT IS_DIRECTORY "${SOURCE_DIR}")
    message(FATAL_ERROR
        "Source directory does not exist: ${SOURCE_DIR}"
    )
endif()

get_filename_component(
    SOURCE_DIR "${SOURCE_DIR}" ABSOLUTE
)

get_filename_component(
    DEST_DIR "${DEST_DIR}" ABSOLUTE
)

if(SOURCE_DIR STREQUAL DEST_DIR)
    message(FATAL_ERROR
        "Source and destination directories must differ"
    )
endif()

file(MAKE_DIRECTORY "${DEST_DIR}")

file(GLOB_RECURSE source_files
    LIST_DIRECTORIES FALSE
    RELATIVE "${SOURCE_DIR}"
    "${SOURCE_DIR}/*"
)

set(expected_files "")

foreach(relative_file IN LISTS source_files)

    list(APPEND expected_files "${relative_file}")

    set(source_file "${SOURCE_DIR}/${relative_file}")
    set(dest_file "${DEST_DIR}/${relative_file}")

    get_filename_component(
        dest_parent "${dest_file}" DIRECTORY
    )

    file(MAKE_DIRECTORY "${dest_parent}")

    file(COPY_FILE
        "${source_file}"
        "${dest_file}"
        ONLY_IF_DIFFERENT
    )

    message(STATUS
            "Added asset: ${relative_file}"
        )

endforeach()

file(GLOB_RECURSE dest_files
    LIST_DIRECTORIES FALSE
    RELATIVE "${DEST_DIR}"
    "${DEST_DIR}/*"
)

foreach(relative_file IN LISTS dest_files)

    if(NOT relative_file IN_LIST expected_files)

        file(REMOVE "${DEST_DIR}/${relative_file}")

        message(STATUS
            "Removed obsolete asset: ${relative_file}"
        )

    endif()

endforeach()

file(GLOB_RECURSE dest_entries
    LIST_DIRECTORIES TRUE
    RELATIVE "${DEST_DIR}"
    "${DEST_DIR}/*"
)

list(SORT dest_entries)
list(REVERSE dest_entries)

foreach(relative_path IN LISTS dest_entries)

    set(full_path "${DEST_DIR}/${relative_path}")

    if(IS_DIRECTORY "${full_path}")

        file(GLOB children "${full_path}/*")

        if(NOT children)
            file(REMOVE_RECURSE "${full_path}")
        endif()

    endif()

endforeach()