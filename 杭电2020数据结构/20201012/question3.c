/*
 * @Author: Kaizyn
 * @Date: 2020-10-16 09:19:22
 * @LastEditTime: 2020-10-18 23:10:42
 */
/*
设有一头指针为L的带有表头结点的非循环双向链表，
其每个结点中除有pred（前驱指针），data（数据）和
next（后继指针）域外，还有一个访问频度域freq。在
链表被起用前，其值均初始化为零。每当在链表中进行
一次Locate(L,x)运算时，令元素值为x的结点中freq域的
值增1，并使此链表中结点保持按访问频度非增（递减）
的顺序排列，同时最近访问的结点排在频度相同的结点
的最后，以便使频繁访问的结点总是靠近表头。试编写
符合上述要求的Locate(L,x)运算的算法，该运算为函数过
程，返回找到结点的地址，类型为指针型。
*/
typedef int ElemType;

struct LNode {
  ElemType data;
  int freq;
  struct LNode *pred, *next;
};
typedef struct LNode LNode;
typedef LNode* LinkList;

LinkList Locate(LinkList L, ElemType x) {
  // L 是头指针
  LinkList p = L->next;
  while (p && p->data != x) p = p->next;
  if (!p) return p;

  p->freq++;
  LinkList q = p->pred;
  while (q != L && q->freq < p->freq) q = q->pred;
  // 将 p 插入到 q 之后
  p->pred = q;
  p->next = q->next;
  q->next->pred = p;
  q->next = p;
  return p;
}

int main() {
  return 0;
}