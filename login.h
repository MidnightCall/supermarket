#ifndef LOGIN_H_
#define LOGIN_H_

#define FLUSH while(getchar() != '\n')
#define PSIZE 12  /* 存储密码的数组大小 */

struct userInfo
{
	int id;
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

/*
* 操作：注册账号
*/
void registration();

/*
* 操作：登录账号
*/

#endif // !REGGISTER_H_
