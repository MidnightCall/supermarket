#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typeCollection.h"
#include "UI.h"
#include "helpfulFunction.h"
#include "linkList.h"
#include "files.h"
#include "helpfulFunction.h"
#include "customLookup.h"

extern Node_t* userDat;
extern User_t currentUser;

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
void logIn();

#endif // !REGGISTER_H_
