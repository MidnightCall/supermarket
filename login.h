#ifndef LOGIN_H_
#define LOGIN_H_

#define FLUSH while(getchar() != '\n')
#define PSIZE 12  /* �洢����������С */

struct userInfo
{
	int id;
	char* password[PSIZE];
};

/* һ�����Ͷ��� */
typedef struct userInfo UI;

/*
* ���������е�¼/ע��ϵͳ
*/
void runLogIn();

/*
* ��������ʾ�����˵�����ȡ�û���ѡ��Ĳ���
* ������������ʾ�����˵�
*/
int getChoice();

/*
* ������ע���˺�
*/
void registration();

/*
* ��������¼�˺�
*/

#endif // !REGGISTER_H_
