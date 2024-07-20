/*Linear Table On Sequence Structure*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;   //数据类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

//顺序表结构定义
typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

typedef struct{  //线性表的管理表定义
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;

status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType &e);
int LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType &pre);
status NextElem(SqList L,ElemType e,ElemType &next);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType &e);
status ListTraverse(SqList L);
status SaveList(SqList L,char FileName[]);
status LoadList(SqList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
int Multi_LinearTable_management();
status sortList(SqList &L);
int SubArrayNum(SqList L, int k);
int MaxSubArray(SqList L);

int main(void)
{
    SqList L;
    L.elem = NULL;
    printf("*************************************************\n");
    printf("*                   WELCOME                     *\n");
    printf("*              author: Zhou Yujie               *\n");
    printf("*************************************************\n");

    int op = -1;
    while(op){
        printf("\n\n");
        printf("MENU\n");
        printf("-------------------------------------------------\n");
        printf("|    1.InitList              9.NextElem         |\n");
        printf("|    2.DestroyList           10.ListInsert      |\n");
        printf("|    3.ClearList             11.ListDelete      |\n");
        printf("|    4.ListEmpty             12.ListTraverse    |\n");
        printf("|    5.ListLength            13.SaveList        |\n");
        printf("|    6.GetElem               14.LoadList        |\n");
        printf("|    7.LocateElem            15.Multi-linear    |\n");
        printf("|    8.PriorElem                table           |\n");
        printf("|    0.exit                                     |\n");
        printf("-------------------------------------------------\n");
        printf("|ADDITIONAL:                                    |\n");
        printf("|    16.sortList             17.SubArrayNum     |\n");
        printf("|    18.MaxSubArray                             |\n");
        printf("-------------------------------------------------\n");
        printf("请输入选择[0-18]:");
        scanf("%d", &op);
        int states = 0;
        enum st{EXIT = 0, INIT_LIST = 1, DESTROY_LIST, CLEAR_LIST, LIST_EMPTY, LIST_LENGTH, GET_ELEM, LOCATE_ELEM, PRIOR_ELEM,
            NEXT_ELEM, LIST_INSERT, LIST_DELETE, LIST_TRABVERSE, SAVE_LIST, LOAD_LIST, MULTI_TABLLE, SORT_LIST, SUB_ARRAY_NUM, MAX_SUB_ARRAY};
        int e = 0;
        int pos = 0;
        char name[30];
        int k;
        switch(op){
            case EXIT:
                break;
            case INIT_LIST:
                printf("\n");
                states = InitList(L);
                if(states == OK)
                    printf("InitList: Success!\n");
                else if(states == INFEASIBLE){
                    printf("InitList: ERROR!\n");
                    printf("线性表已存在.\n");
                }
                break;
            case DESTROY_LIST:
                printf("\n");
                states = DestroyList(L);
                if(states == OK)
                    printf("DestroyList: Success!\n");
                else if(states == INFEASIBLE){
                    printf("DestroyList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                break;
            case CLEAR_LIST:
                printf("\n");
                states = ClearList(L);
                if(states == OK)
                    printf("ClearList: Success!\n");
                else if(states == INFEASIBLE){
                    printf("ClearList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                break;
            case LIST_EMPTY:
                printf("\n");
                states = ListEmpty(L);
                if(states == INFEASIBLE){
                    printf("ListEmpty: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == TRUE)
                    printf("线性表为空.\n");
                else
                    printf("线性表不为空.\n");
                break;
            case LIST_LENGTH:
                printf("\n");
                states = ListLength(L);
                if(states == INFEASIBLE){
                    printf("ListLength: ERROR!.\n");
                    printf("线性表不存在.\n");
                }
                else
                    printf("线性表长度为%d.\n", states);
                break;
            case GET_ELEM:
                states = ListLength(L);
                if(states == INFEASIBLE){
                    printf("\nGetElem: ERROR!.\n");
                    printf("线性表不存在.\n");
                }
                else if(states == 0){
                    printf("线性表无元素.\n");
                }
                else{
                    printf("\n请输入您想查看的元素的位置.\n");
                    printf("位置的范围在 1-%d 内.\n", states);
                    scanf("%d", &pos);
                    states = GetElem(L, pos, e);
                    if(states == ERROR){
                        printf("GetElem: ERROR!\n");
                        printf("位置的范围应当在 1-%d.\n", ListLength(L));
                    }
                    else
                        printf("第%d个元素为%d.\n", pos, e);
                }
                break;
            case LOCATE_ELEM:
                printf("\n");
                printf("请输入您想查看的元素：");
                scanf("%d", &e);
                states = LocateElem(L, e);
                if(states == INFEASIBLE){
                    printf("LocateElem: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == 0)
                    printf("元素不存在.\n");
                else
                    printf("元素%d在表中第%d个位置.\n", e, states);
                break;
            case PRIOR_ELEM:
                printf("\n");
                printf("请输入元素：");
                scanf("%d", &pos);
                states = PriorElem(L, pos, e);
                if(states == INFEASIBLE){
                    printf("PriorElem: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == ERROR){
                    printf("LocateElem: ERROR!\n");
                    printf("前驱元素不存在.\n");
                }
                else
                    printf("前驱元素为%d.\n", e);
                break;
            case NEXT_ELEM:
                printf("\n");
                printf("请输入元素：");
                scanf("%d", &pos);
                states = NextElem(L, pos, e);
                if(states == INFEASIBLE){
                    printf("NextElem: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == ERROR){
                    printf("NextElem: ERROR!\n");
                    printf("后继元素不存在.\n");
                }
                else
                    printf("后继元素为%d.\n", e);
                break;
            case LIST_INSERT:
                printf("\n");
                printf("请输入您想插入的位置和元素：");
                scanf("%d%d", &pos, &e);
                states = ListInsert(L, pos, e);
                if(states == INFEASIBLE){
                    printf("ListInsert: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == ERROR){
                    printf("ListInsert: ERROR!\n");
                    printf("插入位置非法!\n");
                }
                else
                    printf("ListInsert: Success!\n");
                break;
            case LIST_DELETE:
                printf("\n");
                printf("请输入您想删除的元素的位置：\n");
                scanf("%d", &pos);
                states = ListDelete(L, pos, e);
                if(states == INFEASIBLE){
                    printf("ListDelete: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == ERROR){
                    printf("ListDelete: ERROR!\n");
                    printf("删除位置非法!\n");
                }
                else
                    printf("ListDelete: Success!\n");
                break;
            case LIST_TRABVERSE:
                printf("\n");
                states = ListTraverse(L);
                if(states == INFEASIBLE){
                    printf("ListTraverse: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else {
                    if(L.length == 0)
                        printf("空线性表.\n");
                    printf("ListTraverse: Success!\n");
                }
                break;
            case SAVE_LIST:
                printf("\n");
                printf("输入1对文件进行命名，输入0为默认名称.\n");
                scanf("%d", &states);
                if(states == 1){
                    scanf("%s", name);
                    states = SaveList(L, name);
                    if(states == INFEASIBLE){
                        printf("SaveList: ERROR!\n");
                        printf("线性表不存在.\n");
                    }
                    else if(states == ERROR){
                        printf("SaveList: ERROR!\n");
                        printf("无法打开文件!\n");
                    }
                    else
                        printf("SaveList: Success!\n");
                }
                else if(states == 0){
                    states = SaveList(L, "save.dat");
                    if(states == INFEASIBLE){
                        printf("SaveList: ERROR!\n");
                        printf("线性表不存在.\n");
                    }
                    else if(states == ERROR){
                        printf("SaveList: ERROR!\n");
                        printf("无法打开文件!\n");
                    }
                    else
                        printf("SaveList: Success!\n");
                }
                else
                    printf("请输入1或0!\n");
                break;
            case LOAD_LIST:
                printf("\n");
                printf("请输入您想加载的文件名称.\n");
                scanf("%s", name);
                states = LoadList(L, name);
                if(states == INFEASIBLE){
                    printf("LoadList: ERROR!\n");
                    printf("线性表已存在.\n");
                }
                else if(states == ERROR){
                    printf("LoadList: ERROR!\n");
                    printf("打不开文件!\n");
                }
                else
                    printf("LoadList: Success!\n");
                break;
            case MULTI_TABLLE:
                Multi_LinearTable_management();
                op = -1;
                continue;
            case SORT_LIST:
                printf("\n");
                states = sortList(L);
                if(states == INFEASIBLE){
                    printf("sortList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else
                    printf("sortList: Success!\n");
                break;
            case SUB_ARRAY_NUM:
                printf("\n");
                printf("请输入子数组的和K：");
                scanf("%d", &k);
                states = SubArrayNum(L, k);
                if(states == INFEASIBLE){
                    printf("SubArrayNum: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else{
                    printf("有%d个和为%d的子数组。\n", states, k);
                    printf("SubArrayNum: Success!\n");
                }
                break;
            case MAX_SUB_ARRAY:
                printf("\n");
                states = MaxSubArray(L);
                if (states == INFEASIBLE){
                    printf("MaxSubArray: ERROR!\n");
                    printf("线性表不存在或线性表为空.\n");
                }
                else{
                    printf("最大连续子数组和为%d.\n", states);
                    printf("MaxSubArray: Success!\n");
                }
                break;
            default:
                printf("\n");
                printf("您的选择应当在[0-18]的范围内！\n");
                break;
        }
        while(getchar() != '\n');//清空控制台中字符等非法字符
        if(op != 0) op = -1; //防止op因未改变且在读入操作时未赋新值而继续上一步的操作
    }
    printf("\n\n");
    printf("*************************************************\n");
    printf("*             Welcome back again!               *\n");
    printf("*************************************************\n");
    printf("\n\n");
    system("pause");
    return 0;
}

int Multi_LinearTable_management() {
    int op = -1;
    LISTS ls;
    ls.length = 0;
    ls.listsize = 0;
    while (op) {
        printf("\n\n");
        printf("MENU-多线性表管理\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("+    0.exit                  9.NextElem         +\n");
        printf("+    1.InitList              10.ListInsert      +\n");
        printf("+    2.DestroyList           11.ListDelete      +\n");
        printf("+    3.ClearList             12.ListTraverse    +\n");
        printf("+    4.ListEmpty             13.SaveList        +\n");
        printf("+    5.ListLength            14.LoadList        +\n");
        printf("+    6.GetElem               15.AddList         +\n");
        printf("+    7.LocateElem            16.RemoveList      +\n");
        printf("+    8.PriorElem             17.LocateList      +\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("+ADDITIONAL:                                    +\n");
        printf("+    18.sortList             19.SubArrayNum     +\n");
        printf("+    20.MaxSubArray                             +\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("请输入选择[0-20]:");
        scanf("%d", &op);
        int states = 0;
        int k = 0;
        enum st {
            EXIT = 0,
            INIT_LIST = 1,
            DESTROY_LIST,
            CLEAR_LIST,
            LIST_EMPTY,
            LIST_LENGTH,
            GET_ELEM,
            LOCATE_ELEM,
            PRIOR_ELEM,
            NEXT_ELEM,
            LIST_INSERT,
            LIST_DELETE,
            LIST_TRABVERSE,
            SAVE_LIST,
            LOAD_LIST,
            ADD_LIST,
            REMOVE_LIST,
            LOCATE_LIST,
            SORT_LIST,
            SUB_ARRAY_NUM,
            MAX_SUB_ARRAY
        };
        int e = 0;
        int pos = 0;
        int ls_pos = 0;
        char name[30];
        switch (op) {
            case EXIT:
                break;
            case INIT_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                states = InitList(ls.elem[ls_pos - 1].L);
                if (states == OK)
                    printf("InitList: Success!\n");
                else if (states == INFEASIBLE) {
                    printf("InitList: ERROR!\n");
                    printf("线性表已存在.\n");
                }
                break;
            case DESTROY_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                states = DestroyList(ls.elem[ls_pos - 1].L);
                if (states == OK)
                    printf("DestroyList: Success!\n");
                else if (states == INFEASIBLE) {
                    printf("DestroyList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                break;
            case CLEAR_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                states = ClearList(ls.elem[ls_pos - 1].L);
                if (states == OK)
                    printf("ClearList: Success!\n");
                else if (states == INFEASIBLE) {
                    printf("ClearList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                break;
            case LIST_EMPTY:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                states = ListEmpty(ls.elem[ls_pos - 1].L);
                if (states == INFEASIBLE) {
                    printf("ListEmpty: ERROR!\n");
                    printf("线性表不存在.\n");
                } else if (states == TRUE)
                    printf("线性表为空.\n");
                else
                    printf("线性表不为空.\n");
                break;
            case LIST_LENGTH:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                states = ListLength(ls.elem[ls_pos - 1].L);
                if (states == INFEASIBLE) {
                    printf("ListLength: ERROR!.\n");
                    printf("线性表不存在.\n");
                } else
                    printf("线性表长度为%d.\n", states);
                break;
            case GET_ELEM:
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                states = ListLength(ls.elem[ls_pos - 1].L);
                if (states == INFEASIBLE) {
                    printf("\nGetElem: ERROR!.\n");
                    printf("线性表不存在.\n");
                } else if (states == 0) {
                    printf("线性表无元素.\n");
                } else {
                    printf("\n请输入您想查看的元素的位置.\n");
                    printf("位置的范围在 1-%d 内.\n", states);
                    scanf("%d", &pos);
                    states = GetElem(ls.elem[ls_pos - 1].L, pos, e);
                    if (states == ERROR) {
                        printf("GetElem: ERROR!\n");
                        printf("位置的范围应当在 1-%d.\n", ListLength(ls.elem[ls_pos - 1].L));
                    } else
                        printf("第%d个元素为%d.\n", pos, e);
                }
                break;
            case LOCATE_ELEM:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("请输入您想查看的元素：");
                scanf("%d", &e);
                states = LocateElem(ls.elem[ls_pos - 1].L, e);
                if (states == INFEASIBLE) {
                    printf("LocateElem: ERROR!\n");
                    printf("线性表不存在.\n");
                } else if (states == 0)
                    printf("元素不存在.\n");
                else
                    printf("元素%d在表中第%d个位置.\n", e, states);
                break;
            case PRIOR_ELEM:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("请输入元素：");
                scanf("%d", &pos);
                states = PriorElem(ls.elem[ls_pos - 1].L, pos, e);
                if (states == INFEASIBLE) {
                    printf("PriorElem: ERROR!\n");
                    printf("线性表不存在.\n");
                } else if (states == ERROR) {
                    printf("LocateElem: ERROR!\n");
                    printf("前驱元素不存在.\n");
                } else
                    printf("前驱元素为%d.\n", e);
                break;
            case NEXT_ELEM:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("请输入元素：");
                scanf("%d", &pos);
                states = NextElem(ls.elem[ls_pos - 1].L, pos, e);
                if (states == INFEASIBLE) {
                    printf("NextElem: ERROR!\n");
                    printf("线性表不存在.\n");
                } else if (states == ERROR) {
                    printf("NextElem: ERROR!\n");
                    printf("后继元素不存在.\n");
                } else
                    printf("后继元素为%d.\n", e);
                break;
            case LIST_INSERT:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("请输入您想插入的位置和元素：");
                scanf("%d%d", &pos, &e);
                states = ListInsert(ls.elem[ls_pos - 1].L, pos, e);
                if (states == INFEASIBLE) {
                    printf("ListInsert: ERROR!\n");
                    printf("线性表不存在.\n");
                } else if (states == ERROR) {
                    printf("ListInsert: ERROR!\n");
                    printf("插入位置非法!\n");
                } else
                    printf("ListInsert: Success!\n");
                break;
            case LIST_DELETE:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("请输入您想删除的元素的位置：\n");
                scanf("%d", &pos);
                states = ListDelete(ls.elem[ls_pos - 1].L, pos, e);
                if (states == INFEASIBLE) {
                    printf("ListDelete: ERROR!\n");
                    printf("线性表不存在.\n");
                } else if (states == ERROR) {
                    printf("ListDelete: ERROR!\n");
                    printf("删除位置非法!\n");
                } else
                    printf("ListDelete: Success!\n");
                break;
            case LIST_TRABVERSE:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                states = ListTraverse(ls.elem[ls_pos - 1].L);
                if (states == INFEASIBLE) {
                    printf("ListTraverse: ERROR!\n");
                    printf("线性表不存在.\n");
                } else {
                    if(ls.elem[ls_pos - 1].L.length == 0)
                        printf("空线性表\n");
                    printf("ListTraverse: Success!\n");
                }
                break;
            case SAVE_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("输入1对文件进行命名，输入0为默认名称.\n");
                scanf("%d", &states);
                if (states == 1) {
                    scanf("%s", name);
                    states = SaveList(ls.elem[ls_pos - 1].L, name);
                    if (states == INFEASIBLE) {
                        printf("SaveList: ERROR!\n");
                        printf("线性表不存在.\n");
                    } else if (states == ERROR) {
                        printf("SaveList: ERROR!\n");
                        printf("无法打开文件!\n");
                    } else
                        printf("SaveList: Success!\n");
                } else if (states == 0) {
                    states = SaveList(ls.elem[ls_pos - 1].L, "save.dat");
                    if (states == INFEASIBLE) {
                        printf("SaveList: ERROR!\n");
                        printf("线性表不存在.\n");
                    } else if (states == ERROR) {
                        printf("SaveList: ERROR!\n");
                        printf("无法打开文件!\n");
                    } else
                        printf("SaveList: Success!\n");
                } else
                    printf("请输入1或0!\n");
                break;
            case LOAD_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("请输入您想加载的文件名称.\n");
                scanf("%s", name);
                states = LoadList(ls.elem[ls_pos - 1].L, name);
                if (states == INFEASIBLE) {
                    printf("LoadList: ERROR!\n");
                    printf("线性表已存在.\n");
                } else if (states == ERROR) {
                    printf("LoadList: ERROR!\n");
                    printf("打不开文件!\n");
                }
                else
                    printf("LoadList: Success!\n");
                break;
            case ADD_LIST:
                printf("\n");
                printf("请输入新增的表名(25个英文字符以内)：");
                scanf("%s", name);
                states = AddList(ls, name);
                if(states == OVERFLOW){
                    printf("AddList: ERROR!\n");
                    printf("表已满，无法再添加.\n");
                }
                else if(states == ERROR){
                    printf("AddList: ERROR!\n");
                    printf("命名字符数超过上限！\n");
                }
                else
                    printf("AddList: Success!\n");
                break;
            case REMOVE_LIST:
                printf("\n");
                printf("请输入要删除的表名：");
                scanf("%s", name);
                states = RemoveList(ls, name);
                if(states == ERROR){
                    printf("RemoveList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else
                    printf("RemoveList: Success!\n");
                break;
            case LOCATE_LIST:
                printf("\n");
                printf("请输入要查找的表名：");
                scanf("%s", name);
                states = LocateList(ls, name);
                if(!states){
                    printf("LocateList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else
                    printf("您所查找的线性表在第%d个位置.\n", states);
                break;
            case SORT_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = sortList(ls.elem[ls_pos-1].L);
                if(states == INFEASIBLE){
                    printf("sortList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else
                    printf("sortList: Success!\n");
                break;
            case SUB_ARRAY_NUM:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                printf("请输入子数组的和K：");
                scanf("%d", &k);
                states = SubArrayNum(ls.elem[ls_pos-1].L, k);
                if(states == INFEASIBLE){
                    printf("SubArrayNum: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else{
                    printf("有%d个和为%d的子数组。\n", states, k);
                    printf("SubArrayNum: Success!\n");
                }
                break;
            case MAX_SUB_ARRAY:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = MaxSubArray(ls.elem[ls_pos-1].L);
                if (states == INFEASIBLE){
                    printf("MaxSubArray: ERROR!\n");
                    printf("线性表不存在或线性表为空.\n");
                }
                else{
                    printf("最大连续子数组和为%d.\n", states);
                    printf("MaxSubArray: Success!\n");
                }
                break;
            default:
                printf("\n");
                printf("您的选择应当在[0-20]的范围内！\n");
                break;
        }
        while(getchar() != '\n');
        if(op != 0) op = -1;
    }
    return 0;
}

status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK， 否则返回INFEASIBLE。
{
    if(L.elem)
        return INFEASIBLE;	//线性表存在，则返回INFEASIBLE
    L.elem = (ElemType*) malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    if(!L.elem)
        exit(OVERFLOW);	//申请不到空间，溢出，则退出程序并返回OVERFLOW
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    L.length = 0;
    L.listsize = 0;
    free(L.elem);
    L.elem = NULL;
    return OK;
}

status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    if(L.length)
        return FALSE;
    return TRUE;
}

status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    return L.length;
}

status GetElem(SqList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    if(i < 1 || i > L.length)
        return ERROR;
    e = L.elem[i - 1];
    return OK;
}

int LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    if(!L.elem)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        if(L.elem[i] == e)
            return i + 1;
    }
    return 0;
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        if(L.elem[i] == e){
            if(i == 0)
                return ERROR;
            pre = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR;
}

status NextElem(SqList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        if(L.elem[i] == e){
            if(i == L.length - 1)
                return ERROR;
            next = L.elem[i + 1];
            return OK;
        }
    }
    return ERROR;
}

status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    if(i < 1 || i > L.length + 1)
        return ERROR;
    if(L.length == L.listsize){
        L.elem = (ElemType*) realloc(L.elem, sizeof(ElemType)*(L.listsize + LISTINCREMENT));
        if(L.elem == NULL)
            exit(OVERFLOW);
        L.listsize += LISTINCREMENT;
    }
    for (int j = L.length - 1; j >= i - 1; j--)
    {
        L.elem[j + 1] = L.elem[j];
    }
    L.elem[i - 1] = e;
    L.length ++;
    return OK;
}

status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    if(i < 1 || i > L.length)
        return ERROR;
    e = L.elem[i - 1];
    for (int j = i - 1; j < L.length; j++)
    {
        L.elem[j] = L.elem[j + 1];
    }
    L.length --;
    return OK;
}

status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        printf("%d", L.elem[i]);
        printf("%c", (i == L.length - 1 ? '\n' : ' '));
    }
    return OK;
}

status SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(!L.elem)
        return INFEASIBLE;
    FILE *fp = fopen(FileName, "wb");
    if(!fp)
        return ERROR;
    fwrite(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    return OK;
}

status LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L.elem)
        return INFEASIBLE;
    FILE *fp = fopen(FileName, "rb");
    if(!fp)
        return ERROR;
    L.elem = (ElemType*) malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    if(!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    while(fread(&L.elem[L.length], sizeof(ElemType), 1, fp)){
        L.length ++;
        if(L.length >= L.listsize){
            L.elem = (ElemType*) realloc(L.elem, sizeof(ElemType) * (L.listsize + LISTINCREMENT));
            if(!L.elem)
                exit(OVERFLOW);
            L.listsize += LISTINCREMENT;
        }
    }
    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    if(Lists.length == 10)
        return OVERFLOW;
    int i = 0;
    while(ListName[i])  i++;
    if(i >= 30)
        return ERROR;
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = (ElemType*) malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    Lists.elem[Lists.length].L.length = 0;
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
    Lists.length ++;
    return OK;
}

status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    int pos;
    for (pos = 0; pos < Lists.length; pos++)
    {
        if(!strcmp(Lists.elem[pos].name, ListName))
            break;
    }
    if(pos == Lists.length)
        return ERROR;
    free(Lists.elem[pos].L.elem);
    for(int i = pos; i < Lists.length - 1; i ++){
        strcpy(Lists.elem[i].name, Lists.elem[i+1].name);
        if(Lists.elem[i].L.listsize < Lists.elem[i+1].L.listsize){
            Lists.elem[i].L.elem = (ElemType*) realloc(Lists.elem[i+1].L.elem, Lists.elem[i+1].L.listsize);
            Lists.elem[i].L.listsize = Lists.elem[i+1].L.listsize;
            Lists.elem[i].L.length = Lists.elem[i+1].L.length;
        }
        else{
            for (int j = 0; j < Lists.elem[i + 1].L.length; ++j) {
                Lists.elem[i].L.elem[j] = Lists.elem[i+1].L.elem[j];
            }
            Lists.elem[i].L.length = Lists.elem[i+1].L.length;
        }
    }
    Lists.length --;
    free(Lists.elem[Lists.length].L.elem);
    return OK;
}

int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    int pos = 0;
    while(pos < Lists.length && strcmp(Lists.elem[pos].name, ListName))
    {
        pos ++;
    }
    if(pos == Lists.length)
        return 0;
    return pos + 1;
}

status sortList(SqList &L)
{
    if(!L.elem)
        return INFEASIBLE;
    ElemType tmp;
    int i, j;
    for(i = 0; i < L.length - 1; i ++){
        for(j = 0; j < L.length - 1 - i; j ++){
            if(L.elem[j] > L.elem[j + 1]){
                tmp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = tmp;
            }
        }
    }
    return OK;
}

int SubArrayNum(SqList L, int k)
{
    if(!L.elem)
        return INFEASIBLE;
    if(L.length == 1 || L.length == 0)
        return 0;
    SqList prefix;
    prefix.elem = (ElemType *) malloc(sizeof(ElemType) * (L.length + 5));
    prefix.length = 0;
    int sum = 0;
    prefix.elem[0] = sum;
    prefix.length ++;
    for(int i = 0; i < L.length; i ++){
        sum += L.elem[i];
        prefix.elem[prefix.length] = sum;
        prefix.length ++;
    }
    int num = 0;
    for(int i = 1; i < prefix.length; i ++){
        int j;
        for(j = i; j < prefix.length; j ++){
            if(prefix.elem[j] - prefix.elem[i - 1] == k)
                if(j - i + 1 >= 2)
                    num ++;
        }
    }
    free(prefix.elem);
    return num;
}

int MaxSubArray(SqList L)
{
    if(!L.elem)
        return INFEASIBLE;
    if(L.length == 0)
        return INFEASIBLE;
    int ThisSum, MaxSum, j;
    ThisSum = 0;
    MaxSum = 0;
    for(j = 0; j < L.length; j ++){
        ThisSum += L.elem[j];
        if(ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if(ThisSum < 0)
            ThisSum = 0;
    }
    return MaxSum;
}
