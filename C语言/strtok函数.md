# strtok 函数

`strtok` 是 C 标准库中的一个函数，用于将字符串分割成多个子字符串（**令牌**，tokens）。它通过指定的分隔符（delimiters）来分割字符串。`strtok` 是一个非常常用的函数，特别是在需要解析字符串（如 CSV 文件、命令行参数等）时。

### 函数原型

```
char *strtok(char *str, const char *delim);
```

### 参数说明

1. **`char \*str`**：
   - 要分割的字符串。在第一次调用时，传入待分割的字符串；后续调用传入 `NULL`，表示继续分割同一个字符串。
2. **`const char \*delim`**：
   - 分隔符字符串。`strtok` 会将 `delim` 中的每个字符都视为分隔符。

### 返回值

- 返回下一个分割出的子字符串（令牌）的指针。
- 如果没有更多的子字符串可分割，则返回 `NULL`。

### 使用示例

以下是一些使用 `strtok` 的示例：

#### 示例 1：基本用法

```
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "apple,banana,cherry";
    const char *delim = ",";

    // 第一次调用 strtok
    char *token = strtok(str, delim);

    while (token != NULL) {
        printf("Token: %s\n", token);
        // 后续调用 strtok，传入 NULL
        token = strtok(NULL, delim);
    }

    return 0;
}
```

**输出**：

```
Token: apple
Token: banana
Token: cherry
```

**解释**：

- 字符串 `"apple,banana,cherry"` 被 `,` 分割成三个子字符串。
- 第一次调用 `strtok` 时，传入待分割的字符串 `str`。
- 后续调用 `strtok` 时，传入 `NULL`，表示继续分割同一个字符串。

------

#### 示例 2：多个分隔符

```
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "apple;banana cherry,orange";
    const char *delim = " ;,"; // 分隔符可以是空格、分号或逗号

    char *token = strtok(str, delim);

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }

    return 0;
}
```

**输出**：

复制

```
Token: apple
Token: banana
Token: cherry
Token: orange
```

**解释**：

- 字符串 `"apple;banana cherry,orange"` 被 `;`、空格和 `,` 分割成四个子字符串。

------

#### 示例 3：处理连续分隔符

```
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "apple,,banana,,,cherry";
    const char *delim = ",";

    char *token = strtok(str, delim);

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }

    return 0;
}
```

**输出**：

```
Token: apple
Token: banana
Token: cherry
```

**解释**：

- 连续的分隔符（如 `,,` 或 `,,,`）会被视为一个分隔符，不会产生空字符串。

------

#### 示例 4：修改原始字符串

`strtok` 会修改原始字符串，将分隔符替换为 `\0`。因此，原始字符串会被破坏。

```
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "apple,banana,cherry";
    const char *delim = ",";

    char *token = strtok(str, delim);

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }

    // 原始字符串已被修改
    printf("Original string: %s\n", str);

    return 0;
}
```

**输出**：

```
Token: apple
Token: banana
Token: cherry
Original string: apple
```

**解释**：

- 原始字符串 `str` 被修改为 `"apple\0banana\0cherry"`，因此打印时只会显示 `"apple"`。

------

### 注意事项

1. **修改原始字符串**：
   - `strtok` 会修改原始字符串，将分隔符替换为 `\0`。如果需要保留原始字符串，可以先复制一份。
2. **线程安全问题**：
   - `strtok` 是不可重入的（not thread-safe），因为它使用静态缓冲区来存储状态。
   - 在多线程环境中，可以使用 `strtok_r`（POSIX 标准）代替 `strtok`。
3. **空令牌**：
   - 如果字符串以分隔符开头或包含连续的分隔符，`strtok` 会忽略它们，不会返回空字符串。
4. **结束条件**：
   - 当没有更多的子字符串可分割时，`strtok` 返回 `NULL`。

------

### 替代函数

- **`strtok_r`**：
  - 是 `strtok` 的可重入版本，适用于多线程环境。
  - 函数原型：`char *strtok_r(char *str, const char *delim, char **saveptr);`
- **`strsep`**：
  - 是另一个字符串分割函数，行为与 `strtok` 类似，但更灵活。
  - 函数原型：`char *strsep(char **stringp, const char *delim);`

------

### 总结

- `strtok` 用于将字符串按指定的分隔符分割成多个子字符串。
- 它会修改原始字符串，将分隔符替换为 `\0`。
- 适用于解析简单的字符串，但在多线程环境中需要使用 `strtok_r`。