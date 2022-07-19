/*****************************************************************//**
 * \file   customLookup.c
 * \brief  ���ض��ṹ��������Ϣ�Ĵ�ӡ�Ͱ�������ѯ�����ļ���ʵ��
 *
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#include "typeCollection.h"
#include "customLookup.h"
#include "helpfulFunction.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 /* �ṹ���ڲ��ڴ�ƫ��ֵ */
const int OFFSET_PRODUCT = 4;
const int OFFSET_EMPLOYEE = 12;
const int OFFSET_SUPPLIER = 4;
const int OFFSET_PRODUCT_TYPE = 80;
const int OFFSET_PRODUCT_SUPPLIER = 52;

static char* sexConv[] = { "Ů", "��" };
static char* typeConv[] = { "����", "����Ʒ", "�ľ�", "ʳƷ", "��ˮ", "���õ���" };

/**
 * \brief ��������û� (User_t) ��Ϣ
 *
 * \param node Ҫ������û���Ϣ�ڵ�
 */
void printUserInfo(User_t* node)
{
	static char* pmsConv[] = { "��ͨ�û�", "����Ա", "��������Ա" };
	printf("�� %7u�� %12s�� %24s��\n", node->id, node->password, pmsConv[node->permission]);
	return;
}

/**
 * \brief ���������Ʒ (Product_t) ��Ϣ
 *
 * \param node Ҫ�������Ʒ��Ϣ�ڵ�
 */
void printProductInfo(Product_t* node)
{
	printf("%d, %s, %s, %f\n",node->id, node->name, typeConv[node->type], node->price);
	return;
}

/**
 * \brief �������������Ʒ (OnSale_t) ��Ϣ
 *
 * \param node Ҫ�����������Ʒ�ڵ�
 */
void printOnSaleInfo(OnSale_t* node)
{
	if (0 == node->allowance)
		return;
	printf("�� %7u�� %48s�� %10.2f�� %10s�� %6u��\n", node->product.id, node->product.name, node->product.price, typeConv[node->product.type], node->allowance);
	return;
}

/**
 * \brief ������������Ʒ (Storage_t) ��Ϣ
 *
 * \param node Ҫ����Ŀ����Ʒ�ڵ�
 */
void printStorageInfo(Storage_t* node)
{
	printf("�� %7u�� %48s�� %10.2f�� %10.2f�� %24s�� %8u��\n", node->product.id, node->product.name, node->product.price, node->product.purchase, node->product.supplier, node->allowance);
	return;
}

/**
 * \brief �������Ա�� (Employee_t) ��Ϣ
 *
 * \param node Ҫ�����Ա����Ϣ�ڵ�
 */
void printEmployeeInfo(Employee_t* node)
{
	printf("�� %5u�� %8s�� %6s�� %5u�� %15s��\n", node->id, node->name, sexConv[node->sex], node->age, node->position);
	return;
}

/**
 * \brief ������������� (Supplier_t) ��Ϣ
 *
 * \param node Ҫ����Ĺ�������Ϣ�ڵ�
 */
void printSupplierInfo(Supplier_t* node)
{
	printf("�� %5u�� %40s��\n", node->id, node->name);
	return;
}

/**
 * \brief ����������� (Order_t) �Ĵ�����Ϣ
 *
 * \param node Ҫ����Ķ�����Ϣ�ڵ�
 */
void printOrderInfo(Order_t* node)
{
	char* timeStr = timeConv(node->time);
	printf("�� %7u�� %20s�� %6u�� %12.2f��\n", node->id, timeStr, node->operatorId, node->total);
	/* timeConv ���ص��������һ����ʱ�ڴ�ռ䣬�����˾��ͷš��������ԣ�������д�Ļ��ᵼ���ڴ�й¶ (ռ����ÿ�� 400K ���ҵ��ٶ�����)�� */
	free(timeStr);
	return;
}

/**
 * \brief ����������� (Order_t) ����ϸ��Ϣ
 *
 * \param node Ҫ����Ķ�����Ϣ�ڵ�
 */
