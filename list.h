#ifndef LIST_H_
#define LIST_H_
#include<stdbool.h>


#define FLUSH while(getchar()!='\n')
/*特定程序的声明*/

#define TSIZE 45/*存储电影名的数组大小*/
struct film
{
	char title[TSIZE];
	int rating;
};

/*一般类型定义*/

typedef struct film Item;

typedef struct node
{
	Item item;
	struct node* next;
}Node;

typedef Node* List;

/*函数原型*/

/*操作：         初始化一个链表*/
/*前提条件：     plist指向一个链表*/
/*后置条件：     链表初始化为空*/
void InitializeList(List* plist);

/*操作：         确认链表是否为空，plist指向一个已初始化的链表*/
/*后置条件：     如果链表为空，则函数返回True，否则返回False*/
bool ListIsEmpty(const List* plist);

/*操作：         确认链表是否已满，plist指向一个已经初始化的链表*/
/*后置条件：     若链表已满，则函数返回真，否则返回假*/
bool ListIsFull(const List* plist);

/*操作：         确定链表中的项数，plist指向一个已初始化的链表*/
/*后置条件：     该函数返回链表中的项数*/
unsigned int ListItemCount(const List* plist);

/*操作：         在链表的末尾添加项*/
/*前置条件：     item是一个待添加至链表的项，plist指向一个已初始化的链表*/
/*后置条件：     如果可以，该函数在链表末尾添加一个项，且返回true；否则返回false*/
bool AddItem(Item item, List* plist);

/*操作：         把函数作用于链表中的每一项*/
/*前置条件：     plist指向一个已初始化的链表*/
/*               pfun指向一个函数，该函数接收一个Item类型的参数，且无返回值*/
/*后置条件：     pfun指向的函数作用于链表中的每一项*/
void Traverse(const int* plist, void(pfun)(Item item));

/*操作：         释放已分配的内存*/
/*前置条件：     plsit指向一个已初始化的链表*/
/*后置条件：     释放为了链表分配的所有内存，链表设置为空*/
void EmptyTheList(List* plist);

#endif