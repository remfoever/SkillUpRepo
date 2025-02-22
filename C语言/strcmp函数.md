# strcmp函数

`strcmp` 是 C 标准库中的一个函数，用于比较两个字符串。它的功能是按字典顺序逐个字符比较两个字符串，直到遇到不同的字符或字符串结束符（`\0`）。`strcmp` 是一个非常常用的函数，特别是在需要比较字符串内容时。

### 函数原型

```c
int strcmp(const char *str1, const char *str2);
```

### 参数说明

1. **`const char \*str1`**：
   - 第一个要比较的字符串。
2. **`const char \*str2`**：
   - 第二个要比较的字符串。

### 返回值

- **返回值 < 0**：`str1` 小于 `str2`（按字典顺序）。
- **返回值 = 0**：`str1` 等于 `str2`。
- **返回值 > 0**：`str1` 大于 `str2`（按字典顺序）。

### 使用示例

以下是一些使用 `strcmp` 的示例：

#### 示例 1：基本用法

```c
#include <stdio.h>
#include <string.h>

int main() {
    const char *str1 = "apple";
    const char *str2 = "banana";

    int result = strcmp(str1, str2);

    if (result < 0) {
        printf("%s is less than %s\n", str1, str2);
    } else if (result == 0) {
        printf("%s is equal to %s\n", str1, str2);
    } else {
        printf("%s is greater than %s\n", str1, str2);
    }

    return 0;
}
```

**输出**：

```c
apple is less than banana
```

**解释**：

- 字符串 `"apple"` 和 `"banana"` 按字典顺序比较，`"apple"` 小于 `"banana"`，因此返回值为负数。

------

#### 示例 2：比较相等的字符串

```c
#include <stdio.h>
#include <string.h>

int main() {
    const char *str1 = "hello";
    const char *str2 = "hello";

    int result = strcmp(str1, str2);

    if (result < 0) {
        printf("%s is less than %s\n", str1, str2);
    } else if (result == 0) {
        printf("%s is equal to %s\n", str1, str2);
    } else {
        printf("%s is greater than %s\n", str1, str2);
    }

    return 0;
}
```

**输出**：

```c
hello is equal to hello
```

**解释**：

- 字符串 `"hello"` 和 `"hello"` 完全相同，因此返回值为 0。

------

#### 示例 3：比较大小写不同的字符串

```c
#include <stdio.h>
#include <string.h>

int main() {
    const char *str1 = "Apple";
    const char *str2 = "apple";

    int result = strcmp(str1, str2);

    if (result < 0) {
        printf("%s is less than %s\n", str1, str2);
    } else if (result == 0) {
        printf("%s is equal to %s\n", str1, str2);
    } else {
        printf("%s is greater than %s\n", str1, str2);
    }

    return 0;
}
```

**输出**：

```c
Apple is less than apple
```

**解释**：

- 在 ASCII 编码中，大写字母的值小于小写字母，因此 `"Apple"` 小于 `"apple"`。

------

#### 示例 4：比较部分字符串

`strcmp` 会一直比较到字符串的结束符（`\0`）。如果需要比较部分字符串，可以使用 `strncmp` 函数。

```c
#include <stdio.h>
#include <string.h>

int main() {
    const char *str1 = "applepie";
    const char *str2 = "apple";

    int result = strcmp(str1, str2);

    if (result < 0) {
        printf("%s is less than %s\n", str1, str2);
    } else if (result == 0) {
        printf("%s is equal to %s\n", str1, str2);
    } else {
        printf("%s is greater than %s\n", str1, str2);
    }

    return 0;
}
```

**输出**：

```c
applepie is greater than apple
```

**解释**：

- 字符串 `"applepie"` 和 `"apple"` 的前 5 个字符相同，但 `"applepie"` 更长，因此 `"applepie"` 大于 `"apple"`。

------

### 注意事项

1. **区分大小写**：
   - `strcmp` 是区分大小写的。如果需要不区分大小写的比较，可以使用 `strcasecmp`（在 POSIX 标准中）或自己实现比较逻辑。
2. **字符串结束符**：
   - `strcmp` 会一直比较到字符串的结束符（`\0`）。如果字符串没有正确的结束符，可能会导致未定义行为。
3. **空指针**：
   - 如果传入的字符串指针为 `NULL`，会导致程序崩溃。在使用 `strcmp` 之前，应确保字符串指针有效。

------

### 总结

- `strcmp` 用于按字典顺序比较两个字符串。
- 返回值小于 0 表示 `str1` 小于 `str2`，等于 0 表示相等，大于 0 表示 `str1` 大于 `str2`。
- `strcmp` 是区分大小写的，且会一直比较到字符串的结束符。