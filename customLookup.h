#ifndef __CUSTOM_LOOKUP_H_
#define __CUSTOM_LOOKUP_H_

/* �ڴ�ƫ��ֵ */
extern const int OFFSET_PRODUCT;
extern const int OFFSET_EMPLOYEE;
extern const int OFFSET_SUPPLIER;

/**
* @brief ָ���û���Ϣ�������ʽ
*
* @param node Ҫ������û���Ϣ�ڵ�
*/
void printUserInfo(User_t* node);

/* ���º���ִ�����ƹ��� */

void printProductInfo(Product_t* node);

void printEmployeeInfo(Employee_t* node);

void printSupplierInfo(Supplier_t* node);

void printStorageInfo(Storage_t* node);

void printOrderInfo(Order_t* node);

/**
* @brief ���� ID ���ҽڵ��������е�λ�á������ں� ID �Ľṹ�����͡�
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (ID)
* 
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findIndexByID(Node_t* head, unsigned int id);

/**
* @brief ���� ID ���ҽڵ��������е�λ�á������ں� ID �Ľṹ�����͡�
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (ID)
* @param dest �ش����ҵ����������ڵ�ʵ�ʵ�ַ
*
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findIndexByID_d(Node_t* head, unsigned int id, void** dest);

/**
* @brief �������Ʋ��ҽڵ��������е�λ�á����������� Product_t, Employee_t �� Supplier_t.
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (ID)
* @param offset ��Ӧ��������������Ҫ��ƫ���� (OFFSET_XXX)
*
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findIndexByName(Node_t* head, char* name, const int offset);

/**
* @brief �������Ʋ��ҽڵ��������е�λ�á����������� Product_t, Employee_t �� Supplier_t.
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (ID)
* @param offset ��Ӧ��������������Ҫ��ƫ���� (OFFSET_XXX)
* @param dest �ش����ҵ����������ڵ�ʵ�ʵ�ַ
*
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findIndexByName_d(Node_t* head, char* name, const int offset, void** dest);

#endif