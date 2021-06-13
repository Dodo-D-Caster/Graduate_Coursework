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

void binaryTree::destory(binaryTreeNode *subTree){
    if(subTree != NULL){
        destory(subTree->leftChild);
        destory(subTree->rightChild);
        delete subTree;
    }
}

binaryTreeNode * binaryTree::parent(binaryTreeNode *subTree, binaryTreeNode *d){
    //不存在则返回空
    if(subTree == NULL)
        return NULL;

    //找到则返回
    if(subTree->leftChild == d || subTree->rightChild == d)
        return subTree;

    //递归搜索
    binaryTreeNode *search = parent(subTree->leftChild);
    if(search != NULL)
        return search;
    else
        return parent(subTree->rightChild,d);
}

//递归算法
void binaryTree::preOrder_recursion(binaryTreeNode *subTree){
    if(subTree != NULL){
        printf("%c",subTree->data);
        preOrder_recursion(subTree->leftChild);
        preOrder_recursion(subTree->rightChild);
    }
}

void binaryTree::infixOrder_recursion(binaryTreeNode *subTree){
    if(subTree != NULL){
        infixOrder_recursion(subTree->leftChild);
        printf("%c",subTree->data);
        infixOrder_recursion(subTree->rightChild);
    }
}

void binaryTree::postOrder_recursion(binaryTreeNode *subTree){
    if(subTree != NULL){
        postOrder_recursion(subTree->leftChild);
        postOrder_recursion(subTree->rightChild);
        printf("%c",subTree->data);
    }
}

//非递归算法
void binaryTree::preOrder_NONrecursion(binaryTreeNode *subTree){
    std::stack<binaryTreeNode *> s;
    binaryTreeNode *bin = root;
    s.push(NULL);
    while(bin!=NULL){
        printf("%c",bin->data);
        if(bin->rightChild != NULL)
            s.push(bin->rightChild);
        if(bin->leftChild != NULL)
            bin = bin->leftChild;
        else{
            bin = s.top();
            s.pop();
        }
    }
}

void binaryTree::infixOrder_NONrecursion(binaryTreeNode *subTree){
    std::stack<binaryTreeNode *> s;
    binaryTreeNode * bin = root;
    do{
        while(bin != NULL){
            s.push(bin);
            bin = bin->leftChild;
        }
        if(!s.empty()){
            bin = s.top();
            s.pop();
            printf("%c",bin->data);
            bin = bin->rightChild;
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

int binaryTree::getLeaves(){
    int size = 0;
    std::stack<binaryTreeNode *> s;
    binaryTreeNode * bin = root;
    do{
        while(bin != NULL){
            s.push(bin);
            bin = bin->leftChild;
        }
        if(!s.empty()){
            bin = s.top();
            s.pop();
            if(bin->rightChild == NULL && bin->leftChild == NULL)
                size++;
            bin = bin->rightChild;
        }
    }while(bin!=NULL || !s.empty());
    return size;

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
