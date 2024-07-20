#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define BOOL int
#define INFINITY INT_MAX

#define SET_INIT_SIZE 100
#define SETINCREMENT 10

typedef int status;

/******邻接表图******/
typedef int KeyType;
typedef enum {DG,DN,UDG,UDN} GraphKind;//{有向图，有向网，无向图，无向网}
typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //顶点类型定义

typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号
    struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;

typedef struct VNode{				//头结点及其数组类型定义
    VertexType data;       	//顶点信息
    ArcNode *firstarc;      	 //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;
/************/


/******多图管理******/
typedef struct{
    struct{
        char name[30];
        ALGraph Graph;
    }elem[100];
    int length;
    int listsize;
}GRAPHS;

status AddGraph(GRAPHS &graphs, char GraphName[]);
status RemoveGraph(GRAPHS &graphs, char GraphName[]);
int LocateGraph(GRAPHS &graphs, char GraphName[]);
status InitGRAPHS(GRAPHS &graphs);
/************/


/******辅助队列******/
typedef int QElemType;
typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode, *QNodePtr;

typedef struct LinkQueue{
    QNode *front;
    QNode *rear;
}LinkQueue;

status InitQueue(LinkQueue &Q);
status EnQueue(LinkQueue &Q, QElemType elem);
status DeQueue(LinkQueue &Q, QElemType &elem);
status QueueEmpty(LinkQueue Q);
status DestroyQueue(LinkQueue &Q);
/************/


/******集合******/
typedef KeyType SetElemType;
typedef struct{
    SetElemType *elem;
    int setsize;
    int setlength;
}Set, *SetPtr;

status SetInit(Set &set);
status SetInsert(Set &set, SetElemType elem);
status SetDestroy(Set &set);
void PrintSet(Set set, ALGraph G);
/************/


BOOL *visited;//标记是否遍历过

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2], GraphKind kind);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
void DFS(ALGraph G, int pos, void (*visit)(VertexType));

Set VerticesSetLessThanK(ALGraph G, KeyType v, int k);
int ShortestPathLength(ALGraph G, KeyType v, KeyType w);
void DFS_CCN(ALGraph G, int pos);
int ConnectedComponentsNums(ALGraph G);

status Multi_Graph_management();
void visit(VertexType v);

