/*
 * @Author: Kaizyn
 * @Date: 2021-03-04 14:12:58
 * @LastEditTime: 2021-03-04 16:41:55
 */
/*
 * @Author: Kaizyn
 * @Date: 2021-03-04 14:12:58
 * @LastEditTime: 2021-03-04 14:15:33
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STATUS_H
#define STATUS_H

/* 状态码 */
#define	TRUE		1			//真 
#define	FALSE		0			//假
#define YES			1			//是
#define NO          0			//否 
#define	OK			1			//通过
#define	ERROR		0			//错误
#define SUCCESS		1			//成功 
#define UNSUCCESS	0			//失败 
#define	INFEASIBLE	-1			//不可行

#ifndef _MATH_H_ 				//系统中已有此状态码定义，要避免冲突 
#define	OVERFLOW	-2			//堆栈上溢
#define UNDERFLOW	-3			//堆栈下溢
#endif 

#ifndef NULL
#define NULL ((void*)0)
#endif

/* 状态码识别类型 */
typedef int Status;

/*宏函数*/
//函数暂停一段时间
#define Wait(x)\
 {\
	double _Loop_Num_;\
	for(_Loop_Num_=0.01; _Loop_Num_<=100000.0*x; _Loop_Num_+=0.01)\
		;\
 }//设立一个空循环 
 
//摁Enter键继续 
#define PressEnter\
 {\
	fflush(stdin);\
	printf("Press Enter...");\
	getchar();\
	fflush(stdin);\
 }

#endif

#ifndef SCANF_C
#define SCANF_C

#include <stdio.h>
#include <string.h>
#include <stdarg.h>				//提供宏va_list、va_start、va_arg、va_end	
#include <ctype.h> 				//提供isprint原型 

/*
    自定义的数据录入函数，用于从文件fp
中读取格式化的输入。
    与fscanf不同之处在于此函数只会读取
西文字符，对于中文字符，则会跳过。 
*/

int Scanf(FILE *fp, char *format, ...)
{
	int *i;
	char *ch, *s;
	float *f;
	int count, k, len, n;		
	int tmp;
	va_list ap;
	
	len = strlen(format);
	
	va_start(ap, format);
	
	for(count=0,k=2; k<=len; k=k+2)
	{
		while((tmp=getc(fp))!=EOF)			//跳过所有非西文字符 
		{
			if((tmp>=0 && tmp<=127))
			{
				ungetc(tmp, fp);			//遇到首个西文字符，将此西文字符放入输入流 
				break;
			}
		}
		
		if(tmp==EOF)
			break;
		
		if(format[k-1]=='c')				//读取字符		 
		{
			ch = va_arg(ap, char*);
						
			if(tmp!=EOF)
				count += fscanf(fp, "%c", ch);					
		}	
		
		if(format[k-1]=='d')				//读取整型 
		{
			i = va_arg(ap, int*);
			
			while((tmp=getc(fp))!=EOF)
			{
				if((tmp>='0' && tmp<='9') || tmp=='-' || tmp=='+')
				{
					ungetc(tmp, fp);
					break;
				}
			}
			
			if(tmp!=EOF)
				count += fscanf(fp, "%d", i);
		}

		if(format[k-1]=='f')				//读取浮点型 
		{
			f = va_arg(ap, float*);
			
			while((tmp=getc(fp))!=EOF)
			{
				if((tmp>='0' && tmp<='9') || tmp=='-' || tmp=='+'|| tmp=='.' )
				{
					ungetc(tmp, fp);
					break;
				}
			}
			
			if(tmp!=EOF)
				count += fscanf(fp, "%f", f);
		}
		
		if(format[k-1]=='s')				//读取字符串 
		{
			s = va_arg(ap, char*);
			
			while((tmp=getc(fp))!=EOF && (!isprint(tmp) || tmp==' '))
				;
			
			n = 0;
			if(!feof(fp))
			{
				ungetc(tmp, fp);
				while((tmp=getc(fp))!=EOF)
				{
					if(isprint(tmp) && tmp!=' ')
						s[n++] = tmp;
					else
						break;	
				}
				ungetc(tmp, fp);			
			}
                                                                                
			s[n] = '\0';
					
			count++;		
		}		
	}
		
	va_end(ap);
	
	return count;
}

