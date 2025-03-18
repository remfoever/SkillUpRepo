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

