int main()
{
    ALGraph G;
    G.vexnum = 0;
    G.arcnum = 0;
    printf("**************************************************\n");
    printf("*                    WELCOME                     *\n");
    printf("*               author: Zhou Yujie               *\n");
    printf("**************************************************\n");

    int op = -1;
    while(op){
        printf("\n\n");
        printf("MENU\n");
        printf("-----------------------------------------------------\n");
        printf("|    1.CreateGraph        11.DFSTraverse            |\n");
        printf("|    2.DestroyGraph       12.BFSTraverse            |\n");
        printf("|    3.LocateVex          13.VerticesSetLessThanK   |\n");
        printf("|    4.PutVex             14.ShortestPathLength     |\n");
        printf("|    5.FirstAdjVex        15.ConnectedComponentsNums|\n");
        printf("|    6.NextAdjVex         16.SaveGraph              |\n");
        printf("|    7.InsertVex          17.LoadGraph              |\n");
        printf("|    8.DeleteVex          18.MultiGraphManagement   |\n");
        printf("|    9.InsertArc                                    |\n");
        printf("|    10.DeleteArc                                   |\n");
        printf("|    0.exit                                         |\n");
        printf("-----------------------------------------------------\n");
        printf("请输入选择[0-18]:");
        scanf("%d", &op);
        int states = 0;
        enum st{
            EXIT = 0, CREATE_GRAPH = 1, DESTROY_GRAPH, LOCATE_VEX, PUT_VEX,
            FIRST_ADJ_VEX, NEXT_ADJ_VEX, INSERT_VEX, DELETE_VEX, INSERT_ARC,
            DELETE_ARC, DFS_TRAVERSE, BFS_TRAVERSE, VERTICES_SET_LESS_THAN_K,
            SHORTEST_PATH_LENGTH, CONNECTED_COMPONENTS_NUMS, SAVE_GRAPH, LOAD_GRAPH,
            MULTI_GRAPH_MANAGEMENT
        };
        if(G.vexnum == 0 && (op != 0 && op != CREATE_GRAPH && op != LOAD_GRAPH && op != MULTI_GRAPH_MANAGEMENT)) {
            printf("Error!\n");
            printf("图为空！\n");
            continue;
        }
        KeyType e = 0;
        KeyType v;
        KeyType w;
        VertexType value;
        char others[20];
        int pos = 0;
        char name[30];
        int k;
        VertexType V[30];
        KeyType VR[30][2];
        Set st;
        switch(op){
            case EXIT:
                break;
            case CREATE_GRAPH:
                printf("\n");
                printf("请输入图的类型(DG=0,DN=1,UDG=2,UDN=3):");
                scanf("%d", &G.kind);
                printf("请输入顶点关键字和信息，以 -1 null 结尾：\n");
                k = 0;
                scanf("%d %s", &V[k].key, V[k].others);
                while (V[k].key != -1 && k < 30){
                    k ++;
                    scanf("%d %s", &V[k].key, V[k].others);
                }
                printf("请输入边，以 -1 -1 结尾:\n");
                k = 0;
                scanf("%d%d", &VR[k][0], &VR[k][1]);
                while(VR[k][0] != -1 && VR[k][1] != -1 && k < 30){
                    k ++;
                    scanf("%d%d", &VR[k][0], &VR[k][1]);
                }
                states = CreateGraph(G, V, VR, G.kind);
                if(states == ERROR){
                    printf("CreateGraph: Error!\n");
                    printf("创建失败！\n");
                }
                else printf("CreateGraph: Success!\n");
                break;
            case DESTROY_GRAPH:
                printf("\n");
                if(G.vexnum == 0){
                    printf("DestroyGraph: Error!\n");
                    printf("图为空！\n");
                }
                else{
                    states = DestroyGraph(G);
                    printf("DestroyGraph: Success!\n");
                }
                break;
            case LOCATE_VEX:
                printf("\n");
                printf("请输入您想要查找的顶点的关键字：");
                scanf("%d", &e);
                states = LocateVex(G, e);
                if(states == -1){
                    printf("LocateVex: Error!\n");
                    printf("未查找到顶点！\n");
                }
                else printf("您所查找的顶点的位序为%d.\n", states);
                break;
            case PUT_VEX:
                printf("\n");
                printf("请输入您想要修改的顶点的关键字：");
                scanf("%d", &e);
                printf("请输入修改后的关键字与顶点信息：");
                scanf("%d %s", &value.key, value.others);
                states = PutVex(G, e, value);
                if(states == ERROR){
                    printf("PutVex: Error!\n");
                    printf("未能查找到结点或结点关键字不唯一！\n");
                }
                else printf("PutVex: Success!\n");
                break;
            case FIRST_ADJ_VEX:
                printf("\n");
                printf("请输入顶点关键字：");
                scanf("%d", &e);
                states = FirstAdjVex(G, e);
                if(states == -1){
                    printf("FirstAdjVex: Error!\n");
                    printf("未查找到顶点！\n");
                }
                else printf("您所查找的结点的第一邻接点位序为%d,关键字为：%d,信息为：%s.\n", states, G.vertices[states].data.key, G.vertices[states].data.others);
                break;
            case NEXT_ADJ_VEX:
                printf("\n");
                printf("请输入您想查看哪个结点的下一邻接点(输入关键字):");
                scanf("%d", &v);
                printf("请输入您想查看相对于哪个结点的下一邻接点(输入关键字):");
                scanf("%d", &w);
                states = NextAdjVex(G, v, w);
                if(states == -1){
                    printf("NextAdjVex: Error!\n");
                    printf("未找到顶点！\n");
                }
                else printf("您所查找的结点的下一邻接点位序为%d,关键字为：%d,信息为：%s.\n", states, G.vertices[states].data.key, G.vertices[states].data.others);
                break;
            case INSERT_VEX:
                printf("\n");
                printf("请输入您想添加的顶点的关键字和信息：");
                scanf("%d %s", &value.key, value.others);
                states = InsertVex(G, value);
                if(states == ERROR){
                    printf("InsertVex: Error!\n");
                    printf("未能插入结点，数据溢出或关键字已经存在！\n");
                }
                else printf("InsertVex: Success!\n");
                break;
            case DELETE_VEX:
                printf("\n");
                printf("请输入您想删除的顶点的关键字：");
                scanf("%d", &e);
                states = DeleteVex(G, e);
                if(states == ERROR){
                    printf("DeleteVex: Error!\n");
                    printf("未能删除顶点，图不存在或顶点不存在！\n");
                }
                else printf("DeleteVex: Success!\n");
                break;
            case INSERT_ARC:
                printf("\n");
                printf("请输入您想增加的弧：");
                scanf("%d%d", &v, &w);
                states = InsertArc(G, v, w);
                if(states == ERROR){
                    printf("InsertArc: Error!\n");
                    printf("未找到相关顶点或弧已存在！\n");
                }
                else printf("InsertArc: Success!\n");
                break;
            case DELETE_ARC:
                printf("\n");
                printf("请输入您想删除的弧：");
                scanf("%d%d", &v, &w);
                states = DeleteArc(G, v, w);
                if(states == ERROR){
                    printf("DeleteArc: Error!\n");
                    printf("未找到相关顶点或未找到边！\n");
                }
                else printf("DeleteArc: Success!\n");
                break;
            case DFS_TRAVERSE:
                printf("\n");
                if(G.vexnum == 0){
                    printf("DFSTraverse: Error!\n");
                    printf("图不存在！\n");
                }
                else{
                    states = DFSTraverse(G, visit);
                    printf("\n");
                    printf("DFSTraverse: Success!\n");
                }
                break;
            case BFS_TRAVERSE:
                printf("\n");
                if(G.vexnum == 0){
                    printf("BFSTraverse: Error!\n");
                    printf("图不存在！\n");
                }
                else{
                    states = BFSTraverse(G, visit);
                    printf("\n");
                    printf("BFSTraverse: Success!\n");
                }
                break;
            case VERTICES_SET_LESS_THAN_K:
                printf("\n");
                printf("请输入顶点关键字：");
                scanf("%d", &v);
                printf("请输入路径长度小于几：");
                scanf("%d", &k);
                st = VerticesSetLessThanK(G, v, k);
                if(st.setlength == 0)
                    printf("不存在满足条件的顶点.\n");
                else PrintSet(st, G);
                SetDestroy(st);
                break;
            case SHORTEST_PATH_LENGTH:
                printf("\n");
                printf("请输入您想查看的路径的两个端点的关键字：");
                scanf("%d%d", &v, &w);
                states = ShortestPathLength(G, v, w);
                if(states == ERROR){
                    printf("ShortestPathLength: Error!\n");
                    printf("不存在顶点.\n");
                }
                else if(states == INFINITY) printf("两顶点不可达.\n");
                else    printf("两顶点的最短路径长度为%d.", states);
                break;
            case CONNECTED_COMPONENTS_NUMS:
                printf("\n");
                states = ConnectedComponentsNums(G);
                printf("连通分量数目为%d.", states);
                break;
            case SAVE_GRAPH:
                printf("\n");
                printf("请输入保存的文件名(不多于25个英文字符)：");
                scanf("%s", name);
                states = SaveGraph(G, name);
                if(G.vexnum == 0){
                    printf("SaveGraph: Error!\n");
                    printf("图不存在！\n");
                }
                else if(states == ERROR){
                    printf("SaveGraph: Error!\n");
                    printf("打不开文件！\n");
                }
                else    printf("SaveGraph: Success!\n");
                break;
            case LOAD_GRAPH:
                printf("\n");
                if(G.vexnum != 0){
                    printf("Error!\n");
                    printf("图已存在！\n");
                    continue;
                }
                printf("请输入加载的文件名：\n");
                scanf("%s", name);
                states = LoadGraph(G, name);
                if(states == ERROR){
                    printf("LoadGraph: Error!\n");
                    printf("打不开文件！\n");
                }
                else if(G.vexnum == 0){
                    printf("LoadGraph: Error!\n");
                    printf("图为空！\n");
                }
                else printf("LoadGraph: Success!\n");
                break;
            case MULTI_GRAPH_MANAGEMENT:
                Multi_Graph_management();
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

status Multi_Graph_management()
{
    GRAPHS graphs;
    InitGRAPHS(graphs);
    int op = -1;
    while(op){
        printf("\n\n");
        printf("MENU\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("+    1.CreateGraph        11.DFSTraverse            +\n");
        printf("+    2.DestroyGraph       12.BFSTraverse            +\n");
        printf("+    3.LocateVex          13.VerticesSetLessThanK   +\n");
        printf("+    4.PutVex             14.ShortestPathLength     +\n");
        printf("+    5.FirstAdjVex        15.ConnectedComponentsNums+\n");
        printf("+    6.NextAdjVex         16.SaveGraph              +\n");
        printf("+    7.InsertVex          17.LoadGraph              +\n");
        printf("+    8.DeleteVex          18.AddGraph               +\n");
        printf("+    9.InsertArc          19.RemoveGraph            +\n");
        printf("+    10.DeleteArc         20.LocateGraph            +\n");
        printf("+    0.exit                                         +\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("请输入选择[0-20]:");
        scanf("%d", &op);
        int states = 0;
        enum st{
            EXIT = 0, CREATE_GRAPH = 1, DESTROY_GRAPH, LOCATE_VEX, PUT_VEX,
            FIRST_ADJ_VEX, NEXT_ADJ_VEX, INSERT_VEX, DELETE_VEX, INSERT_ARC,
            DELETE_ARC, DFS_TRAVERSE, BFS_TRAVERSE, VERTICES_SET_LESS_THAN_K,
            SHORTEST_PATH_LENGTH, CONNECTED_COMPONENTS_NUMS, SAVE_GRAPH, LOAD_GRAPH,
            ADD_GRAPH, REMOVE_GRAPH, LOCATE_GRAPH
        };
        KeyType e = 0;
        KeyType v;
        KeyType w;
        VertexType value;
        char others[20];
        int pos = 0;
        char name[30];
        char graph_name[30];
        int k;
        int ls_pos;
        VertexType V[30];
        KeyType VR[30][2];
        Set st;
        switch(op){
            case EXIT:
                break;
            case CREATE_GRAPH:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                printf("请输入图的类型(DG=0,DN=1,UDG=2,UDN=3):");
                scanf("%d", &graphs.elem[ls_pos-1].Graph.kind);
                printf("请输入顶点关键字和信息，以 -1 null 结尾：\n");
                k = 0;
                scanf("%d %s", &V[k].key, V[k].others);
                while (V[k].key != -1 && k < 30){
                    k ++;
                    scanf("%d %s", &V[k].key, V[k].others);
                }
                printf("请输入边，以 -1 -1 结尾:\n");
                k = 0;
                scanf("%d%d", &VR[k][0], &VR[k][1]);
                while(VR[k][0] != -1 && VR[k][1] != -1 && k < 30){
                    k ++;
                    scanf("%d%d", &VR[k][0], &VR[k][1]);
                }
                states = CreateGraph(graphs.elem[ls_pos-1].Graph, V, VR, graphs.elem[ls_pos-1].Graph.kind);
                if(states == ERROR){
                    printf("CreateGraph: Error!\n");
                    printf("创建失败！\n");
                }
                else printf("CreateGraph: Success!\n");
                break;
            case DESTROY_GRAPH:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0){
                    printf("DestroyGraph: Error!\n");
                    printf("图为空！\n");
                }
                else{
                    states = DestroyGraph(graphs.elem[ls_pos-1].Graph);
                    printf("DestroyGraph: Success!\n");
                }
                break;
            case LOCATE_VEX:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入您想要查找的顶点的关键字：");
                scanf("%d", &e);
                states = LocateVex(graphs.elem[ls_pos-1].Graph, e);
                if(states == -1){
                    printf("LocateVex: Error!\n");
                    printf("未查找到顶点！\n");
                }
                else printf("您所查找的顶点的位序为%d.\n", states);
                break;
            case PUT_VEX:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入您想要修改的顶点的关键字：");
                scanf("%d", &e);
                printf("请输入修改后的关键字与顶点信息：");
                scanf("%d %s", &value.key, value.others);
                states = PutVex(graphs.elem[ls_pos-1].Graph, e, value);
                if(states == ERROR){
                    printf("PutVex: Error!\n");
                    printf("未能查找到结点或结点关键字不唯一！\n");
                }
                else printf("PutVex: Success!\n");
                break;
            case FIRST_ADJ_VEX:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入顶点关键字：");
                scanf("%d", &e);
                states = FirstAdjVex(graphs.elem[ls_pos-1].Graph, e);
                if(states == -1){
                    printf("FirstAdjVex: Error!\n");
                    printf("未查找到顶点！\n");
                }
                else printf("您所查找的结点的第一邻接点位序为%d,关键字为：%d,信息为：%s.\n", states, graphs.elem[ls_pos-1].Graph.vertices[states].data.key, graphs.elem[ls_pos-1].Graph.vertices[states].data.others);
                break;
            case NEXT_ADJ_VEX:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入您想查看哪个结点的下一邻接点(输入关键字):");
                scanf("%d", &v);
                printf("请输入您想查看相对于哪个结点的下一邻接点(输入关键字):");
                scanf("%d", &w);
                states = NextAdjVex(graphs.elem[ls_pos-1].Graph, v, w);
                if(states == -1){
                    printf("NextAdjVex: Error!\n");
                    printf("未找到顶点！\n");
                }
                else printf("您所查找的结点的下一邻接点位序为%d,关键字为：%d,信息为：%s.\n", states, graphs.elem[ls_pos-1].Graph.vertices[states].data.key, graphs.elem[ls_pos-1].Graph.vertices[states].data.others);
                break;
            case INSERT_VEX:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入您想添加的顶点的关键字和信息：");
                scanf("%d %s", &value.key, value.others);
                states = InsertVex(graphs.elem[ls_pos-1].Graph, value);
                if(states == ERROR){
                    printf("InsertVex: Error!\n");
                    printf("未能插入结点，数据溢出或关键字已经存在！\n");
                }
                else printf("InsertVex: Success!\n");
                break;
            case DELETE_VEX:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入您想删除的顶点的关键字：");
                scanf("%d", &e);
                states = DeleteVex(graphs.elem[ls_pos-1].Graph, e);
                if(states == ERROR){
                    printf("DeleteVex: Error!\n");
                    printf("未能删除顶点，图不存在或顶点不存在！\n");
                }
                else printf("DeleteVex: Success!\n");
                break;
            case INSERT_ARC:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入您想增加的弧：");
                scanf("%d%d", &v, &w);
                states = InsertArc(graphs.elem[ls_pos-1].Graph, v, w);
                if(states == ERROR){
                    printf("InsertArc: Error!\n");
                    printf("未找到相关顶点或弧已存在！\n");
                }
                else printf("InsertArc: Success!\n");
                break;
            case DELETE_ARC:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入您想删除的弧：");
                scanf("%d%d", &v, &w);
                states = DeleteArc(graphs.elem[ls_pos-1].Graph, v, w);
                if(states == ERROR){
                    printf("DeleteArc: Error!\n");
                    printf("未找到相关顶点或未找到边！\n");
                }
                else printf("DeleteArc: Success!\n");
                break;
            case DFS_TRAVERSE:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                else{
                    states = DFSTraverse(graphs.elem[ls_pos-1].Graph, visit);
                    printf("\n");
                    printf("DFSTraverse: Success!\n");
                }
                break;
            case BFS_TRAVERSE:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                else{
                    states = BFSTraverse(graphs.elem[ls_pos-1].Graph, visit);
                    printf("\n");
                    printf("BFSTraverse: Success!\n");
                }
                break;
            case VERTICES_SET_LESS_THAN_K:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入顶点关键字：");
                scanf("%d", &v);
                printf("请输入路径长度小于几：");
                scanf("%d", &k);
                st = VerticesSetLessThanK(graphs.elem[ls_pos-1].Graph, v, k);
                if(st.setlength == 0)
                    printf("不存在满足条件的顶点.\n");
                else PrintSet(st, graphs.elem[ls_pos-1].Graph);
                SetDestroy(st);
                break;
            case SHORTEST_PATH_LENGTH:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                printf("请输入您想查看的路径的两个端点的关键字：");
                scanf("%d%d", &v, &w);
                states = ShortestPathLength(graphs.elem[ls_pos-1].Graph, v, w);
                if(states == ERROR){
                    printf("ShortestPathLength: Error!\n");
                    printf("不存在顶点.\n");
                }
                else if(states == INFINITY) printf("两顶点不可达.\n");
                else    printf("两顶点的最短路径长度为%d.", states);
                break;
            case CONNECTED_COMPONENTS_NUMS:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0) {
                    printf("Error!\n");
                    printf("图为空！\n");
                    continue;
                }
                states = ConnectedComponentsNums(graphs.elem[ls_pos-1].Graph);
                printf("连通分量数目为%d.", states);
                break;
            case SAVE_GRAPH:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                printf("请输入保存的文件名(不多于25个英文字符)：");
                scanf("%s", name);
                states = SaveGraph(graphs.elem[ls_pos-1].Graph, name);
                if(graphs.elem[ls_pos-1].Graph.vexnum == 0){
                    printf("SaveGraph: Error!\n");
                    printf("图不存在！\n");
                }
                else if(states == ERROR){
                    printf("SaveGraph: Error!\n");
                    printf("打不开文件！\n");
                }
                else    printf("SaveGraph: Success!\n");
                break;
            case LOAD_GRAPH:
                printf("\n");
                printf("请输入您想此操作的图名：");
                scanf("%s", graph_name);
                ls_pos = LocateGraph(graphs, graph_name);
                if(ls_pos == 0){
                    printf("您想操作的图不存在.\n");
                    break;
                }
                if(graphs.elem[ls_pos-1].Graph.vexnum != 0) {
                    printf("Error!\n");
                    printf("图已存在！\n");
                    continue;
                }
                printf("请输入加载的文件名：\n");
                scanf("%s", name);
                states = LoadGraph(graphs.elem[ls_pos-1].Graph, name);
                if(states == ERROR){
                    printf("LoadGraph: Error!\n");
                    printf("打不开文件！\n");
                }
                else if(graphs.elem[ls_pos-1].Graph.vexnum == 0){
                    printf("LoadGraph: Error!\n");
                    printf("图为空！\n");
                }
                else printf("LoadGraph: Success!\n");
                break;
            case ADD_GRAPH:
                printf("\n");
                printf("请输入新增图名(25个英文字符以内):");
                scanf("%s", graph_name);
                states = AddGraph(graphs, graph_name);
                if(states == OVERFLOW){
                    printf("AddGraph: Error!\n");
                    printf("表已满，无法再添加！\n");
                }
                else if(states == ERROR){
                    printf("AddGraph: Error!\n");
                    printf("命名字符数超上限！\n");
                }
                else printf("AddGraph: Success!\n");
                break;
            case REMOVE_GRAPH:
                printf("\n");
                printf("请输入您想要删除的图名：");
                scanf("%s", graph_name);
                states = RemoveGraph(graphs, graph_name);
                if(states == ERROR){
                    printf("RemoveGraph: Error!\n");
                    printf("图不存在!\n");
                }
                else printf("RemoveGraph: Success!\n");
                break;
            case LOCATE_GRAPH:
                printf("\n");
                printf("请输入您想操作的图名：");
                scanf("%s", graph_name);
                states = LocateGraph(graphs, graph_name);
                if(states == 0){
                    printf("LocateGraph: Error!\n");
                    printf("图不存在！\n");
                }
                else printf("您所查找的图在第%d个位置.\n", states);
                break;
            default:
                printf("\n");
                printf("您的选择应当在[0-20]的范围内！\n");
                break;
        }
        while(getchar() != '\n');//清空控制台中字符等非法字符
        if(op != 0) op = -1; //防止op因未改变且在读入操作时未赋新值而继续上一步的操作
    }
}
void visit(VertexType v)
{
    printf("%d %s ", v.key, v.others);
    return;
}

/******辅助队列函数******/
status InitQueue(LinkQueue &Q)
{
    Q.front = (QNode *) malloc(sizeof(QNode));
    if(!Q.front)
        exit(OVERFLOW);
    Q.rear = Q.front;
    Q.front->next = NULL;
    return OK;
}

status EnQueue(LinkQueue &Q, QElemType elem)
{
    QNode *s = (QNode*) malloc(sizeof(QNode));
    if(!s) exit(OVERFLOW);
    s->data = elem;
    s->next = Q.rear->next;
    Q.rear->next = s;
    Q.rear = s;
    return OK;
}

status DeQueue(LinkQueue &Q, QElemType &elem)
{
    if(Q.front == Q.rear)   return ERROR;
    elem = Q.front->next->data;

    QNodePtr p = Q.front->next;
    Q.front->next = p->next;
    if(Q.rear == p)
        Q.rear = Q.front;
    free(p);
    p = NULL;
}

status QueueEmpty(LinkQueue Q)
{
    if(Q.front == Q.rear)
        return TRUE;
    return FALSE;
}

status DestroyQueue(LinkQueue &Q)
{
    QNodePtr p = Q.front;
    while(Q.front != NULL){
        Q.front = Q.front->next;
        free(p);
        p = Q.front;
    }
    free(p);
    Q.front = NULL;
    Q.rear = NULL;
    p = NULL;
    return OK;
}
/************/

/******集合******/
status SetInit(Set &set)
{
    set.elem = (SetElemType *) malloc(sizeof(SetElemType) * SET_INIT_SIZE);
    if(!set.elem)
        exit(OVERFLOW);
    set.setlength = 0;
    set.setsize = SET_INIT_SIZE;
    return OK;
}

status SetInsert(Set &set, SetElemType elem)
{
    if(!set.elem)   return INFEASIBLE;
    if(set.setsize == set.setlength){
        set.elem = (SetElemType *) realloc(set.elem, sizeof(SetElemType)*(set.setsize + SETINCREMENT));
        if(set.elem == NULL)
            exit(OVERFLOW);
        set.setsize += SETINCREMENT;
    }
    set.elem[set.setlength] = elem;
    set.setlength ++;
    return OK;
}

status SetDestroy(Set &set)
{
    free(set.elem);
    set.setlength = 0;
    set.setsize = 0;
    return OK;
}

void PrintSet(Set set, ALGraph G)
{
    if(set.setlength == 0){
        printf("None!\n");
        return;
    }
    for(int i = 0; i < set.setlength; i ++){
        printf("%d ", set.elem[i]);
        int pos_elem = 0;
        for(;pos_elem < G.vexnum; pos_elem ++){
            if(G.vertices[pos_elem].data.key == set.elem[i])
                break;
        }
        printf("%s ", G.vertices[pos_elem].data.others);
        printf("%c", (i == set.setlength-1) ? '\n' : ' ');
    }
    return;
}
/************/

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2], GraphKind kind)
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    G.kind = kind;
    for(VertexType *p = V; p->key != -1; p ++){
        for(VertexType *q = V; q < p; q ++){
            if(p->key == q->key)
                return ERROR;
        }
    }
    for(int i = 0; VR[i][0] != -1 && VR[i][1] != -1; i ++){
        for(int j = 0; j < i; j ++){
            if(VR[i][0] == VR[j][0] && VR[i][1] == VR[j][1])
                return ERROR;
        }
    }
    int cnt = 0;
    while(V[cnt].key != -1)   cnt ++;
    if(cnt > MAX_VERTEX_NUM || cnt == 0)    return ERROR;
    G.vexnum = cnt;
    for(int i = 0; i < G.vexnum; i ++){
        G.vertices[i].data.key = V[i].key;
        strcpy(G.vertices[i].data.others, V[i].others);
        G.vertices[i].firstarc = NULL;
    }
    int i = 0;
    while(VR[i][0] != -1 && VR[i][1] != -1){
        int v = LocateVex(G, VR[i][0]);
        int w = LocateVex(G, VR[i][1]);
        if(v == -1 || w == -1 || v >= G.vexnum || w >= G.vexnum)  return ERROR;
        ArcNode *s = (ArcNode*) malloc(sizeof(ArcNode));
        s->adjvex = w;
        s->nextarc = G.vertices[v].firstarc;
        G.vertices[v].firstarc = s;
        G.arcnum ++;
        if(G.kind == UDN || G.kind == UDG){
            s = (ArcNode *) malloc(sizeof(ArcNode));
            s->adjvex = v;
            s->nextarc = G.vertices[w].firstarc;
            G.vertices[w].firstarc = s;
        }
        i ++;
    }
    return OK;
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    for(int pos = 0; pos < G.vexnum; pos ++){
        ArcNode *p = G.vertices[pos].firstarc;
        while(p){
            G.vertices[pos].firstarc = p->nextarc;
            free(p);
            p = G.vertices[pos].firstarc;
        }
        p = NULL;
    }
    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    int pos = -1;
    for(int i = 0; i < G.vexnum; i ++){
        if(G.vertices[i].data.key == u){
		    pos = i;
            break; 
    	}
    }
    return pos;
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    int pos = -1;
    int cnt = 0;
    for(int i = 0; i < G.vexnum; i ++){
        if(G.vertices[i].data.key == u){
            cnt ++;
            pos = i;
        }
        if(G.vertices[i].data.key == value.key && value.key != u)
            return ERROR;
    }
    if(cnt != 1)    return ERROR;
    G.vertices[pos].data.key = value.key;
    strcpy(G.vertices[pos].data.others, value.others);
    return OK;
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    int pos = -1;
    for(int i = 0; i < G.vexnum; i ++){
        if(G.vertices[i].data.key == u)
        {
		    pos = i;
		    break;
		}
    }
    if(pos == -1)   return pos;
    if(G.vertices[pos].firstarc == NULL)    return -1;
    else return G.vertices[pos].firstarc->adjvex;
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    int vex = 0;
    for(; vex < G.vexnum; vex ++){
        if(G.vertices[vex].data.key == v){
            ArcNode *p;
            for(p = G.vertices[vex].firstarc; p->nextarc != NULL; p = p->nextarc){
                if(G.vertices[p->adjvex].data.key == w)  return p->nextarc->adjvex;
            }
            return -1;
        }
    }
    return -1;
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    if(G.vexnum >= MAX_VERTEX_NUM)  return ERROR;
    for(int i = 0; i < G.vexnum; i ++){
        if(G.vertices[i].data.key == v.key) return ERROR;
    }
    G.vertices[G.vexnum].data.key = v.key;
    strcpy(G.vertices[G.vexnum].data.others, v.others);
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum ++;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    if(G.vexnum == 0 || G.vexnum == 1)   return ERROR;
    int pos = 0;
    while(pos < G.vexnum){
        if(G.vertices[pos].data.key == v)
            break;
        pos ++;
    }
    if(pos == G.vexnum) return ERROR;
    ArcNode *p = G.vertices[pos].firstarc;
    while(p){
        G.vertices[pos].firstarc = p->nextarc;
        free(p);
        p = G.vertices[pos].firstarc;
        G.arcnum --;
    }
    for(int i = pos + 1; i < G.vexnum; i ++){
        G.vertices[i - 1].data.key = G.vertices[i].data.key;
        strcpy(G.vertices[i-1].data.others, G.vertices[i].data.others);
        G.vertices[i-1].firstarc = G.vertices[i].firstarc;
    }
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum --;
    for(int i = 0; i < G.vexnum; i ++){
        p = G.vertices[i].firstarc;
        while(p && p->adjvex == pos){
            G.vertices[i].firstarc = p->nextarc;
            free(p);
            p = G.vertices[i].firstarc;
            if(G.kind == DG || G.kind == DN)    G.arcnum --;
        }
        while(p){
            if(p->adjvex > pos) p->adjvex --;
            if(p->nextarc && p->nextarc->adjvex == pos){
                ArcNode *s = p->nextarc;
                p->nextarc = s->nextarc;
                free(s);
                if(G.kind == DG || G.kind == DN)    G.arcnum --;
                s = NULL;
            }
            p = p->nextarc;
        }
    }
    return OK;
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    if(G.vexnum == 1 || G.vexnum == 0)  return ERROR;
    int pos = 0;
    for(; pos < G.vexnum; pos ++){
        if(G.vertices[pos].data.key == v)
            break;
    }
    if(pos == G.vexnum) return ERROR;

    int pos1 = 0;
    for(; pos1 < G.vexnum; pos1 ++){
        if(G.vertices[pos1].data.key == w)
            break;
    }
    if(pos1 == G.vexnum)    return ERROR;

    for(ArcNode *s = G.vertices[pos].firstarc; s != NULL; s = s->nextarc){
        if(s->adjvex == pos1)  return ERROR;
    }

    ArcNode *p = (ArcNode*) malloc(sizeof(ArcNode));
    p->adjvex = pos1;
    p->nextarc = G.vertices[pos].firstarc;
    G.vertices[pos].firstarc = p;


    if(G.kind == UDG || G.kind == UDN){
        p = (ArcNode*) malloc(sizeof(ArcNode));
        p->adjvex = pos;
        p->nextarc = G.vertices[pos1].firstarc;
        G.vertices[pos1].firstarc = p;
    }
    G.arcnum ++;
    return OK;
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    if(G.vexnum == 1 || G.vexnum == 0)  return ERROR;

    int pos_v = 0;
    int pos_w = 0;
    for(pos_v; pos_v < G.vexnum; pos_v ++){
        if(G.vertices[pos_v].data.key == v)
            break;
    }
    if(pos_v == G.vexnum)   return ERROR;
    for(pos_w; pos_w < G.vexnum; pos_w ++){
        if(G.vertices[pos_w].data.key == w)
            break;
    }
    if(pos_w == G.vexnum)   return ERROR;

    ArcNode *p = G.vertices[pos_v].firstarc;
    if(p->adjvex == pos_w){
        G.vertices[pos_v].firstarc = p->nextarc;
        free(p);
        p = NULL;
        G.arcnum --;
    }
    else{
        while(p->nextarc && p->nextarc->adjvex != pos_w)
            p = p->nextarc;
        if(p->nextarc == NULL)  return ERROR;
        ArcNode *s = p->nextarc;
        p->nextarc = s->nextarc;
        free(s);
        s = NULL;
        G.arcnum --;
    }

    if(G.kind == UDG || G.kind == UDN){
        p = G.vertices[pos_w].firstarc;
        if(p->adjvex == pos_v){
            G.vertices[pos_w].firstarc = p->nextarc;
            free(p);
            p = NULL;
        }
        else{
            while(p->nextarc && p->nextarc->adjvex != pos_v)
                p = p->nextarc;
            ArcNode *s = p->nextarc;
            p->nextarc = s->nextarc;
            free(s);
            s = NULL;
        }
    }
    return OK;
}

