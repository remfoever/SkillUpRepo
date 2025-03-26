# C结构体

C 数组允许定义可存储相同类型数据项的变量，**结构**是 C 编程中另一种用户自定义的可用的数据类型，它允许您存储不同类型的数据项。

结构体中的数据成员可以是基本数据类型（如 int、float、char 等），也可以是其他结构体类型、指针类型等。

---

结构用于表示一条记录，假设您想要跟踪图书馆中书本的动态，您可能需要跟踪每本书的下列属性：

- Title
- Author
- Subject
- Book ID

---

## 定义结构

结构体定义由关键字 **struct** 和结构体名组成，结构体名可以根据需要自行定义。

struct 语句定义了一个包含多个成员的新的数据类型，struct 语句的格式如下：

```c
struct tag {
  member-list
  member-list
  member-list  
  ...
} variable-list ;
```

**tag** 是结构体标签。

**member-list** 是标准的变量定义，比如 **int i;** 或者 **float f;**，或者其他有效的变量定义。

**variable-list** 结构变量，定义在结构的末尾，最后一个分号之前，您可以指定一个或多个结构变量。下面是声明 Book 结构的方式：

```c
struct Books
{
  char title[50];
  char author[50];
  char subject[100];
  int  book_id;
} book; 
```

在一般情况下，**tag、member-list、variable-list** 这 3 部分至少要出现 2 个。以下为实例：

```c
//此声明声明了拥有3个成员的结构体，分别为整型的a，字符型的b和双精度的c
//同时又声明了结构体变量s1
//这个结构体并没有标明其标签
struct
{
  int a;
  char b;
  double c;
} s1;

//此声明声明了拥有3个成员的结构体，分别为整型的a，字符型的b和双精度的c
//结构体的标签被命名为SIMPLE,没有声明变量
struct SIMPLE
{
  int a;
  char b;
  double c;
};
//用SIMPLE标签的结构体，另外声明了变量t1、t2、t3
struct SIMPLE t1, t2[20], *t3;

//也可以用typedef创建新类型
typedef struct
{
  int a;
  char b;
  double c;
} Simple2;
//现在可以用Simple2作为类型声明新的结构体变量
Simple2 u1, u2[20], *u3;
```

在上面的声明中，第一个和第二声明被编译器当作两个完全不同的类型，即使他们的成员列表是一样的，如果令 t3=&s1，则是非法的。

结构体的成员可以包含其他结构体，也可以包含指向自己结构体类型的指针，而通常这种指针的应用是为了实现一些更高级的数据结构如链表和树等。

```c
//此结构体的声明包含了其他的结构体
struct COMPLEX
{
  char string[100];
  struct SIMPLE a;
};

//此结构体的声明包含了指向自己类型的指针
struct NODE
{
  char string[100];
  struct NODE *next_node;
};


```

如果两个结构体互相包含，则需要对其中一个结构体进行不完整声明，如下所示：

```c
struct B;   //对结构体B进行不完整声明

//结构体A中包含指向结构体B的指针
struct A
{
  struct B *partner;
  //other members;
};

//结构体B中包含指向结构体A的指针，在A声明完后，B也随之进行声明
struct B
{
  struct A *partner;
  //other members;
};
```



------

## 结构体变量的初始化

和其它类型变量一样，对结构体变量可以在定义时指定初始值。

## 实例

```c
#include <stdio.h>

struct Books
{
  char title[50];
  char author[50];
  char subject[100];
  int  book_id;
} book = {"C 语言", "RUNOOB", "编程语言", 123456};

int main()
{
  printf("title : %s**\n**author: %s**\n**subject: %s**\n**book_id: %d**\n**", book.title, book.author, book.subject, book.book_id);
}
```

执行输出结果为：

```
title : C 语言
author: RUNOOB
subject: 编程语言
book_id: 123456
```

## 访问结构成员

为了访问结构的成员，我们使用**成员访问运算符（.）**。成员访问运算符是结构变量名称和我们要访问的结构成员之间的一个句号。您可以使用 **struct** 关键字来定义结构类型的变量。下面的实例演示了结构的用法：

## 实例

