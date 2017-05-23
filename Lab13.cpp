// Lab13.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "cstring"
#include "math.h"
#include "cstdlib"
#include "locale"
/*
#pragma region _1st
class center
{
public:
	double x, y, z;

	double distance()
	{
		return(sqrt(x*x + y*y + z*z));
	}
	virtual double per() = 0;
	virtual double s() = 0;
	virtual double v() = 0;
};
class sphere :
	public center
{
public:
	double r;
	double per()
	{
		return 2 * 3.14*r;
	}
	double s()
	{
		return(3.14 * r*r);
	}
	double v()
	{
		return(4 / 3 * 3.14*r*r*r);
	}
};
class rectangl :public center
{
public:
	double a, b;
	double per()
	{
		return (a + b) * 2;
	}
	double s()
	{
		return a*b;
	}
	double v()
	{
		return 0;
	}
};
class scolor :public sphere
{
public:
	char color[20];

};
class prizm :public rectangl
{
public:
	double h;
	double per()
	{
		return (a + b)*h;
	}
	double s()
	{
		return (((a + b)*h) + ((a*b) * 2));
	}
	double v()
	{
		return (a*b)*h;
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	puts("C����");
	sphere sp;
	puts("\n������� ������");
	scanf("%lf", &sp.r);
	printf("\n������: %lf", sp.r);
	puts("\n������� �������� ���������� X Y Z");
	scanf("%lf %lf %lf", &sp.x, &sp.y, &sp.z);
	printf("\n���� ��������: %lf %lf %lf", sp.x, sp.y, sp.z);
	printf("\n������� ����������: %lf", sp.distance());
	center *p;
	center *s;
	center *v;
	p = &sp;
	s = &sp;
	v = &sp;
	printf("\n�������� = %lf", p->per());
	printf("\n������� = %lf", s->s());
	printf("\n����� = %lf", v->v());
	printf("\n");

	puts("\n �������������");
	rectangl b;
	puts("������� ����� � ������:");
	scanf("%lf %lf", &b.a, &b.b);
	p = &b;
	s = &b;
	v = &b;
	printf("\n�������� = %lf", p->per());
	printf("\n������� = %lf", s->s());
	printf("\n����� = %lf", v->v());
	printf("\n");

	puts("\n������� �����");
	scolor c;
	p = &c;
	s = &c;
	v = &c;
	puts("\n������� ������");
	scanf("%lf", &c.r);
	printf("\n��������� ���� ������: %lf", c.r);
	puts("\n������� �������� ���������� X Y Z");
	scanf("%lf %lf %lf", &c.x, &c.y, &c.z);
	printf("\n���� ��������: %lf %lf %lf", c.x, c.y, c.z);
	printf("\n������� ����������: %lf", c.distance());
	puts("\n������� ����");
	scanf("%s", &c.color);
	printf("\n��� ����: %s", c.color);
	printf("\n�������� = %lf", p->per());
	printf("\n������� = %lf", s->s());
	printf("\n����� = %lf", v->v());
	printf("\n");

	puts("������");
	prizm d;
	p = &d;
	s = &d;
	v = &d;
	puts("������� ������:");
	scanf("%lf", &d.h);
	puts("\n������� �������� ���������� X Y Z");
	scanf("%lf %lf %lf", &d.x, &d.y, &d.z);
	printf("\n���� ��������: %lf %lf %lf", d.x, d.y, d.z);
	printf("\n������� ����������: %lf", d.distance());
	puts("\n������� ����� � ������:");
	scanf("%lf %lf", &d.a, &d.b);
	printf("�������� ���� ����� � ������: %lf %lf", d.a, d.b);
	printf("\n�������� = %lf", p->per());
	printf("\n������� = %lf", s->s());
	printf("\n����� = %lf", v->v());
	printf("\n");
	system ("pause");
	return 0;
}

#pragma endregion
*/
#pragma region _2nd

class a 
{ 
public: 
	char name[20]; 
private: 
	int kol; 
protected: 
	int cost; 
public: 
	a(char *namex, int kolx, int costx) 
	{ 
		strcpy(name, namex); 
		kol=kolx; 
		cost=costx; 
	} 
	a() {} 
	int get_kol() 
	{ 
		return kol; 
	} 
	int get_cost() 
	{ 
		return cost; 
	} 
}; 

