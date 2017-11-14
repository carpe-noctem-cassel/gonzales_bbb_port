ROSCORE_PATH := deps/roscpp_core
ROSTIME_PATH := ${ROSCORE_PATH}/rostime

ROSTIME_SRC := ${ROSTIME_PATH}/src/duration.cpp \
	${ROSTIME_PATH}/src/rate.cpp \
	${ROSTIME_PATH}/src/time.cpp \

ROSTIME_OBJ := $(ROSTIME_SRC:.cpp=.o)

-include ${ROSTIME_PATH}/src/*.d

ROSTIME_LIB := lib/librostime.a

${ROSTIME_LIB}: ${ROSTIME_OBJ}
	@echo AR $@
	@ar rcs $@ $^

ALL_OBJ := ${ALL_OBJ} ${ROSTIME_OBJ}
ALL_LIB := ${ALL_LIB} ${ROSTIME_LIB}

# TODO: Make include flags for library local?
G_CXXFLAGS := ${G_CXXFLAGS} -I${ROSTIME_PATH}/include
G_CXXFLAGS := ${G_CXXFLAGS} -I${ROSCORE_PATH}/cpp_common/include
G_CXXFLAGS := ${G_CXXFLAGS} -I${ROSCORE_PATH}/roscpp_serialization/include
G_CXXFLAGS := ${G_CXXFLAGS} -I${ROSCORE_PATH}/roscpp_traits/include


