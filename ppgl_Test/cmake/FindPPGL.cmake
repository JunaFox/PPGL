set(FIND_PPGL_PATHS ../ppgl)

find_path(PPGL_INCLUDE_DIR ppgl.h
        PATHS ${FIND_PPGL_PATHS})

find_library(PPGL_LIBRARY
             NAMES libppgl
             PATHS ${FIND_PPGL_PATHS}/cmake-build-release)