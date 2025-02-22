# strncpy 函数

`strncpy` 是 C 标准库中的一个函数，用于将一个字符串的指定长度复制到另一个字符串中。它的功能类似于 `strcpy`，但可以指定最大复制长度，从而避免缓冲区溢出的问题。`strncpy` 是一个常用的函数，特别是在需要安全地复制字符串时。

### 函数原型

```c
char *strncpy(char *dest, const char *src, size_t n);
```

### 参数说明

1. **`char \*dest`**：
   - 目标字符串的指针，用于存储复制的内容。
2. **`const char \*src`**：
   - 源字符串的指针，提供要复制的内容。
3. **`size_t n`**：
   - 最大复制的字符数（包括结束符 `\0`）。

### 返回值

- 返回目标字符串的指针 `dest`。

### 使用示例

以下是一些使用 `strncpy` 的示例：

#### 示例 1：基本用法

```c
#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    strncpy(dest, src, sizeof(dest) - 1); // 复制最多 sizeof(dest) - 1 个字符
    dest[sizeof(dest) - 1] = '\0';       // 确保目标字符串以 \0 结尾

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}
```

**输出**：

```c
Source: Hello, World!
Destination: Hello, World!
```

**解释**：

- 将 `src` 的内容复制到 `dest` 中。
- `sizeof(dest) - 1` 确保不会超出 `dest` 的缓冲区大小。
- 手动添加 `\0` 以确保目标字符串正确终止。

------

#### 示例 2：复制部分字符串

```c
#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Hello, World!";
    char dest[10];

    strncpy(dest, src, 5); // 只复制前 5 个字符
    dest[5] = '\0';        // 手动添加结束符

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}
```

**输出**：

```c
Source: Hello, World!
Destination: Hello
```

**解释**：

- 只复制 `src` 的前 5 个字符到 `dest` 中。
- 手动添加 `\0` 以确保目标字符串正确终止。

------

#### 示例 3：目标缓冲区较小

```c
#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Hello, World!";
    char dest[5];

    strncpy(dest, src, sizeof(dest) - 1); // 复制最多 sizeof(dest) - 1 个字符
    dest[sizeof(dest) - 1] = '\0';       // 确保目标字符串以 \0 结尾

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}
```

**输出**：

```c
Source: Hello, World!
Destination: Hell
```

**解释**：

- `dest` 的大小为 5，因此最多只能复制 4 个字符（留一个位置给 `\0`）。
- 手动添加 `\0` 以确保目标字符串正确终止。

------

#### 示例 4：源字符串较短

```c
#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Hi";
    char dest[10];

    strncpy(dest, src, sizeof(dest) - 1); // 复制最多 sizeof(dest) - 1 个字符
    dest[sizeof(dest) - 1] = '\0';       // 确保目标字符串以 \0 结尾

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}
```

**输出**：

```c
Source: Hi
Destination: Hi
```

**解释**：

- `src` 的长度小于 `dest` 的大小，因此 `strncpy` 会复制整个 `src` 并在后面填充 `\0`。

------

### 注意事项

1. **目标缓冲区大小**：
   - `strncpy` 不会自动在目标字符串的末尾添加 `\0`，如果复制的字符数达到 `n`，则目标字符串可能不以 `\0` 结尾。
   - 因此，通常需要手动添加 `\0` 以确保字符串正确终止。
2. **填充 `\0`**：
   - 如果 `src` 的长度小于 `n`，`strncpy` 会在 `dest` 的剩余部分填充 `\0`，直到总共写入 `n` 个字符。
3. **性能问题**：
   - 如果 `n` 远大于 `src` 的长度，`strncpy` 会填充大量 `\0`，这可能导致性能问题。
4. **替代函数**：
   - 如果需要更安全的字符串复制，可以考虑使用 `snprintf` 或 `strlcpy`（如果可用）。

------

### 总结

- `strncpy` 用于将源字符串的指定长度复制到目标字符串中。
- 需要手动确保目标字符串以 `\0` 结尾。
- 适用于需要控制复制长度以避免缓冲区溢出的场景。