#endif 


/* 单链表类型定义 */
#ifndef BANKQUEUING_H			/*后续的模拟银行排队算法中，此类型需要重新定义*/
typedef int LElemType_L;

/* 单链表结构体 */
typedef struct LNode
{
	LElemType_L data;
	struct LNode* next;
}LNode;
typedef LNode* LinkList;		//指向单链表结点的指针 
#endif

/* 单链表（带头结点）函数列表 */ 
Status InitList_L(LinkList *L);
/*━━━━━━━━━━┓
┃(01)初始化单链表L。 ┃
┗━━━━━━━━━━*/

Status ClearList_L(LinkList L);
/*━━━━━━━━━━━━━━━┓
┃(02)置空单链表L，头结点保留。 ┃ 
┗━━━━━━━━━━━━━━━*/ 

void DestroyList_L(LinkList *L);
/*━━━━━━━━━━━━━━━━━━━┓
┃(03)销毁单链表L，连同通结点一起销毁。 ┃
┗━━━━━━━━━━━━━━━━━━━*/

Status ListEmpty_L(LinkList L);
/*━━━━━━━━━━━━━━━┓
┃(04)判断单链表L是否为空。     ┃
┗━━━━━━━━━━━━━━━*/

int ListLength_L(LinkList L);
/*━━━━━━━━━━━━┓
┃(05)返回单链表L元素个数 ┃
┗━━━━━━━━━━━━*/ 

Status GetElem_L(LinkList L, int i, LElemType_L *e);
/*━━━━━━━━━━━━━━━━━━━┓
┃(06)算法2.8：用e接收单链表L中第i个元素┃
┗━━━━━━━━━━━━━━━━━━━*/ 

int LocateElem_L(LinkList L, LElemType_L e, Status(Compare)(LElemType_L, LElemType_L));
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(07)返回单链表L中第一个与e满足Compare关系的元素位序。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━*/ 

Status PriorElem_L(LinkList L, LElemType_L cur_e, LElemType_L *pre_e);
/*━━━━━━━━━━━━━━┓
┃(08)用pre_e接收cur_e的前驱。┃
┗━━━━━━━━━━━━━━*/ 

Status NextElem_L(LinkList L, LElemType_L cur_e, LElemType_L *next_e);
/*━━━━━━━━━━━━━━━┓
┃(09)用next_e接收cur_e的后继。 ┃
┗━━━━━━━━━━━━━━━*/

Status ListInsert_L(LinkList L, int i, LElemType_L e);
/*━━━━━━━━━━━━━━━━━━━━━┓
┃(10)算法2.9：在单链表L第i个位置之前插入e。┃
┗━━━━━━━━━━━━━━━━━━━━━*/

Status ListDelete_L(LinkList L, int i, LElemType_L *e);
/*━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(11)算法2.10：删除单链表L第i个位置的值，并用e接收。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━*/ 

Status ListTraverse_L(LinkList L, void(Visit)(LElemType_L));
/*━━━━━━━━━━━━━━┓
┃(12)用Visit函数访问单链表L。┃
┗━━━━━━━━━━━━━━*/  

Status CreateList_HL(FILE *fp, LinkList *L, int n);
/*━━━━━━━━━━━━━━━━━━━━━━┓
┃(13)算法2.11：头插法建立单链表L(逆序输入)。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━*/  

Status CreateList_TL(FILE *fp, LinkList *L, int n);
/*━━━━━━━━━━━━━━━━━┓
┃(14)尾插法建立单链表L(顺序输入)。 ┃
┗━━━━━━━━━━━━━━━━━*/  

Status InitList_L(LinkList *L)
{
	(*L) = (LinkList)malloc(sizeof(LNode));
	if(!(*L))
		exit(OVERFLOW);
	(*L)->next = NULL;
	
	return OK;
}

