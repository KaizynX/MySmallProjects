/*
 * @Author: Kaizyn
 * @Date: 2020-12-02 21:00:26
 * @LastEditTime: 2020-12-02 21:24:06
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

typedef int VRType;
typedef int InfoType;
typedef int VertexType;
typedef int GraphKind;

typedef struct ArcCell {
  VRType adj;
  InfoType *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
  VertexType vexs[MAX_VERTEX_NUM];
  AdjMatrix arcs;
  int vexnum, arcnum;
  GraphKind kind;
} MGraph;


void InsertVex(MGraph *G, int v) {
  G->vexs[G->vexnum++] = v;
}

void InsertArc(MGraph *G, int v, int w) {
  ++G->arcnum;
  G->arcs[v][w].adj = G->arcs[w][v].adj = 1;
}

void DeleteVex(MGraph *G, int v) {
  int p = 0;
  while (p < G->vexnum && G->vexs[p] != v) ++p;
  --G->vexnum;
  while (p < G->vexnum) G->vexs[p] = G->vexs[p+1], ++p;
  for (int i = 0, w; i < G->vexnum; ++i) {
    w = G->vexs[i];
    if (G->arcs[v][w].adj) {
      G->arcs[v][w].adj = G->arcs[w][v].adj = 0;
      --G->arcnum;
    }
  }
}

void DeleteArc(MGraph *G, int v, int w) {
  --G->arcnum;
  G->arcs[v][w].adj = G->arcs[w][v].adj = 0;
}

int main() {
  return 0;
}