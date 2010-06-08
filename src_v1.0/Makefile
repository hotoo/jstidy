######################################
#
# Generic makefile
#
# by George Foot
# email: george.foot@merton.ox.ac.uk
#
# Copyright (c) 1997 George Foot
# All rights reserved.
#
# No warranty, no liability;
# you use this at your own risk.#
# You are free to modify and
# distribute this without giving
# credit to the original author.
#
######################################### Customising
#
# Adjust the following if necessary; EXECUTABLE is the target
# executable’s filename, and LIBS is a list of libraries to link in
# (e.g. alleg, stdcx, iostr, etc). You can override these on make’s
# command line of course, if you prefer to do it that way.
#
#
# 修改生成可执行文件的名称
EXECUTABLE := jstidy
# 修改LIBS，添加所需要链接的库，以空格分隔，例如 LIBS := pthread rt ssl
#LIBS :=# Now alter any implicit rules’ variables if you like, e.g.:

#
# 修改CC，改变编译器
CC:=g++
# 修改编译选项
CFLAGS := -g -D_DEBUG -Wall
CXXFLAGS := $(CFLAGS)RM-F := rm -f# You shouldn’t need to change anything below this point.
#
#匹配的文件，默认仅匹配当前目录，可做如下修改
#可添加所需要包含的目录，例如$(wildcard test/*.cpp)
#可添加所支持的后缀文件，例如$(wildcard *.cc)
SOURCE := $(wildcard *.c) $(wildcard *.cpp) OBJS := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.c,$(MISSING_DEPS))
$(patsubst %.d,%.cpp,$(MISSING_DEPS)))
CPPFLAGS += -MD.PHONY : everything deps objs clean veryclean rebuildeverything : $(EXECUTABLE)deps : $(DEPS)

objs : $(OBJS)

clean :
@$(RM-F) *.o
@$(RM-F) *.d

veryclean: clean
@$(RM-F) $(EXECUTABLE)

rebuild: veryclean everything

ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
@$(RM-F) $(patsubst %.d,%.o,$@)
endif

-include $(DEPS)

$(EXECUTABLE) : $(OBJS)
$(CC) -o $(EXECUTABLE) $(OBJS) $(addprefix -l,$(LIBS))
