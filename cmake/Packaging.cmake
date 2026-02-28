# cmake/Packaging.cmake

# metadata
set(CPACK_PACKAGE_NAME "code-snippets-custom")
set(CPACK_PACKAGE_VENDOR "Ace")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "Custom C++ utils and snippets")
set(CPACK_PACKAGE_CONTACT "https://github.com/Ace606606/code_snippets_custom")

if(TARGET csc-load-daemon)
    install(TARGETS csc-load-daemon RUNTIME DESTINATION bin)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/systemd/csc-load-daemon.service")
    install(FILES "${CMAKE_SOURCE_DIR}/cmake/systemd/csc-load-daemon.service"
            DESTINATION /lib/systemd/system)
endif()

install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/include/"
        DESTINATION include/csc
        FILES_MATCHING PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_RELEASE "1")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
