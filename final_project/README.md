# 需求分析

1. 动态链表实现字符的频度统计
2. 用二叉树结构实现哈夫曼编码和解码

## 从实现角度将其分成若干模块

1. 动态链表的构建
2. 用动态链表实现字符的频度统计
3. 哈夫曼编码解码
4. 对文件的操作，要包含普通读写和二进制读写
5. 设计UI友好的入口文件  

---

# 项目目录结构

    /headers
    ---header.h
    /sources
    ---list.c
    ---count.c
    ---huffman.c
    ---output.c
    ---main.c

---

## 接口分析 
1. list.c

    主要用来提供统计词频的链表的相关功能，如append，create
	
	```c
	//创建一个新的链表，返回链表头
	listHead* create_list(void);

	//向链表末尾增加一个结点，返回1表示成功，0表示未成功
	//参数head为目标链表的头结点，参数ch为要插入的字符变量。
	listNode* append_list(listHead *head, char ch[]);

	//循环链表每一个结点，返回结点的data指针,循环完毕或长度为空时返回NULL
	//注意如果在foreach的过程中break了，需要将head->traverseTag置为假
	//参数head为目标链表的头结点。
	listData* foreach(listHead *head);	
	```


2. count.c

    主要用来完成词频统计的功能。
	
	```c
	//用来统计频率，返回一个链表头
	//@param filename string 文件名
	//@return listHead* 链表头
	listHead* count_from_file(char filename[]);

	//将统计结果排序。
	//@param listHead* head 目标链表头结点
	//@param bool mode true表示增序，false表示降序
	void sort_list(listHead* head, bool mode);
	```

3. huffman.c

    主要是利用统计词频的链表建立哈夫曼树，以及实现编码解码的功能。
	
	```c  
	//由统计结果建立哈夫曼树
	//@param listHead* head
	//@return huffmanNode* 返回树根结点指针
	huffmanNode* build_tree(listHead* head);
	```
	
4. output.c

    主要来实现将统计结果或二进制码流、哈夫曼树等打印或输出到文件的功能。
	
	```c 
	void print_data(listHead *head);
	
	void print_huffman_tree(huffmanNode* head);
	
	void print_function();
	
	void put_code_to_file(XXXX);
	```

5. main.c

    入口文件，主要完成美观的人机交互界面的功能

---

# 项目部分规范

## 命名规范

1. 局部变量 小写下划线
2. 全局变量 G_小写下划线
3. 接口函数的函数名 小写下划线
4. 非接口函数函数名 小写驼峰
5. 结构体属性 小写开头驼峰
6. 宏定义(常量) 全大写下划线

```cpp
bool traverse_tag;  //局部变量
void traverse_link(void){  //接口函数函数名
    //somecode
} 
linkHead* getMiddle(void);  //非接口函数函数名(仅在某个文件中使用)
bool traverseTag;  //结构体属性
#define FILE_NAME “test.txt”   //宏定义
```

## 控制结构

1. 函数定义、for、while、if等，大括号{紧接上一行行尾，回大括号}单独成行

    ```c  
    int main(void){  
        for(int i = 0;i < n;i++){  
            // somecode
        }
    }
    ```
    
2. 逗号，后接以空格。

    ```c  
    int append(linkHead *head, char ch){
        //somecode
    }
    ```
    
3. 若注释不单独成行，注释应与正文间有两个空格

    ```c
    p->data.cnt = 0;  //此处与上一个分号有两个空格
    //此处注释单独成行
    p->data.freq = 0;  //前面依然是两个半角空格
    ```
    
4. 涉及到比较时，最好将常量写在前面，牺牲部分可读性，减少出错概率

    ```c
    if(true == flag){
        //somecode
        //TODO
    }
    ```
---

# 随笔

### 2017-10-17  

1. 试图完成链表和输入输出  
    * 链表定义在header中，链表操作定义在link.c中  
        * 验证wchar_t格式的可行性——否定，直接用char  

### 2017-10-20

1. 认为在处理大量数据时，用char处理汉字会出现问题。char有8位，可以直接存ASCII码，然而在遇到汉字时，计算机内部可能是这样处理的：检测第一个八位对应的值，发现是负的，于是将前16位或前24位等看做一个字符处理(如utf-8就是通过第一个八位的开头有几个1来确定该字符占据几个字节)，然而此时sizeof(char)仍为1，因此就可能出现问题。考虑到utf-8中常用汉字用2个字节就可储存，因此应当将节点中的数据储存换成一个长度为2的char型数组。(还未更改代码，此仅为理论分析)。
 
### 2017-10-24

1. 继续完善上周要完成的东西  
用链表实现字符频度统计，涉及文件读写和链表知识  
2. 终于明白c处理中文的原理了：
用printf("%c%c\n",b[0],b[1]);可以输出中文。
fgetc只读取一个字节，这样如果循环起来，如果b[0]<0,就可以认为是中文，然后在读一个字节，这两个字节共同存储为中文。  
3. 要注意文件的编码必须和windows控制台的编码一致，不一致的话需要转换——转换成GB2312
4. 目前还有一个问题，文件中有中文的时候，两个相同的字符会占据两个节点，而且频数都是1。

### 2017-10-25

1. 解决了昨天的问题4：strcpy和memcpy存在很大的区别，strcmp和strcpy会到'\0'截止，而mem-需要制定长度
2. 尝试完成排序功能

### 2017-10-26

1. 重新思考了一下file.c应包含的内容，主要内容应该就是把统计结果输出成文件、把二进制码流存成文件，涉及到文件读取的部分实在很少，因此考虑把file.c改成output.c，并如下功能包含进该文件：把统计结果打印、输出成文件，把二进制码流存成文件，美观地打印出哈夫曼树
2. 建立树的过程，需要两种节点，一种是哈夫曼树中的节点，另一种是用来建立树时构造森林的节点。用一个链表储存需要排序的森林

### 2017-10-28

1.对于\t \n \r等字符在输出时要进行处理，不能直接输出，否则会让格式混乱。

### 2017-10-29

1. 突然发现不对劲，链表的英文是linked list,在程序里我把他命名成了linkNode、linkData，这好像不是很合理，但已经这样了，就不改了。
2. 排序功能完成，利用归并排序的递归算法，现在尝试完成建树过程
3. 如果leafTag==true，那么就用左子树指向
4. 完成哈夫曼树的建立（仅仅是编译成功，不保证逻辑正确）

---

# 优化、反思

### 2017-10-31
1. 英文的储存会造成浪费，但最多浪费128个字节，问题不大。优化方案：定义两种链表结点，一个是char，一个长度为2的char数组。在判断到字符的第一个字节大于0后，为其开辟第一种链表结点
