#include<stdio.h>
#include<malloc.h>
#include<math.h>

#define TRUE 1
#define FALSE 0

typedef struct mulpoly
{
	float coef;        //系数
	int expn;        //指数
	struct mulpoly *next;     //指针域
}LNode,*LinkList;

typedef   LinkList   polynomial;

void PrintPoly(polynomial L)       //多项式的输出
{
	polynomial p;
	int nCount = 0;
	p = L;

	while(1)
	{
        if((abs(p->coef)) > 1e-6)
        {
            printf("%f",p->coef);
            if(p->expn == 1)
            {
                printf("X",p->expn);
            }
            else if(p->expn != 0)
            {
                printf("X^%d",p->expn);
            }
            nCount++;
        }

        if(p->next != NULL)
        {
            if(p->next->coef > 0)
            {
                printf("+");
            }
            p=p->next;
        }
        else
        {
            break;
        }
	}

	if(nCount == 0)
	{
	    printf("0");
	}
    printf("\n\n");
} //end PrintPoly


polynomial SortPoly(polynomial &ha)
{
    polynomial hb;
    polynomial t,r,s;
    int  expn = -256;
    int nCount = 0;

    t = ha;
    while(t != NULL)
    {
        if(t->expn > expn)
        {
            expn = t->expn;
        }
        t = t->next;
    }
    //printf("\nexpn = %d \n",expn);

    hb = (polynomial)malloc(sizeof(LNode));
    r = hb;

    while(expn >= -256)
    {
        t = ha;
        nCount = 0;
        while(t != NULL)
        {
            if(expn == t->expn)
            {
                nCount += t->coef;
            }
            t = t->next;
            //printf("\nnCount = %d \n",nCount);
        }

        if(nCount != 0)
        {
            s = r;
            r ->coef = nCount;
            r ->expn = expn;
            r ->next = (polynomial)malloc(sizeof(LNode));
            r = r->next;
        }
        expn--;
    }
    s ->next = NULL;
    free(r);
    return (hb);
}

void CreatPoly(LinkList &L)     //产生多项式链表
{
	polynomial r,s;
	float m;
	int n = 0;
	char c = '0',flag = 0,array[1000];
	L = (polynomial)malloc(sizeof(LNode));     //建立一个头结点
	printf("  请按指数由大到小输入多项式,系数和指数间以逗号间隔：\n");
	printf("  (系数,指数):");
	scanf("%f,%d",&L->coef,&L->expn);
	printf("\n");
	r = L;
	while(1)            //n不等于0时建立多项式链表
	{
        printf("  (系数,指数):");
        scanf("%f,%d",&m,&n);
        printf("\n");
	    if((abs(m)) > 1e-6)
	    {
            s = (polynomial)malloc(sizeof(LNode));    //建立一个新结点
            s->coef = m;
            s->expn = n;
            r->next = s;     //把s链接到r的后面
            r = r->next;
	    }
	    else
	    {
            break;
	    }
	}
	r->next = NULL;
}



polynomial AddPoly(polynomial &ha,polynomial &hb)      //两个多项式相加
{
	polynomial hc,p,q,s,r;
	float x;
	p = ha; q = hb;
	hc = (polynomial)malloc(sizeof(LNode));
	r = hc;
    while((p != NULL) && (q != NULL))
	{
        s = r;
		if(p->expn == q->expn)             //两结点指数相等时
		{
			x = p->coef + q->coef;        //系数相加
			if((abs(x)) > 10e-6)
			{
			    r->coef = x;
			    r->expn = p->expn;
                r->next = (polynomial)malloc(sizeof(LNode));
                r = r->next;
			}
			p = p->next;
			q = q->next;
		}
		else if(p->expn < q->expn)   //两结点指数不相等时
        {
            r->coef = q->coef;
            r->expn = q->expn;
            r->next = (polynomial)malloc(sizeof(LNode));
            r = r->next;
            q = q->next;
        }
        else           //p->expn > q->expn时
        {
            r->coef = p->coef;
            r->expn = p->expn;
            r->next = (polynomial)malloc(sizeof(LNode));
            r = r->next;
            p = p->next;
        }
	}

	while(p!=NULL)              //p!=NULL，复制A的剩余部分
	{
        s = r;
        r->coef = p->coef;
        r->expn = p->expn;
        r->next = (polynomial)malloc(sizeof(LNode));
        r = r->next;
        p = p->next;
	}

    while(q!=NULL)              //q!=NULL，复制B的剩余部分
	{
        s = r;
        r->coef = q->coef;
        r->expn = q->expn;
        r->next = (polynomial)malloc(sizeof(LNode));
        r = r->next;
        q = q->next;
	}

	s->next = NULL;       //链成单链表
    free(r);
	return (SortPoly(hc));
} //end AddPoly

