## 参考csdn博客链接：[Linux平台Lua源码如何编译成so动态库文件 - 5.0.2](https://blog.csdn.net/weixin_41399433/article/details/80702932)
 * 不过按照该博客编译lua 5.3.5的源代码，还需要做一些修改，才能成功生成liblua.so文件。主要是他所说的config文件在lua 5.3.5的源代码中不存在，需要在lua-5.3.5/src/Makefile文件中
 件做对应修改。
### 1. lua源码下载路径:
[https://www.lua.org/ftp/](https://www.lua.org/ftp/)
// 下载 lua-5.3.5源代码
```shell
sudo wget https://www.lua.org/ftp/lua-5.3.5.tar.gz
sudo tar -zxvf lua-5.3.5.tar.gz
cd lua-5.3.5
```

### 2. 修改lua-5.3.5/src目录下的Makefile文件
#### (1).在 /src/Makefile 文件中, 加入如下字符：
```
LUA_SO=liblua.so
ALL_T= $(LUA_A) $(LUA_T) $(LUAC_T) $(LUA_SO)
$(LUA_SO): $(CORE_O) $(LIB_O)
  $(CC) -o $@ -shared $? -ldl -lm   #(注意前面空白部分是Tab符不是空格符)
```

#### (2)在 /src/Makefile 文件中,
在 lua-5.3.5/src/Makefile 文件中做如下修改, 
找到 MYCFLAGS=  ,追加-O2 -fPIC编译选项
即修改为：
```shell
MYCFLAGS= -O2 -fPIC
```

### 3. 配置lua-5.3.5目录下的 Makefile文件
在 lua-5.3.5/Makefile 文件中, 加入如下字符
```shell
TO_LIB= liblua.a liblua.so
```

### 4. 在源代码根目录下执行如下指令.
haha@ubuntu:~/Programming/software_sources/lua-5.3.5$ 
``` shell
sudo make clean
sudo make linux
sudo make install
```
### 5. 静态库liblua.a、动态库liblua.so文件产生在/usr/local/lib目录，如下所示：
haha@ubuntu:~/Programming/software_sources/lua-5.3.5$ sudo make install
```shell
cd src && mkdir -p /usr/local/bin /usr/local/include /usr/local/lib /usr/local/man/man1 /usr/local/share/lua/5.3 /usr/local/lib/lua/5.3
cd src && install -p -m 0755 lua luac /usr/local/bin
cd src && install -p -m 0644 lua.h luaconf.h lualib.h lauxlib.h lua.hpp /usr/local/include
cd src && install -p -m 0644 liblua.a  liblua.so /usr/local/lib
cd doc && install -p -m 0644 lua.1 luac.1 /usr/local/man/man1
```