class prod:public a 
{ 
protected: 
	int old; 
public: 
	prod(char *namex, int kolx, int costx, int oldx):a(namex, kolx, costx) 
	{ 
		old=oldx; 
	} 
	prod() {} 
	double cost1() { return (get_cost()*1.0)/(get_kol()*1.0); } 
	int get_old() { return old; } 
}; 

class tool:public a 
{ 
public: 
	int date; 
	tool(char *namex, int kolx, int costx, int datex):a(namex, kolx, costx) 
	{ 
		date=datex; 
	} 
	tool() {} 
	double cost1() 
	{ 
		return (get_cost()*1.0)/(get_kol()*1.0); 
	} 
	int time() 
	{ 
		return 2017-date; 
	} 
}; 

void putprod(prod *a, int n1) 
{ 
	int i; 
	puts("\n������ ����������������� ������� �� ������:");
	for(i=0;i<n1;i++) 
	{ 
		printf("\t\t\t#%d\t\t\t\n", i+1); 
		printf("��������: %s\n", a[i].name); 
		printf("���-��: %d\n", a[i].get_kol()); 
		printf("������ ����: %d\n", a[i].get_cost()); 
		printf("���� ��������: %d\n", a[i].get_old()); 
		printf("��������� ������: %lf\n", a[i].cost1()); 
	} 
} 

void puttool(tool *b, int n2) 
{ 
	int i; 
	puts("\n������ ������������ ������� �� ������:");
	for(i=0;i<n2;i++) 
	{ 
		printf("\t\t\t#%d\t\t\t\n", i+1); 
		printf("��������: %s\n", b[i].name); 
		printf("���-��: %d\n", b[i].get_kol()); 
		printf("������ ����: %d\n", b[i].get_cost()); 
		printf("���� �����������: %d\n", b[i].date); 
		printf("��������� ���������� ������: %lf\n", b[i].cost1()); 
		printf("����� ���������� ������ �� ������: %d\n", b[i].time()); 
	} 
} 

void q123q(prod *a, int n1) 
{ 
	int i, x; 
	printf("\n������� ���� ��������:"); 
	scanf("%d", &x); 
	puts("����� �� ����� ��������� ��������� ������������������ ������:"); 
	for(i=0;i<n1;i++) 
	{ 
		if(a[i].get_old()>x) 
		{ 
			printf("-%s (%d ����)\n", a[i].name, a[i].get_kol()); 
		} 
	} 
} 

int _tmain(int argc, _TCHAR* argv[]) 
{ 
	setlocale(LC_ALL, ""); 
	int n1=0, n2=0, i, x1, x2, x3; 
	char s1[20]; 
	FILE*f; 
	f=fopen("products.txt", "r"); 
	if(f==NULL) 
	{ 
		puts("Can't open products.txt "); 
		system("pause");
		return 1; 
	} 
	while(fscanf(f, "%s", s1)!=EOF) 
	{ 
		n1++; 
	} 
	n1=n1/4; 
	rewind(f); 
	prod *a=new prod[n1]; 
	for(i=0;i<n1;i++) 
	{ 
		fscanf(f, "%s", s1); 
		fscanf(f, "%d", &x1); 
		fscanf(f, "%d", &x2); 
		fscanf(f, "%d", &x3); 
		a[i]=prod(s1, x1, x2, x3); 
	} 
	fclose(f); 
	f=fopen("tools.txt", "r"); 
	if(f==NULL) 
	{ 
		puts("Can't open tools.txt "); 
		system("pause");
		return 2; 
	} 
	while(fscanf(f, "%s", s1)!=EOF) 
	{ 
		n2++; 
	} 
	n2=n2/4; 
	rewind(f); 
	tool *b=new tool[n2]; 
	for(i=0;i<n2;i++) 
	{ 
		fscanf(f, "%s", s1); 
		fscanf(f, "%d", &x1); 
		fscanf(f, "%d", &x2); 
		fscanf(f, "%d", &x3); 
		b[i]=tool(s1, x1, x2, x3); 
	} 
	fclose(f); 
	putprod(a, n1); 
	puttool(b, n2); 
	q123q(a, n1); 
	system ("pause");
	return 0; 
}


#pragma endregion 
