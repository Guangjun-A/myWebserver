[toc]

# 参考链接

<https://www.jianshu.com/p/887f2d1e18b4>

# 什么是webserver?

从浏览器(客户端)的角度出发：客户需要输入IP，查看网页。网页这些资源都是存放在一个实实在在的物理硬盘上，也就是webserver，他负责存储和接受客户端的请求（HTTP请求），并对其做出HTTP响应，客户端返回请求的内容（文件或者网页）或者返回error。
<img src="./figs/web-server.svg" width=500px; height=500px; />

## HTTP请求和连接过程

1. https请求。客户端向服务端发送https请求
2. 生成公钥和私钥。服务端收到请求之后，生成公钥和私钥。公钥相当于是锁，私钥相当于是钥匙，只有私钥才能够打开公钥锁住的内容
3. 返回公钥。服务端将公钥（证书）返回给客户端，公钥里面包含有很多信息，比如证书的颁发机构、过期时间等等；
4. 客户端验证公钥。客户端收到公钥之后，首先会验证其是否有效，如颁发机构或者过期时间等，如果发现有问题就会抛出异常，提示证书存在问题。如果没有问题，那么就生成一个随机值，作为客户端的密钥，然后用服务端的公钥加密；
5. 发送客户端密钥。客户端用服务端的公钥加密密钥，然后发送给服务端。
6. 服务端收取密钥，对称加密内容。服务端收到经过加密的密钥，然后用私钥将其解密，得到客户端的密钥，然后服务端把要传输的内容和客户端的密钥进行对称加密，这样除非知道密钥，否则无法知道传输的内容。
7. 加密传输。服务端将经过加密的内容传输给客户端。
8. 获取加密内容，解密。客户端获取加密内容后，用之前生成的密钥对其进行解密，获取到内容。
<img src="./figs/HTTPS.jpg" width=500px; height=500px; />

# URL和域名的区别？

URL和域名之间的主要区别在于URL是一个字符串，它提供网页的信息位置或完整的Internet地址，而域名是URL的一部分，而URL是IP地址的一种更人性化的形式。
URL就是输入的网址：
一个完整的URL：<https://www.cnblogs.com/Guang-Jun/p/14315416.html> 包含以下部分

- 协议：https
- 服务器名，域名：www.cnblogs.com
- 目录：Guang-Jun
- 文件：14315416.html
域名：方便人们将特定含义的主机名（www.cnblogs.com）转化为便于机器处理的IP地址。
- 三级域名：www
- 二级域名：cnblogs
- 顶级域名：com

# 用户如何与你的webserver进行通信的（从输入网址到获取页面的过程）？

<http://www.dailichun.com/2018/03/12/whenyouenteraurl.html>
<https://zhuanlan.zhihu.com/p/80551769>
用户使用web浏览器与相应的服务器进行通信。

1. 输入网址，判断是否合法，解析出域名
2. 解析域名（DNS查询），获取域名的IP地址（IP地址：端口号），通过DNS（Domain name system）域名系统查询
3. 建立TCP连接
4. HTTP请求
5. 接受响应

# 对于一个服务器而言，上面的流程大概是这样组合的

1. listener = socket()，bind()，listen()，设置nonblocking
2. 创建一个event_base
3. 创建一个event，将该socket托管给event_base，指定要监听的事件类型，并绑定上相应的回调函数。对于listener socket来说，只需要监听EV_READ|EV_PERSIST
4. 启用该事件
5. 进入事件循环
6. (异步) 当有client发起请求的时候，调用该回调函数，进行处理。
链接：<https://www.jianshu.com/p/887f2d1e18b4>

# 大端存放和小端存放？

<https://blog.csdn.net/jason_cuijiahui/article/details/79010257>
累加器一次性能装载4个字节（4个字节有大端和小端两种方法排列），每个地址单元对应着一个字节（=8位）

1. 大端模式是指数据的低位保存在内存的高地址中，而数据的高位保存在内存的低地址中
2. 小端模式是指数据的低位保存在内存的低地址中，而数据的高位保存在内存的高地址中

# 命令行传参

