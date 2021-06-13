#include <iostream>
#include "binarytree.h"
using namespace std;

int main()
{
    //��չ�������д�����
    char end = '*';
    binaryTree b(end);
    printf("��������Ҫ����������ǰ�����:\n");
    b.createTreeByPreOrder(b.root);
    cout<<"�������"<<endl<<endl;

    //����������
    cout<<"��ʼ��������������..."<<endl;
    b.createInfixThread();
    cout<<"�������������"<<endl<<endl;

    //���
    //�ݹ�
    //����
    printf("�ݹ��������: ");
    b.infixOrder_recursion(b.getRoot());
    cout<<endl;
    //�ǵݹ�
    //����
    printf("�ǵݹ��������: ");
    b.infixOrder_NONrecursion(b.getRoot());
    cout<<endl<<endl;

    //�����������ָ�����ֵ�����Һ��ӽ��
    char data;
    cout<<"������Ҫ�������Һ��ӵĽ��Ľ��ֵ: ";
    cin>>data;
    binaryTreeNode *tmp =  b.getNodeByData(data);
    if(b.pre(tmp)!=NULL)
        cout<<"ǰ�����ֵ:"<<b.pre(tmp)->data<<endl;
    else
        cout<<"��ǰ�����"<<endl;
    if(b.next(tmp)!=NULL)
        cout<<"��̽��ֵ:"<<b.next(tmp)->data<<endl;
    else
        cout<<"�޺�̽��"<<endl;
    cout<<endl;

    //�ͷŶ�����
    b.~binaryTree();
}
