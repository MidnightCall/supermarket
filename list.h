#ifndef LIST_H_
#define LIST_H_
#include<stdbool.h>


#define FLUSH while(getchar()!='\n')
/*�ض����������*/

#define TSIZE 45/*�洢��Ӱ���������С*/
struct film
{
	char title[TSIZE];
	int rating;
};

/*һ�����Ͷ���*/

typedef struct film Item;

typedef struct node
{
	Item item;
	struct node* next;
}Node;

typedef Node* List;

/*����ԭ��*/

/*������         ��ʼ��һ������*/
/*ǰ��������     plistָ��һ������*/
/*����������     �����ʼ��Ϊ��*/
void InitializeList(List* plist);

/*������         ȷ�������Ƿ�Ϊ�գ�plistָ��һ���ѳ�ʼ��������*/
/*����������     �������Ϊ�գ���������True�����򷵻�False*/
bool ListIsEmpty(const List* plist);

/*������         ȷ�������Ƿ�������plistָ��һ���Ѿ���ʼ��������*/
/*����������     ���������������������棬���򷵻ؼ�*/
bool ListIsFull(const List* plist);

/*������         ȷ�������е�������plistָ��һ���ѳ�ʼ��������*/
/*����������     �ú������������е�����*/
unsigned int ListItemCount(const List* plist);

/*������         �������ĩβ�����*/
/*ǰ��������     item��һ���������������plistָ��һ���ѳ�ʼ��������*/
/*����������     ������ԣ��ú���������ĩβ���һ����ҷ���true�����򷵻�false*/
bool AddItem(Item item, List* plist);

/*������         �Ѻ��������������е�ÿһ��*/
/*ǰ��������     plistָ��һ���ѳ�ʼ��������*/
/*               pfunָ��һ���������ú�������һ��Item���͵Ĳ��������޷���ֵ*/
/*����������     pfunָ��ĺ��������������е�ÿһ��*/
void Traverse(const int* plist, void(pfun)(Item item));

/*������         �ͷ��ѷ�����ڴ�*/
/*ǰ��������     plsitָ��һ���ѳ�ʼ��������*/
/*����������     �ͷ�Ϊ���������������ڴ棬��������Ϊ��*/
void EmptyTheList(List* plist);

#endif