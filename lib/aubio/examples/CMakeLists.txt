project(aubioonset)

set(aubioonset_SRC aubioonset.c utils.h utils.c)

FIND_LIBRARY(aubio aubio ${aubioonset_SOURCE_DIR})


SET(EXECUTABLE_OUTPUT_PATH ${aubioonset_SOURCE_DIR}/win_bin            CACHE PATH "Single output directory for building all executables.")


add_executable(aubioonset ${aubioonset_SRC})

TARGET_LINK_LIBRARIES(aubioonset ${aubio})