#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <iostream>

int cppFunc(lua_State *L) {
  std::cout << "cppFunc called with args:" << std::endl;

  for (int n=1; n <= lua_gettop(L); ++n)
    std::cout << lua_tostring(L, n) << std::endl;

  return 0;
}

int cppFunc2(std::string str, int a, int b) {
  std::cout << "cppFunc2 called with args: " <<
    str << " " << a << " " << b << std::endl;

  return 0;
}

int main([[maybe_unused]] int argc, char ** argv)
{
  // Create a new lua state and open libraries
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::string);

  // Export a C++ function to Lua
  lua["cppFunc"] = cppFunc2;

  // Load and run the Lua file
  lua.script_file(argv[1]);

  // Call 'f' with the arguments "how", t.x, 14
  sol::function f = lua["f"];
  f("how", lua["t"]["x"], 14);
}
