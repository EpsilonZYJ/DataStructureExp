#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
//带头结点的链表

typedef struct LISTNode{
    struct {
        char name[30];
        LinkList L;
    };
    struct LISTNode *next;
}LISTNode, *LISTS;

status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
status LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status SaveList(LinkList L,char FileName[]);
status LoadList(LinkList &L,char FileName[]);
status reverseList(LinkList &L);
status RemoveNthFromEnd(LinkList &L, int n);
void swap_data(LNode* &s, LNode* &p);
status sortList(LinkList &L);
int Multi_LinearTable_management();
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &List, char ListName[]);
int LocateList(LISTS Lists, char ListName[], ...);

int main(void){
    printf("*************************************************\n");
    printf("*                   WELCOME                     *\n");
    printf("*              author: Zhou Yujie               *\n");
    printf("*************************************************\n");

    LinkList L;
    L = NULL;
    int op = -1;
    while(op){
        printf("\n\n");
        printf("MENU\n");
        printf("--------------------------------------------------\n");
        printf("|    1.InitList              9.NextEelem         |\n");
        printf("|    2.DestroyList           10.ListInsert       |\n");
        printf("|    3.ClearList             11.ListDelete       |\n");
        printf("|    4.ListEmpty             12.ListTrabverse    |\n");
        printf("|    5.ListLength            13.SaveList         |\n");
        printf("|    6.GetElem               14.LoadList         |\n");
        printf("|    7.LocateElem                                |\n");
        printf("|    8.PriorElem                                 |\n");
        printf("|    0.exit                                      |\n");
        printf("--------------------------------------------------\n");
        printf("|ADDITIONAL:                                     |\n");
        printf("|    15.reverseList         17.sortList          |\n");
        printf("|    16.RemoveNthFromEnd    18.Multi-linear table|\n");
        printf("--------------------------------------------------\n");
        printf("请输入选择[0-18]:");
        scanf("%d", &op);

        int states = 0;
        enum st{
            EXIT = 0, INIT_LIST = 1, DESTROY_LIST, CLEAR_LIST, LIST_EMPTY, LIST_LENGTH, GET_ELEM, LOCATE_ELEM,
        PRIOR_ELEM, NEXT_ELEM, LIST_INSERT, LIST_DELETE, LIST_TRABVERSE, SAVE_LIST, LOAD_LIST, REVERSE_LIST,
        REMOVE_NTH_FROM_END, SORT_LIST, MULT_LINEAR_TABLE
        };
        int e = 0;
        int pos = 0;
        char name[30];
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
                else if(states == ERROR)
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
                    if(L->next == NULL)
                        printf("线性表为空.\n");
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
            case REVERSE_LIST:
                printf("\n");
                states = reverseList(L);
                if(states == INFEASIBLE){
                    printf("reverseList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else
                    printf("reverseList: Success!\n");
                break;
            case SORT_LIST:
                printf("\n");
                states = sortList(L);
                if(states == INFEASIBLE){
                    printf("sortList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == ERROR){
                    printf("sortList: ERROR!\n");
                    printf("线性表为空.\n");
                }
                else
                    printf("sortList: Success!\n");
                break;
            case REMOVE_NTH_FROM_END:
                printf("\n");
                printf("请输入您想移除倒数第几个元素\n");
                scanf("%d", &pos);
                states = RemoveNthFromEnd(L, pos);
                if(states == INFEASIBLE){
                    printf("RemoveNthFromEnd: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == ERROR){
                    printf("RemoveNthFromEnd: ERROR!\n");
                    printf("删除位置非法.\n");
                }
                else
                    printf("RemoveNthFromEnd: Success!\n");
                break;
            case MULT_LINEAR_TABLE:
                Multi_LinearTable_management();
                op = -1;
                continue;
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

int Multi_LinearTable_management(){
    LISTS ls;
    ls = (LISTS) malloc(sizeof(LISTNode));
    ls->next = NULL;
    int op = -1;
    while(op){
        printf("\n\n");
        printf("MENU\n");
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("+    1.InitList              12.ListTrabverse    +\n");
        printf("+    2.DestroyList           13.SaveList         +\n");
        printf("+    3.ClearList             14.LoadList         +\n");
        printf("+    4.ListEmpty             15.reverseList      +\n");
        printf("+    5.ListLength            16.RemoveNthFromEnd +\n");
        printf("+    6.GetElem               17.sortList         +\n");
        printf("+    7.LocateElem            18.AddList          +\n");
        printf("+    8.PriorElem             19.RemoveList       +\n");
        printf("+    9.NextEelem             20.LocateList       +\n");
        printf("+    10.ListInsert                               +\n");
        printf("+    11.ListDelete                               +\n");
        printf("+    0.exit                                      +\n");
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("请输入选择[0-20]:");
        scanf("%d", &op);

        int states = 0;
        enum st{
            EXIT = 0, INIT_LIST = 1, DESTROY_LIST, CLEAR_LIST, LIST_EMPTY, LIST_LENGTH, GET_ELEM, LOCATE_ELEM,
            PRIOR_ELEM, NEXT_ELEM, LIST_INSERT, LIST_DELETE, LIST_TRABVERSE, SAVE_LIST, LOAD_LIST, REVERSE_LIST, REMOVE_NTH_FROM_END,
            SORT_LIST, ADD_LIST, REMOVE_LIST, LOCATE_LIST
        };
        int e = 0;
        int pos = 0;
        char name[30];
        LISTNode *ls_p = NULL;
        int ls_pos = 0;
        switch(op){
            case EXIT:
                break;
            case INIT_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = InitList(ls_p->L);
                if(states == OK)
                    printf("InitList: Success!\n");
                else if(states == INFEASIBLE){
                    printf("InitList: ERROR!\n");
                    printf("线性表已存在.\n");
                }
                break;
            case DESTROY_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = DestroyList(ls_p->L);
                if(states == OK)
                    printf("DestroyList: Success!\n");
                else if(states == INFEASIBLE){
                    printf("DestroyList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                break;
            case CLEAR_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = ClearList(ls_p->L);
                if(states == OK)
                    printf("ClearList: Success!\n");
                else if(states == INFEASIBLE){
                    printf("ClearList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                break;
            case LIST_EMPTY:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = ListEmpty(ls_p->L);
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
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = ListLength(ls_p->L);
                if(states == INFEASIBLE){
                    printf("ListLength: ERROR!.\n");
                    printf("线性表不存在.\n");
                }
                else
                    printf("线性表长度为%d.\n", states);
                break;
            case GET_ELEM:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                states = ListLength(ls_p->L);
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
                    states = GetElem(ls_p->L, pos, e);
                    if(states == ERROR){
                        printf("GetElem: ERROR!\n");
                        printf("位置的范围应当在 1-%d.\n", ListLength(ls_p->L));
                    }
                    else
                        printf("第%d个元素为%d.\n", pos, e);
                }
                break;
            case LOCATE_ELEM:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                printf("请输入您想查看的元素：");
                scanf("%d", &e);
                states = LocateElem(ls_p->L, e);
                if(states == INFEASIBLE){
                    printf("LocateElem: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == ERROR)
                    printf("元素不存在.\n");
                else
                    printf("元素%d在表中第%d个位置.\n", e, states);
                break;
            case PRIOR_ELEM:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                printf("请输入元素：");
                scanf("%d", &pos);
                states = PriorElem(ls_p->L, pos, e);
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
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                printf("请输入元素：");
                scanf("%d", &pos);
                states = NextElem(ls_p->L, pos, e);
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
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                printf("请输入您想插入的位置和元素：");
                scanf("%d%d", &pos, &e);
                states = ListInsert(ls_p->L, pos, e);
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
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                printf("请输入您想删除的元素的位置：\n");
                scanf("%d", &pos);
                states = ListDelete(ls_p->L, pos, e);
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
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = ListTraverse(ls_p->L);
                if(states == INFEASIBLE){
                    printf("ListTraverse: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else {
                    if(ls_p->L->next == NULL)
                        printf("线性表为空.\n");
                    printf("ListTraverse: Success!\n");
                }
                break;
            case SAVE_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                printf("输入1对文件进行命名，输入0为默认名称.\n");
                scanf("%d", &states);
                if(states == 1){
                    scanf("%s", name);
                    states = SaveList(ls_p->L, name);
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
                    states = SaveList(ls_p->L, "save.dat");
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
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                printf("请输入您想加载的文件名称.\n");
                scanf("%s", name);
                states = LoadList(ls_p->L, name);
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
            case REVERSE_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = reverseList(ls_p->L);
                if(states == INFEASIBLE){
                    printf("reverseList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else
                    printf("reverseList: Success!\n");
                break;
            case SORT_LIST:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                states = sortList(ls_p->L);
                if(states == INFEASIBLE){
                    printf("sortList: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == ERROR){
                    printf("sortList: ERROR!\n");
                    printf("线性表为空.\n");
                }
                else
                    printf("sortList: Success!\n");
                break;
            case REMOVE_NTH_FROM_END:
                printf("\n");
                printf("请输入您想操作的表名：");
                scanf("%s", name);
                ls_pos = LocateList(ls, name, &ls_p);
                if (ls_pos == 0) {
                    printf("线性表不存在");
                    break;
                }
                printf("\n");
                printf("请输入您想移除倒数第几个元素\n");
                scanf("%d", &pos);
                states = RemoveNthFromEnd(ls_p->L, pos);
                if(states == INFEASIBLE){
                    printf("RemoveNthFromEnd: ERROR!\n");
                    printf("线性表不存在.\n");
                }
                else if(states == ERROR){
                    printf("RemoveNthFromEnd: ERROR!\n");
                    printf("删除位置非法.\n");
                }
                else
                    printf("RemoveNthFromEnd: Success!\n");
                break;
            case ADD_LIST:
                printf("\n");
                printf("请输入新增的表名(25个英文字符以内):");
                scanf("%s", name);
                states = AddList(ls, name);
                if(states == ERROR){
                    printf("AddList: ERROR!\n");
                    printf("命名字符超过上限.\n");
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
            default:
                printf("\n");
                printf("您的选择应当在[0-20]的范围内！\n");
                break;
        }
        while(getchar() != '\n');//清空控制台中字符等非法字符
        if(op != 0) op = -1; //防止op因未改变且在读入操作时未赋新值而继续上一步的操作
    }
    return 0;
}

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L)
        return INFEASIBLE;
    L = (LinkList) malloc(sizeof(LNode));
    L->next = NULL;
    return OK;
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    LNode *s = L;
    while(L->next != NULL){
        L = L->next;
        free(s);
        s = L;
    }
    free(s);
    L = NULL;
    s = NULL;
    return OK;
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    LNode *s = L->next;
    while(L->next != NULL){
        L->next = s->next;
        free(s);
        s = L->next;
    }
    return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    if(L->next == NULL)
        return TRUE;
    return FALSE;
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    int len = 0;
    LNode *s = L;
    while(s->next != NULL){
        s = s->next;
        len ++;
    }
    return len;
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    if(i < 1)
        return ERROR;
    int pos = 0;
    LNode *s = L;
    while(pos < i && s){
        s = s->next;
        pos ++;
    }
    if(!s)
        return ERROR;
    e = s->data;
    return OK;
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    int pos = 0;
    LNode *s = L;
    while(s && s->data != e){
        s = s->next;
        pos ++;
    }
    if(!s)
        return ERROR;
    return pos;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    LNode *s = L;
    if(s->next == NULL || s->next->data == e)
        return ERROR;
    while(s->next != NULL){
        if(s->next->data == e){
            pre = s->data;
            return OK;
        }
        s = s->next;
    }
    return ERROR;
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    LNode *s = L;
    if(s->next == NULL)
        return ERROR;
    s = s->next;
    while(s->next != NULL){
        if(s->data == e){
            next = s->next->data;
            return OK;
        }
        s = s->next;
    }
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    if(i < 1)
        return ERROR;
    int pos = 0;
    LNode *s = L;
    while(s && pos < i - 1){
        s = s->next;
        pos ++;
    }
    if(!s)
        return ERROR;
    LNode *p = (LNode *) malloc(sizeof(LNode));
    p->data = e;
    p->next = s->next;
    s->next = p;
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    if(i < 1)
        return ERROR;
    int pos = 0;
    LNode *s = L;
    while(s && pos < i - 1){
        s = s->next;
        pos ++;
    }
    if(!s)
        return ERROR;
    if(!s->next)
        return ERROR;
    LNode *p = s->next;
    e = p->data;
    s->next = p->next;
    free(p);
    return OK;
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    LNode *s = L->next;
    while(s){
        printf("%d", s->data);
        printf("%c",(s->next ? ' ' : '\n'));
        s = s->next;
    }
    return OK;
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(!L)
        return INFEASIBLE;
    FILE *fp = fopen(FileName, "w");
    if(!fp)
        return ERROR;
    LNode *s = L->next;
    while(s){
        fprintf(fp, "%d", s->data);
        fprintf(fp, "%c", (s->next ? ' ' : '\n'));
        s = s->next;
    }
    fclose(fp);
    return OK;
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L)
        return INFEASIBLE;
    L = (LinkList) malloc(sizeof(LNode));
    L->next = NULL;
    FILE *fp = fopen(FileName, "r");
    if(!fp)
        return ERROR;
    ElemType data;
    LNode *cur, *pre;
    pre = L;
    while(fscanf(fp, "%d", &data) != EOF){
        cur = (LNode*) malloc(sizeof(LNode));
        cur->data = data;
        pre->next = cur;
        pre = cur;
    }
    cur->next = NULL;
    fclose(fp);
    return OK;
}

status reverseList(LinkList &L)
{
    if(!L)
        return INFEASIBLE;
    if(!L->next)
        return OK;
    LinkList rev = (LinkList) malloc(sizeof(LNode));
    LNode *L_cur;
    L_cur = L->next;
    rev->next = NULL;
    while(L_cur != NULL){
        L->next = L_cur->next;
        L_cur->next = rev->next;
        rev->next = L_cur;
        L_cur = L->next;
    }
    L->next = rev->next;
    free(rev);
    rev = NULL;
    L_cur = NULL;
    return OK;
}

status RemoveNthFromEnd(LinkList &L, int n)
{
    if(!L)
        return INFEASIBLE;
    if(!L->next || n < 1)
        return ERROR;
    int cnt = 0;
    LNode *pre, *cur;
    pre = cur = L;
    while(cnt < n && pre->next != NULL){
        pre = pre->next;
        cnt ++;
    }
    if(cnt < n)
        return ERROR;
    while(pre->next != NULL){
        pre = pre->next;
        cur = cur->next;
    }
    LNode *s = cur->next;
    cur->next = s->next;
    free(s);
    s = NULL;
    return OK;
}

void swap_data(LNode* &s, LNode* &p)
{
    int tmp;
    tmp = s->data;
    s->data = p->data;
    p->data = tmp;
}

status sortList(LinkList &L)
{
    if(!L)
        return INFEASIBLE;
    if(L->next == NULL)
        return ERROR;
    LNode *s, *p;
    s = L->next;
    p = L->next;
    for(s; s != NULL; s = s->next){
        for(p = s->next; p != NULL; p = p->next){
            if(s->data > p->data)
                swap_data(s, p);
        }
    }
    return OK;
}

status AddList(LISTS &Lists, char ListName[])
{
    LISTNode *s = (LISTNode *) malloc(sizeof(LISTNode));
    int i = 0;
    while(ListName[i]) i ++;
    if(i >= 30)
        return ERROR;
    strcpy(s->name, ListName);
    s->L = NULL;
    InitList(s->L);
    s->next = Lists->next;
    Lists->next = s;
    return OK;
}

status RemoveList(LISTS &List, char ListName[])
{
    if(!List->next)
        return ERROR;
    LISTNode *cur, *nxt;
    cur = List;
    nxt = cur->next;
    while(nxt && strcmp(nxt->name, ListName) != 0){
        cur = cur->next;
        nxt = nxt->next;
    }
    if(nxt == NULL)
        return ERROR;
    cur->next = nxt->next;
    free(nxt);
    nxt = NULL;
    return OK;
}

int LocateList(LISTS Lists, char ListName[], ...)
{
    if(!Lists->next)
        return 0;
    int pos = 1;
    LISTNode *cur = Lists->next;
    while(cur && strcmp(cur->name, ListName) != 0){
        cur = cur->next;
        pos ++;
    }
    if(!cur)
        return 0;
    va_list ap;
    va_start(ap, 1);
    LISTNode **s = va_arg(ap, LISTNode**);
    if(s){
        *s = cur;
        va_end(ap);
    }
    return pos;
}
