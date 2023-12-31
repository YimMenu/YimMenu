find_package(Git)
if(Git_FOUND)
    message("Git found: ${GIT_EXECUTABLE}")

    # the commit's SHA1, and whether the building workspace was dirty or not
    execute_process(COMMAND
        "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=40 --dirty
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GIT_SHA1
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

    # the date of the commit
    execute_process(COMMAND
        "${GIT_EXECUTABLE}" log -1 --format=%ad --date=local
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GIT_DATE
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

    # the subject of the commit
    execute_process(COMMAND
        "${GIT_EXECUTABLE}" log -1 --format=%s
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GIT_COMMIT_SUBJECT
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

    # Commit messages may have quotes in them, which can affect the const char* variable.
    string(REPLACE "\"" "\\\"" GIT_COMMIT_SUBJECT "${GIT_COMMIT_SUBJECT}")

    # branch name
    execute_process(COMMAND
        "${GIT_EXECUTABLE}" branch --show-current
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GIT_BRANCH
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

    # generate version.cpp
    configure_file("${SRC_DIR}/version.cpp.in" "${SRC_DIR}/version.cpp" @ONLY)
endif()