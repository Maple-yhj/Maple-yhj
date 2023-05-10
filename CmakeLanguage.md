# CMakeLanguage

#### 1、基础设置

```cmake
cmake_minimum_required(VERSION X.XX) #设置cmake的最低要求版本
project(project_name) #设置项目名称
set(C_STANDARD 11)  #设置使用c++11的标准
```

#### 2、Cmake中提供的预定义变量

可以通过set修改以下预定义变量的值

`CMAKE_BINARY_DIR`：生成二进制文件的根目录。

`CMAKE_CURRENT_BINARY_DIR`：当前处理的二进制文件目录。

`CMAKE_CURRENT_SOURCE_DIR`：当前处理的源文件目录。

`CMAKE_MODULE_PATH`：查找CMake模块的路径。

`CMAKE_SOURCE_DIR`：项目根目录的路径。

`CMAKE_CURRENT_LIST_FILE`：当前处理的CMakeLists.txt文件的完整路径。

`CMAKE_CURRENT_LIST_DIR`：当前处理的CMakeLists.txt文件所在目录的完整路径。

`CMAKE_INSTALL_PREFIX`：在安装时使用的路径前缀。

`CMAKE_C_COMPILER`：使用的C编译器。

`CMAKE_C_FLAGS`：当前编译器使用的C标志。

`CMAKE_C_FLAGS_DEBUG`：编译调试版本时的C标志。

`CMAKE_C_FLAGS_RELEASE`：编译发布版本时的C标志。

`CMAKE_CXX_COMPILER`：使用的C++编译器。

`CMAKE_CXX_FLAGS`：当前编译器使用的C++标志。

`CMAKE_CXX_FLAGS_DEBUG`：编译调试版本时的C++标志。

`CMAKE_CXX_FLAGS_RELEASE`：编译发布版本时的C++标志。

`CMAKE_RUNTIME_OUTPUT_DIRECTORY`: 用于指定可执行文件的输出目录。 

`CMAKE_ARCHIVE_OUTPUT_DIRECTORY`: 用于指定静态库的输出目录。 

`CMAKE_OBJECT_PATH_MAX`: 用于指定对象文件存放的最大目录深度限制。 

#### 3、命令集

##### a、 include_directories()

用于向项目添加包含文件目录，该目录将在编译器中使用`.h`文件时进行搜索 

```cmake
include_directories(dir1 dir2 ...)
```

##### b、file()

主要用来读取或修改文件系统中的文件，并将其存储为CMake变量 

- `file(READ filename variable)`：将文件的内容读取到变量中。
- `file(WRITE filename content)`：将指定的内容写入文件。
- `file(APPEND filename content)`：将指定的内容追加到文件的末尾。
- `file(MAKE_DIRECTORY directory)`：创建目录。
- `file(RENAME oldname newname)`：将一个文件或目录重命名。
- `file(GLOB variable file)`： 搜索指定目录下符合特定模式的文件，并将文件列表存储到变量中 
- `file(REMOVE path)`：删除文件或目录。
- `file(RELATIVE_PATH variable directory file)`：将文件的相对路径存储到变量中。
- `file(TO_CMAKE_PATH path result)`：将路径转换为相应的CMake路径。在Windows平台上，它将反斜杠转换为正斜杠。
- `file(TO_NATIVE_PATH path result)`：将路径转换为本机路径。在Windows平台上，它将正斜杠转换为反斜杠。

##### c、 aux_source_directory() 

 用于查找指定目录下的所有源文件，并将其保存到一个变量中 

```cmake
aux_source_directory(<dir> <variable>)
```

##### d、target_compile_options()

用于为给定的目标添加编译选项。

`target_compile_options()`指令后接目标名称以及带有关联编译选项的命令参数列表。`target_compile_options()`指令还可以接受可选的`PUBLIC`、`PRIVATE`和`INTERFACE`关键字，以便在目标和它的链接库之间传递编译选项。具体来说:

- `PUBLIC`表示该编译选项将被目标、链接到该目标的任何其他目标以及使用该目标的任何目标所使用。
- `PRIVATE`表示该编译选项仅适用于目标。
- `INTERFACE`表示该编译选项将被使用该目标的任何目标使用，但不应该应用于目标本身。

```cmake
target_compile_options([target name] [PUBLIC\PRIVATE\INTERFACE] [compile option])
```

##### e、 add_executable() 

 用于创建一个可执行文件，并将源文件添加到该可执行文件中 

```cmake
add_executable(<name> <source>...)
```

其中`<name>`表示可执行文件的昵称，`<source>` 表示需要编译的源文件列表 

##### f、add_library()

用于创建一个库文件，并将源文件添加到该库中

```cmake
add_library(<name> [STATIC | SHARED | MODULE] <source>...)
```

其中，`<name>`代表生成的库文件的名称，`[STATIC | SHARED | MODULE]`则用于指定库的类型，分别表示静态库、动态库、模块库，`<source>`代表源文件列表

##### g、install()

 用于将生成的文件或目录复制到指定的安装目录中 。 这个命令有两个主要的参数：文件或目录列表和安装目录。 

```cmake
install(TARGETS <target> DESTINATION <destination>)
install(FILES <file1> <file2> ... DESTINATION <destination>)
install(DIRECTORY <dir1> <dir2> ... DESTINATION <destination>)
```

- `TARGETS` 参数用于指定要安装的目标，通常是一个可执行文件或一个库。`DESTINATION` 参数用于指定安装目录的路径 
- `FILES` 参数用于指定要安装的文件列表。`DESTINATION` 参数用于指定安装目录的路径。
- `DIRECTORY` 参数用于指定要安装的目录列表。`DESTINATION` 参数用于指定安装目录的路径。