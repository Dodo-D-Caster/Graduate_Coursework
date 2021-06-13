#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

struct binaryTreeNode{
    char data;  //元素
    binaryTreeNode *leftChild, *rightChild; //左孩子,右孩子
    binaryTreeNode(){leftChild = NULL; rightChild = NULL;}
    binaryTreeNode(char d){
        data = d;
        leftChild = NULL;
        rightChild = NULL;
    }
};

class binaryTree
{
protected:

    char end;   //输入终止符
    binaryTreeNode *parent(binaryTreeNode *subTree,binaryTreeNode*d);   //返回父结点
    int size(binaryTreeNode *subTree);  //返回结点个数
    int height(binaryTreeNode *subTree);    //返回高度
    void Insert(binaryTreeNode *subTree, char d);   //插入
    void destory(binaryTreeNode *subTree);  //删除
    bool find(binaryTreeNode *subTree, char d); //查找

public:
    binaryTreeNode *root;   //根
    binaryTree(){root = NULL;}
    binaryTree(char end){this->end = end; root = NULL;}
    ~binaryTree(){destory(root);}

    void createTreeByPreOrder(binaryTreeNode * &subTree); //前序遍历创建树
    binaryTreeNode * createTreeByPreOrderAndInfixOrder
    (int preFront, int preRear, int infFront, int infRear, char preOrder[], char infixOrder[]);  //根据先序中序创建树

    binaryTreeNode *parent(binaryTreeNode *d){
        if(root!=NULL && root!=d)
            return parent(root, d);
        else
            return NULL;
    }  //返回父结点
    binaryTreeNode *leftChild(binaryTreeNode *d){
        if(d!=NULL)
            return d->leftChild;
        else
            return NULL;
    }   //返回左孩子
    binaryTreeNode *rightChild(binaryTreeNode *d){
        if(d!=NULL)
            return d->rightChild;
        else
            return NULL;
    }  //返回右孩子

    bool isEmpty(){return root==NULL;}  //判断是否为空
    binaryTreeNode *getRoot(){return root;} //返回根结点
    char getData(binaryTreeNode *tree){return tree->data;}
    int getSize(){return size(root);}   //获取结点数
    int getLeaves();    //获取叶子结点
    int getHeight(){return height(root);}   //获取高度
    binaryTreeNode *getNodeByData(char d);

    //递归算法
    void preOrder_recursion(binaryTreeNode *subTree);  //前序遍历
    void infixOrder_recursion(binaryTreeNode *subTree);  //中序遍历
    void postOrder_recursion(binaryTreeNode *subTree);  //后序遍历

    //非递归算法
    void preOrder_NONrecursion(binaryTreeNode *subTree);  //前序遍历
    void infixOrder_NONrecursion(binaryTreeNode *subTree);  //中序遍历

    void output(binaryTreeNode *b);

};

#endif // BINARYTREE_H
