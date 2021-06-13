#include <iostream>
#include "binarytree.h"
using namespace std;

int main()
{
    //��չ�������д�����
    char end = '*';
    binaryTree b(end);
    char preOrder[100]={0};
    char infOrder[100]={0};
    int length;
    printf("��������г���: ");
    cin>>length;
    printf("��������Ҫ����������ǰ�����:\n");
    for(int i=0; i<length; ++i)
        cin>>preOrder[i];
    printf("��������Ҫ�����������������:\n");
    for(int i=0; i<length; ++i)
        cin>>infOrder[i];

//    int length = 8;
//    char preOrder[]={'A','B','C','E','D','F','Y','G'};
//    char infOrder[]={'C','B','E','A','Y','F','D','G'};

    b.root = b.createTreeByPreOrderAndInfixOrder(0,length-1,0,length-1,preOrder,infOrder);
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
