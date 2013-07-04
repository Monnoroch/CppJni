# set build type to static lib

BUILD_MODE := RELEASE

ifeq ($(ARCH),)
	ARCH := $(shell uname -m)
	ifeq ($(ARCH),unknown)
		ARCH := $$(shell uname -i)
	endif
	ifeq ($(ARCH),i686)
		ARCH := x86
	endif
endif

# arch flag
COMPILER_ARCH_FLAG :=
ifeq ($(ARCH),x86)
	COMPILER_ARCH_FLAG := -m32
endif

ifeq ($(ARCH),x86_64)
	COMPILER_ARCH_FLAG := -m64
endif

COMPILER_FlAGS_BASIC := -Wall -c $(COMPILER_ARCH_FLAG) -fvisibility=hidden

ifneq ($(V_OS), Win)
		COMPILER_FlAGS_BASIC += -fPIC
endif

COMPILER_FLAGS_DEBUG   := -O0 -DMSymDebug -ggdb3
COMPILER_FLAGS_RELEASE := -O3

COMPILER_FLAGS := $(COMPILER_FlAGS_BASIC) $(COMPILER_FLAGS_$(BUILD_MODE))


SOURSE := \
	JniHelper.cpp \
	JniJavaVM.cpp \
	JniJavaEnv.cpp \
	JniJavaObject.cpp \
	JniJavaClass.cpp \
	JniJavaString.cpp

HEADERS := \
	JniForwards.h \
	JniHelper.h \
	JniProxy.h \
	JniSignatureBuilder.h \
	JniJavaVM.h \
	JniJavaEnv.h \
	JniJavaObject.h \
	JniJavaClass.h \
	JniJavaString.h \
	JniJavaArray.h \
	JniJavaMethod.h \
	JniJavaField.h

###################################################

INCLUDES := . $(JAVA_HOME)/include $(JAVA_HOME)/include/linux

CFLAGS := $(COMPILER_FLAGS) -s -std=c++0x

###################################################

OBJECTS := $(SOURSE:%.cpp=%.o)

RESULT_NAME := libCppJni.a
COMPILER := g++

###################################################

all: build

%.o: %.cpp
	$(COMPILER) $(CFLAGS) $(addprefix -I, $(INCLUDES)) $< -o $@

test:

$(RESULT_NAME): $(OBJECTS)
	ar rvs $@ $(OBJECTS)

build: $(RESULT_NAME)

clean:
	rm -f $(RESULT_NAME)
	rm -f $(OBJECTS)

rebuild: clean build
