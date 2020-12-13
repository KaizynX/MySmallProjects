/*
 * @Author: Kaizyn
 * @Date: 2020-12-02 19:09:28
 * @LastEditTime: 2020-12-02 20:47:34
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20
typedef int VertexType;
typedef int InfoType;

typedef struct ArcNode {
  int adjvex;
  struct ArcNode *nextarc;
  InfoType *info;
} ArcNode;

typedef struct VNode {
  VertexType data;
  ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
  AdjList vertices;
  int vexnum, arcnum;
  int kind;
} ALGraph;

void AddArc(ALGraph *G, int u, int v) {
  ArcNode *arc = (ArcNode*)malloc(sizeof(ArcNode));
  arc->adjvex = v;
  arc->nextarc = G->vertices[u].firstarc;
  G->vertices[u].firstarc = arc;
}

int main() {
  ALGraph G;
  printf("输入顶点数：");
  scanf("%d", &G.vexnum);
  printf("输入弧数：");
  scanf("%d", &G.arcnum);
  printf("输入是无向图(1)还是有向图(0)：");
  scanf("%d", &G.kind);
  printf("输入点的信息：");
  for (int i = 0; i < G.vexnum; ++i) {
    scanf("%d", &G.vertices[i].data);
  }
  printf("输入边的信息：(初始点,终端点) ");
  for (int i = 0, u, v; i < G.arcnum; ++i) {
    scanf("%d%d", &u, &v);
    AddArc(&G, u, v);
    if (G.kind) AddArc(&G, v, u);
  }
  return 0;
}