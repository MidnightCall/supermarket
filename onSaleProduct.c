#include "onSaleProduct.h"
#include "helpfulFunction.h"

/* �ֲ�����ģ�� */
static int getChoice();
static void showSingleOnSale(OnSale_t* onSale);
extern User_t currentUser;
/**
*  @brief: ����������Ʒ����
*
*/
void runOnSaleProductSystem()
{
	while (1)
	{
		int choice = getChoice();

		switch (choice)
		{
		default:
			return;
		case 1:
			displayOnSaleProduct();
			PAUSE;
			break;
		case 2:
			queryOnSaleProduct();
			break;
		}
	}
}

void queryOnSaleProduct(void)
{
	if (NULL == productDat->next)
	{
		printf("�����ϻ�û����Ʒ���޷���ѯ��Ϣ��");
		PAUSE;
		return;
	}

	displayOnSaleProduct();

	unsigned int id = 0;
	char tempName[48];
	int op = 0, onSaleType;
	OnSale_t* onSale = NULL;
	while (true)
	{
		printf("�������ѯ���� [0. ID, 1. ��Ʒ��, 2. ����]: ");
		scanf("%d", &op);
		if (op > 2 || op < 0)
		{
			printf("����Ĳ�����ʽ����ȷ�����������롣");
			PAUSE;
			continue;
		}
		break;
	}

	getchar();
	switch (op)
	{
	case 0:
		id = getNonNegativeNumber("��Ʒ ID");

		if (findProduct_d(productDat, id, &onSale))
			showSingleOnSale(onSale);
		else
			printf("������ %d ����Ʒ\n", id);
		break;

	case 1:
		printf("��������Ʒ��: ");
		stringGet(tempName, 48);

		if (findProductByName_d(productDat, tempName, &onSale))
			showSingleOnSale(onSale);
		else
			printf("��������Ʒ [%s]\n", tempName);
		break;

	case 2:
		while (1)
		{
			onSaleType = getNonNegativeNumber("��Ʒ����\n[0. ����    , 1. ����Ʒ  ]\n[2. �칫��Ʒ, 3. ʳƷ    ]\n[4. ��ˮ����, 5. ���õ���]");
			if (onSaleType > 5)
			{
				printf("����Ĳ�����ʽ����ȷ�����������롣");
				PAUSE;
				continue;
			}
			break;
		}

		printf("�������������������Щ�������������������������������������������������������������Ʒ��ϸ��Ϣ���������������Щ����������������������Щ����������������������Щ���������������\n");
		printf("�� %7s�� %48s�� %10s�� %10s�� %6s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "����");
		printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤��������������\n");

		Node_t* tHead = productDat;
		tHead = productDat->next;
		bool flag = false;

		while (tHead != NULL)
		{
			if (*(ProductTypeEnum*)((char*)tHead->data + 84) == onSaleType)
			{
				printOnSaleInfo(tHead->data);
				flag = true;
			}
			tHead = tHead->next;
		}

		if (!flag)
		{
			printf("��                                       һ��Ҳû�С�                                       ��\n");
		}

		printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة���������������\n");
	}
	PAUSE;
	return;
}

/**
*  @brief: ��ʾ���д�����Ʒ��Ϣ
*
*/
void displayOnSaleProduct(void)
{
	printf("�������������������Щ�������������������������������������������������������������Ʒ��ϸ��Ϣ���������������Щ����������������������Щ����������������������Щ���������������\n");
	printf("�� %7s�� %48s�� %10s�� %10s�� %6s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "����");
	printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤��������������\n");
	printList(productDat, printOnSaleInfo, false);
	printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة���������������\n");
	
	return;
}

/* �ֲ�����ʵ�� */
static int getChoice()
{
	int choice = 0;

	showTitle(currentUser);
	do
	{
		showOnSaleBusinessMenu();
		HINT;
		scanf("%d", &choice);
	} while (choice > 3 || choice < 1);
	flush();

	return choice;
}

static void showSingleOnSale(OnSale_t* onSale)
{
	printf("�������������������Щ�������������������������������������������������������������Ʒ��ϸ��Ϣ���������������Щ����������������������Щ����������������������Щ���������������\n");
	printf("�� %7s�� %48s�� %10s�� %10s�� %6s��\n", "��Ʒ ID", "��Ʒ��", "����", "����", "����");
	printf("�������������������੤�������������������������������������������������������������������������������������������������੤���������������������੤���������������������੤��������������\n");
	printOnSaleInfo(onSale);
	printf("�������������������ة��������������������������������������������������������������������������������������������������ة����������������������ة����������������������ة���������������\n");
	return;
}
