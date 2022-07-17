/*****************************************************************//**
 * \file   account.h
 * \brief  
 * 
 * \author praist
 * \date   July 2022
 *********************************************************************/

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


void runLogIn();

int getChoice();

/*
* ²Ù×÷£º×¢²áÕËºÅ
*/
void registration();

/*
* ²Ù×÷£ºµÇÂ¼ÕËºÅ
*/
void logIn();

#endif // !REGGISTER_H_
