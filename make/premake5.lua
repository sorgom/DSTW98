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

includedirs_testenv = {
    '../testing/testenv',
    includedirs_cpputest,
    includedirs_teststeps
}

files_testenv = {
    '../testing/testenv/**.cpp',
    base_teststeps .. '/src/*.cpp'
}

files_testmain = { '../testing/testmain/testMain.cpp' }

-- leads to test env IL interface
includedirs_test = {
    includedirs_testenv,
    includedirs_app
}

-- leads to application IL interface
includedirs_test_IL = {
    includedirs_app,
    includedirs_testenv
}

files_moduletest = { '../testing/tests/moduletests/**.cpp' }

--  ============================================================
--  premake5 build rules
--  ============================================================

workspace 'DSTW'
    configurations { 'ci', 'debug', 'memleak', 'bullseye', 'fail' }
    language 'C++'
    targetdir '../build/%{_TARGET_OS}'
    objdir  '../build/%{_TARGET_OS}/obj'
    kind 'ConsoleApp'
    libdirs { '../build/%{_TARGET_OS}/lib/%{cfg.name}' }
    defines {
        'CAPACITY=20',
        'CPPUTEST_USE_LONG_LONG=0',
        'CPPUTEST_MEM_LEAK_DETECTION_DISABLED'
    }

    filter { 'kind:ConsoleApp' }
        targetdir '../build/%{_TARGET_OS}/%{cfg.name}'

    filter { 'kind:StaticLib' }
        targetdir '../build/%{_TARGET_OS}/lib/%{cfg.name}'

    filter { 'action:vs*' }
        buildoptions { buildoptions_vs_test }
        warnings 'high'
        defines { '_WINSOCK_DEPRECATED_NO_WARNINGS' }

    filter { 'action:gmake*' }
        buildoptions { buildoptions_gcc }

    filter { 'kind:ConsoleApp', 'action:vs*',  }
        links { 'winmm', 'ws2_32' }

    filter { 'kind:ConsoleApp', 'action:gmake*' }
        linkoptions { '-pthread' }

    filter { 'configurations:ci' }
        filter { 'configurations:ci' }
        defines { 'NDEBUG' }

    filter { 'configurations:memleak' }
        defines { 'NDEBUG' }

    filter { 'configurations:bullseye' }
        defines { 'NDEBUG' }

    filter { 'configurations:debug' }
        defines { 'DEBUG' }
        symbols 'On'

    filter { 'configurations:fail' }
        defines { 'STATIC_FAIL' }

    --  ============================================================
    --  testenv
    --  ============================================================
    project 'testenv'
        kind 'StaticLib'

        includedirs { includedirs_test }
        files {
            files_testenv,
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
        files { files_app, files_moduletest, files_testmain }
        includedirs { includedirs_test }
        links { 'testenv' }

    project 'moduletestsIL'
        files { files_app, '../testing/tests/moduletestsIL/*.cpp', files_testmain }
        includedirs { includedirs_test_IL }
        links { 'testenv' }

    project 'devtests'
        files { files_app, '../testing/tests/devtests/*.cpp', files_testmain }
        includedirs { includedirs_test, '../devel' }
        links { 'testenv' }

    project 'buildfail'
        filter { 'configurations:*'}
        filter { 'configurations:fail' }
            kind 'StaticLib'
            files { '../testing/tests/buildfail/*.cpp' }
            includedirs { includedirs_app }

    project 'memleak'
        filter { 'configurations:*'}
        filter { 'configurations:memleak' }
            files { '../testing/tests/memleak/memLeakMain.cpp' }
            includedirs { includedirs_app }


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
        files { '../testing/tests/systemtests/SYST_*.cpp', files_testmain }
        includedirs { includedirs_test }
        defines { 'REQUIRE_PARAM' }
        links { 'testenv' }

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
            includedirs { includedirs_test }
            files { files_app }
            buildoptions {'-fprofile-arcs -ftest-coverage' }

    project 'gcovtests'
        filter { 'action:vs*' }

        filter { 'action:gmake*' }
            files { files_testenv, files_moduletest, files_testmain }
            includedirs { includedirs_test }
            links { 'gcovapp', 'gcov', 'testenv' }
            linkoptions { '--coverage' }
