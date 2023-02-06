#[[
based on https://github.com/riebl/vanetza/blob/aed571d6297258a2a499b9cb4eedb8254d977360/cmake/FindCryptoPP.cmake

Input:
CryptoPP_ROOT_DIR (optional) - specify where CryptoPP was installed
    (e.g. /usr/local or $CMAKE_SOURCE_DIR/3rdparty/usr/local)
    Directory must contain subdirectories include and lib
Output:
CryptoPP::CryptoPP   - target (release build)
CryptoPP_INCLUDE_DIR - includes directory containing subdirectory cryptopp/
CryptoPP_LIBRARY     - CryptoPP library file (libcryptopp.a)
]]

if (CryptoPP_ROOT_DIR)
    # find using CryptoPP_ROOT_DIR ONLY
    find_path(CryptoPP_INCLUDE_DIR
        NAMES cryptopp/config.h
        DOC "CryptoPP include directory"
        NO_DEFAULT_PATH
        PATHS ${CryptoPP_ROOT_DIR}/include
        )
    find_library(CryptoPP_LIBRARY
        NAMES cryptopp
        DOC "CryptoPP library"
        NO_DEFAULT_PATH
        PATHS ${CryptoPP_ROOT_DIR}/lib
        )
    message("PACZPAN with root given: ${CryptoPP_INCLUDE_DIR} ${CryptoPP_LIBRARY}")
else()
    find_path(CryptoPP_INCLUDE_DIR
        NAMES cryptopp/config.h
        DOC "CryptoPP include directory"
        )
    find_library(CryptoPP_LIBRARY
        NAMES cryptopp
        DOC "CryptoPP library"
        NO_PACKAGE_ROOT_PATH
        PATHS "/usr/lib/x86_64-linux-gnu/"
        )
    message("PACZPAN without root given: ${CryptoPP_INCLUDE_DIR} ${CryptoPP_LIBRARY}")
endif(CryptoPP_ROOT_DIR)

if(CryptoPP_INCLUDE_DIR)
    file(STRINGS ${CryptoPP_INCLUDE_DIR}/cryptopp/config.h _config_version REGEX "CRYPTOPP_VERSION")
    # string(REGEX MATCH "([0-9]+)([0-9]+)([0-9]+)" _match_version ${_config_version})
    set(CryptoPP_VERSION_STRING "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CryptoPP
    REQUIRED_VARS CryptoPP_INCLUDE_DIR CryptoPP_LIBRARY
    FOUND_VAR CryptoPP_FOUND
    VERSION_VAR CryptoPP_VERSION_STRING)

if(CryptoPP_FOUND AND NOT TARGET CryptoPP::CryptoPP)
    add_library(CryptoPP::CryptoPP UNKNOWN IMPORTED)
    set_target_properties(CryptoPP::CryptoPP PROPERTIES
        IMPORTED_LOCATION "${CryptoPP_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${CryptoPP_INCLUDE_DIR}")
endif()

mark_as_advanced(CryptoPP_INCLUDE_DIR CryptoPP_LIBRARY)
set(CryptoPP_INCLUDE_DIRS ${CryptoPP_INCLUDE_DIR})
set(CryptoPP_LIBRARIES ${CryptoPP_LIBRARY})
