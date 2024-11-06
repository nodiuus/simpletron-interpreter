
local function cutoff(path)
   local folder = path:match("([^/]+)$")
   local trimmed_str = folder:match("^%s*(.-)%s*$")
   return tostring(trimmed_str)
end    

local handle = io.popen("pwd")
local current_dir = handle:read("*a")
handle:close()

local worksapce_name = cutoff(current_dir)
local project_name = cutoff(current_dir) .. "_"


workspace(tostring(workspace_name))
   configurations { "Debug", "Release" }

project(project_name)
   kind "ConsoleApp"
   language "C++"
   --cppdialect "C++latest"
   buildoptions "-Wall -Wextra -pedantic -fPIC -std=c++23"
   targetdir "bin"
   objdir "obj"

   files { "src/**.h", "src/**.cpp", "src/VM/**.cpp", "src/lexer/**.cpp", "src/parser/**.cpp", "src/code_generation/**.cpp" }
    
    includedirs {
        "include/VM",
        "include/lexer",
        "include/parser",
        "include/code_generation"
    }

    files {
        "include/VM/**.cpp",
        "include/VM/**.h",
        "include/lexer/**.cpp",
        "include/lexer/**.h",
        "include/parser/**.cpp",
        "include/parser/**.h",
        "include/code_generation/**.cpp",
        "include/code_generation/**.h"
    }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

newaction {
   trigger     = "clangd",
   description = "Generate compile_commands.json for clangd",
   execute     = function ()
      os.execute("premake5 gmake2")  -- or any other generator
      print("executing...")
      os.execute("bear -- make VERBOSE=0")
      print("done")
   end
}

--this is where the real shit begins, kid
os.execute("mkdir src")
if not os.isfile("./src/entry.cpp") then
    print("Creating entry.cpp")
    os.execute("cp -r ~/Projects/C++/entry.cpp src/")
end