```c
#include <stdio.h>
#include <string.h>

struct Books
{
  char title[50];
  char author[50];
  char subject[100];
  int  book_id;
};

int main( )
{
  struct Books Book1;     */* 声明 Book1，类型为 Books */*
  struct Books Book2;     */* 声明 Book2，类型为 Books */*

  */* Book1 详述 */*
  strcpy( Book1.title, "C Programming");
  strcpy( Book1.author, "Nuha Ali");
  strcpy( Book1.subject, "C Programming Tutorial");
  Book1.book_id = 6495407;

  */* Book2 详述 */*
  strcpy( Book2.title, "Telecom Billing");
  strcpy( Book2.author, "Zara Ali");
  strcpy( Book2.subject, "Telecom Billing Tutorial");
  Book2.book_id = 6495700;
 
  */* 输出 Book1 信息 */*
  printf( "Book 1 title : %s**\n**", Book1.title);
  printf( "Book 1 author : %s**\n**", Book1.author);
  printf( "Book 1 subject : %s**\n**", Book1.subject);
  printf( "Book 1 book_id : %d**\n**", Book1.book_id);

  */* 输出 Book2 信息 */*
  printf( "Book 2 title : %s**\n**", Book2.title);
  printf( "Book 2 author : %s**\n**", Book2.author);
  printf( "Book 2 subject : %s**\n**", Book2.subject);
  printf( "Book 2 book_id : %d**\n**", Book2.book_id);

  return 0;
}
```

当上面的代码被编译和执行时，它会产生下列结果：

```
Book 1 title : C Programming
Book 1 author : Nuha Ali
Book 1 subject : C Programming Tutorial
Book 1 book_id : 6495407
Book 2 title : Telecom Billing
Book 2 author : Zara Ali
Book 2 subject : Telecom Billing Tutorial
Book 2 book_id : 6495700
```

## 结构作为函数参数

您可以把结构作为函数参数，传参方式与其他类型的变量或指针类似。您可以使用上面实例中的方式来访问结构变量：

## 实例

```c
#include <stdio.h>
#include <string.h>

struct Books
{
  char title[50];
  char author[50];
  char subject[100];
  int  book_id;
};

*/* 函数声明 */*
void printBook( struct Books book );
int main( )
{
  struct Books Book1;     */* 声明 Book1，类型为 Books */*
  struct Books Book2;     */* 声明 Book2，类型为 Books */*
 
  /* Book1 详述 */
  strcpy( Book1.title, "C Programming");
  strcpy( Book1.author, "Nuha Ali");
  strcpy( Book1.subject, "C Programming Tutorial");
  Book1.book_id = 6495407;

  /* Book2 详述 */
  strcpy( Book2.title, "Telecom Billing");
  strcpy( Book2.author, "Zara Ali");
  strcpy( Book2.subject, "Telecom Billing Tutorial");
  Book2.book_id = 6495700;
 
  /* 输出 Book1 信息 /
  printBook( Book1 );

  /* 输出 Book2 信息 */
  printBook( Book2 );

  return 0;
}
void printBook( struct Books book )
{
  printf( "Book title : %s**\n**", book.title);
  printf( "Book author : %s**\n**", book.author);
  printf( "Book subject : %s**\n**", book.subject);
  printf( "Book book_id : %d**\n**", book.book_id);
}
```



当上面的代码被编译和执行时，它会产生下列结果：

```
Book title : C Programming
Book author : Nuha Ali
Book subject : C Programming Tutorial
Book book_id : 6495407
Book title : Telecom Billing
Book author : Zara Ali
Book subject : Telecom Billing Tutorial
Book book_id : 6495700
```

## 指向结构的指针

您可以定义指向结构的指针，方式与定义指向其他类型变量的指针相似，如下所示：

```c
struct Books *struct_pointer;
```

现在，您可以在上述定义的指针变量中存储结构变量的地址。为了查找结构变量的地址，请把 & 运算符放在结构名称的前面，如下所示：

```c
struct_pointer = &Book1;
```

为了使用指向该结构的指针访问结构的成员，您必须使用 -> 运算符，如下所示：

```c
struct_pointer->title;
```

让我们使用结构指针来重写上面的实例，这将有助于您理解结构指针的概念：

## 实例

