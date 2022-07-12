#ifndef LOGIN_H_
#define LOGIN_H

#define FLUSH while(getchar() != '\n')
#define ASIZE 9   /* 存储账号的数组大小 */
#define PSIZE 12  /* 存储密码的数组大小 */

struct userInfo
{
	char* account[ASIZE];
	char* password[PSIZE];
};

/* 一般类型定义 */
typedef struct userInfo UI;

/*
* 操作：运行登录/注册系统
*/
void runLogIn();

/*
* 操作：显示操作菜单、读取用户的选择的操作
* 后置条件：显示操作菜单
*/
int getChoice();


#endif // !REGGISTER_H_
