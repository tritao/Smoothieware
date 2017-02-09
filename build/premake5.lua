-- This is the starting point of the build scripts for the project.
-- It defines the common build settings that all the projects share
-- and calls the build scripts of all the sub-projects.

builddir = path.getabsolute("./" .. _ACTION);
if _ARGS[1] then
    builddir = path.getabsolute("./" .. _ARGS[1]);
end

workspace "Smoothieware"

  configurations { "Debug", "Release" }
  platforms { "x64" }
  symbols  "On"
  
  location (builddir)
  objdir (path.join(builddir, "obj", "%{cfg.buildcfg}_%{cfg.platform}"))
  targetdir (path.join(builddir, "lib", "%{cfg.buildcfg}_%{cfg.platform}"))

  project "Smoothieware"
    kind "ConsoleApp"
    language "C++"

    local smdefines =
    {
      "__GITVERSIONSTRING__=\"edge\"",
      "SIM",
      "MRI_ENABLE=0",
      "__INLINE=inline",
      "__STATIC_INLINE=inline",
      "DEFAULT_SERIAL_BAUD_RATE=9600",
      "CHECKSUM_USE_CPP",
      "NONETWORK",
      "DISABLESD",
      "DISABLEMSD",
      "DISABLEUSB",
      "NO_TOOLS_ENDSTOPS",
      "NO_TOOLS_SWITCH",
      "NO_TOOLS_EXTRUDER",
      "NO_TOOLS_LASER",
      "NO_TOOLS_SPINDLE",
      "NO_UTILS_PANEL",
      "NO_TOOLS_ZPROBE",
      "NO_TOOLS_SCARACAL",
      "NO_TOOLS_ROTARYDELTACALIBRATION",
      "NO_TOOLS_TEMPERATURECONTROL",
      "NO_TOOLS_TEMPERATURESWITCH",
      "NO_TOOLS_DRILLINGCYCLES",
      "NO_TOOLS_FILAMENTDETECTOR",
      "NO_UTILS_MOTORDRIVERCONTROL"
    }

    defines { smdefines }

    files
    {
      "../src/libs/**",
      "../src/modules/communication/**",
      "../src/modules/robot/**",
      "../src/modules/utils/configurator/**",
      "../src/modules/utils/simpleshell/**",
      "../src/version.cpp",
      "../src/main.cpp",
      "../src/sim/**",
      "../mbed/src/cpp/FileBase.*",
      "../mbed/src/cpp/FileHandle.*",
      "../mbed/src/cpp/FileLike.*",
      "../mbed/src/cpp/FileSystemLike.*",
      "../mbed/src/cpp/FunctionPointer.*",
      "../mbed/src/cpp/Stream.*"
    }

    excludes
    {
      "../src/libs/Watchdog*",
      "../src/libs/ADC/**",
      "../src/libs/ChaNFS/**",
      "../src/libs/ConfigSources/Firm**",
      "../src/libs/MRI_Hooks.*",
      "../src/libs/LPC17xx/**",
      "../src/libs/Network/**",
      "../src/libs/USBDevice/**",
    }

    local includes =
    {
      "../src/sim",
      "../mbed/src/capi",
      "../mbed/src/cpp",
      "../mbed/src/vendor/NXP/capi/LPC1768",
      "../mbed/src/vendor/NXP/cmsis/LPC1768",
      "../mri",
      "../src",
      "../src/libs",
      "../src/libs/ChaNFS",
      "../src/libs/ConfigSources",
      "../src/libs/LPC17xx/LPC17xxLib/inc",
      "../src/libs/USBDevice/USBMSD",
      "../src/modules/communication",
      "../src/modules/communication/utils",
      "../src/modules/tools/endstops",
      "../src/modules/tools/extruder",
      "../src/modules/tools/filamentdetector",
      "../src/modules/tools/rotarydeltacalibration",
      "../src/modules/tools/spindle",
      "../src/modules/tools/spindle/Modbus",
      "../src/modules/tools/spindle/SoftSerial",
      "../src/modules/tools/switch",
      "../src/modules/tools/temperaturecontrol",
      "../src/modules/tools/temperatureswitch",
      "../src/modules/tools/toolmanager",
      "../src/modules/robot",
      "../src/modules/robot/arm_solutions",
      "../src/modules/utils/configurator",
      "../src/modules/utils/motordrivercontrol",
      "../src/modules/utils/simpleshell",
    }

    includedirs
    {
      includes,
      "../src/libs/Network/uip",
      "../src/libs/Network/uip/uip",
      "../src/libs/Network/uip/unix",
      "../src/libs/Network/uip/apps/webserver"
    }

    filter "system:windows"
      buildoptions "/wd4200 /wd4244 /wd4267 /wd4302 /wd4305 /wd4311 /wd4312 /wd4838 /wd4996"
      --prebuildcommands { "..\\..\\src\\generate-version.bat" }

    filter "not system:windows"

      --prebuildcommands { "../../src/generate-version.sh" }

    filter {}

  project "Smoothieware.Tests"
    kind "ConsoleApp"
    language "C++"

    defines { smdefines }

    files
    {
      "../src/testframework/**.cpp",
      "../src/testframework/**.h",
    }

    includedirs
    {
      includes,
      "../src/testframework"
    }

    links { "Smoothieware" }

    filter "system:windows"
      buildoptions "/wd4244 /wd4267 /wd4312 /wd4996"

