-- A solution contains projects, and defines the available configurations
solution "CSignals"
   configurations { "Debug", "Release" }
   location "build"
 
   -- A project defines one build target
   project "signals"
      location "build"
      kind "ConsoleApp"
      language "C"
      files { "*.h", "*.c" }
      --excludes { "vector_template.*" }
--      libdirs { }
      targetdir "build"
  
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
 
      configuration { "linux", "gmake" }
         buildoptions { "-ansi", "-pedantic-errors" }