# strtoul函数(输入字符串转换为数字)

一、函数原型：
          unsigned long int strtoul(const char *nptr, char **endptr, int base);
          unsigned long long int strtoull(const char *nptr, char **endptr,int base);
        1、参数nptr：字符串的起始地址。

        2、参数endptr： 返回字符串有效数字的结尾地址。如 123456fe789 则返回数字f的地址。
    
        3、参数base：转化基数。   
            参数 base 范围从2 至36，或0。参数 base 代表 nptr 采用的进制方式，如 base 值为10 则采用             10 进制，若 base 值为16 则采用16 进制数等。


二、功能描述：
          convert a string to an unsigned long integer(把输入的字符串转换成数字).
          strtoul() 会扫描参数nptr 字符串，跳过前面的空白字符（例如空格，tab缩进等，可以通过 isspace() 函数来检测），直到遇上数字或正负符号才开始做转换，再遇到非数字或字符串结束时('\0')结束转换，并将结果返回。


三、所需头文件：
          #include <stdlib.h>

四、特别需要注意下面两点：

    1、当 base 的值为 0 时，默认采用 10 进制转换，但如果遇到 '0x' / '0X' 前置字符则会使用 16 进制转换，遇到 '0' 前置字符则会使用 8 进制转换。
    
    2、若 endptr 不为NULL，则会将遇到的不符合条件而终止的字符指针由 endptr 传回；若 endptr 为 NULL，则表示该参数无效，或不使用该参数。本文最后的范例没有展示 endptr 参数的使用，你可以参考 strtol() 函数的范例来更加直观地了解 endptr 参数。

五、实例一：输入字符串，base 的值为2，二进制转换。
测试代码：
#include <stdio.h> 
#include <stdlib.h> 
int main () 
{   
	char buffer [256];   
	unsigned long ul; 
    char * endptr;
    while(1)
	{
	   printf ("Enter an unsigned number: ");  
	   fgets (buffer, 256, stdin);   
	   ul = strtoul (buffer, &endptr, 2);   
       printf ("Value entered: %lu ,the address of the first invalid character is %d ,invalid character=%s\n", ul,endptr,endptr);   
	   system("pause"); 
	}
	return 0; 
} 

测试结果：

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/20171106163345669)



六、实例二：输入字符串，base 的值为10，十进制转换。
测试代码：
#include <stdio.h> 
#include <stdlib.h> 
int main () 
{   
	char buffer [256];   
	unsigned long ul; 
    char * endptr;
    while(1)
	{
	   printf ("Enter an unsigned number: ");  
	   fgets (buffer, 256, stdin);   
	   ul = strtoul (buffer, &endptr, 10);   
       printf ("Value entered: %lu ,the address of the first invalid character is %d ,invalid character=%s\n", ul,endptr,endptr);   
	   system("pause"); 
	}
	return 0; 
} 

测试结果： 

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/20171106163810413)


六、实例三：输入字符串，base 的值为0的特殊情况。
     1、当 base 的值为 0 时，默认采用 10 进制转换，但如果遇到 '0x' / '0X' 前置字符则会使用 16 进制转换，遇到 '0' 前置字符则会使用 8 进制转换。

     2、若 endptr 不为NULL，则会将遇到的不符合条件而终止的字符指针由 endptr 传回；若 endptr 为 NULL，则表示该参数无效，或不使用该参数。本文最后的范例没有展示 endptr 参数的使用，你可以参考 strtol() 函数的范例来更加直观地了解 endptr 参数。

测试代码：
#include <stdio.h> 
#include <stdlib.h> 
int main () 
{   
	char buffer [256];   
	unsigned long ul; 
    char * endptr;
    while(1)
	{
	   printf ("Enter an unsigned number: ");  
	   fgets (buffer, 256, stdin);   
	   ul = strtoul (buffer, &endptr, 0);   
       printf ("Value entered: %lu ,the address of the first invalid character is %d ,invalid character=%s\n", ul,endptr,endptr);   
	   system("pause"); 
	}
	return 0; 
} 


测试结果：

![img](https://picture-1344593885.cos.ap-beijing.myqcloud.com/20171106164329709)