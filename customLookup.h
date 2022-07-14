#ifndef __CUSTOM_LOOKUP_H_
#define __CUSTOM_LOOKUP_H_

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
* @brief �������Ʋ��ҽڵ��������е�λ�á����������� Product_t, Employee_t �� Supplier_t.
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (ID)
* @param type ��Ӧ����������ö��
*
* @return �ڵ��������е�λ�á��������ڻ����˲�֧�ֵ����ͣ��򷵻� 0.
*/
int findIndexByName(Node_t* head, char* name, RequiredTypeEnum type);


#endif