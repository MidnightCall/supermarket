#ifndef LOGIN_H_
#define LOGIN_H

#define FLUSH while(getchar() != '\n')
#define ASIZE 9   /* �洢�˺ŵ������С */
#define PSIZE 12  /* �洢����������С */

struct userInfo
{
	char* account[ASIZE];
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


#endif // !REGGISTER_H_