``` cpp
int main (int argc, char* agrv[]) {
    cout << argc << endl;
    cout << agrv[0] << endl;
    cout << agrv[agrc] endl;
}

(1).int argc:英文名为arguments count(参数计数, 计算传入的参数个数)
count of cmd line args,运行程序传送给main函数的命令行参数总个数,包括可执行程序名,其中当argc=1时表示只有一个程序名称,此时存储在argv[0]中.
(2).char **argv:英文名为arguments value/vector(参数值，参数列表，存放参数)
pointer to table of cmd line args,字符串数组,用来存放指向字符串参数的指针数组,每个元素指向一个参数,空格分隔参数,其长度为argc.数组下标从0开始,argv[argc]=NULL.
argv[0] 指向程序运行时的全路径名
argv[1] 指向程序在DOS命令中执行程序名后的第一个字符串
argv[2] 指向执行程序名后的第二个字符串
argv[argc] 为NULL.

```

# basename 使用

``` cpp
printf(basename(argv[0]));

// 返回最后的那个地址，例如
//  $ basename /usr/bin/sort       输出"sort"。
//  $ basename ./include/stdio.h .h  输出"stdio"。
//  为basename指定一个路径，basename命令会删掉所有的前缀包括最后一个slash（'/'）字符，然后将字符串显示出来。
 ```

# bzero 函数使用

头文件：`#include <string.h>`

`bzero()`会将内存块（字符串）的前n个字节清零，其原型为：
    `void bzero(void *s, int n);`

【参数】s为内存（字符串）指针，n 为需要清零的字节数。

`bzero()`会将参数s 所指的内存区域前n个字节，全部设为零值。

实际上，`bzero(void *s, int n)` 等价于 `memset((void*)s, 0,size_tn)`，用来将内存块的前 n 个字节清零，但是 s 参数为指针，又很奇怪的位于 string.h 文件中，也可以用来清零字符串。

# bzero和memset函数

为探究竟，这里结合文献内容进行阐述：

1、bzero()好记忆：2个参数；

2、memset()易出错：3个参数，且第二、三个参数易记混淆，如若出现位置互换的情况，C编译器并不能察觉。

使用
1、bzero()
函数原型：extern void bzero(void *s, int n)

头文件：<string.h>

功能：置字节字符串s的前n个字节为零且包括'\0'

说明：无返回值

2、memset()

``` cpp
函数原型：extern void *memset(void *buffer, int c, int count)

头文件：<string.h>

功能：把buffer所指内存区域的前count个字节设置成c的值。
```

原文链接：<https://blog.csdn.net/liuxu324/article/details/81543580>

# 进程，进程组，僵尸进程，会话

<https://blog.51cto.com/u_15015138/2555390>

# 阻塞IO,非阻塞IO，同步IO,异步IO

<https://www.jianshu.com/p/2461535c38f3>
<https://cloud.tencent.com/developer/article/1684951>

- 一个IO操作其实分成了两个步骤：发起IO请求（请求资源是否被占用）和实际的IO操作（读写操作）
阻塞IO：发起请求后，之后等待实际的IO操作发生
非阻塞IO：发起请求后，立即返回，不管事件发生与否
同步IO：包括阻塞IO,IO复用，信号驱动IO模型。在读写操作时，进程阻塞
异步IO：读写操作立刻返回。在进行读写操作时，交给内核处理（数据从内核缓冲区读入用户缓冲区，从用户缓冲区写入内核缓冲区），程序立刻返回，不会阻塞进程。处理后内核通知用户程序。

# 零拷贝

<https://www.cnblogs.com/xiaolincoding/p/13719610.html>
这就是所谓的零拷贝（Zero-copy）技术，因为我们没有在内存层面去拷贝数据，也就是说全程没有通过 CPU 来搬运数据，所有的数据都是通过 DMA 来进行传输的。

``` cpp
#include <sys/socket.h>
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
```

## getopt函数

``` cpp
int getopt(int argc, char * const argv[], const char *optstring);
// 外部声明
extern char *optarg;
extern int optind, opterr, optopt;
```

getopt 参数说明：

