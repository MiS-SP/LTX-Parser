#include <luajit-2.1/lua.hpp>
#include "xr_ini_file.h"

extern "C"
{
    static void l_push(lua_State *L, xray_re::xr_ini_file *ltx)
    {
        xray_re::xr_ini_file **ptr = (xray_re::xr_ini_file **)lua_newuserdata(L, sizeof(xray_re::xr_ini_file *));
        *ptr = ltx;

        luaL_getmetatable(L, "LtxMeta");
        lua_setmetatable(L, -2);
    }

    static int l_new(lua_State *L)
    {
        const char *path = luaL_checkstring(L, 1);
        if (lua_isstring(L, 2))
        {
            const char *name = luaL_checkstring(L, 2);
            xray_re::xr_ini_file *ltx = new xray_re::xr_ini_file(path, name);
            l_push(L, ltx);
        }
        else
        {
            xray_re::xr_ini_file *ltx = new xray_re::xr_ini_file(path);
            l_push(L, ltx);
        }

        return 1;
    }

    static xray_re::xr_ini_file *l_is_ltx(lua_State *L, int ud)
    {
        void *ptr = luaL_checkudata(L, ud, "LtxMeta");
        xray_re::xr_ini_file *ltx = (xray_re::xr_ini_file *)ptr;

        return ltx;
    }

    static int l_load(lua_State *L)
    {
        xray_re::xr_ini_file *ltx = l_is_ltx(L, 1);
        const char *path = luaL_checkstring(L, 2);
        const char *name = luaL_checkstring(L, 3);
        bool status = ltx->load(name);
        return 1;
    }

    static int l_gc(lua_State *L)
    {
        xray_re::xr_ini_file *ltx = l_is_ltx(L, 1);
        delete ltx;
        return 0;
    }

    static const luaL_Reg ltx_lib[] = {
        {"new", l_new},
        {NULL, NULL}};

    static const luaL_Reg ltx_methods[] = {
        {"load", l_load},
        {"__gc", l_gc},
        {NULL, NULL}};

    int luaopen_ltx(lua_State *L)
    {
        luaL_newmetatable(L, "LtxMeta");
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        luaL_register(L, NULL, ltx_methods);

        luaL_register(L, "ltx", ltx_lib);

        return 1;
    }
}