# SPI Interface

![image-20250320165844078](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250320165844078.png)

![image-20250320165927547](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250320165927547.png)

![image-20250320165952044](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250320165952044.png)

![image-20250320170702153](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250320170702153.png)

![image-20250320170932403](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250320170932403.png)

![image-20250320170945667](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250320170945667.png)

```mermaid
graph TD
    A[SPI] --> B[Perform abort and reset]
    B --> C[Disable controller]
    C --> D[Clear RX FIFO, drop the data]
    D --> E[Clear mode fault condition]
    E --> F[Enable the mode fail generation]
    F --> G[Perform a self test]
    G --> H{If interrupt based?}
    H -- Yes --> I[Setup an interrupt system]
    H -- No --> J[Set options]
    J --> K[Set device as SPI master]
    K --> L[Force slave select]
    L --> M[Set the baud rate prescaler value]
    M --> N[Assert slave select flash chip pin]
    N --> O[Perform flash erase]
    O --> P[Write data into the flash]
    P --> Q[Read back the data from flash]
    Q --> R[Verify data]
    R --> S[Disable interrupt system]
    S --> T[END]
```

![image-20250320172935906](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250320172935906.png)



![image-20250320172945810](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250320172945810.png)

![image-20250321010205879](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250321010205879.png)





































