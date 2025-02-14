# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=ci
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq ($(shell echo "test"), "test")
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

ifeq ($(origin CC), default)
  CC = gcc
endif
ifeq ($(origin CXX), default)
  CXX = g++
endif
ifeq ($(origin AR), default)
  AR = ar
endif
RESCOMP = windres
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS +=
LDDEPS +=
LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),ci)
TARGETDIR = ../build/linux/ci
TARGET = $(TARGETDIR)/memleak
OBJDIR = ../build/linux/obj/ci/memleak
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG
INCLUDES +=
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/ci -s -pthread

else ifeq ($(config),debug)
TARGETDIR = ../build/linux/debug
TARGET = $(TARGETDIR)/memleak
OBJDIR = ../build/linux/obj/debug/memleak
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DDEBUG
INCLUDES +=
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/debug -pthread

else ifeq ($(config),memleak)
TARGETDIR = ../build/linux/memleak
TARGET = $(TARGETDIR)/memleak
OBJDIR = ../build/linux/obj/memleak/memleak
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG
INCLUDES += -I../specification -I../application/components
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/memleak -s -pthread

else ifeq ($(config),bullseye)
TARGETDIR = ../build/linux/bullseye
TARGET = $(TARGETDIR)/memleak
OBJDIR = ../build/linux/obj/bullseye/memleak
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG
INCLUDES +=
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/bullseye -s -pthread

else ifeq ($(config),fail)
TARGETDIR = ../build/linux/fail
TARGET = $(TARGETDIR)/memleak
OBJDIR = ../build/linux/obj/fail/memleak
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DSTATIC_FAIL
INCLUDES +=
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/fail -s -pthread

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

ifeq ($(config),memleak)
GENERATED += $(OBJDIR)/memLeakMain.o
OBJECTS += $(OBJDIR)/memLeakMain.o

endif

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning memleak
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) del /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


ifeq ($(config),ci)
$(TARGET): $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking memleak
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)


else ifeq ($(config),debug)
$(TARGET): $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking memleak
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)


else ifeq ($(config),memleak)
$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking memleak
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)


else ifeq ($(config),bullseye)
$(TARGET): $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking memleak
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)


else ifeq ($(config),fail)
$(TARGET): $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking memleak
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)


endif

# File Rules
# #############################################

ifeq ($(config),memleak)
$(OBJDIR)/memLeakMain.o: ../testing/tests/memleak/memLeakMain.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

endif

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif