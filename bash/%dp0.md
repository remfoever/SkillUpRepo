# %dp0用法

在批处理文件中，`%~dp0` 是一个特殊的语法，用于获取当前批处理文件所在的目录路径。具体来说：

- `%0` 表示当前批处理文件本身的路径（包括文件名）。
- `%~dp0` 是对 `%0` 的扩展：
  - `d` 表示驱动器（Drive）。
  - `p` 表示路径（Path）。
  - `0` 表示当前批处理文件。

因此，`%~dp0` 会返回当前批处理文件所在的完整目录路径（以反斜杠 `\` 结尾）。

### 举个例子：

假设您的批处理文件路径是：

复制

```
D:\Projects\Vitis\build_script.bat
```

那么：

- `%0` 的值是 `D:\Projects\Vitis\build_script.bat`。
- `%~dp0` 的值是 `D:\Projects\Vitis\`。

### 为什么 `set work_space_dir=%~dp0` 是当前目录？

因为 `%~dp0` 返回的是批处理文件所在的目录路径，所以 `set work_space_dir=%~dp0` 会将 `work_space_dir` 变量设置为当前批处理文件所在的目录路径。

### 示例代码：

```batch
@echo off
set work_space_dir=%~dp0
echo The current script directory is: %work_space_dir%
pause
```

运行结果：

```batch
The current script directory is: D:\Projects\Vitis\
```

### 注意事项：

1. `%~dp0` 返回的路径以反斜杠 `\` 结尾，因此可以直接用于拼接其他路径。
2. 如果批处理文件位于根目录（如 `C:\script.bat`），`%~dp0` 会返回 `C:\`。
3. 如果批处理文件位于网络路径或 UNC 路径（如 `\\server\share\script.bat`），`%~dp0` 会返回 `\\server\share\`。