polynomial DecPoly(polynomial &ha,polynomial &hb)      //两个多项式相减
{
	polynomial hc,p,q,s,r;
	float x;
	p = ha; q = hb;
	hc = (polynomial)malloc(sizeof(LNode));
	hc->coef = 0;
	hc->expn = 0;
	r ->next = NULL;
	r = hc;
    while((p != NULL) && (q != NULL))
	{
        s = r;
		if(p->expn == q->expn)             //两结点指数相等时
		{
			x = p->coef - q->coef;        //系数相加
			if((abs(x)) > 10e-6)
			{
			    r->coef = x;
			    r->expn = p->expn;
                r->next = (polynomial)malloc(sizeof(LNode));
                r = r->next;
			}
			p = p->next;
			q = q->next;
		}
		else if(p->expn < q->expn)   //两结点指数不相等时
        {
            r->coef = -(q->coef);
            r->expn = q->expn;
            r->next = (polynomial)malloc(sizeof(LNode));
            r = r->next;
            q = q->next;
        }
        else           //p->expn > q->expn时
        {
            r->coef = p->coef;
            r->expn = p->expn;
            r->next = (polynomial)malloc(sizeof(LNode));
            r = r->next;
            p = p->next;
        }
	}

	while(p!=NULL)              //p!=NULL，复制A的剩余部分
	{
        s = r;
        r->coef = p->coef;
        r->expn = p->expn;
        r->next = (polynomial)malloc(sizeof(LNode));
        r = r->next;
        p = p->next;
	}

    while(q!=NULL)              //q!=NULL，复制B的剩余部分
	{
        s = r;
        r->coef = -(q->coef);
        r->expn = q->expn;
        r->next = (polynomial)malloc(sizeof(LNode));
        r = r->next;
        q = q->next;
	}
	s->next = NULL;       //链成单链表
    free(r);
	return (SortPoly(hc));
} //end DecPoly

polynomial MultiPoly1(polynomial p1, polynomial p2)
{
   polynomial hd;
   polynomial t,s,r;

   hd = (polynomial)malloc(sizeof(LNode));
   t = hd;
   while(p2 != NULL)
   {
        s = t;
        t->coef = p2->coef * p1->coef;
        t->expn = p2->expn + p1->expn;
        t->next = (polynomial)malloc(sizeof(LNode));
        t = t->next;
        p2 = p2->next;
   }
   	s->next = NULL;       //链成单链表
    free(t);
    return (SortPoly(hd));
}

//下面程序是实现两个多项式相乘的运算结果
polynomial MultiPoly(polynomial &p1, polynomial &p2)
{
   polynomial hd;
   polynomial t,q,s,r;
   hd = (polynomial)malloc(sizeof(LNode));
   hd->coef = 0;
   hd->expn = 0;
   hd->next = NULL;

   while(p1 != NULL)
   {
       t = MultiPoly1(p1,p2);
       hd = AddPoly(t,hd);
       p1 = p1->next;
   }
   return (SortPoly(hd));
}


int main()            //主程序
{
	polynomial ha,hb,hc,hd;
    char Flag = 0;

    while(Flag != '\n')
    {
        printf("              本程序实现两个多项式A和B相乘。\n");
        printf("下面请输入第一个多项式，以输入系数等于0并回车结束输入\n");
        CreatPoly(ha);  printf("第一个多项式为：A=");
        PrintPoly(ha);
        printf("下面请输入第二个多项式，以输入系数等于0并回车结束输入\n");
        CreatPoly(hb);  printf("第二个多项式为：B=");
        PrintPoly(hb);
        printf("多项式A和B相加所得的多项式C为：C=");
        hc = AddPoly(ha,hb);
        PrintPoly(hc);
        printf("多项式A和B相减所得的多项式D为：D=");
        hc = DecPoly(ha,hb);
        PrintPoly(hc);
        printf("多项式A和B相乘所得的多项式E为：E=");
        hd = MultiPoly(ha,hb);
        PrintPoly(hd);

        Flag = getchar();
        setbuf(stdin,NULL);
    }

	return 0;
}
