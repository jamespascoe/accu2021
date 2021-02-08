#include <iostream>
#include "lua.hpp"

int cppFunc(lua_State *L) {
  std::cout << "cppFunc called with args:" << std::endl;

  for (int n=1; n <= lua_gettop(L); ++n)
    std::cout << lua_tostring(L, n) << std::endl;

  return 0;
}

int main([[maybe_unused]] int argc, char ** argv)
{
  // Create a new lua state
  lua_State *L = luaL_newstate();

  // Open all libraries
  luaL_openlibs(L);

  // export a C++ function to Lua
  lua_register(L, "cppFunc", cppFunc);

  // Load and run the Lua file
  luaL_loadfile(L, argv[1]);
  lua_pcall(L, 0, 0, 0);

  // Call 'f' with the arguments "how", t.x, 14
  lua_getglobal(L, "f");     /* function to be called */
  lua_pushliteral(L, "how"); /* 1st argument */
  lua_getglobal(L, "t");     /* table to be indexed */
  lua_getfield(L, -1, "x");  /* push t.x (2nd arg) */
  lua_remove(L, -2);         /* remove 't' from the stack */
  lua_pushinteger(L, 14);    /* 3rd argument */
  lua_call(L, 3, 1);         /* call 'f' (3 args, 1 res) */

  lua_close(L);
}
