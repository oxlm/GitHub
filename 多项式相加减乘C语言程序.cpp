#include<stdio.h>
#include<malloc.h>
#include<math.h>

#define TRUE 1
#define FALSE 0

typedef struct mulpoly
{
	float coef;        //ϵ��
	int expn;        //ָ��
	struct mulpoly *next;     //ָ����
}LNode,*LinkList;

typedef   LinkList   polynomial;

void PrintPoly(polynomial L)       //����ʽ�����
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

void CreatPoly(LinkList &L)     //��������ʽ����
{
	polynomial r,s;
	float m;
	int n = 0;
	char c = '0',flag = 0,array[1000];
	L = (polynomial)malloc(sizeof(LNode));     //����һ��ͷ���
	printf("  �밴ָ���ɴ�С�������ʽ,ϵ����ָ�����Զ��ż����\n");
	printf("  (ϵ��,ָ��):");
	scanf("%f,%d",&L->coef,&L->expn);
	printf("\n");
	r = L;
	while(1)            //n������0ʱ��������ʽ����
	{
        printf("  (ϵ��,ָ��):");
        scanf("%f,%d",&m,&n);
        printf("\n");
	    if((abs(m)) > 1e-6)
	    {
            s = (polynomial)malloc(sizeof(LNode));    //����һ���½��
            s->coef = m;
            s->expn = n;
            r->next = s;     //��s���ӵ�r�ĺ���
            r = r->next;
	    }
	    else
	    {
            break;
	    }
	}
	r->next = NULL;
}



polynomial AddPoly(polynomial &ha,polynomial &hb)      //��������ʽ���
{
	polynomial hc,p,q,s,r;
	float x;
	p = ha; q = hb;
	hc = (polynomial)malloc(sizeof(LNode));
	r = hc;
    while((p != NULL) && (q != NULL))
	{
        s = r;
		if(p->expn == q->expn)             //�����ָ�����ʱ
		{
			x = p->coef + q->coef;        //ϵ�����
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
		else if(p->expn < q->expn)   //�����ָ�������ʱ
        {
            r->coef = q->coef;
            r->expn = q->expn;
            r->next = (polynomial)malloc(sizeof(LNode));
            r = r->next;
            q = q->next;
        }
        else           //p->expn > q->expnʱ
        {
            r->coef = p->coef;
            r->expn = p->expn;
            r->next = (polynomial)malloc(sizeof(LNode));
            r = r->next;
            p = p->next;
        }
	}

	while(p!=NULL)              //p!=NULL������A��ʣ�ಿ��
	{
        s = r;
        r->coef = p->coef;
        r->expn = p->expn;
        r->next = (polynomial)malloc(sizeof(LNode));
        r = r->next;
        p = p->next;
	}

    while(q!=NULL)              //q!=NULL������B��ʣ�ಿ��
	{
        s = r;
        r->coef = q->coef;
        r->expn = q->expn;
        r->next = (polynomial)malloc(sizeof(LNode));
        r = r->next;
        q = q->next;
	}

	s->next = NULL;       //���ɵ�����
    free(r);
	return (SortPoly(hc));
} //end AddPoly

polynomial DecPoly(polynomial &ha,polynomial &hb)      //��������ʽ���
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
		if(p->expn == q->expn)             //�����ָ�����ʱ
		{
			x = p->coef - q->coef;        //ϵ�����
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
		else if(p->expn < q->expn)   //�����ָ�������ʱ
        {
            r->coef = -(q->coef);
            r->expn = q->expn;
            r->next = (polynomial)malloc(sizeof(LNode));
            r = r->next;
            q = q->next;
        }
        else           //p->expn > q->expnʱ
        {
            r->coef = p->coef;
            r->expn = p->expn;
            r->next = (polynomial)malloc(sizeof(LNode));
            r = r->next;
            p = p->next;
        }
	}

	while(p!=NULL)              //p!=NULL������A��ʣ�ಿ��
	{
        s = r;
        r->coef = p->coef;
        r->expn = p->expn;
        r->next = (polynomial)malloc(sizeof(LNode));
        r = r->next;
        p = p->next;
	}

    while(q!=NULL)              //q!=NULL������B��ʣ�ಿ��
	{
        s = r;
        r->coef = -(q->coef);
        r->expn = q->expn;
        r->next = (polynomial)malloc(sizeof(LNode));
        r = r->next;
        q = q->next;
	}
	s->next = NULL;       //���ɵ�����
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
   	s->next = NULL;       //���ɵ�����
    free(t);
    return (SortPoly(hd));
}

//���������ʵ����������ʽ��˵�������
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


int main()            //������
{
	polynomial ha,hb,hc,hd;
    char Flag = 0;

    while(Flag != '\n')
    {
        printf("              ������ʵ����������ʽA��B��ˡ�\n");
        printf("�����������һ������ʽ��������ϵ������0���س���������\n");
        CreatPoly(ha);  printf("��һ������ʽΪ��A=");
        PrintPoly(ha);
        printf("����������ڶ�������ʽ��������ϵ������0���س���������\n");
        CreatPoly(hb);  printf("�ڶ�������ʽΪ��B=");
        PrintPoly(hb);
        printf("����ʽA��B������õĶ���ʽCΪ��C=");
        hc = AddPoly(ha,hb);
        PrintPoly(hc);
        printf("����ʽA��B������õĶ���ʽDΪ��D=");
        hc = DecPoly(ha,hb);
        PrintPoly(hc);
        printf("����ʽA��B������õĶ���ʽEΪ��E=");
        hd = MultiPoly(ha,hb);
        PrintPoly(hd);

        Flag = getchar();
        setbuf(stdin,NULL);
    }

	return 0;
}
