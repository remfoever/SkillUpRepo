# **基于系统滴答数（tick）实现一个简单的节流机制**

```c
// 将时钟节拍数转换为毫秒（假设 configTICK_RATE_HZ 为 1000）
    unsigned long long curTick = (unsigned long long)tickCount * (1000 / configTICK_RATE_HZ);
    static unsigned long long lastDisplayTick = 0;
    wx_debug("curTick:%llu, lastDisplayTick:%llu", curTick, lastDisplayTick);
    if (curTick > lastDisplayTick) {
        if (curTick - lastDisplayTick < 100) {
            return;
        }
    }
    else {
        if (lastDisplayTick - curTick < 100) {
            return;
        }
    }
    lastDisplayTick = curTick;
```

这段代码的作用是**基于系统滴答数（tick）实现一个简单的节流机制**，避免某些操作（如调试信息输出）过于频繁地执行。以下是代码的详细解释：

------

### 代码逻辑分析

1. **将滴答数转换为毫秒**：

   ```c
   unsigned long long curTick = (unsigned long long)tickCount * (1000 / configTICK_RATE_HZ);
   ```

   - `tickCount` 是当前的系统滴答数。
   - `configTICK_RATE_HZ` 是 FreeRTOS 的系统时钟频率（例如 1000 Hz，表示每秒 1000 个 tick）。
   - `1000 / configTICK_RATE_HZ` 将 tick 转换为毫秒（ms）。
   - `curTick` 表示当前的系统时间（以毫秒为单位）。

2. **静态变量 `lastDisplayTick`**：

   ```c
   static unsigned long long lastDisplayTick = 0;
   ```

   - `lastDisplayTick` 是一个静态变量，用于记录上一次操作的时间（以毫秒为单位）。
   - 静态变量会在函数调用之间保持其值，因此可以用于记录历史状态。

3. **调试信息输出**：

   ```c
   wx_debug("curTick:%llu, lastDisplayTick:%llu", curTick, lastDisplayTick);
   ```

   - 输出当前的 `curTick` 和 `lastDisplayTick` 的值，用于调试。

4. **节流逻辑**：

   ```c
   if (curTick > lastDisplayTick) {
       if (curTick - lastDisplayTick < 100) {
           return;
       }
   }
   else {
       if (lastDisplayTick - curTick < 100) {
           return;
       }
   }
   ```

   - **目的**：确保两次操作之间的时间间隔至少为 100 毫秒。
   - **逻辑**：
     - 如果 `curTick` 大于 `lastDisplayTick`，检查两者差值是否小于 100 毫秒。如果是，则直接返回，不执行后续操作。
     - 如果 `curTick` 小于 `lastDisplayTick`（可能由于系统滴答数溢出），检查两者差值是否小于 100 毫秒。如果是，则直接返回。
     - 如果时间间隔大于或等于 100 毫秒，则继续执行后续操作。

5. **更新 `lastDisplayTick`**：

   ```c
   lastDisplayTick = curTick;
   ```

   - 更新 `lastDisplayTick` 为当前的 `curTick`，以便下一次调用时使用。

------

### 代码的作用

这段代码的核心目的是**限制某些操作的执行频率**。例如：

- 如果这段代码用于调试信息输出，可以避免在短时间内输出大量日志，从而减少资源占用。
- 如果用于事件触发，可以防止事件过于频繁地触发。

------

### 示例场景

假设 `configTICK_RATE_HZ` 为 1000（即 1 tick = 1 毫秒），以下是一个可能的执行过程：

1. 第一次调用时：
   - `curTick = 500`（假设当前时间为 500 毫秒）。
   - `lastDisplayTick = 0`（初始值）。
   - 时间差为 `500 - 0 = 500` 毫秒，大于 100 毫秒，因此执行后续操作。
   - 更新 `lastDisplayTick = 500`。
2. 第二次调用时：
   - `curTick = 550`（当前时间为 550 毫秒）。
   - `lastDisplayTick = 500`。
   - 时间差为 `550 - 500 = 50` 毫秒，小于 100 毫秒，因此直接返回。
3. 第三次调用时：
   - `curTick = 650`（当前时间为 650 毫秒）。
   - `lastDisplayTick = 500`。
   - 时间差为 `650 - 500 = 150` 毫秒，大于 100 毫秒，因此执行后续操作。
   - 更新 `lastDisplayTick = 650`。

------

### 总结

这段代码的主要功能是：

1. 将系统滴答数转换为毫秒。
2. 通过比较当前时间和上一次操作时间，限制操作的执行频率（至少间隔 100 毫秒）。
3. 适用于需要节流的场景，如调试信息输出、事件触发等。

如果 `configTICK_RATE_HZ` 不是 1000，需要根据实际值调整转换公式。





```c
    // 判断是否需要显示图片，因为传感搬数的比较快，HDMI处理比较慢，这里需要流控一下
    TickType_t tickCount = xTaskGetTickCount();
    UINT64 curTick = (unsigned long long)tickCount * (1000 / configTICK_RATE_HZ);
    static UINT64 lastDisplayTick = 0;
    /* 距离上次经过了多久 */
    UINT64 diffTick = WX_ABS(curTick, lastDisplayTick);
    /* 如果距离上次经过的时间大于50ms并且当前的图片和上次的图片地址不一样，则显示图像 */
    if (diffTick < 30 || lastDisplayPictureAddr == addrA) {
        return;
    }
    wx_debug("curTick:%llu, lastDisplayTick:%llu, %llu, addrIdxA=%u", curTick, lastDisplayTick,
             diffTick, addrIdxA);
    // 计算中心点
    // 显示该图片
    WxCameraPicture picture = {.frame = this->hdmiout.framePtr[addrIdxA]};
    WX_Camera_SetPictureInfo(this, &picture, (UINT16 *)addrA, frame);
    UINT32 ret = WX_Camera_DmaPic2HdmiDdr(this, &picture);
    if (ret != WX_SUCCESS) {
        wx_fail_code_cnt(ret);
        wx_critical("Error Exit: WX_Camera_DmaPic2HdmiDdr fail(%u)", ret);
        return;
    }
    WX_Camera_HdmioutPic(this, addrIdxA);
    lastDisplayPictureAddr = addrA;
    lastDisplayTick = curTick;
```

























