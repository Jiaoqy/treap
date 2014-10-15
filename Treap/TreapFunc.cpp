#include "stdafx.h"
#include "TreapFunc.h"
using namespace std;

void Treap_Left_Rotate(Treap_Node *&a) //左旋 节点指针一定要传递引用
{
	Treap_Node *b=a->right;
	a->right=b->left;
	b->left=a;
	a=b;
}
void Treap_Right_Rotate(Treap_Node *&a) //右旋 节点指针一定要传递引用
{
	Treap_Node *b=a->left;
	a->left=b->right;
	b->right=a;
	a=b;
}

void Treap_Insert(Treap_Node *&P,int value, int fix) //节点指针一定要传递引用
{
	if (NULL == P) //找到位置，建立节点
	{
		P=new Treap_Node;
		P->left = NULL;
		P->right = NULL;
		P->value=value;
		P->fix=fix;//生成随机的修正值
	}
	else if (value <= P->value)
	{
		Treap_Insert(P->left,value, fix);
		if (P->left->fix < P->fix)
			Treap_Right_Rotate(P);//左子节点修正值小于当前节点修正值，右旋当前节点
	}
	else
	{
		Treap_Insert(P->right,value, fix);
		if (P->right->fix < P->fix)
			Treap_Left_Rotate(P);//右子节点修正值小于当前节点修正值，左旋当前节点
	}
}

void Treap_Delete(Treap_Node * &P,int value) //节点指针要传递引用
{
	if (value==P->value) //找到要删除的节点 对其删除
	{
		if (!P->right || !P->left) //情况一，该节点可以直接被删除
		{
			Treap_Node *t=P;
			if (!P->right)
				P=P->left; //用左子节点代替它
			else
				P=P->right; //用右子节点代替它
			delete t; //删除该节点
		}
		else //情况二
		{
			if (P->left->fix < P->right->fix) //左子节点修正值较小，右旋
			{
				Treap_Right_Rotate(P);
				Treap_Delete(P->right,value);
			}
			else //左子节点修正值较小，左旋
			{
				Treap_Left_Rotate(P);
				Treap_Delete(P->left,value);
			}
		}
	}
	else if (value < P->value)
		Treap_Delete(P->left,value); //在左子树查找要删除的节点
	else
		Treap_Delete(P->right,value); //在右子树查找要删除的节点
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