#include<stdio.h>
#include<stdlib.h>
#include"list.h"

/*�ֲ�����ģ��*/
static void CopyToNode(Item item, Node* pnode);

/*�ӿں���*/
/*��������Ϊ��*/
void InitializeList(List* plist)
{
	*plist = NULL;
}

/*������Ϊ�գ�����true*/
bool ListIsEmpty(const List * plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
}

/*����������������true*/
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

/*���ؽڵ�����*/
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

/*�����洢��Ľڵ㣬�����������plistָ�������ĩβ(������ʵ��)*/
bool AddItem(Item item, List* plist)
{
	Node* pnew;
	Node* scan = *plist;
	
	pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
		return false;/*ʧ��ʱ�˳�����*/

	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (scan == NULL)
		*plist = pnew;
	else
	{
		while (scan->next != NULL)
			scan = scan->next;/*�ҵ������ĩβ*/
		scan->next = pnew;
	}

	return true;
}

/*����ÿ���ڵ㲢ִ��pfunָ��ĺ���*/
void Traverse(const List* plist, void(pfun)(Item item))
{
	Node* pnode = *plist;/*��������Ŀ�ʼ*/
	while (pnode != NULL)
	{
		(*pfun)(pnode->item);/*����Ӧ���������е���*/
		pnode = pnode->next;
	}
}

/*�ͷ�malloc()������ڴ�*/
/*��������ָ��ΪNULL*/
void EmptyTheList(List* plist)
{
	Node* psave;

	while (*plist != NULL)
	{
		psave = (*plist)->next;/*������һ�����ĵ�ַ*/
		free(*plist);/*�ͷŵ�ǰ�ڵ�*/
		*plist = psave;/*ǰ������һ���ڵ�*/
	}
}

/*�ֲ���������*/
/*��һ��������ڵ���*/
static void CopyToNode(Item item, Node* pnode)
{
	pnode->item = item;
}