argc：通常由 main 函数直接传入，表示参数的数量
argv：通常也由 main 函数直接传入，表示参数的字符串变量数组
optstring：一个包含正确的参数选项字符串，用于参数的解析。例如 “abc:”，其中 -a，-b 就表示两个普通选项，-c 表示一个必须有参数的选项，因为它后面有一个冒号

外部变量（全局变量）说明：

optarg：如果某个选项有参数，这包含当前选项的参数字符串
optind：argv 的当前索引值
opterr：正常运行状态下为 0。非零时表示存在无效选项或者缺少选项参数，并输出其错误信息
optopt：当发现无效选项字符时，即 getopt() 方法返回 ? 字符，optopt 中包含的就是发现的无效选项字符

返回值说明：

- 如果参数读取完成，返回-1
- 如果有参数对应，将参数放在optarg中
- 如果一个选项要求必须要有值，但是没有传入的话，返回？
- 如果放置一个冒号表示选项后面必须带参数，放置两个冒号表示可选可不选，不放置冒号
- 将冒号放置在字符串的前面，表示如果没有加冒号的选项有参数传入时，返回？

原文链接：<https://blog.csdn.net/afei__/article/details/81261879>

``` cpp
#include <stdio.h> 
#include <unistd.h> 
  
int main(int argc, char *argv[]) 
{
    int opt;
    const char *str = ":if:lrx";
    // put ':' in the starting of the
    // string so that program can 
    //distinguish between '?' and ':' 
    while((opt = getopt(argc, argv, str)) != -1) 
    { 
        printf("optind:%d，opterr：%d %c: \n",optind,opterr, str[optind]);

        switch(opt) 
        { 
            case 'i': 
            case 'l': 
            case 'r': 
                printf(“option: %c\n”, opt); 
                break; 
            case 'f': 
                printf(“filename: %s\n”, optarg); 
                break; 
            case ':': 
                printf(“option needs a value\n”); 
                break; 
            case '?': 
                printf(“unknown option: %c\n”, optopt);
                break; 
        } 
    } 
      
    // optind is for the extra arguments
    // which are not parsed
    for(; optind < argc; optind++){     
        printf(“extra arguments: %s\n”, argv[optind]); 
    }
      
    return 0
}

```

## 字符串操作

对于字符串的操作，需要引入`string.h`
对于内存分配操作，需要引入`malloc.h`

1. `getcwd(char* buf, unsign long int size);`
获取当前的目录，存放在buf中，buf的大小为size, 如果当前目录路径大小大于size，返回NULL.

```cpp
    char server_path[200];
    // getcwd 获取当前的工作目录，并将目录放在server_path中,其实可以采用
    // char server_path = NULL;
    // getcwd(server_path, 0); 调用malloc自动分配内存
    getcwd(server_path, 200);
    printf("the size of server_path is %lu. the path is: %s \n", sizeof(server_path), server_path);
```

## 单例模式

- 懒汉模式
直到实例被创建了才开始占用内存，C++ 11中要求局部静态变量的初始化要线程安全。静态局部变量

```cpp
// 实现方法一：call_once 和 call_flag
template <class T>
class Singleton
{
private:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
 
public:
    template <typename... Args>
    static T* instance(Args&&... args) // ...允许传入参数包，通过对参数包进行推导，可以传入多个参数值
    // https://en.cppreference.com/w/cpp/language/template_argument_deduction
    {
        std::call_once(_flag, [&](){
            _instance = new T(std::forward<Args>(args)...);
        });
        return _instance;
    }
 
    static void destroy()
    {
        if (_instance)
        {
            delete _instance;
            _instance = NULL;
        }
    }
 
private:
    static T* _instance;
    static std::once_flag _flag;
};
 
template <class T>
T* Singleton<T>::_instance = NULL; 
 
template <class T>
std::once_flag Singleton<T>::_flag;
// 方法二：使用C++11特性，静态局部变量初始化满足线程安全，初始化具有原子性，线程安全。数据在静态存储区
class Singleton
{
public:
    static Singleton* instance()
    {
        static Singleton _instance;
        return &s_instance;
    }
private:
    Singleton() {}
};
```