void DFS(ALGraph G, int pos, void (*visit)(VertexType))
{
    visit(G.vertices[pos].data);
    visited[pos] =   TRUE;
    for(int w = FirstAdjVex(G, G.vertices[pos].data.key); w >= 0; w = NextAdjVex(G, G.vertices[pos].data.key, G.vertices[w].data.key)){
        if(visited[w] == FALSE)
            DFS(G, w, visit);
    }
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    visited = (BOOL *) malloc(sizeof(BOOL) * (G.vexnum + 5));
    for(int i = 0; i < G.vexnum; i ++)
        visited[i] = FALSE;
    for(int v = 0; v < G.vexnum; v ++){
        if(visited[v] == FALSE)
            DFS(G, v, visit);
    }
    free(visited);
    return OK;
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    visited = (BOOL *) malloc(sizeof(BOOL) * (G.vexnum + 5));
    for(int i = 0; i < G.vexnum; i ++)
        visited[i] = FALSE;
    LinkQueue Q;
    InitQueue(Q);
    for(int pos = 0; pos < G.vexnum; pos ++){
        if(visited[pos] == FALSE){
            visit(G.vertices[pos].data);
            visited[pos] = TRUE;
            EnQueue(Q, pos);
            while(!QueueEmpty(Q)){
                int v = -1;
                DeQueue(Q, v);
                for(int w = FirstAdjVex(G, G.vertices[v].data.key); w >= 0; w = NextAdjVex(G, G.vertices[v].data.key, G.vertices[w].data.key)){
                    if(visited[w] == FALSE){
                        visit(G.vertices[w].data);
                        visited[w] = TRUE;
                        EnQueue(Q, w);
                    }
                }
            }
        }
    }
    DestroyQueue(Q);
    free(visited);
    return OK;
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE *fp = fopen(FileName, "w");
    if(!fp) return ERROR;
    fprintf(fp, "%d %d %d ", G.kind, G.vexnum, G.arcnum);;
    for(int i = 0; i < G.vexnum; i ++){
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    fprintf(fp, "-1 nil ");
    for(int i = 0; i < G.vexnum; i ++){
        ArcNode *p = G.vertices[i].firstarc;
        while(p){
            fprintf(fp, "%d %d ", i, p->adjvex);
            p = p->nextarc;
        }
    }
    fprintf(fp, "-1 -1");
    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    VertexType V;
    KeyType VR[2];
    FILE *fp = fopen(FileName, "r");
    if(!fp) return ERROR;
    fscanf(fp, "%d", &G.kind);
    fscanf(fp, "%d%d", &G.vexnum, &G.arcnum);
    int i = 0;
    while(fscanf(fp, "%d %s", &V.key, V.others) && V.key != -1){
        G.vertices[i].data.key = V.key;
        strcpy(G.vertices[i].data.others, V.others);
        G.vertices[i].firstarc = NULL;
        i ++;
    }
    while(fscanf(fp, "%d%d", &VR[0], &VR[1]) && VR[0] != -1){
        ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
        p->adjvex = VR[1];
        ArcNode *s = G.vertices[VR[0]].firstarc;
        while(s &&s->nextarc != NULL)   s = s->nextarc;
        if(s == NULL){
            p->nextarc = NULL;
            G.vertices[VR[0]].firstarc = p;
        }
        else{
            s->nextarc = p;
            p->nextarc = NULL;
        }
    }
    fclose(fp);
    return OK;
}

Set VerticesSetLessThanK(ALGraph G, KeyType v, int k)
{
    Set set;
    SetInit(set);
    for(int i = 0; i < G.vexnum; i ++){
        if(ShortestPathLength(G, v, G.vertices[i].data.key) < k){
            SetInsert(set, G.vertices[i].data.key);
        }
    }
    return set;
}

int ShortestPathLength(ALGraph G, KeyType v, KeyType w)
//从关键字为v的顶点到关键字为w的顶点的最短路径长度
{
    int pos_v = 0;
    int pos_w = 0;
    for(pos_v; pos_v < G.vexnum; pos_v ++){
        if(G.vertices[pos_v].data.key == v)
            break;
    }
    if(pos_v == G.vexnum)   return ERROR;
    for(pos_w; pos_w < G.vexnum; pos_w ++){
        if(G.vertices[pos_w].data.key == w)
            break;
    }
    if(pos_w == G.vexnum)   return ERROR;

    int *d = (int *) malloc(sizeof(int) * (G.vexnum+5));
    for(int i = 0; i < G.vexnum; i ++)
        d[i] = INFINITY;
    LinkQueue Q;
    InitQueue(Q);
    d[pos_v] = 0;
    EnQueue(Q, pos_v);
    while(!QueueEmpty(Q)){
        int pos_next;
        DeQueue(Q, pos_next);
        if(pos_next == pos_w)
            break;
        for(int ww = FirstAdjVex(G, G.vertices[pos_next].data.key); ww >= 0; ww = NextAdjVex(G, G.vertices[pos_next].data.key, G.vertices[ww].data.key)){
//            int pos_ww;
//            for(pos_ww = 0; pos_ww < G.vexnum; pos_ww ++){
//                if(G.vertices[pos_ww].data.key == ww)
//                    break;
//            }
            if(d[ww] == INFINITY){
                d[ww] = d[pos_next] + 1;
                EnQueue(Q, ww);
            }
        }
    }
    int n = d[pos_w];
    free(d);
    DestroyQueue(Q);
    return n;
}

void DFS_CCN(ALGraph G, int pos)
{
    visited[pos] = TRUE;
    for(int w = FirstAdjVex(G, G.vertices[pos].data.key); w >= 0; w = NextAdjVex(G, G.vertices[pos].data.key, G.vertices[w].data.key)){
        if(visited[w] == FALSE)
            DFS_CCN(G, w);
    }
}

int ConnectedComponentsNums(ALGraph G)
{
    visited = (int *) malloc(sizeof(int) * (G.vexnum + 5));
    int cnt = 0;
    for(int i = 0; i < G.vexnum; i ++)
        visited[i] = FALSE;
    for(int v = 0; v < G.vexnum; v ++){
        if(visited[v] == FALSE) {
            cnt ++;
            DFS_CCN(G, v);
        }
    }
    free(visited);
    return cnt;
}

status AddGraph(GRAPHS &graphs, char GraphName[])
{
    if(graphs.length == graphs.listsize)
        return OVERFLOW;
    int i = 0;
    while(GraphName[i]) i ++;
    if(i >= 30) return ERROR;
    strcpy(graphs.elem[graphs.length].name, GraphName);
    graphs.elem[graphs.length].Graph.vexnum = 0;
    graphs.elem[graphs.length].Graph.arcnum = 0;
    graphs.length ++;
    return OK;
}
status RemoveGraph(GRAPHS &graphs, char GraphName[])
{
    int pos = 0;
    while(pos < graphs.length && strcmp(graphs.elem[pos].name, GraphName))
        pos ++;
    if(pos == graphs.length)    return ERROR;
    DestroyGraph(graphs.elem[pos].Graph);
    for (int i = pos; i < graphs.length - 1; i ++) {
        strcpy(graphs.elem[i].name, graphs.elem[i+1].name);
        graphs.elem[i].Graph = graphs.elem[i+1].Graph;
    }
    graphs.length --;
    return OK;
}
int LocateGraph(GRAPHS &graphs, char GraphName[])
{
    int pos = 0;
    while(pos < graphs.length && strcmp(graphs.elem[pos].name, GraphName))
        pos ++;
    if(pos == graphs.length)
        return 0;
    return pos + 1;
}

status InitGRAPHS(GRAPHS &graphs)
{
    graphs.listsize = 100;
    graphs.length = 0;
    return OK;
}
