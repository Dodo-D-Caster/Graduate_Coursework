#include <iostream>
#include "binarytree.h"
using namespace std;

int main()
{
    //拓展先序序列创建树
    char end = '*';
    binaryTree b(end);
    printf("请输入所要创建的树的前序遍历:\n");
    b.createTreeByPreOrder(b.root);
    cout<<"创建完成"<<endl<<endl;

    //中序线索化
    cout<<"开始进行中序线索化..."<<endl;
    b.createInfixThread();
    cout<<"中序线索化完成"<<endl<<endl;

    //输出
    //递归
    //中序
    printf("递归中序输出: ");
    b.infixOrder_recursion(b.getRoot());
    cout<<endl;
    //非递归
    //中序
    printf("非递归中序输出: ");
    b.infixOrder_NONrecursion(b.getRoot());
    cout<<endl<<endl;

    //输出二叉树中指定结点值的左右孩子结点
    char data;
    cout<<"请输入要查找左右孩子的结点的结点值: ";
    cin>>data;
    binaryTreeNode *tmp =  b.getNodeByData(data);
    if(b.pre(tmp)!=NULL)
        cout<<"前驱结点值:"<<b.pre(tmp)->data<<endl;
    else
        cout<<"无前驱结点"<<endl;
    if(b.next(tmp)!=NULL)
        cout<<"后继结点值:"<<b.next(tmp)->data<<endl;
    else
        cout<<"无后继结点"<<endl;
    cout<<endl;

    //释放二叉树
    b.~binaryTree();
}
