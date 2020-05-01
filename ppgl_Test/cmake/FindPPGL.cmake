set(FIND_PPGL_PATHS ../ppgl)

find_path(PPGL_INCLUDE_DIR ppgl.h
          PATH_SUFFIXES include
          PATHS ${FIND_PPGL_PATHS})

find_library(PPGL_LIBRARY
             NAMES ppgl
             PATH_SUFFIXES lib
             PATHS ${FIND_PPGL_PATHS})