Status ClearList_L(LinkList L)			//保留头结点 
{	
	LinkList pre, p;
	
	if(!L)
		return ERROR;
	
	pre = L->next;

	while(pre)
	{
		p = pre->next;
		free(pre);
		pre = p;
	}

	L->next = NULL;

	return OK; 
}

void DestroyList_L(LinkList *L)			//销毁所有结点 
{
	LinkList p = *L;	

	while(p)
	{
		p = (*L)->next;
		free(*L);
		(*L) = p;
	}
}

Status ListEmpty_L(LinkList L)
{
	if(L!=NULL && L->next==NULL)		//链表存在且只有头结点 
		return TRUE;
	else
		return FALSE;
}

int ListLength_L(LinkList L)
{
	LinkList p;
	int i;
	
	if(L)
	{
		i = 0;
		p = L->next;
		while(p)
		{
			i++;
			p = p->next;
		}		
	}
	
	return i;
}

/*════╗
║ 算法2.8║ 
╚════*/
Status GetElem_L(LinkList L, int i, LElemType_L *e)
{
	int j;
	LinkList p = L->next;
	
	j = 1;
	p = L->next;
	
	while(p && j<i)						//p不为空且还未到达i处
	{
		j++;
		p = p->next;
	}

	if(!p || j>i)						//第i个元素不存在 
		return ERROR;

	*e = p->data;

	return OK; 
}

int LocateElem_L(LinkList L, LElemType_L e, Status(Compare)(LElemType_L, LElemType_L))
{
	int i;
	LinkList p;
	
	i = -1;								//L不存在时返回-1 
	
	if(L)
	{
		i = 0;
		p = L->next;
		
		while(p)
		{
			i++;
			
			if(!Compare(e, p->data))
			{
				p = p->next;
				if(p==NULL)		//失配时已经是最后一个结点 
					i++;
			}
			else
				break;
		}	
	}

	return i;	
}

/* 银行排队算法中，此处两个函数不能直接使用，原因是结构不能直接比较 */
#ifndef BANKQUEUING_C				
Status PriorElem_L(LinkList L, LElemType_L cur_e, LElemType_L *pre_e)
{
	LinkList p, suc;
	
	if(L)
	{
		p = L->next;
		
		if(p->data!=cur_e)				//第一个结点无前驱 
		{
			while(p->next)				//若p结点有后继 
			{
				suc = p->next;			//suc指向p的后继
				if(suc->data==cur_e)
				{
					*pre_e = p->data;
					return OK;
				}
				p = suc;
			}			
		}	
	}

	return ERROR;
}

Status NextElem_L(LinkList L, LElemType_L cur_e, LElemType_L *next_e)
{
	LinkList p, suc;
	
	if(L)
	{
		p = L->next;
		
		while(p && p->next)
		{
			suc = p->next;
			
			if(suc && p->data==cur_e)
			{
				*next_e = suc->data;
				return OK;
			}
			
			if(suc)
				p = suc;
			else
				break;
		}	
	}

	return ERROR;
}
#endif

/*════╗
║ 算法2.9║ 
╚════*/
Status ListInsert_L(LinkList L, int i, LElemType_L e)
{
	LinkList p, s;
	int j;
	
	p = L;
	j = 0; 
	
	while(p && j<i-1)					//寻找第i-1个结点 
	{
		p = p->next;
		++j;
	}
	
	if(!p || j>i-1)
		return ERROR;

	s = (LinkList)malloc(sizeof(LNode));
	if(!s)
		exit(OVERFLOW);
	s->data = e;
	s->next = p->next;
	p->next = s;

	return OK;
}

/*═════╗
║ 算法2.10 ║ 
╚═════*/
Status ListDelete_L(LinkList L, int i, LElemType_L *e)
{
	LinkList pre, p; 
	int j;

	pre = L;
	j = 1; 

	while(pre->next && j<i)			//寻找第i个结点，并令pre指向其前驱 
	{
		pre = pre->next;
		++j;
	}
	
	if(!pre->next || j>i)			//删除位置不合理
		return ERROR;

	p = pre->next;
	pre->next = p->next;
	*e = p->data;
	free(p);

	return OK; 
}

