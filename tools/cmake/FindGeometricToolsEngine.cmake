# - Try to find Geometric Tools Engine library

# GTE_FOUND - System has Geometric Tools Engine library
# GTE_INCLUDE_DIRS - The Geometric Tools Engine library include directories
# GTE_LIBRARIES - The libraries needed to use Geometric Tools Engine library
# GTE_DEFINITIONS - Compiler switches required for using Geometric Tools Engine library

SET (GTE_ROOT_DIR ${GTE_ROOT_DIR} "/usr/local")

FIND_PATH (GTE_INCLUDE_DIR "Gte/GTEngine.h" PATHS ${GTE_ROOT_DIR} PATH_SUFFIXES "include" NO_DEFAULT_PATH)

SET (GTE_LIBRARIES ${GTE_LIBRARY})
SET (GTE_INCLUDE_DIR "${GTE_INCLUDE_DIR}/Gte")

# MESSAGE (STATUS "GTE_ROOT_DIR = ${GTE_ROOT_DIR}")
# MESSAGE (STATUS "GTE_INCLUDE_DIR = ${GTE_INCLUDE_DIR}")

INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (GTE DEFAULT_MSG GTE_INCLUDE_DIR)

MARK_AS_ADVANCED (GTE_INCLUDE_DIR)