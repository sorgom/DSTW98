--  ============================================================
--  premake5 build settings
--  ============================================================

buildoptions_gcc = '-std=c++98 -pedantic-errors -Werror -Wall'

buildoptions_vs = '/MP /W4 /wd4100 /wd4103'
buildoptions_vs_test = buildoptions_vs .. ' /wd4127'
buildoptions_vs_cpputest = buildoptions_vs .. ' /wd4611 /wd4996'

base_cpputest = '../submodules/cpputest'
includedirs_cpputest = { base_cpputest .. '/include' }

base_teststeps = '../submodules/CppUTestSteps/TestSteps'
includedirs_teststeps = { base_teststeps .. '/include' }

includedirs_app = {
    '../specification',
    '../application/components'
}
files_app = { '../application/components/**.cpp'}

includedirs_testenv = { '../testing/testenv' }
files_testenv = {
    '../testing/testenv/**.cpp',
    base_teststeps .. '/src/*.cpp'
}

-- leads to test env IL interface
includedirs_test = {
    includedirs_testenv,
    includedirs_cpputest,
    includedirs_teststeps,
    includedirs_app
}

-- leads to application IL interface
includedirs_test_IL = {
    includedirs_app,
    includedirs_testenv,
    includedirs_cpputest,
    includedirs_teststeps
}

files_moduletest = { '../testing/tests/moduletests/**.cpp' }

--  ============================================================
--  premake5 build rules
--  ============================================================

workspace 'DSTW98'
    configurations { 'ci', 'debug', 'fail' }
    language 'C++'
    targetdir '../build/%{_TARGET_OS}'
    objdir  '../build/%{_TARGET_OS}/obj'
    kind 'ConsoleApp'
    libdirs { '../build/%{_TARGET_OS}/lib' }
    defines {
        'CAPACITY=20',
        'CPPUTEST_USE_LONG_LONG=0',
        'CPPUTEST_MEM_LEAK_DETECTION_DISABLED'
    }

    filter { 'action:vs*' }
        targetdir '../build/%{_TARGET_OS}'
        buildoptions { buildoptions_vs_test }
        links { 'ws2_32' }
        warnings 'high'
        defines { '_WINSOCK_DEPRECATED_NO_WARNINGS' }

    filter { 'action:vs*', 'kind:ConsoleApp' }
        links { 'winmm' }

    filter { 'action:gmake*', 'kind:ConsoleApp' }
        targetdir '../build/%{_TARGET_OS}/bin'
        buildoptions { buildoptions_gcc }
        linkoptions { '-pthread' }

    filter { 'kind:StaticLib' }
        targetdir '../build/%{_TARGET_OS}/lib'

    filter { 'configurations:ci' }
        defines { 'NDEBUG' }

    filter { 'configurations:debug' }
        defines { 'DEBUG' }
        symbols 'On'

    filter { 'configurations:fail' }
        defines { 'NDEBUG', 'STATIC_FAIL' }
    --  ============================================================
    --  cpputest
    --  ============================================================
    project 'cpputest'
        kind 'StaticLib'
        defines { 'NDEBUG' }

        includedirs { includedirs_cpputest }
        files {
            base_cpputest .. '/src/CppUTest/*.cpp',
            base_cpputest .. '/src/CppUTestExt/*.cpp'
        }

        filter { 'action:vs*' }
            buildoptions { buildoptions_vs_cpputest }
            files { base_cpputest .. '/src/Platforms/VisualCpp/*.cpp' }

        filter { 'action:gmake*' }
            files { base_cpputest .. '/src/Platforms/Gcc/*.cpp' }

    --  ============================================================
    --  module tests / dev tests
    --  ============================================================
    project 'moduletests'
        files { files_app, files_testenv, files_moduletest }
        includedirs { includedirs_test }
        links { 'cpputest' }

    project 'moduletestsIL'
        files { files_app, files_testenv, '../testing/tests/moduletestsIL/*.cpp' }
        includedirs { includedirs_test_IL }
        links { 'cpputest' }

    project 'devtests'
        files { files_app, files_testenv, '../testing/tests/devtests/*.cpp' }
        includedirs { includedirs_test, '../devel' }
        links { 'cpputest' }

    project 'buildfail'
        kind 'StaticLib'
        files { '../testing/tests/buildfail/*.cpp' }
        includedirs { includedirs_app }
        targetdir '../build/fail'

    --  ============================================================
    --  system tests
    --  ============================================================
    --  run first
    project 'dstw_gen'
        includedirs { includedirs_test }
        files {
            '../testing/gendata/genDataMain.cpp',
            '../testing/testenv/testlib/src/TestLib.cpp',
            '../testing/testenv/testlib/src/NetTest.cpp'
        }

    --  run second in background
    --  must be unstrumented for coverage
    project 'dstw_runtime'
        files { files_app, '../application/main/*.cpp' }
        includedirs { includedirs_app }

    --  run third
    project 'systemtests'
        files { files_testenv, '../testing/tests/systemtests/SYST_*.cpp' }
        includedirs { includedirs_test }
        defines { 'REQUIRE_PARAM' }
        links { 'cpputest' }

    --  run last to stop application in background
    project 'dstw_stop'
        files {
            '../testing/tests/systemtests/stopAppMain.cpp',
            '../testing/testenv/TCP/src/TCP_Client.cpp'
        }
        includedirs { includedirs_test }

    project 'gcovapp'
        filter { 'action:vs*' }

        filter { 'action:gmake*' }
            kind 'StaticLib'
            targetdir '../build/%{_TARGET_OS}/lib'
            includedirs { includedirs_test }
            files { files_app }
            buildoptions {'-fprofile-arcs -ftest-coverage' }

    project 'gcovtests'
        filter { 'action:vs*' }

        filter { 'action:gmake*' }
            files { files_testenv, files_moduletest }
            includedirs { includedirs_test }
            links { 'gcovapp', 'gcov', 'cpputest' }
            linkoptions { '--coverage' }