Status ListTraverse_L(LinkList L, void(Visit)(LElemType_L))
{
	LinkList p;

	if(!L)
		return ERROR;
	else
		p = L->next;	

	while(p)
	{
		Visit(p->data);
		p = p->next;
	}

	return OK;
}

/*═════╗
║ 算法2.11 ║ 
╚═════*/
/*
Status CreateList_HL(FILE *fp, LinkList *L, int n)
{
	int i;
	LinkList p;
	LElemType_L tmp;
		
	*L = (LinkList)malloc(sizeof(LNode));
	if(!(*L))
		exit(OVERFLOW);
	(*L)->next = NULL;							//建立头结点 
	
	for(i=1; i<=n; ++i)
	{
		if(Scanf(fp, "%d", &tmp)==1)
		{
			p = (LinkList)malloc(sizeof(LNode));
			if(!p)
				exit(OVERFLOW);
			p->data = tmp;						//录入数据 
			p->next = (*L)->next;
			(*L)->next = p;		
		}
		else
			return ERROR;
	}
	
	return OK;
}  

Status CreateList_TL(FILE *fp, LinkList *L, int n)
{
	int i;
	LinkList p, q;
	LElemType_L tmp;	
			
	*L = (LinkList)malloc(sizeof(LNode));
	if(!(*L))
		exit(OVERFLOW);
	(*L)->next = NULL;
		
	for(i=1,q=*L; i<=n; ++i)
	{
		if(Scanf(fp, "%d", &tmp)==1)
		{
			p = (LinkList)malloc(sizeof(LNode));
			if(!p)
				exit(OVERFLOW);
			p->data = tmp;						//录入数据 
			q->next = p;
			q = q->next;		
		}
		else
			return ERROR;		
	}
	
	q->next = NULL;

	return OK;
}
*/

#ifndef SEQUENCELIST_H
#define SEQUENCELIST_H

/* 宏定义 */
#define LIST_INIT_SIZE 100				//顺序表存储空间的初始分配量 
#define LISTINCREMENT  10				//顺序表存储空间的分配增量

/* 顺序表类型定义 */
#ifndef LELEMTYPE_SQ
#define LELEMTYPE_SQ
typedef int LElemType_Sq;
#endif

typedef struct
{
	LElemType_Sq *elem;					//存储空间基址（指向第一个结点的指针） 
	int length;							//当前顺序表长度 
	int listsize;						//当前分配的存储容量 
}SqList;								//顺序表0号单元正常使用 

/* 顺序表函数列表 */
Status InitList_Sq(SqList *L);
/*━━━━━━━━━━━━━━━┓
┃(01)算法2.3：初始化空顺序表L。┃
┗━━━━━━━━━━━━━━━*/

void ClearList_Sq(SqList *L);
/*━━━━━━━━━┓
┃(02)清空顺序表L。 ┃
┗━━━━━━━━━*/

void DestroyList_Sq(SqList *L);
/*━━━━━━━━━┓
┃(03)销毁顺序表L。 ┃
┗━━━━━━━━━*/
	  
Status ListEmpty_Sq(SqList L);
/*━━━━━━━━━━━━━┓
┃(04)判断顺序表L是否为空。 ┃
┗━━━━━━━━━━━━━*/

int ListLength_Sq(SqList L);
/*━━━━━━━━━━━━━━┓
┃(05)返回顺序表L中元素个数。 ┃
┗━━━━━━━━━━━━━━*/
	
Status GetElem_Sq(SqList L, int i, LElemType_Sq *e);
/*━━━━━━━━━━━━━━━━┓
┃(06)用e接收顺序表L中第i个元素。 ┃
┗━━━━━━━━━━━━━━━━*/

int LocateElem_Sq(SqList L, LElemType_Sq e, Status(Compare)(LElemType_Sq, LElemType_Sq));
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(07)算法2.6：返回顺序表L中首个与e满足Compare关系的元素位序。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

