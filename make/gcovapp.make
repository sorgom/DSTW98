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
TARGETDIR = ../build/linux/lib
TARGET = $(TARGETDIR)/libgcovapp.a
INCLUDES += -I../testing/testenv -I../submodules/cpputest/include -I../submodules/CppUTestSteps/TestSteps/include -I../specification -I../application/components
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS +=
LDDEPS +=
LINKCMD = $(AR) -rcs "$@" $(OBJECTS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),ci)
OBJDIR = ../build/linux/obj/ci/gcovapp
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall -fprofile-arcs -ftest-coverage
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall -fprofile-arcs -ftest-coverage
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib -s -pthread

else ifeq ($(config),debug)
OBJDIR = ../build/linux/obj/debug/gcovapp
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g -std=c++98 -pedantic-errors -Werror -Wall -fprofile-arcs -ftest-coverage
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g -std=c++98 -pedantic-errors -Werror -Wall -fprofile-arcs -ftest-coverage
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib -pthread

else ifeq ($(config),fail)
OBJDIR = ../build/linux/obj/fail/gcovapp
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG -DSTATIC_FAIL
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall -fprofile-arcs -ftest-coverage
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall -fprofile-arcs -ftest-coverage
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib -s -pthread

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/Com.o
GENERATED += $(OBJDIR)/Ctrl.o
GENERATED += $(OBJDIR)/LCR_X.o
GENERATED += $(OBJDIR)/Main.o
GENERATED += $(OBJDIR)/Mapper.o
GENERATED += $(OBJDIR)/Net.o
GENERATED += $(OBJDIR)/Provider.o
GENERATED += $(OBJDIR)/Reader.o
GENERATED += $(OBJDIR)/SIG_X.o
GENERATED += $(OBJDIR)/TCP.o
GENERATED += $(OBJDIR)/TCP_Com.o
GENERATED += $(OBJDIR)/TSW.o
OBJECTS += $(OBJDIR)/Com.o
OBJECTS += $(OBJDIR)/Ctrl.o
OBJECTS += $(OBJDIR)/LCR_X.o
OBJECTS += $(OBJDIR)/Main.o
OBJECTS += $(OBJDIR)/Mapper.o
OBJECTS += $(OBJDIR)/Net.o
OBJECTS += $(OBJDIR)/Provider.o
OBJECTS += $(OBJDIR)/Reader.o
OBJECTS += $(OBJDIR)/SIG_X.o
OBJECTS += $(OBJDIR)/TCP.o
OBJECTS += $(OBJDIR)/TCP_Com.o
OBJECTS += $(OBJDIR)/TSW.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking gcovapp
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

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
	@echo Cleaning gcovapp
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


# File Rules
# #############################################

$(OBJDIR)/Net.o: ../application/components/BAS/src/Net.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Com.o: ../application/components/COM/src/Com.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TCP.o: ../application/components/COM/src/TCP.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TCP_Com.o: ../application/components/COM/src/TCP_Com.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/LCR_X.o: ../application/components/LCR/src/LCR_X.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SIG_X.o: ../application/components/SIG/src/SIG_X.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Ctrl.o: ../application/components/SYS/src/Ctrl.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Main.o: ../application/components/SYS/src/Main.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Mapper.o: ../application/components/SYS/src/Mapper.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Provider.o: ../application/components/SYS/src/Provider.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Reader.o: ../application/components/SYS/src/Reader.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TSW.o: ../application/components/TSW/src/TSW.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif