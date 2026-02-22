# third_party/CMakeLists.txt

set(FMT_INSTALL OFF CACHE INTERNAL "")
set(FMT_DOC OFF CACHE INTERNAL "")
set(FMT_TEST OFF CACHE INTERNAL "")

if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/fmt")
     add_subdirectory(fmt EXCLUDE_FROM_ALL)
else()
     message(FATAL_ERROR
          "FMT submodule not found at: ${CMAKE_CURRENT_SOURCE_DIR}/fmt\n"
          "Please run: git submodule update --init --recursive"
     )
endif()

set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)