- 饿汉模式
一开始就占用内存创建单例，这个是线程安全的。使用static定义全局变量，在编译时就加载成功。

```cpp
class Singleton {
 private:
  Singleton() = default; // 默认无参构造
  // 防止拷贝和赋值。
  Singleton& operator=(const Singleton&) = delete; // 赋值构造
  Singleton(const Singleton& singleton2) = delete; // 拷贝构造
  static Singleton* m_instance;  // 确保共享一个m_instance

 public:
  static Singleton* getInstance() { return m_instance; }
};

// Singleton* Singleton::m_instance = new Singleton;
Singleton* Singleton::m_instance = new Singleton(); // 静态数据可以定义在类外


```

### 创建线程

```cpp
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __THROWNL __nonnull ((1, 3));
    ```
- `__restrict`代表只能由一个指针固定的访问
- `attr`线程属性
- `__start_routine`, 返回值为`void*`的函数，代表可以返回任意类型的值
- `arg`, 输入为`void*`的参数, 可以传入结构体，实现多参数传入。void*类型代表可以传入任意类型的数据

创建线程代码
```cpp
void* func(void* parm) { // 线程要求返回值和输入值必须是void*类型
    for (int i = 0; i < 100; i++) 
    printf("this is %d childern thread.\n", i);
}
int main() {
    pthread_t id; //  创建线程标识符
    pthread_create(&id, NULL, func, NULL); 

    for (int i = 1000; i < 1019; i++) {
        printf("%d foo thread.\n", i);
    }    
    pthread_join(id, NULL);
    return 0;
}

```

### 条件变量线程

参考链接：<https://stackoverflow.com/questions/16522858/understanding-of-pthread-cond-wait-and-pthread-cond-signal>
执行过程

- 在tid线程，blockedThread函数中先加锁获取资源，然后因为条件变量cond未满足，在cond_wait函数内部先进行解锁，然后放到条件变量的等待队列里。

- 在主线程（releaseFun函数）中加锁，这时候能加锁是因为在cond_wait中释放了锁，所以再次加锁不会造成死锁现象。在releaseFun函数通过pthread_cond_signal释放信号唤醒一个等待cond变量的线程（也就是tid）。
- tid线程被唤醒，pthread_cond_wait接着进行加锁占用资源，执行操作后解锁。

```cpp
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Declaration of thread condition variable
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// Thread function
void releaseFun() {
  pthread_mutex_lock(&lock);
  // Let's signal condition variable cond
  printf("Signaling condition variable cond\n");
  pthread_mutex_unlock(&lock);

  pthread_cond_signal(&cond);
}

// Thread function
void* blockedThread(void* arg) {
  // acquire a lock
  pthread_mutex_lock(&lock);
  printf("Waiting on condition variable cond\n");
  pthread_cond_wait(&cond, &lock); // 当有多个线程等待条件时候，要加while(!condition)判断
    // do something 


  // release lock
  pthread_mutex_unlock(&lock);

  printf("Returning thread\n");

  return NULL;
}

// Driver code
int main() {
  pthread_t tid;

  // Create thread 1
  pthread_create(&tid, NULL, blockedThread, NULL);

  // sleep for 1 sec so that thread 1
  // would get a chance to run first
  sleep(1);
    // do something 

  releaseFun();
  // wait for the completion of thread 2
  pthread_join(tid, NULL);

  return 0;
}
```

## __VA_ATGS__

__VA_ARGS__是一个可变参数的宏，定义时宏定义中参数列表的最后一个参数为省略号，在实际使用时会发现有时会加##，有时又不加。

```cpp
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdarg.h>

#define FOO(n, ...) printf(n, __VA_ARGS__);
#define BAR(fmt, ...)  printf(fmt, ##__VA_ARGS__)



int main() {
BAR("here is a log message with a param: \n"); // 不报错
FOO("here is a log message with a param: \n"); // 报错

  return 0;
}
```

__VA_ARGS__宏前面加上##的作用在于，当可变参数的个数为0时，这里printf参数列表中的的##会把前面多余的","去掉，否则会编译出错，建议使用后面这种，使得程序更加健壮。

