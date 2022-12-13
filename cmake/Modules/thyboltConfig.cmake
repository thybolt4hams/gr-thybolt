INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_THYBOLT thybolt)

FIND_PATH(
    THYBOLT_INCLUDE_DIRS
    NAMES thybolt/api.h
    HINTS $ENV{THYBOLT_DIR}/include
        ${PC_THYBOLT_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    THYBOLT_LIBRARIES
    NAMES gnuradio-thybolt
    HINTS $ENV{THYBOLT_DIR}/lib
        ${PC_THYBOLT_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/thyboltTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(THYBOLT DEFAULT_MSG THYBOLT_LIBRARIES THYBOLT_INCLUDE_DIRS)
MARK_AS_ADVANCED(THYBOLT_LIBRARIES THYBOLT_INCLUDE_DIRS)
