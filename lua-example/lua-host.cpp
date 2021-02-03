extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#include "stdio.h"

const char * my_global = "JSP is string";



void PrintTable(lua_State *L)
{
    lua_pushnil(L);

    while(lua_next(L, -2) != 0)
    {
        if(lua_isstring(L, -1))
          printf("%s = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
        else if(lua_isnumber(L, -1))
          printf("%s = %f\n", lua_tostring(L, -2), lua_tonumber(L, -1));
        else if(lua_istable(L, -1))
          PrintTable(L);

        lua_pop(L, 1);
    }
}

int hello(lua_State *L) {
    printf("C++ says: Hello World\n");

    int argc = lua_gettop(L);

    for(int n=1; n<=argc; ++n)
	    printf("argument received - index: %d - value: %s\n", n, lua_tostring(L, n));

    lua_pushlightuserdata(L, (void *)my_global);

    return 1;
}


int hello2(lua_State *L) {

    printf("\nhello2:  is light user data: %d\n", lua_islightuserdata(L,0));
    const char *ptr = (const char *)lua_touserdata(L, 0);

    printf("Ptr is: %s\n\n", ptr);


  return 1;
}


int main(int argc, char ** argv){

    //iterate all files and execute
    for(int n=1; n<argc; n++){
        const char * file = argv[n];

        //create a new lua state
        lua_State * L = luaL_newstate();

        //open all libraries
        luaL_openlibs(L);

	//register new custom method
	lua_register(L, "hello", hello);
	lua_register(L, "hello2", hello2);

        int s = luaL_loadfile(L, file);

        if(!s)
            s = lua_pcall(L, 0, LUA_MULTRET, 0);

        //show any errors
        if(s){
            printf("Error: %s \n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }

        // Evaluate table
	lua_getglobal(L, "DefaultBehaviour");
	PrintTable(L);

	lua_getglobal(L, "entry");
//	lua_pushnumber(L, 1.0);
	lua_pushlightuserdata(L, &my_global);
        s = lua_pcall(L, 1, 0, 0);
        if(s){
            printf("Error: %s \n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }


        lua_close(L);
    }

    return 0;
}
