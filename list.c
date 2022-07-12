#include<stdio.h>
#include<stdlib.h>
#include"list.h"

/*局部函数模型*/
static void CopyToNode(Item item, Node* pnode);

/*接口函数*/
/*链表设置为空*/
void InitializeList(List* plist)
{
	*plist = NULL;
}

/*若链表为空，返回true*/
bool ListIsEmpty(const List * plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
}

/*若链表已满，返回true*/
bool ListIsFull(const List* plist)
{
	Node* pt;
	bool full;
	pt = (Node*)malloc(sizeof(Node));
	if (pt == NULL)
		full = true;
	else
		full = false;
	free(pt);
	return full;
}

/*返回节点数量*/
unsigned int ListItemCount(const int* plist)
{
	unsigned int count = 0;
	Node* pnode = *plist;
	while (pnode != NULL)
	{
		++count;
		pnode = pnode->next;
	}
	return count;
}

/*创建存储项的节点，并将其添加至plist指向的链表末尾(较慢的实现)*/
bool AddItem(Item item, List* plist)
{
	Node* pnew;
	Node* scan = *plist;
	
	pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
		return false;/*失败时退出函数*/

	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (scan == NULL)
		*plist = pnew;
	else
	{
		while (scan->next != NULL)
			scan = scan->next;/*找到链表的末尾*/
		scan->next = pnew;
	}

	return true;
}

/*访问每个节点并执行pfun指向的函数*/
void Traverse(const List* plist, void(pfun)(Item item))
{
	Node* pnode = *plist;/*设置链表的开始*/
	while (pnode != NULL)
	{
		(*pfun)(pnode->item);/*函数应用于链表中的项*/
		pnode = pnode->next;
	}
}

/*释放malloc()分配的内存*/
/*设置链表指针为NULL*/
void EmptyTheList(List* plist)
{
	Node* psave;

	while (*plist != NULL)
	{
		psave = (*plist)->next;/*保存下一个结点的地址*/
		free(*plist);/*释放当前节点*/
		*plist = psave;/*前进至下一个节点*/
	}
}

/*局部函数定义*/
/*把一个项拷贝到节点中*/
static void CopyToNode(Item item, Node* pnode)
{
	pnode->item = item;
}