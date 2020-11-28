/*
 * @Author: Kaizyn
 * @Date: 2020-11-18 18:40:14
 * @LastEditTime: 2020-11-18 19:22:43
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define max(x,y) ((x)>(y)?(x):(y))
typedef int ElemType;

typedef struct TreeNode {
  ElemType data;
  struct TreeNode *lchild, *rchild;
} TreeNode, *TreeLink;

TreeLink TreeBuild(ElemType *pre, ElemType *in, int n) {
  if (!n) return NULL;
  TreeLink root = (TreeLink)malloc(sizeof(TreeNode));
  root->data = *pre;
  for (int i = 0; i < n; ++i) {
    if (in[i] == *pre) {
      root->lchild = TreeBuild(pre+1, in, i);
      root->rchild = TreeBuild(pre+i+1, in+i+1, n-i-1);
      break;
    }
  }
  return root;
}

int TreeHeight(TreeLink root) {
  if (!root) return 0;
  return max(TreeHeight(root->lchild), TreeHeight(root->rchild))+1;
}

void dfs(TreeLink root, int *cnt) {
  if (!root) return;
  ++(*cnt);
  dfs(root->lchild, cnt+1);
  dfs(root->rchild, cnt+1);
}

int TreeWidth(TreeLink root) {
  int height = TreeHeight(root), width = 0;
  int *cnt = (int*)malloc(sizeof(int)*height);
  memset(cnt, 0, 4*height);
  dfs(root, cnt);
  for (int i = 0; i < height; ++i) width = max(width, cnt[i]);
  return width;
}

int TreeNodeCount(TreeLink root) {
  if (!root) return 0;
  return TreeNodeCount(root->lchild)+TreeNodeCount(root->rchild)+1;
}

int TreeLeafCount(TreeLink root) {
  if (!root) return 0;
  int cnt = TreeLeafCount(root->lchild)+TreeLeafCount(root->rchild);
  return cnt ? cnt : 1;
}

int main() {
  static int n;
  static ElemType pre[N], in[N];
  printf("输入结点数：");
  scanf("%d", &n);
  printf("输入前序遍历：");
  for (int i = 0; i < n; ++i) scanf("%d", pre+i);
  printf("输入中序遍历：");
  for (int i = 0; i < n; ++i) scanf("%d", in+i);
  TreeLink root = TreeBuild(pre, in, n);
  printf("该二叉树的高度为：%d\n", TreeHeight(root));
  printf("该二叉树的宽度为：%d\n", TreeWidth(root));
  printf("该二叉树的结点总数为：%d\n", TreeNodeCount(root));
  printf("该二叉树的叶子结点总数为：%d\n", TreeLeafCount(root));
  scanf("%d", &n);
  return 0;
}
/*
7
1 2 3 4 5 6 7
2 3 1 5 6 4 7
*/
/*
输入结点数：7
输入前序遍历：1 2 3 4 5 6 7
输入中序遍历：2 3 1 5 6 4 7
该二叉树的高度为：4
该二叉树的宽度为：3
该二叉树的结点总数为：7
该二叉树的叶子结点总数为：3
*/