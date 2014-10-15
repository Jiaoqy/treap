#ifndef _TREAPFUNC_H_
#define _TREAPFUNC_H_

struct Treap_Node
{
	Treap_Node *left,*right; //节点的左右子树的指针
	int value,fix; //节点的值和优先级
};

void Treap_Left_Rotate(Treap_Node *&a); //左旋 节点指针一定要传递引用
void Treap_Right_Rotate(Treap_Node *&a); //右旋 节点指针一定要传递引用
void Treap_Insert(Treap_Node *&P,int value, int fix); //节点指针一定要传递引用
void Treap_Delete(Treap_Node *&P,int value); //节点指针要传递引用
//void Treap_PreOrderShow(Treap_Node *p);
//void Treap_InOrderShow(Treap_Node *p);

#endif