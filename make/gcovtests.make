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
TARGETDIR = ../build/linux/bin
TARGET = $(TARGETDIR)/gcovtests
INCLUDES += -I../testing/testenv -I../submodules/cpputest/include -I../submodules/CppUTestSteps/TestSteps/include -I../specification -I../application/components
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS += ../build/linux/lib/libgcovapp.a ../build/linux/lib/libcpputest.a -lgcov
LDDEPS += ../build/linux/lib/libgcovapp.a ../build/linux/lib/libcpputest.a
LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),ci)
OBJDIR = ../build/linux/obj/ci/gcovtests
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib -s -pthread --coverage

else ifeq ($(config),debug)
OBJDIR = ../build/linux/obj/debug/gcovtests
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib -pthread --coverage

else ifeq ($(config),fail)
OBJDIR = ../build/linux/obj/fail/gcovtests
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG -DSTATIC_FAIL
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib -s -pthread --coverage

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/BAS_01.o
GENERATED += $(OBJDIR)/BAS_02.o
GENERATED += $(OBJDIR)/BAS_03.o
GENERATED += $(OBJDIR)/COM_01.o
GENERATED += $(OBJDIR)/COM_02.o
GENERATED += $(OBJDIR)/COM_03.o
GENERATED += $(OBJDIR)/COM_04.o
GENERATED += $(OBJDIR)/Comparator.o
GENERATED += $(OBJDIR)/LCR_01.o
GENERATED += $(OBJDIR)/M_Instances.o
GENERATED += $(OBJDIR)/NetTest.o
GENERATED += $(OBJDIR)/SIG_01.o
GENERATED += $(OBJDIR)/SYS_01.o
GENERATED += $(OBJDIR)/SYS_02.o
GENERATED += $(OBJDIR)/SYS_03.o
GENERATED += $(OBJDIR)/TCP_Client.o
GENERATED += $(OBJDIR)/TSW_01.o
GENERATED += $(OBJDIR)/TestGroupBase.o
GENERATED += $(OBJDIR)/TestLib.o
GENERATED += $(OBJDIR)/TestMain.o
GENERATED += $(OBJDIR)/TestSteps.o
GENERATED += $(OBJDIR)/TestStepsPlugin.o
GENERATED += $(OBJDIR)/installComparators.o
GENERATED += $(OBJDIR)/ostreamHelpers.o
GENERATED += $(OBJDIR)/ostreams.o
GENERATED += $(OBJDIR)/wait.o
OBJECTS += $(OBJDIR)/BAS_01.o
OBJECTS += $(OBJDIR)/BAS_02.o
OBJECTS += $(OBJDIR)/BAS_03.o
OBJECTS += $(OBJDIR)/COM_01.o
OBJECTS += $(OBJDIR)/COM_02.o
OBJECTS += $(OBJDIR)/COM_03.o
OBJECTS += $(OBJDIR)/COM_04.o
OBJECTS += $(OBJDIR)/Comparator.o
OBJECTS += $(OBJDIR)/LCR_01.o
OBJECTS += $(OBJDIR)/M_Instances.o
OBJECTS += $(OBJDIR)/NetTest.o
OBJECTS += $(OBJDIR)/SIG_01.o
OBJECTS += $(OBJDIR)/SYS_01.o
OBJECTS += $(OBJDIR)/SYS_02.o
OBJECTS += $(OBJDIR)/SYS_03.o
OBJECTS += $(OBJDIR)/TCP_Client.o
OBJECTS += $(OBJDIR)/TSW_01.o
OBJECTS += $(OBJDIR)/TestGroupBase.o
OBJECTS += $(OBJDIR)/TestLib.o
OBJECTS += $(OBJDIR)/TestMain.o
OBJECTS += $(OBJDIR)/TestSteps.o
OBJECTS += $(OBJDIR)/TestStepsPlugin.o
OBJECTS += $(OBJDIR)/installComparators.o
OBJECTS += $(OBJDIR)/ostreamHelpers.o
OBJECTS += $(OBJDIR)/ostreams.o
OBJECTS += $(OBJDIR)/wait.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking gcovtests
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
	@echo Cleaning gcovtests
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

$(OBJDIR)/TestSteps.o: ../submodules/CppUTestSteps/TestSteps/src/TestSteps.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestStepsPlugin.o: ../submodules/CppUTestSteps/TestSteps/src/TestStepsPlugin.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TCP_Client.o: ../testing/testenv/TCP/src/TCP_Client.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Comparator.o: ../testing/testenv/comparators/src/Comparator.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/installComparators.o: ../testing/testenv/comparators/src/installComparators.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ostreamHelpers.o: ../testing/testenv/comparators/src/ostreamHelpers.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ostreams.o: ../testing/testenv/comparators/src/ostreams.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/M_Instances.o: ../testing/testenv/mocks/src/M_Instances.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/NetTest.o: ../testing/testenv/testlib/src/NetTest.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestGroupBase.o: ../testing/testenv/testlib/src/TestGroupBase.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestLib.o: ../testing/testenv/testlib/src/TestLib.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestMain.o: ../testing/testenv/testlib/src/TestMain.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/wait.o: ../testing/testenv/testlib/src/wait.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/BAS_01.o: ../testing/tests/moduletests/BAS/BAS_01.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/BAS_02.o: ../testing/tests/moduletests/BAS/BAS_02.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/BAS_03.o: ../testing/tests/moduletests/BAS/BAS_03.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/COM_01.o: ../testing/tests/moduletests/COM/COM_01.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/COM_02.o: ../testing/tests/moduletests/COM/COM_02.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/COM_03.o: ../testing/tests/moduletests/COM/COM_03.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/COM_04.o: ../testing/tests/moduletests/COM/COM_04.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/LCR_01.o: ../testing/tests/moduletests/LCR/LCR_01.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SIG_01.o: ../testing/tests/moduletests/SIG/SIG_01.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SYS_01.o: ../testing/tests/moduletests/SYS/SYS_01.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SYS_02.o: ../testing/tests/moduletests/SYS/SYS_02.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SYS_03.o: ../testing/tests/moduletests/SYS/SYS_03.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TSW_01.o: ../testing/tests/moduletests/TSW/TSW_01.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif