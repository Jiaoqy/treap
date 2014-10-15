#ifndef _TREAPFUNC_H_
#define _TREAPFUNC_H_

struct Treap_Node
{
	Treap_Node *left,*right; //�ڵ������������ָ��
	int value,fix; //�ڵ��ֵ�����ȼ�
};

void Treap_Left_Rotate(Treap_Node *&a); //���� �ڵ�ָ��һ��Ҫ��������
void Treap_Right_Rotate(Treap_Node *&a); //���� �ڵ�ָ��һ��Ҫ��������
void Treap_Insert(Treap_Node *&P,int value, int fix); //�ڵ�ָ��һ��Ҫ��������
void Treap_Delete(Treap_Node *&P,int value); //�ڵ�ָ��Ҫ��������
//void Treap_PreOrderShow(Treap_Node *p);
//void Treap_InOrderShow(Treap_Node *p);

#endif