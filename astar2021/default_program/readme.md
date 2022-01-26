
windows 编译：

1，CMake
下载地址：https://cmake.org/download/
下载zip版本“cmake-3.xx-win64-x64.zip”，下载完成解压到指定目录并添加bin所在目录到环境变量。
在终端输入“cmake --help”或 “cmake --version”查看是否配置成功。

2，MinGW-w64
下载地址：https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/
推荐下载 离线版本“x86_64-posix-seh”
将下载文件解压到指定目录并将bin目录加入到环境变量， 例如C:\Program Files\mingw64\bin
将mingw64\bin目录下的“mingw32-make.exe”复制一份并改名为 “make.exe”，就可以在终端直接使用 “make”指令而不必使用“mingw32-make”指令。
在终端输入 “gcc -v”（或输入“make -v”查看版本信息），看到输出含以下信息，表示MinGW配置成功：

3，执行 sh build_win.sh
