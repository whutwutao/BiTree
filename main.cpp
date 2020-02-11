#include "BiTree.h"
#include <iostream>
using namespace std;
int main()
{
//    int Pre[4] = {1,2,3,4};
//    int In[4] = {1,2,3,4};
    ElemType Pre[8] = {'*','+','a','b','*','c','-','d'};
    ElemType In[8] =  {'a','+','b','*','c','*','-','d'};
    BiTree tree = PreInCreateTree(Pre, In, 0, 7, 0, 7);
    cout << "先序遍历: "; PreOrder1(tree); cout << endl;
    cout << "中序遍历: "; InOrder1(tree);  cout << endl;
    cout << "后序遍历: "; PostOrder1(tree); cout << endl;
    cout << "层次遍历: "; LevelOrder(tree); cout << endl;
    cout << "反层次遍历: "; reLevelOrder(tree); cout << endl;
    cout << "二叉树的高度: ";cout << getHeight1(tree) << endl;
//    cout << "带权路径长度: " << wpl_LevelOrder(tree) << endl;
    cout << "二叉树的宽度: " << getWidth(tree) << endl;
    TreeToExpress(tree);
    cout << endl;
    destoryBiTree(tree);
    return 0;
}
