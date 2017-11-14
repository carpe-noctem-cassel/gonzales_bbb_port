SYSTEM_CONFIG_PATH := deps/system_config

SYSTEM_CONFIG_SRC := ${SYSTEM_CONFIG_PATH}/src/Configuration.cpp \
	${SYSTEM_CONFIG_PATH}/src/SystemConfig.cpp \

SYSTEM_CONFIG_OBJ := $(SYSTEM_CONFIG_SRC:.cpp=.o)

-include ${SYSTEM_CONFIG_PATH}/src/*.d

SYSTEM_CONFIG_LIB := lib/libsystem_config.a

${SYSTEM_CONFIG_LIB}: ${SYSTEM_CONFIG_OBJ}
	@echo AR $@
	@ar rcs $@ $^

ALL_OBJ := ${ALL_OBJ} ${SYSTEM_CONFIG_OBJ}
ALL_LIB := ${ALL_LIB} ${SYSTEM_CONFIG_LIB}

G_CXXFLAGS := ${G_CXXFLAGS} -I${SYSTEM_CONFIG_PATH}/include

