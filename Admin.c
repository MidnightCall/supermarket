#include "Admin.h"

/* �ֲ�����ģ�� */
static int getChoice();

void runAdminSystem()
{
	int choice = getChoice();

	switch (choice)
	{
		default:
			break;
		case 1:
			// ������Ʒ����
			break;
		case 2:
			// �����̹���
			break;
		case 3:
			// ��������
			break;
		case 4:
			//������
			break;
	}
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice;

	do
	{
		showAdminMenu();
		scanf("%d", &choice);
	} while (choice > 5 || choice < 1);

	return choice;
}