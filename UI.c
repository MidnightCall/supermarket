#include "UI.h"
#include <stdlib.h>

void showWelcomeMessage()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("|              欢迎使用超市管理系统              |\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showLoginMessage()

{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("|                    1. 登录                     |\n");
    printf("|                    2. 注册                     |\n");
    printf("|                    3. 退出                     |\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showSuperAdminMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("|                  1. 账户管理                   |\n");
    printf("|                  2. 职工信息管理               |\n");
    printf("|                  3. 退出                       |\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showAdminMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|              1. 在售商品信息管理               |\n");
    printf("|              2. 供货商信息                     |\n");
    printf("|              3. 订单审核                       |\n");
    printf("|              4. 库存管理                       |\n");
    printf("|              5. 退出                           |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showUserMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                 |\n");
    printf("|                                                 |\n");
    printf("|                 1. 在售商品查询                 |\n");
    printf("|                 2. 当前订单管理                 |\n");
    printf("|                     3. 退出                     |\n");
    printf("|                                                 |\n");
    printf("|                                                 |\n");
    printf("└------------------------------------------------┘\n");
}

void showEmployeeBusinessMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|               1. 显示所有员工信息              |\n");
    printf("|               2. 查找员工信息                  |\n");
    printf("|               3. 添加员工信息                  |\n");
    printf("|               4. 删除员工信息                  |\n");
    printf("|               5. 修改员工信息                  |\n");
    printf("|               6. 返回上一级                    |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showSupplierBusinessMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|              1. 显示所有供应商信息             |\n");
    printf("|              2. 查找供应商信息                 |\n");
    printf("|              3. 添加供应商信息                 |\n");
    printf("|              4. 删除供应商信息                 |\n");
    printf("|              5. 返回上一级                     |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showOrderBusinessMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|              1. 显示所有订单信息               |\n");
    printf("|              2. 查找订单信息                   |\n");
    printf("|              3. 计算总营业额                   |\n");
    printf("|              4. 返回上一级                     |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showCurrentOrderMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|                 1. 添加商品                    |\n");
    printf("|                 2. 删除商品                    |\n");
    printf("|                 3. 更改数量                    |\n");
    printf("|                 4. 计算金额                    |\n");
    printf("|                 5. 交付订单                    |\n");
    printf("|                 6. 展示订单信息                |\n");
    printf("|                    7.退出                      |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showStorageBusinessMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|              1. 显示所有库存商品信息           |\n");
    printf("|              2. 查找库存商品信息               |\n");
    printf("|              3. 入库                           |\n");
    printf("|              4. 出库                           |\n");
    printf("|              5. 返回上一级                     |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showOnSaleBusinessMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("|            1. 显示所有在售商品信息             |\n");
    printf("|            2. 查找在售商品信息                 |\n");
    printf("|            3. 返回上一级                       |\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showExitMessage()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("|                    感谢使用                    |\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showAccountBusinessMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|               1. 显示所有用户信息              |\n");
    printf("|               2. 查询用户信息                  |\n");
    printf("|               3. 更改用户权限                  |\n");
    printf("|               4. 注销用户                      |\n");
    printf("|               5. 返回上一级                    |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showProductMenu()
{
    printf("┌------------------------------------------------┐\n");
    printf("|                                                |\n");
    printf("|              1. 显示所有商品信息               |\n");
    printf("|              2. 查找商品信息                   |\n");
    printf("|              3. 添加新的商品信息               |\n");
    printf("|              4. 删除商品信息                   |\n");
    printf("|              5. 退出                           |\n");
    printf("|                                                |\n");
    printf("└------------------------------------------------┘\n");
}

void showTitle(User_t user)
{
    system("cls");
    printf("┌------------------------------------------------┐\n");
    switch (user.permission)
    {
    case SU:
        printf("|          您好，尊敬的超级管理员 10000          |\n");
        break;
    case ADMIN:
        printf("|            您好，尊敬的管理员 %5d            |\n", user.id);
        break;
    case COMMON:
        printf("|             您好，尊敬的用户 %5d             |\n", user.id);
        break;
    default:
        printf("?????????????????????你是谁??????????????????????\n");
        break;
    }
    printf("└------------------------------------------------┘\n");
}
