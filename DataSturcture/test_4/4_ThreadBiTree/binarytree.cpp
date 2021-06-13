#include "binarytree.h"
#include "stack"

void binaryTree::createTreeByPreOrder(binaryTreeNode * &subTree){
    char c;
    std::cin>>c;
    if(c!=end){
        //printf("%c",end);
        subTree = new binaryTreeNode(c);
        //subTree->data = c;
        createTreeByPreOrder(subTree->leftChild);
        createTreeByPreOrder(subTree->rightChild);
    }else{
        subTree = NULL;
    }
}

binaryTreeNode * binaryTree::createTreeByPreOrderAndInfixOrder
(int preFront, int preRear, int infFront, int infRear, char preOrder[], char infixOrder[]){
    if(preFront>preRear||infFront>infRear)
        return NULL;
    binaryTreeNode *subTree = new binaryTreeNode;
    subTree->data = preOrder[preFront];    //���ڵ�
    int flag=0;
    for(int i=infFront; i<=infRear; ++i){
        if(preOrder[preFront] == infixOrder[i]){
            flag = i;
            break;
        }
    }
    subTree->leftChild = createTreeByPreOrderAndInfixOrder(preFront+1,preFront+flag-infFront,infFront,flag-1,preOrder,infixOrder);
    subTree->rightChild = createTreeByPreOrderAndInfixOrder(preFront+flag-infFront+1,preRear,flag+1,infRear,preOrder,infixOrder);

    return subTree;
}

void binaryTree::destory(binaryTreeNode *subTree){
    if(subTree != NULL){
        destory(subTree->leftChild);
        destory(subTree->rightChild);
        delete subTree;
    }
}

binaryTreeNode * binaryTree::parent(binaryTreeNode *subTree, binaryTreeNode *d){
    //�������򷵻ؿ�
    if(subTree == NULL)
        return NULL;

    //�ҵ��򷵻�
    if(subTree->leftChild == d || subTree->rightChild == d)
        return subTree;

    //�ݹ�����
    binaryTreeNode *search = parent(subTree->leftChild);
    if(search != NULL)
        return search;
    else
        return parent(subTree->rightChild,d);
}

//�ݹ��㷨
void binaryTree::infixOrder_recursion(binaryTreeNode *subTree){
    if(subTree != NULL){
        if(subTree->leftTag == 0)
            infixOrder_recursion(subTree->leftChild);
        printf("%c",subTree->data);
        if(subTree->rightTag == 0)
            infixOrder_recursion(subTree->rightChild);
    }
}

//�ǵݹ��㷨
void binaryTree::infixOrder_NONrecursion(binaryTreeNode *subTree){
    std::stack<binaryTreeNode *> s;
    binaryTreeNode * bin = root;
    do{
        while(bin != NULL){
            s.push(bin);
            if(bin->leftTag == 0)
                bin = bin->leftChild;
            else
                bin = NULL;
        }
        if(!s.empty()){
            bin = s.top();
            s.pop();
            printf("%c",bin->data);
            if(bin->rightTag == 0)
                bin = bin->rightChild;
            else
                bin = NULL;
        }
    }while(bin!=NULL || !s.empty());
}

binaryTreeNode *binaryTree::getNodeByData(char d){
    std::stack<binaryTreeNode *> s;
    binaryTreeNode *bin = root;
    int flag = 0;
    s.push(NULL);
    while(bin!=NULL){
        if(bin->data == d){
            flag = 1;
            break;
        }
        if(bin->rightChild != NULL)
            s.push(bin->rightChild);
        if(bin->leftChild != NULL)
            bin = bin->leftChild;
        else{
            bin = s.top();
            s.pop();
        }
    }
    if(flag)
        return bin;
    else
        return NULL;
}

int binaryTree::size(binaryTreeNode *subTree){
    if(subTree == NULL)
        return 0;
    else
        return size(subTree->leftChild)+size(subTree->rightChild)+1;
}

int binaryTree::height(binaryTreeNode *subTree){
    if(subTree == NULL)
        return 0;
    else{
        int i = height(subTree->leftChild);
        int j = height(subTree->rightChild);
        return i<j?j+1:i+1;
    }
}



void binaryTree::output(binaryTreeNode *b){
    if(b != NULL){
        std::cout<<b->data;
        if(b->leftChild!=NULL||b->rightChild!=NULL){
            std::cout<<'(';
            output(b->leftChild);
            std::cout<<",";
            if(b->rightChild!=NULL)
                output(b->rightChild);
            std::cout<<")";
        }
    }
}

void binaryTree::createInfixThread(){
    binaryTreeNode *pre = NULL; //ǰ�����
    if(root != NULL){
        createInfixThread(root,pre);
        //�������һ�����
        pre->rightChild = NULL;
        pre->rightTag = 1;
    }
}

void binaryTree::createInfixThread(binaryTreeNode *d, binaryTreeNode *&pre){
    if(d == NULL)
        return;
    //�ݹ�ʹ������������
    createInfixThread(d->leftChild,pre);

    //����ǰ�����
    if(d->leftChild == NULL){
        d->leftChild = pre;
        d->leftTag = 1;
    }

    //����ǰ�����ĺ�̽��
    if(pre != NULL && pre->rightChild == NULL){
        pre->rightChild = d;
        pre->rightTag =1;
    }
    pre = d;
    //�ݹ�ʹ������������
    createInfixThread(d->rightChild,pre);
}
