# Issue

Собираю так
```bash
g++ -shared -fPIC -o ltx.so ltx.cpp -I/usr/include/lua5.1 /usr/lib/libluajit-5.1.so
```

```lua
    -- Закидываю ltx.so в папку libs в проекте
    local ltx = require('libs.ltx')
    -- получаю это:
    --   luajit: error loading module 'libs.ltx' from file './libs/ltx.so':
    --      ./libs/ltx.so: undefined symbol: _ZTIN7xray_re9xr_readerE
    --   stack traceback:
    --      [C]: at 0x7fb07a1b8f60
    --      [C]: in function 'require'
    --      ./mcli.lua:40: in function <./mcli.lua:39>
    --      ./mcli.lua:67: in main chunk
    --      [C]: at 0x55755d49d0d0

        
    -- Такая проблема возникает если я в .h файле объявлю метод класса например 
    -- xr_writer *xr_file_system::w_open(const char *path, const char *name) const
    -- и напишу реализацию этого метода в .cxx, но include в файле где мне этот метод понадобится пропишу .h файл а не .cxx то получу ошибку по undefined symbol по этому методу


    -- что делать?

```
