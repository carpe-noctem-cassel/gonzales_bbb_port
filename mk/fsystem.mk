FSYSTEM_PATH := deps/fsystem

FSYSTEM_SRC := ${FSYSTEM_PATH}/src/FileSystem.cpp
FSYSTEM_OBJ := $(FSYSTEM_SRC:.cpp=.o)

-include ${FSYSTEM_PATH}/src/*.d

FSYSTEM_LIB := lib/libfsystem.a

${FSYSTEM_LIB}: ${FSYSTEM_OBJ}
	@echo AR $@
	@ar rcs $@ $^

ALL_OBJ := ${ALL_OBJ} ${FSYSTEM_OBJ}
ALL_LIB := ${ALL_LIB} ${FSYSTEM_LIB}

CXXFLAGS := ${CXXFLAGS} -I${FSYSTEM_PATH}/include

