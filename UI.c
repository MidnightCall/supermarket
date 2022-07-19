/*****************************************************************//**
 * \file   UI.c
 * \brief  对菜单界面显示的集中实现
 *
 * \author moonlightvigil
 * \date   July 2022
 *********************************************************************/

#include "UI.h"
#include <stdlib.h>

/**
 * \brief 展示初始界面的欢迎信息
 *
 */
void showWelcomeMessage(void)
{
    system("cls");
    printf("┌────────────────────────────────────────────────┐\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│              欢迎使用超市管理系统              │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    /* 最后一行已删去，和下方菜单的第一行连接 */
}

/**
 * \brief 展示登录与注册的菜单页面
 */
void showLoginMessage(void)

{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                    1. 登录                     │\n");
    printf("│                    2. 注册                     │\n");
    printf("│                    3. 退出                     │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示超级管理员功能选择页面
 */
void showSuperAdminMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                1. 账户管理                     │\n");
    printf("│                2. 职工信息管理                 │\n");
    printf("│                3. 退出                         │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示管理员功能选择页面
 *
 */
void showAdminMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│              1. 在售商品信息管理               │\n");
    printf("│              2. 供货商信息                     │\n");
    printf("│              3. 订单审核                       │\n");
    printf("│              4. 库存管理                       │\n");
    printf("│              5. 退出                           │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示普通用户功能选择页面
 *
 */
void showUserMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                 1. 在售商品查询                │\n");
    printf("│                 2. 当前订单管理                │\n");
    printf("│                 3. 退出                        │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示员工管理页面
 */
void showEmployeeBusinessMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│               1. 显示所有员工信息              │\n");
    printf("│               2. 查找员工信息                  │\n");
    printf("│               3. 添加员工信息                  │\n");
    printf("│               4. 删除员工信息                  │\n");
    printf("│               5. 修改员工信息                  │\n");
    printf("│               6. 返回上一级                    │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示供应商管理页面
 *
 */
void showSupplierBusinessMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│              1. 显示所有供应商信息             │\n");
    printf("│              2. 查找供应商信息                 │\n");
    printf("│              3. 修改供应商信息                 │\n");
    printf("│              4. 添加供应商信息                 │\n");
    printf("│              5. 删除供应商信息                 │\n");
    printf("│              6. 返回上一级                     │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示订单管理页面
 *
 */
void showOrderBusinessMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│              1. 显示所有订单信息               │\n");
    printf("│              2. 查找订单信息                   │\n");
    printf("│              3. 按时间查找...                  │\n");
    printf("│              4. 返回上一级                     │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示处理当前订单页面
 *
 */
void showCurrentOrderMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                 1. 添加商品                    │\n");
    printf("│                 2. 删除商品                    │\n");
    printf("│                 3. 更改数量                    │\n");
    printf("│                 4. 交付订单                    │\n");
    printf("│                 5. 展示订单信息                │\n");
    printf("│                 6. 退出                        │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示库存管理页面
 *
 */
void showStorageBusinessMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│              1. 显示所有库存商品信息           │\n");
    printf("│              2. 查找库存商品信息               │\n");
    printf("│              3. 修改商品属性                   │\n");
    printf("│              4. 入库                           │\n");
    printf("│              5. 出库 (上架)                    │\n");
    printf("│              6. 返回上一级                     │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示在售商品处理页面
 *
 */
void showOnSaleBusinessMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│            1. 显示所有在售商品信息             │\n");
    printf("│            2. 查找在售商品信息                 │\n");
    printf("│            3. 下架在售商品                     │\n");
    printf("│            4. 返回上一级                       │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示结束页面
 *
 */
void showExitMessage(void)
{
    printf("┌────────────────────────────────────────────────┐\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│                    感谢使用                    │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 展示账户管理界面
 *
 */
void showAccountBusinessMenu(void)
{
    printf("├────────────────────────────────────────────────┤\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("│               1. 显示所有用户信息              │\n");
    printf("│               2. 查询用户信息                  │\n");
    printf("│               3. 更改用户权限                  │\n");
    printf("│               4. 注销用户                      │\n");
    printf("│               5. 返回上一级                    │\n");
    printf("│                                                │\n");
    printf("│                                                │\n");
    printf("└────────────────────────────────────────────────┘\n");
}

/**
 * \brief 显示用户信息表头 (您好, 尊敬的 XXX)
 *
 * \param user 要显示对应信息的用户
 */
void showTitle(User_t user)
{
    system("cls");
    printf("┌────────────────────────────────────────────────┐\n");
    switch (user.permission)
    {
    case SU:
        printf("│          您好，尊敬的超级管理员 10000          │\n");
        break;
    case ADMIN:
        printf("│            您好，尊敬的管理员 %5d            │\n", user.id);
        break;
    case COMMON:
        printf("│             您好，尊敬的用户 %5d             │\n", user.id);
        break;
    default:
        printf("├ ─  H E L L O, D E B U G G E R [ 9 9 9 9 9 ]  ─ ┤\n");
        break;
    }
    //printf("└────────────────────────────────────────────────┘\n");
}
