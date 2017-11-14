# TODO: Modularize configs for cross compiling
CXX ?= clang++

INCLUDEDIRS := -I./include -I./deps/spdlog/include
G_CXXFLAGS := ${CXXFLAGS} ${INCLUDEDIRS} -std=c++14 -Wall -Wextra

#To compile for beagleboard e.g. use this compiler from buildroot
#CXX := arm-buildroot-linux-musleabihf-g++
#LDFLAGS := -static -lboost_thread -lboost_system

# For static linking, TODO: check out how musl works together with c++
G_LDFLAGS := ${LDFLAGS} -lboost_thread -lboost_system -lpthread

HDR := include/canconnection.h \
	include/Can.h \
	include/canlistener.h \
	include/gonzales.h \
	include/logging.h \
	include/MCDC.h \
	include/MCDCProtocol.h \
	include/pcanconnect.h \
	include/Proxy.h \
	include/RosHelper.h \
	include/settings.h \
	include/udpcanconnection.h \
	include/usbcanconnection.h \
	include/util.h \
	include/utils.h \

SRC := src/settings.cpp \
  src/driver/controller.cpp \
  src/driver/eposcan.cpp \
  src/logging.cpp \
  src/gonzales.cpp \
  src/Proxy.cpp \
  src/usbcanconnection.cpp \
  src/main.cpp

OBJ := $(SRC:.cpp=.o)

ALL_OBJ := ${OBJ}
ALL_SRC := ${SRC}

BINNAME := gonzales_bbb

all: ${BINNAME}

# Minimal ros dependencies
ROSCORE_PATH := deps/roscpp_core
include mk/rostime.mk
include mk/ros_serialization.mk
include mk/system_config.mk
include mk/fsystem.mk
G_CXXFLAGS := ${G_CXXFLAGS} -I${ROSCORE_PATH}/cpp_common/include
G_LDFLGAS := -L./lib -lros_serialization -lrostime -lros_cpp

-include src/*.d

%.o: %.cpp
	@echo CXX $<
	${CXX} -MMD ${G_CXXFLAGS} -o $@ -c $<

${BINNAME}: ${OBJ} ${ALL_LIB}
	@echo LD $@
	${CXX} -o $@ $^ ${G_LDFLAGS}

fmt: ${SRC} ${HDR}
	@echo FMT $^
	@clang-format -i $^

tidy:
	clang-tidy -checks=* ${SRC} 

src:
	@echo ${ALL_SRC} ${HDR}

clean:
	rm -f ${ALL_OBJ} ${ALL_LIB} ${BINNAME}

.PHONY: clean obj fmt src
.SECONDARY:


