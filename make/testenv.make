# GNU Make project makefile autogenerated by Premake

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
TARGETDIR = ../build/linux/lib/ci
TARGET = $(TARGETDIR)/libtestenv.a
OBJDIR = ../build/linux/obj/ci/testenv
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/ci -s

else ifeq ($(config),debug)
TARGETDIR = ../build/linux/lib/debug
TARGET = $(TARGETDIR)/libtestenv.a
OBJDIR = ../build/linux/obj/debug/testenv
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/debug

else ifeq ($(config),memleak)
TARGETDIR = ../build/linux/lib/memleak
TARGET = $(TARGETDIR)/libtestenv.a
OBJDIR = ../build/linux/obj/memleak/testenv
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/memleak -s

else ifeq ($(config),bullseye)
TARGETDIR = ../build/linux/lib/bullseye
TARGET = $(TARGETDIR)/libtestenv.a
OBJDIR = ../build/linux/obj/bullseye/testenv
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/bullseye -s

else ifeq ($(config),fail)
TARGETDIR = ../build/linux/lib/fail
TARGET = $(TARGETDIR)/libtestenv.a
OBJDIR = ../build/linux/obj/fail/testenv
DEFINES += -DCAPACITY=20 -DCPPUTEST_USE_LONG_LONG=0 -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED -DSTATIC_FAIL
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -std=c++98 -pedantic-errors -Werror -Wall
ALL_LDFLAGS += $(LDFLAGS) -L../build/linux/lib/fail -s

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/CodeMemoryReportFormatter.o
GENERATED += $(OBJDIR)/CommandLineArguments.o
GENERATED += $(OBJDIR)/CommandLineTestRunner.o
GENERATED += $(OBJDIR)/Comparator.o
GENERATED += $(OBJDIR)/GTest.o
GENERATED += $(OBJDIR)/IEEE754ExceptionsPlugin.o
GENERATED += $(OBJDIR)/JUnitTestOutput.o
GENERATED += $(OBJDIR)/M_Instances.o
GENERATED += $(OBJDIR)/MemoryLeakDetector.o
GENERATED += $(OBJDIR)/MemoryLeakWarningPlugin.o
GENERATED += $(OBJDIR)/MemoryReportAllocator.o
GENERATED += $(OBJDIR)/MemoryReportFormatter.o
GENERATED += $(OBJDIR)/MemoryReporterPlugin.o
GENERATED += $(OBJDIR)/MockActualCall.o
GENERATED += $(OBJDIR)/MockExpectedCall.o
GENERATED += $(OBJDIR)/MockExpectedCallsList.o
GENERATED += $(OBJDIR)/MockFailure.o
GENERATED += $(OBJDIR)/MockNamedValue.o
GENERATED += $(OBJDIR)/MockSupport.o
GENERATED += $(OBJDIR)/MockSupportPlugin.o
GENERATED += $(OBJDIR)/MockSupport_c.o
GENERATED += $(OBJDIR)/NetTest.o
GENERATED += $(OBJDIR)/OrderedTest.o
GENERATED += $(OBJDIR)/SimpleMutex.o
GENERATED += $(OBJDIR)/SimpleString.o
GENERATED += $(OBJDIR)/SimpleStringInternalCache.o
GENERATED += $(OBJDIR)/TCP_Client.o
GENERATED += $(OBJDIR)/TeamCityTestOutput.o
GENERATED += $(OBJDIR)/TestFailure.o
GENERATED += $(OBJDIR)/TestFilter.o
GENERATED += $(OBJDIR)/TestGroupBase.o
GENERATED += $(OBJDIR)/TestHarness_c.o
GENERATED += $(OBJDIR)/TestLib.o
GENERATED += $(OBJDIR)/TestMemoryAllocator.o
GENERATED += $(OBJDIR)/TestOutput.o
GENERATED += $(OBJDIR)/TestPlugin.o
GENERATED += $(OBJDIR)/TestRegistry.o
GENERATED += $(OBJDIR)/TestResult.o
GENERATED += $(OBJDIR)/TestSteps.o
GENERATED += $(OBJDIR)/TestStepsPlugin.o
GENERATED += $(OBJDIR)/TestTestingFixture.o
GENERATED += $(OBJDIR)/Utest.o
GENERATED += $(OBJDIR)/UtestPlatform.o
GENERATED += $(OBJDIR)/installComparators.o
GENERATED += $(OBJDIR)/ostreamHelpers.o
GENERATED += $(OBJDIR)/ostreams.o
GENERATED += $(OBJDIR)/wait.o
OBJECTS += $(OBJDIR)/CodeMemoryReportFormatter.o
OBJECTS += $(OBJDIR)/CommandLineArguments.o
OBJECTS += $(OBJDIR)/CommandLineTestRunner.o
OBJECTS += $(OBJDIR)/Comparator.o
OBJECTS += $(OBJDIR)/GTest.o
OBJECTS += $(OBJDIR)/IEEE754ExceptionsPlugin.o
OBJECTS += $(OBJDIR)/JUnitTestOutput.o
OBJECTS += $(OBJDIR)/M_Instances.o
OBJECTS += $(OBJDIR)/MemoryLeakDetector.o
OBJECTS += $(OBJDIR)/MemoryLeakWarningPlugin.o
OBJECTS += $(OBJDIR)/MemoryReportAllocator.o
OBJECTS += $(OBJDIR)/MemoryReportFormatter.o
OBJECTS += $(OBJDIR)/MemoryReporterPlugin.o
OBJECTS += $(OBJDIR)/MockActualCall.o
OBJECTS += $(OBJDIR)/MockExpectedCall.o
OBJECTS += $(OBJDIR)/MockExpectedCallsList.o
OBJECTS += $(OBJDIR)/MockFailure.o
OBJECTS += $(OBJDIR)/MockNamedValue.o
OBJECTS += $(OBJDIR)/MockSupport.o
OBJECTS += $(OBJDIR)/MockSupportPlugin.o
OBJECTS += $(OBJDIR)/MockSupport_c.o
OBJECTS += $(OBJDIR)/NetTest.o
OBJECTS += $(OBJDIR)/OrderedTest.o
OBJECTS += $(OBJDIR)/SimpleMutex.o
OBJECTS += $(OBJDIR)/SimpleString.o
OBJECTS += $(OBJDIR)/SimpleStringInternalCache.o
OBJECTS += $(OBJDIR)/TCP_Client.o
OBJECTS += $(OBJDIR)/TeamCityTestOutput.o
OBJECTS += $(OBJDIR)/TestFailure.o
OBJECTS += $(OBJDIR)/TestFilter.o
OBJECTS += $(OBJDIR)/TestGroupBase.o
OBJECTS += $(OBJDIR)/TestHarness_c.o
OBJECTS += $(OBJDIR)/TestLib.o
OBJECTS += $(OBJDIR)/TestMemoryAllocator.o
OBJECTS += $(OBJDIR)/TestOutput.o
OBJECTS += $(OBJDIR)/TestPlugin.o
OBJECTS += $(OBJDIR)/TestRegistry.o
OBJECTS += $(OBJDIR)/TestResult.o
OBJECTS += $(OBJDIR)/TestSteps.o
OBJECTS += $(OBJDIR)/TestStepsPlugin.o
OBJECTS += $(OBJDIR)/TestTestingFixture.o
OBJECTS += $(OBJDIR)/Utest.o
OBJECTS += $(OBJDIR)/UtestPlatform.o
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
	@echo Linking testenv
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
	@echo Cleaning testenv
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
$(OBJDIR)/CommandLineArguments.o: ../submodules/cpputest/src/CppUTest/CommandLineArguments.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CommandLineTestRunner.o: ../submodules/cpputest/src/CppUTest/CommandLineTestRunner.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/JUnitTestOutput.o: ../submodules/cpputest/src/CppUTest/JUnitTestOutput.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MemoryLeakDetector.o: ../submodules/cpputest/src/CppUTest/MemoryLeakDetector.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MemoryLeakWarningPlugin.o: ../submodules/cpputest/src/CppUTest/MemoryLeakWarningPlugin.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SimpleMutex.o: ../submodules/cpputest/src/CppUTest/SimpleMutex.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SimpleString.o: ../submodules/cpputest/src/CppUTest/SimpleString.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SimpleStringInternalCache.o: ../submodules/cpputest/src/CppUTest/SimpleStringInternalCache.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TeamCityTestOutput.o: ../submodules/cpputest/src/CppUTest/TeamCityTestOutput.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestFailure.o: ../submodules/cpputest/src/CppUTest/TestFailure.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestFilter.o: ../submodules/cpputest/src/CppUTest/TestFilter.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestHarness_c.o: ../submodules/cpputest/src/CppUTest/TestHarness_c.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestMemoryAllocator.o: ../submodules/cpputest/src/CppUTest/TestMemoryAllocator.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestOutput.o: ../submodules/cpputest/src/CppUTest/TestOutput.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestPlugin.o: ../submodules/cpputest/src/CppUTest/TestPlugin.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestRegistry.o: ../submodules/cpputest/src/CppUTest/TestRegistry.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestResult.o: ../submodules/cpputest/src/CppUTest/TestResult.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestTestingFixture.o: ../submodules/cpputest/src/CppUTest/TestTestingFixture.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Utest.o: ../submodules/cpputest/src/CppUTest/Utest.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CodeMemoryReportFormatter.o: ../submodules/cpputest/src/CppUTestExt/CodeMemoryReportFormatter.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/GTest.o: ../submodules/cpputest/src/CppUTestExt/GTest.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/IEEE754ExceptionsPlugin.o: ../submodules/cpputest/src/CppUTestExt/IEEE754ExceptionsPlugin.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MemoryReportAllocator.o: ../submodules/cpputest/src/CppUTestExt/MemoryReportAllocator.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MemoryReportFormatter.o: ../submodules/cpputest/src/CppUTestExt/MemoryReportFormatter.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MemoryReporterPlugin.o: ../submodules/cpputest/src/CppUTestExt/MemoryReporterPlugin.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MockActualCall.o: ../submodules/cpputest/src/CppUTestExt/MockActualCall.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MockExpectedCall.o: ../submodules/cpputest/src/CppUTestExt/MockExpectedCall.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MockExpectedCallsList.o: ../submodules/cpputest/src/CppUTestExt/MockExpectedCallsList.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MockFailure.o: ../submodules/cpputest/src/CppUTestExt/MockFailure.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MockNamedValue.o: ../submodules/cpputest/src/CppUTestExt/MockNamedValue.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MockSupport.o: ../submodules/cpputest/src/CppUTestExt/MockSupport.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MockSupportPlugin.o: ../submodules/cpputest/src/CppUTestExt/MockSupportPlugin.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MockSupport_c.o: ../submodules/cpputest/src/CppUTestExt/MockSupport_c.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/OrderedTest.o: ../submodules/cpputest/src/CppUTestExt/OrderedTest.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/UtestPlatform.o: ../submodules/cpputest/src/Platforms/Gcc/UtestPlatform.cpp
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
$(OBJDIR)/wait.o: ../testing/testenv/testlib/src/wait.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif