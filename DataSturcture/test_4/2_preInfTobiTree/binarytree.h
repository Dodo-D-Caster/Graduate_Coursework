#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

struct binaryTreeNode{
    char data;  //Ԫ��
    binaryTreeNode *leftChild, *rightChild; //����,�Һ���
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

    char end;   //������ֹ��
    binaryTreeNode *parent(binaryTreeNode *subTree,binaryTreeNode*d);   //���ظ����
    int size(binaryTreeNode *subTree);  //���ؽ�����
    int height(binaryTreeNode *subTree);    //���ظ߶�
    void Insert(binaryTreeNode *subTree, char d);   //����
    void destory(binaryTreeNode *subTree);  //ɾ��
    bool find(binaryTreeNode *subTree, char d); //����

public:
    binaryTreeNode *root;   //��
    binaryTree(){root = NULL;}
    binaryTree(char end){this->end = end; root = NULL;}
    ~binaryTree(){destory(root);}

    void createTreeByPreOrder(binaryTreeNode * &subTree); //ǰ�����������
    binaryTreeNode * createTreeByPreOrderAndInfixOrder
    (int preFront, int preRear, int infFront, int infRear, char preOrder[], char infixOrder[]);  //�����������򴴽���

    binaryTreeNode *parent(binaryTreeNode *d){
        if(root!=NULL && root!=d)
            return parent(root, d);
        else
            return NULL;
    }  //���ظ����
    binaryTreeNode *leftChild(binaryTreeNode *d){
        if(d!=NULL)
            return d->leftChild;
        else
            return NULL;
    }   //��������
    binaryTreeNode *rightChild(binaryTreeNode *d){
        if(d!=NULL)
            return d->rightChild;
        else
            return NULL;
    }  //�����Һ���

    bool isEmpty(){return root==NULL;}  //�ж��Ƿ�Ϊ��
    binaryTreeNode *getRoot(){return root;} //���ظ����
    char getData(binaryTreeNode *tree){return tree->data;}
    int getSize(){return size(root);}   //��ȡ�����
    int getLeaves();    //��ȡҶ�ӽ��
    int getHeight(){return height(root);}   //��ȡ�߶�
    binaryTreeNode *getNodeByData(char d);

    //�ݹ��㷨
    void preOrder_recursion(binaryTreeNode *subTree);  //ǰ�����
    void infixOrder_recursion(binaryTreeNode *subTree);  //�������
    void postOrder_recursion(binaryTreeNode *subTree);  //�������

    //�ǵݹ��㷨
    void preOrder_NONrecursion(binaryTreeNode *subTree);  //ǰ�����
    void infixOrder_NONrecursion(binaryTreeNode *subTree);  //�������

    void output(binaryTreeNode *b);

};

#endif // BINARYTREE_H
