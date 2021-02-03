#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <iostream>

int main(int argc, char ** argv)
{
  // Create a new lua state
  lua_State *L = luaL_newstate();

  // Open all libraries
  luaL_openlibs(L);

  // Load and run the Lua file
  luaL_loadfile(L, argv[1]);
  lua_pcall(L, 0, LUA_MULTRET, 0);

  lua_getglobal(L, "f");     /* function to be called */
  lua_pushliteral(L, "how"); /* 1st argument */
  lua_getglobal(L, "t");     /* table to be indexed */
  lua_getfield(L, -1, "x");  /* push t.x (2nd arg) */
  lua_remove(L, -2);         /* remove 't' from the stack */
  lua_pushinteger(L, 14);    /* 3rd argument */
  lua_call(L, 3, 1);         /* call 'f' (3 args, 1 result) */
  lua_setglobal(L, "a");     /* set global 'a' */

  lua_close(L);
}
