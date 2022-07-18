/*****************************************************************//**
 * \file   customLookup.h
 * \brief  ���ض��ṹ��������Ϣ�Ĵ�ӡ�Ͱ�������ѯ�����ļ���ʵ��
 * 
 * \author East Monster
 * \date   July 2022
 *********************************************************************/

#ifndef __CUSTOM_LOOKUP_H_
#define __CUSTOM_LOOKUP_H_

/* �ṹ���ڲ��ڴ�ƫ��ֵ */
extern const int OFFSET_PRODUCT;
extern const int OFFSET_EMPLOYEE;
extern const int OFFSET_SUPPLIER;
extern const int OFFSET_PRODUCT_TYPE;
extern const int OFFSET_PRODUCT_SUPPLIER;

/**
 * @brief ��������û� (User_t) ��Ϣ
 *
 * @param node Ҫ������û���Ϣ�ڵ�
 */
void printUserInfo(User_t* node);

/**
 * @brief ���������Ʒ (Product_t) ��Ϣ
 *
 * @param node Ҫ�������Ʒ��Ϣ�ڵ�
 */
void printProductInfo(Product_t* node);

/**
 * @brief �������������Ʒ (OnSale_t) ��Ϣ
 *
 * @param node Ҫ�����������Ʒ�ڵ�
 */
void printOnSaleInfo(OnSale_t* node);

/**
 * @brief ������������Ʒ (Storage_t) ��Ϣ
 *
 * @param node Ҫ����Ŀ����Ʒ�ڵ�
 */
void printStorageInfo(Storage_t* node);

/**
 * @brief �������Ա�� (Employee_t) ��Ϣ
 *
 * @param node Ҫ�����Ա����Ϣ�ڵ�
 */
void printEmployeeInfo(Employee_t* node);

/**
 * @brief ������������� (Supplier_t) ��Ϣ
 *
 * @param node Ҫ����Ĺ�������Ϣ�ڵ�
 */
void printSupplierInfo(Supplier_t* node);

/**
 * @brief ����������� (Order_t) �Ĵ�����Ϣ
 *
 * @param node Ҫ����Ķ�����Ϣ�ڵ�
 */
void printOrderInfo(Order_t* node);

/**
 * @brief ����������� (Order_t) ����ϸ��Ϣ
 *
 * @param node Ҫ����Ķ�����Ϣ�ڵ�
 */
void printOrderDetail(Order_t* node);

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

/**
* @brief ��ȡ��Ʒ���ڽڵ��λ��
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (ID)
* 
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProduct(Node_t* head, unsigned int id);

/**
* @brief ��ȡ��Ʒ���ڽڵ��λ��
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (ID)
* @param dest �ش����ҵ�����Ʒ���ڿ�����ܽڵ��ʵ�ʵ�ַ
*
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProduct_d(Node_t* head, unsigned int id, void** dest);

/**
* @brief ��ȡ��Ʒ���ڽڵ��λ��
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (��Ʒ��)
*
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProductByName(Node_t* head, char* name);

/**
* @brief ��ȡ��Ʒ���ڽڵ��λ��
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (��Ʒ��)
* @param dest �ش����ҵ�����Ʒ���ڿ�����ܽڵ��ʵ�ʵ�ַ
*
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProductByName_d(Node_t* head, char* name, void** dest);

/**
* @brief ��ȡ��Ʒ���ڽڵ��λ��
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (��Ʒ����)
* @param dest �ش����ҵ�����Ʒ���ڿ�����ܽڵ��ʵ�ʵ�ַ
*
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProductByType(Node_t* head, ProductTypeEnum type, void** dest);

/**
* @brief ��ȡ��Ʒ���ڽڵ��λ��
*
* @param head Ҫ���ҵ�����ͷ
* @param id �������� (��Ӧ����)
* @param dest �ش����ҵ�����Ʒ���ڿ�����ܽڵ��ʵ�ʵ�ַ
*
* @return �ڵ��������е�λ�á��������ڣ��򷵻� 0.
*/
int findProductBySupplier(Node_t* head, const char* supplier, void** dest);
#endif