```c
#include <stdio.h>
#include <string.h>

struct Books
{
  char title[50];
  char author[50];
  char subject[100];
  int  book_id;
};

*/\* 函数声明 \*/*
void printBook( struct Books *book );
int main( )
{
  struct Books Book1;     */\* 声明 Book1，类型为 Books \*/*
  struct Books Book2;     */\* 声明 Book2，类型为 Books \*/*
 
  */\* Book1 详述 \*/*
  strcpy( Book1.title, "C Programming");
  strcpy( Book1.author, "Nuha Ali");
  strcpy( Book1.subject, "C Programming Tutorial");
  Book1.book_id = 6495407;

  */\* Book2 详述 \*/*
  strcpy( Book2.title, "Telecom Billing");
  strcpy( Book2.author, "Zara Ali");
  strcpy( Book2.subject, "Telecom Billing Tutorial");
  Book2.book_id = 6495700;
 
  */\* 通过传 Book1 的地址来输出 Book1 信息 \*/*
  printBook( &Book1 );

  */\* 通过传 Book2 的地址来输出 Book2 信息 \*/*
  printBook( &Book2 );

  return 0;
}
void printBook( struct Books *book )
{
  printf( "Book title : %s**\n**", book->title);
  printf( "Book author : %s**\n**", book->author);
  printf( "Book subject : %s**\n**", book->subject);
  printf( "Book book_id : %d**\n**", book->book_id);
}
```

当上面的代码被编译和执行时，它会产生下列结果：

```
Book title : C Programming
Book author : Nuha Ali
Book subject : C Programming Tutorial
Book book_id : 6495407
Book title : Telecom Billing
Book author : Zara Ali
Book subject : Telecom Billing Tutorial
Book book_id : 6495700
```

## 结构体大小的计算

C 语言中，我们可以使用 **sizeof** 运算符来计算结构体的大小，**sizeof** 返回的是给定类型或变量的字节大小。

对于结构体，**sizeof** 将返回结构体的总字节数，包括所有成员变量的大小以及可能的填充字节。

以下实例演示了如何计算结构体的大小：

## 实例

```c
#include <stdio.h>

struct Person {
  char name[20];
  int age;
  float height;
};

int main() {
  struct Person person;
  printf("结构体 Person 大小为: %zu 字节**\n**", sizeof(person));
  return 0;
}
```

以上实例中，我们定义了一个名为 **Person** 的结构体，它包含了一个字符数组 **name**、一个整数 **age** 和一个浮点数 **height**。

在 **main** 函数中，我们声明了一个 **Person** 类型的变量 **person**，然后使用 **sizeof** 运算符来获取 **person** 结构体的大小。

最后，我们使用 **printf** 函数打印出结构体的大小，输出结果如下：

```
结构体 Person 大小为: 28 字节
```

**注意**，结构体的大小可能会受到编译器的优化和对齐规则的影响，编译器可能会在结构体中插入一些额外的填充字节以对齐结构体的成员变量，以提高内存访问效率。因此，结构体的实际大小可能会大于成员变量大小的总和，如果你需要确切地了解结构体的内存布局和对齐方式，可以使用 **offsetof** 宏和 **__attribute__((packed))** 属性等进一步控制和查询结构体的大小和对齐方式。













# C语言中结构体标签的使用
我们都知道，结构体标签就是结构体的名称，为结构体命名可以方便我们在后续继续使用该结构体。
如

```c
struct student {
	char* name;
	int age;
}

struct student zhangsan;
struct student lisi;
```



这里定义了两个student结构体类型的变量，每次使用时都需要加上struct，比较麻烦。实际上更多情况下
我们会使用typedef来给一个匿名结构体起个别名，不用每次都输入struct。
如

```c
typedef struct {
	char* name;
	int age;
} student;

student zhangsan;
student lisi;
```



这个结构体没有标签，所以是个匿名结构体，但是我们通过typedef给他定义一个别名student，通过别名
定义变量不需要加struct前缀。

有了typedef，似乎结构体标签没有存在的必要了，其实不然。

使用typedef的写法，如果student类型要暴露给其他模块，那么必须要写在头文件当中。这将同时暴露
所有结构体的成员，有时候这是违背设计者意愿的。可能设计者希望其他模块的使用者只通过提供的API
来访问student，或者有些成员仅仅是内部使用。

使用结构体标签就可以避免这个问题。我们可以将结构体定义写在源文件中，头文件中仅包含结构体的
声明。

```c
struct student;
extern struct student* create_student(const char* name);
extern void set_student_age(struct student* s, int age);
```


使用者将不能自己创建student类型对象，只能通过create_student来获取，也不能通过获取到的指针访问
成员age，而是必须通过set_student_age函数接口。

这样写还能避免student结构体成员的变动，导致使用者需要重新编译。当然，为了不重复使用struct这个
单词，我们仍然可以使用typedef来重命名。