Status PriorElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *pre_e);
/*━━━━━━━━━━━━━━━━━┓
┃(08)用pre_e接收cur_e的前驱。      ┃
┗━━━━━━━━━━━━━━━━━*/

Status NextElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *next_e);
/*━━━━━━━━━━━━━━━━━┓
┃(09)用next_e接收cur_e的后继。     ┃
┗━━━━━━━━━━━━━━━━━*/

Status ListInsert_Sq(SqList *L, int i, LElemType_Sq e);
/*━━━━━━━━━━━━━━━━━━━━━┓
┃(10)算法2.4：在顺序表L的第i个位置上插入e。┃
┗━━━━━━━━━━━━━━━━━━━━━*/

Status ListDelete_Sq(SqList *L, int i, LElemType_Sq *e);
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(11)算法2.5：删除顺序表L上第i个位置的元素，并用e返回。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

Status ListTraverse_Sq(SqList L, void (Visit)(LElemType_Sq)); 
/*━━━━━━━━━━━━━━┓
┃(12)用visit函数访问顺序表L。┃
┗━━━━━━━━━━━━━━*/

#endif

Status InitList_Sq(SqList *L)
{
	(*L).elem = (LElemType_Sq*)malloc(LIST_INIT_SIZE*sizeof(LElemType_Sq));
	if(!(*L).elem)
		exit(OVERFLOW); 				//分配内存失败

	(*L).length = 0;					//初始化顺序表长度为0
	(*L).listsize = LIST_INIT_SIZE;		//顺序表初始内存分配量

	return OK;							//初始化成功	 
} 

void ClearList_Sq(SqList *L)
{
	(*L).length = 0;
}

void DestroyList_Sq(SqList *L)
{
	free((*L).elem);

	(*L).elem = NULL;					//释放内存后置空指针 
	(*L).length = 0;
	(*L).listsize = 0;
}

Status ListEmpty_Sq(SqList L)
{
	return 	L.length==0 ? TRUE : FALSE;
}

int ListLength_Sq(SqList L)
{
	return L.length;	
}

Status GetElem_Sq(SqList L, int i, LElemType_Sq *e)
{ 
	if(i<1 || i>L.length)
		return ERROR;					//i值不合法
	else
		*e = L.elem[i-1];

	return OK;
}

/*════╗
║算法2.6 ║ 
╚════*/
int LocateElem_Sq(SqList L, LElemType_Sq e, Status(Compare)(LElemType_Sq, LElemType_Sq))
{
	int i = 1;							//i的初值为第一个元素的位序
	
	while(i<=L.length && !Compare(e, L.elem[i-1]))
		++i;

	if(i<=L.length)
		return i;
	else
		return 0; 
}

Status PriorElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *pre_e)
{
	int i = 1;
	
	if(L.elem[0]!=cur_e)				//第一个结点无前驱 
	{
		while(i<L.length && L.elem[i]!=cur_e)
			++i;
		
		if(i<L.length)
		{
			*pre_e = L.elem[i-1];
			return OK;
		}	
	}
			
	return ERROR;
}

Status NextElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *next_e)
{
	int i = 0;
	
	while(i<L.length && L.elem[i]!=cur_e)
		++i;

	if(i<L.length-1)					//最后一个结点无后继 
	{
		*next_e = L.elem[i+1];	
		return OK;
	}

	return ERROR;
}

/*════╗
║算法2.4 ║ 
╚════*/
Status ListInsert_Sq(SqList *L, int i, LElemType_Sq e)
{
	LElemType_Sq *newbase; 
	LElemType_Sq *p, *q;

	if(i<1 || i>(*L).length+1)
		return ERROR;					//i值不合法

	if((*L).length >= (*L).listsize)	//若存储空间已满，需开辟新空间 
	{
		newbase = (LElemType_Sq*)realloc((*L).elem, ((*L).listsize+LISTINCREMENT)*sizeof(LElemType_Sq));
		if(!newbase)
			exit(OVERFLOW);

		(*L).elem = newbase;
		(*L).listsize += LISTINCREMENT;
	}
	
	q = &(*L).elem[i-1];				//q为插入位置 
	
	for(p=&(*L).elem[(*L).length-1]; p>=q; --p)
		*(p+1) = *p;					//插入位置及之后的元素右移 
	
	*q = e;								//插入e 
	(*L).length++;						//表长增1

	return OK; 
}

