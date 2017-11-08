# TODO: Modularize configs for cross compiling
CXX ?= clang++

INCLUDEDIRS := -I./include -I./deps/spdlog/include
CXXFLAGS := -O0 -g -std=c++14 -Wall -Wextra ${INCLUDEDIRS}

#CXX := arm-buildroot-linux-musleabihf-g++
#LDFLAGS := -static -lboost_thread -lboost_system

# For static linking, TODO: check out how musl works together with c++
LDFLAGS := -static -L/usr/lib/x86_64-linux-gnu/ -lboost_thread -lboost_system -lpthread

HDR := include/CanSocket.h \

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
CXXFLAGS := ${CXXFLAGS} -I${ROSCORE_PATH}/cpp_common/include
LDFLGAS := -L./lib -lros_serialization -lrostime -lros_cpp

-include src/*.d

%.o: %.cpp
	@echo CXX $<
	@${CXX} -MMD ${CXXFLAGS} -o $@ -c $<

${BINNAME}: ${OBJ} ${ALL_LIB}
	@echo LD $@
	@${CXX} -o $@ $^ ${LDFLAGS}

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