```c
typedef struct student student_t;
extern student_t* create_student(const char* name);
extern void set_student_age(student_t* s, int age);
```







# 属性声明：aligned

GNU C通过__attribute__来声明aligned和packed属性， 指定一个变量或类型的对齐方式。 这两个属性用来告诉编译器： 在给变量分配存储空间时， 要按指定的地址对齐方式给变量分配地址。 如果你想定义一个变量， 在内存中以8字节地址对齐， 就可以这样定义。  

```c
int a __attribute__((aligned(8)))
```

通过aligned属性， 我们可以显式地指定变量a在内存中的地址对齐方式。 aligned有一个参数， 表示要按几字节对齐， 使用时要注意， 地址对齐的字节数必须是2的幂次方， 否则编译就会出错。  

###### 对齐方式

一般情况下， 当我们定义一个变量时， 编译器会按照默认的地址对齐方式， 来给该变量分配一个存储空间地址。 如果该变量是一个int型数据， 那么编译器就会按4字节或4字节的整数倍地址对齐； 如果该变量是一个short型数据， 那么编译器就会按2字节或2字节的整数倍地址对齐；如果是一个char类型的变量， 那么编译器就会按照1字节地址对齐。  

![image-20250326133219687](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250326133219687.png)

程序运行结果如下。  

![image-20250326133246609](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250326133246609.png)

通过运行结果可以看到， 字符变量c2由于使用aligned属性声明按照4字节边界对齐， 所以编译器不可能再给其分配0x00402009这个地址，因为这个地址不是按照4字节对齐的。 编译器会空出3个存储单元， 直接从0x0040200C这个地址上给变量c2分配存储空间。

通过aligned属性声明， 虽然可以显式地指定变量的地址对齐方式，但是也会因边界对齐造成一定的内存空洞， 浪费内存资源。 如在上面这个程序中，0x00402009～0x0040200b这三个地址上的存储单元就没有被使用。



既然地址对齐会造成一定的内存空洞， 那么我们为什么还要按照这种对齐方式去存储数据呢？ 一个主要原因就是： **这种对齐设置可以简化CPU和内存RAM之间的接口和硬件设计**。 一个32位的计算机系统， 在CPU读取内存时， 硬件设计上可能只支持4字节或4字节倍数对齐的地址访问， CPU每次向内存RAM读写数据时， 一个周期可以读写4字节。 如果我们把一个int型数据放在4字节对齐的地址上， 那么CPU一次就可以把数据读写完毕； 如果我们把一个int型数据放在一个非4字节对齐的地址上， 那么CPU可能就要分两次才能把这个4字节大小的数据读写完毕。为了配合计算机的硬件设计， 编译器在编译程序时， 对于一些基本数据类型， 如int、 char、 short、 float等， 会按照其数据类型的大小进行地址对齐， 按照这种地址对齐方式分配的存储地址， CPU一次就可以读写完毕。 虽然边界对齐会造成一些内存空洞， 浪费一些内存单元， 但是在硬件上的设计却大大简化了。 这也是编译器给我们定义的变量分配地址时， 不同类型的变量按照不同字节数地址对齐的主要原因。

除了int、 char、 short、 float这些基本类型数据， 对于一些复合类型数据， 也要满足地址对齐要求。





# 结构体的对齐

结构体作为一种复合数据类型，编译器在给一个结构体变量分配内存空间时不仅要考虑结构体内各个基本成员的对齐地址，还要考虑结构体整体的对齐。为了结构体内各个成员地址对齐编译器可能会在结构体内填充一些空间；为了结构体整体对齐，编译器可能会在结构体的末尾填充一些空间。



```c
struct data{
    char a;
    int b;
    short c;
}


size: 12
```

因为结构体的成员b需要4字节对齐， 所以编译器在给成员a分配完1字节的存储空间后， 会空出3字节， 在满足4字节对齐的0x0028FF34地址处才给成员b分配4字节的存储空间。 接着是short类型的成员c占据2字节的存储空间。 三个结构体成员一共占据1+3+4+2=10字节的存储空间。根据结构体的对齐规则， 结构体的整体对齐要按结构体所有成员中最大对齐字节数或其整数倍对齐， 或者说结构体的整体长度要为其最大成员字节数的整数倍， 如果不是整数倍则要补齐。 因为结构体最大成员int为4字节， 所以结构体要按4字节对齐， 或者说结构体的整体长度要是4的整数倍， 要在结构体的末尾补充2字节， 最后结构体的大小为12字节。  