/*════╗
║算法2.5 ║ 
╚════*/
Status ListDelete_Sq(SqList *L, int i, LElemType_Sq *e)
{
	LElemType_Sq *p, *q;
		
	if(i<1 || i>(*L).length)
		return ERROR;					//i值不合法
	
	p = &(*L).elem[i-1];				//p为被删除元素的位置 
	*e = *p;
	q = (*L).elem+(*L).length-1; 		//表尾元素位置 
	
	for(++p; p<=q; ++p)
		*(p-1) = *p;					//被删元素之后的元素左移 

	(*L).length--;						//表长减1

	return OK;
}

Status ListTraverse_Sq(SqList L, void(Visit)(LElemType_Sq))
{
	int i;

	for(i=0; i<L.length; i++)
		Visit(L.elem[i]);
	
	return OK;
}
void ReverseSqList(SqList *L) {
  for (int i = 0, j = ListLength_Sq(*L)-1; i != j; ++i, --j) {
    LElemType_Sq tmp = L->elem[i];
    L->elem[i] = L->elem[j];
    L->elem[j] = tmp;
  }
}

void MergeSqList(SqList La, SqList Lb, SqList *Lc) {
  for (int i = 0, j = 0, k = 0;
      i < ListLength_Sq(La) && j < ListLength_Sq(Lb);
      La.elem[i] <= Lb.elem[j] ? ++i : ++j) {
    if (La.elem[i] == Lb.elem[j]) ListInsert_Sq(Lc, ++k, La.elem[i]);
  }
}

int main() {
  int lena;//, lenb, lenc;
  SqList La, Lb, Lc;
  InitList_Sq(&La);
  InitList_Sq(&Lb);
  InitList_Sq(&Lc);

  // printf("2.21逆置\n");
  // printf("输入顺序表元素个数:");
  scanf("%d", &lena);
  // printf("输入顺序表的%d个元素:", lena);
  for (int i = 1, a; i <= lena; ++i) {
    scanf("%d", &a);
    ListInsert_Sq(&La, i, a);
  }
	for (int i = 1; i <= lena; ++i) {
    LElemType_Sq a;
    GetElem_Sq(La, i, &a);
    printf("%d", a);
    if (i == lena) puts("");
    else printf("->");
  }
  ReverseSqList(&La);
  // printf("顺序表逆置后结果:");
  for (int i = 1; i <= lena; ++i) {
    LElemType_Sq a;
    GetElem_Sq(La, i, &a);
    printf("%d", a);
    if (i == lena) puts("");
    else printf("->");
  }
  ClearList_Sq(&La);

/*
  printf("2.25交集\n");
  printf("输入顺序表A元素个数:");
  scanf("%d", &lena);
  printf("输入顺序表A的%d个元素:", lena);
  for (int i = 1, a; i <= lena; ++i) {
    scanf("%d", &a);
    ListInsert_Sq(&La, i, a);
  }
  printf("输入顺序表B元素个数:");
  scanf("%d", &lenb);
  printf("输入顺序表B的%d个元素:", lenb);
  for (int i = 1, b; i <= lenb; ++i) {
    scanf("%d", &b);
    ListInsert_Sq(&Lb, i, b);
  }
  MergeSqList(La, Lb, &Lc);
  printf("A与B的交集C为:");
  lenc = ListLength_Sq(Lc);
  for (int i = 1; i <= lenc; ++i) {
    LElemType_Sq c;
    GetElem_Sq(Lc, i, &c);
    printf("%d%c", c, " \n"[i==lenc]);
  }

*/
  return 0;
}