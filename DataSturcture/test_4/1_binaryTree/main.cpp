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

    //���
    //�ݹ�
    //ǰ��
    printf("�ݹ��������: ");
    b.preOrder_recursion(b.getRoot());
    cout<<endl;
    //����
    printf("�ݹ��������: ");
    b.infixOrder_recursion(b.getRoot());
    cout<<endl;
    //����
    printf("�ݹ�������: ");
    b.postOrder_recursion(b.getRoot());
    cout<<endl;
    //�ǵݹ�
    //ǰ��
    printf("�ǵݹ��������: ");
    b.preOrder_NONrecursion(b.getRoot());
    cout<<endl;
    //����
    printf("�ǵݹ��������: ");
    b.infixOrder_NONrecursion(b.getRoot());
    cout<<endl<<endl;

    //��������
    cout<<"��������: ";
    b.output(b.getRoot());
    cout<<endl<<endl;

    //�����������ָ�����ֵ�����Һ��ӽ��
    char data;
    cout<<"������Ҫ�������Һ��ӵĽ��Ľ��ֵ: ";
    cin>>data;
    binaryTreeNode *tmp =  b.getNodeByData(data);
    if(b.leftChild(tmp)!=NULL)
        cout<<"����:"<<b.leftChild(tmp)->data<<endl;
    else
        cout<<"������"<<endl;
    if(b.rightChild(tmp)!=NULL)
        cout<<"�Һ���:"<<b.rightChild(tmp)->data<<endl;
    else
        cout<<"���Һ���"<<endl;
    cout<<endl;

    //���������Ҷ�ӽ�����
    cout<<"������Ҷ�ӽ�����: "<<b.getLeaves()<<endl<<endl;

    //����������߶�
    cout<<"�������߶�: "<<b.getHeight();

    //�ͷŶ�����
    b.~binaryTree();
}