**结构体成员按不同的顺序排放， 可能会导致结构体的整体长度不一样**

```c
struct data{
    char a;
    short b;
    int c;
}


size: 8
```

调整了一些成员顺序， 你会发现， char型变量a和short型变量b， 被分配在了结构体前4字节的存储空间中， 而且都满足各自的地址对齐方式， 整个结构体大小是8字节， 只造成1字节的内存空洞。   

```c
struct data{
    char a;
    short b __attribute__((aligned(4)));
    int c;
}


size: 12
```

显式指定short变量以4字节地址对齐， 导致变量a的后面填充了3字节空间。int型变量c也要4字节对齐， 所以变量b的后面也填充了2字节， 导致整个结构体的大小为12字节。



我们不仅可以显式指定结构体内某个成员的地址对齐， 也可以**显式指定整个结构体的对齐方式**。  

```c
struct data{
    char a;
    short b;
    int c;
}__attribute__((aligned(16)))


size: 16
```

在这个结构体中， 各个成员共占8字节。 通过前面的学习我们知道， 整个结构体的对齐只要按最大成员的对齐字节数对齐即可。 所以这个结构体整体就以4字节对齐， 结构体的整体长度为8字节。 但是在这里， 显式指定结构体整体以16字节对齐， 所以编译器就会在这个结构体的末尾填充8字节以满足16字节对齐的要求， 最终导致结构体的总长度变为16字节  

我们通过这个属性声明， 其实***只是建议编译器按照这种大小地址对齐， 但不能超过编译器允许的最大值***。 一个编译器， 对每个基本数据类型都有默认的最大边界对齐字节数。 如果超过了， 则编译器只能按照它规定的最大对齐字节数来给变量分配地址。  





# 属性声明：packed

aligned属性一般用来增大变量的地址对齐， 元素之间因为地址对齐会造成一定的内存空洞。 而packed属性则与之相反， 一般用来减少地址对齐， 指定变量或类型使用最可能小的地址对齐方式。  

```c
struct data{
    char a;
    short b __attribute__((packed));
    int c __attribute__((packed));
};

size 7
```

在上面的程序中， 我们将结构体的成员b和c使用packed属性声明，就是告诉编译器， 尽量使用最可能小的地址对齐给它们分配地址， 尽可能地减少内存空洞。 程序的运行结果如下。  

![image-20250326134308782](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250326134308782.png)

通过结果我们看到， 结构体内各个成员地址的分配， 使用最小1字节的对齐方式， 没有任何内存空间的浪费， 导致整个结构体的大小只有7字节。

这个特性在底层驱动开发中还是非常有用的。 例如， 你想定义一个结构体， 封装一个IP控制器的各种寄存器， 在ARM芯片中， 每一个控制器的寄存器地址空间一般都是连续存在的。 如果考虑数据对齐， 则结构体内就可能有空洞， 就和实际连续的寄存器地址不一致。 使用packed可以避免这个问题， 结构体的每个成员都紧挨着， 依次分配存储地址， 这样就避免了各个成员因地址对齐而造成的内存空洞。

```c
struct data{
    char a;
    short b;
    int c;
}__attribute__((packed));
```

我们也可以对整个结构体添加packed属性， 这和分别对每个成员添加packed属性效果是一样的。 修改结构体后， 重新编译程序， 运行结果和上面程序的运行结果相同： 结构体的大小为7， 结构体内各成员地址相同。  

##### aligned、packed一起使用

在Linux内核源码中， 我们经常看到aligned和packed一起使用， 即对一个变量或类型同时使用aligned和packed属性声明。 这样做的好处是：既避免了结构体内各成员因地址对齐产生内存空洞， 又指定了整个结构体的对齐方式。  

![image-20250326134549119](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250326134549119.png)

程序运行结果如下。  

![image-20250326134601027](https://picture-1344593885.cos.ap-beijing.myqcloud.com/image-20250326134601027.png)

在上面的程序中， 结构体data虽然使用了packed属性声明， 结构体内所有成员所占的存储空间为7字节， 但是我们同时使用了aligned(8)指定结构体按8字节地址对齐， 所以编译器要在结构体后面填充1字节， 这样整个结构体的大小就变为8字节， 按8字节地址对齐。  

































































