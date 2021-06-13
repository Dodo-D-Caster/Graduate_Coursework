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

    //输出
    //递归
    //前序
    printf("递归先序输出: ");
    b.preOrder_recursion(b.getRoot());
    cout<<endl;
    //中序
    printf("递归中序输出: ");
    b.infixOrder_recursion(b.getRoot());
    cout<<endl;
    //后续
    printf("递归后序输出: ");
    b.postOrder_recursion(b.getRoot());
    cout<<endl;
    //非递归
    //前序
    printf("非递归先序输出: ");
    b.preOrder_NONrecursion(b.getRoot());
    cout<<endl;
    //中序
    printf("非递归中序输出: ");
    b.infixOrder_NONrecursion(b.getRoot());
    cout<<endl<<endl;

    //广义表输出
    cout<<"广义表输出: ";
    b.output(b.getRoot());
    cout<<endl<<endl;

    //输出二叉树中指定结点值的左右孩子结点
    char data;
    cout<<"请输入要查找左右孩子的结点的结点值: ";
    cin>>data;
    binaryTreeNode *tmp =  b.getNodeByData(data);
    if(b.leftChild(tmp)!=NULL)
        cout<<"左孩子:"<<b.leftChild(tmp)->data<<endl;
    else
        cout<<"无左孩子"<<endl;
    if(b.rightChild(tmp)!=NULL)
        cout<<"右孩子:"<<b.rightChild(tmp)->data<<endl;
    else
        cout<<"无右孩子"<<endl;
    cout<<endl;

    //输出二叉树叶子结点个数
    cout<<"二叉树叶子结点个数: "<<b.getLeaves()<<endl<<endl;

    //输出二叉树高度
    cout<<"二叉树高度: "<<b.getHeight();

    //释放二叉树
    b.~binaryTree();
}
