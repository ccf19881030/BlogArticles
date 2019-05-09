## makefile编写
[跟我一起写 Makefile-csdn 陈皓](https://blog.csdn.net/haoel/article/details/2886#comments) 

## Linux下C++的通用Makefile与解析
[Linux下C++的通用Makefile与解析](https://blog.csdn.net/zhoujiaxq/article/details/25972859)
C++万能Makefile，即可编译链接所有的C++程序，而只需作很少的修改。
```
####################################################
# Generic makefile - 万能Makefile
# for compiling and linking C++ projects on Linux 
# Author: George Foot  Modified:Jackie Lee
####################################################
### Customising
#
# Adjust the following if necessary; EXECUTABLE is the target
# executable's filename, and LIBS is a list of libraries to link in
# (e.g. alleg, stdcx, iostr, etc). You can override these on make's
# command line of course, if you prefer to do it that way.
#
#
EXECUTABLE := main    # 可执行文件名
LIBDIR:=              # 静态库目录
LIBS :=               # 静态库文件名
INCLUDES:=.           # 头文件目录
SRCDIR:=              # 除了当前目录外，其他的源代码文件目录
#
# # Now alter any implicit rules' variables if you like, e.g.:

CC:=g++
CFLAGS := -g -Wall -O3
CPPFLAGS := $(CFLAGS)
CPPFLAGS += $(addprefix -I,$(INCLUDES))
CPPFLAGS += -MMD
#
# # The next bit checks to see whether rm is in your djgpp bin
# # directory; if not it uses del instead, but this can cause (harmless)
# # `File not found' error messages. If you are not using DOS at all,
# # set the variable to something which will unquestioningly remove
# # files.
#

RM-F := rm -f


# # You shouldn't need to change anything below this point.
#
SRCS := $(wildcard *.cpp) $(wildcard $(addsuffix /*.cpp, $(SRCDIR)))
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.cpp,$(MISSING_DEPS)))


.PHONY : all deps objs clean veryclean rebuild info

all: $(EXECUTABLE)

deps : $(DEPS)

objs : $(OBJS)

clean :
        @$(RM-F) *.o
        @$(RM-F) *.d
veryclean: clean
        @$(RM-F) $(EXECUTABLE)

rebuild: veryclean all
ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
        @$(RM-F) $(patsubst %.d,%.o,$@)
endif
-include $(DEPS)
$(EXECUTABLE) : $(OBJS)
        $(CC) -o $(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))

info:
        @echo $(SRCS)
        @echo $(OBJS)
        @echo $(DEPS)
        @echo $(MISSING_DEPS)
        @echo $(MISSING_DEPS_SOURCES)

```