void printOrderDetail(Order_t* node)
{
	int i = 0;
	while (node->items[i].product.id != 0)
	{
		printf("�� %7u�� %48s�� %10.2f�� %6d�� %12.2f��\n", node->items[i].product.id,
			node->items[i].product.name, node->items[i].product.price,
			node->items[i].quantity, node->items[i].quantity * node->items[i].product.price);
		++i;
	}
	return;
}

/**
 * \brief ���� ID ���ҽڵ��������е�λ�á������ں� ID �Ľṹ�����͡�
 *
 * \param head Ҫ���ҵ�����ͷ
 * \param id �������� (ID)
 *
 * \return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
 */
int findIndexByID(Node_t* head, unsigned int id)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (*(unsigned int*)(tHead->data) == id)
		{
			flag = true;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

/**
* \brief ���� ID ���ҽڵ��������е�λ�á������ں� ID �Ľṹ�����͡�
*
* \param head Ҫ���ҵ�����ͷ
* \param id �������� (ID)
* \param dest �ش����ҵ����������ڵ�ʵ�ʵ�ַ
*
* \return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findIndexByID_d(Node_t* head, unsigned int id, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (*(unsigned int*)(tHead->data) == id)
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

/**
* \brief �������Ʋ��ҽڵ��������е�λ�á����������� Product_t, Employee_t �� Supplier_t.
*
* \param head Ҫ���ҵ�����ͷ
* \param id �������� (ID)
* \param offset ��Ӧ��������������Ҫ��ƫ���� (OFFSET_XXX)
*
* \return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findIndexByName(Node_t* head, char* name, const int offset)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (0 == strcmp((char*)tHead->data + offset, name))
		{
			flag = true;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

/**
* \brief �������Ʋ��ҽڵ��������е�λ�á����������� Product_t, Employee_t �� Supplier_t.
*
* \param head Ҫ���ҵ�����ͷ
* \param id �������� (ID)
* \param offset ��Ӧ��������������Ҫ��ƫ���� (OFFSET_XXX)
* \param dest �ش����ҵ����������ڵ�ʵ�ʵ�ַ
*
* \return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findIndexByName_d(Node_t* head, char* name, const int offset, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (0 == strcmp((char*)tHead->data + offset, name))
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

/**
* \brief ��ȡ��Ʒ���ڽڵ��λ��
*
* \param head Ҫ���ҵ�����ͷ
* \param id �������� (ID)
*
* \return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProduct(Node_t* head, unsigned int id)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		/* OnSale_t �� Storage_t �Ľṹ��һ���� */
		if ((*(Storage_t*)tHead->data).product.id == id)
		{
			flag = true;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

/**
* \brief ��ȡ��Ʒ���ڽڵ��λ��
*
* \param head Ҫ���ҵ�����ͷ
* \param id �������� (ID)
* \param dest �ش����ҵ�����Ʒ���ڿ�����ܽڵ��ʵ�ʵ�ַ
*
* \return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProduct_d(Node_t* head, unsigned int id, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		/* OnSale_t �� Storage_t �Ľṹ��һ���� */
		if ((*(Storage_t*)tHead->data).product.id == id)
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

/**
* \brief ��ȡ��Ʒ���ڽڵ��λ��
*
* \param head Ҫ���ҵ�����ͷ
* \param id �������� (��Ʒ��)
*
* \return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProductByName(Node_t* head, char* name)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (0 == strcmp((char*)tHead->data + OFFSET_PRODUCT, name))
		{
			flag = true;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}

/**
* \brief ��ȡ��Ʒ���ڽڵ��λ��
*
* \param head Ҫ���ҵ�����ͷ
* \param id �������� (��Ʒ��)
* \param dest �ش����ҵ�����Ʒ���ڿ�����ܽڵ��ʵ�ʵ�ַ
*
* \return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProductByName_d(Node_t* head, char* name, void** dest)
{
	int count = 1;
	bool flag = false;

	if (NULL == head->next)
		return 0;

	Node_t* tHead = head->next;

	while (tHead != NULL)
	{
		if (0 == strcmp((char*)tHead->data + OFFSET_PRODUCT, name))
		{
			flag = true;
			*dest = tHead->data;
			break;
		}
		tHead = tHead->next;
		++count;
	}

	if (flag)
		return count;
	else
		return 0;
}