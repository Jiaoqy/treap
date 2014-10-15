#include "stdafx.h"
#include "TreapFunc.h"
using namespace std;

void Treap_Left_Rotate(Treap_Node *&a) //���� �ڵ�ָ��һ��Ҫ��������
{
	Treap_Node *b=a->right;
	a->right=b->left;
	b->left=a;
	a=b;
}
void Treap_Right_Rotate(Treap_Node *&a) //���� �ڵ�ָ��һ��Ҫ��������
{
	Treap_Node *b=a->left;
	a->left=b->right;
	b->right=a;
	a=b;
}

void Treap_Insert(Treap_Node *&P,int value, int fix) //�ڵ�ָ��һ��Ҫ��������
{
	if (NULL == P) //�ҵ�λ�ã������ڵ�
	{
		P=new Treap_Node;
		P->left = NULL;
		P->right = NULL;
		P->value=value;
		P->fix=fix;//�������������ֵ
	}
	else if (value <= P->value)
	{
		Treap_Insert(P->left,value, fix);
		if (P->left->fix < P->fix)
			Treap_Right_Rotate(P);//���ӽڵ�����ֵС�ڵ�ǰ�ڵ�����ֵ��������ǰ�ڵ�
	}
	else
	{
		Treap_Insert(P->right,value, fix);
		if (P->right->fix < P->fix)
			Treap_Left_Rotate(P);//���ӽڵ�����ֵС�ڵ�ǰ�ڵ�����ֵ��������ǰ�ڵ�
	}
}

void Treap_Delete(Treap_Node * &P,int value) //�ڵ�ָ��Ҫ��������
{
	if (value==P->value) //�ҵ�Ҫɾ���Ľڵ� ����ɾ��
	{
		if (!P->right || !P->left) //���һ���ýڵ����ֱ�ӱ�ɾ��
		{
			Treap_Node *t=P;
			if (!P->right)
				P=P->left; //�����ӽڵ������
			else
				P=P->right; //�����ӽڵ������
			delete t; //ɾ���ýڵ�
		}
		else //�����
		{
			if (P->left->fix < P->right->fix) //���ӽڵ�����ֵ��С������
			{
				Treap_Right_Rotate(P);
				Treap_Delete(P->right,value);
			}
			else //���ӽڵ�����ֵ��С������
			{
				Treap_Left_Rotate(P);
				Treap_Delete(P->left,value);
			}
		}
	}
	else if (value < P->value)
		Treap_Delete(P->left,value); //������������Ҫɾ���Ľڵ�
	else
		Treap_Delete(P->right,value); //������������Ҫɾ���Ľڵ�
}

//void Treap_PreOrderShow(Treap_Node *p){
//	if (p)
//	{
//		cout<<p->value;
//		Treap_PreOrderShow(p->left);
//		Treap_PreOrderShow(p->right);
//	}
//}
//
//void Treap_InOrderShow(Treap_Node *p){
//	if (p)
//	{
//		Treap_InOrderShow(p->left);
//		cout<<p->value;
//		Treap_InOrderShow(p->right);
//	}
//}