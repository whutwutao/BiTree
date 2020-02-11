//
//  BiTree.h
//  二叉树
//
//  Created by WuTao on 2020/2/6.
//  Copyright © 2020 WuTao. All rights reserved.
//

#ifndef BiTree_h
#define BiTree_h
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

int find(ElemType a[], ElemType x, int n)
{
    for (int i = 0; i < n ; i++)
    {
        if (a[i] == x)
        {
            return i;
        }
    }
    return -1;
}


//根据前序遍历序列和中序遍历序列构造二叉树
BiTree PreInCreateTree(ElemType Pre[], ElemType In[], int n)
{
    BiTree T = (BiTNode*)malloc(sizeof(BiTNode));
    T->data = Pre[0];
    T->lchild = NULL;
    T->rchild = NULL;
    if (n > 1)
    {
        int index = find(In,Pre[0],n);
        int lSize = index;
        int rSize = n-1-lSize;
        ElemType lPre[lSize],lIn[lSize];//左子树的先序、中序序列
        ElemType rPre[rSize],rIn[rSize];//右子树的先序、中序序列
        if (lSize > 0 && rSize > 0)//若左右子树均非空
        {
            int i = 0;
            for (; i < lSize; i++)
            {
                lPre[i] = Pre[i+1];
                lIn[i] = In[i];
            }
            T->lchild = PreInCreateTree(lPre, lIn, lSize);//构造左子树
            i++;
            for (int j = 0; i < n; j++,i++)
            {
                rPre[j] = Pre[i];
                rIn[j] = In[i];
            }
            T->rchild = PreInCreateTree(rPre, rIn, rSize);//构造右子树
        }
        else if (lSize > 0)//左子树不为空，右子树为空
        {
            for (int i = 0; i < lSize; i++)
            {
                lPre[i] = Pre[i+1];
                lIn[i] = In[i];
            }
            T->lchild = PreInCreateTree(lPre, lIn, lSize);
        }
        else if (rSize > 0)//左子树为空，右子树不为空
        {
            int i = 1,j = 0;
            for (;i < n; i++,j++)
            {
                rPre[j] = Pre[i];
                rIn[j] = In[i];
            }
            T->rchild = PreInCreateTree(rPre, rIn,rSize);
        }
    }
    return T;
}

//另一种写法，代码量比较少
//s1,e1分别为先序遍历序列的起点和终点位置下标，s2,e2分别为中序遍历序列的起点和终点位置下标
BiTree PreInCreateTree(ElemType Pre[],ElemType In[],int s1,int e1,int s2,int e2)
{
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    T->data = Pre[s1];
    int i;
    for (i = s2; T->data != In[i]; i++);
    int len1 = i - s2;//左子树序列长度
    int len2 = e2 - i;//右子树序列长度
    if (len1 > 0)
    {
        T->lchild = PreInCreateTree(Pre,In,s1+1,s1+len1,s2,s2+len1-1);
    }
    else
    {
        T->lchild = NULL;
    }
    if (len2 > 0)
    {
        T->rchild = PreInCreateTree(Pre,In,s1+1+len1,s1+len1+len2,s2+len1+1,s2+len1+len2);
    }
    else
    {
        T->rchild = NULL;
    }
    return T;
}


//释放以T为根结点的二叉树所占存储空间
void destoryBiTree(BiTree T)
{
    if (T != NULL)
    {
        destoryBiTree(T->lchild);
        destoryBiTree(T->rchild);
//        printf("结点%d已释放\n",T->data);
        free(T);
    }
}


//访问结点
void visit(BiTNode *node)
{
    if (node != NULL)
    {
        cout << node->data << " ";
    }
}

//先序遍历
void PreOrder(BiTree T)
{
    if (T != NULL)
    {
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}


//先序遍历的非递归算法
void PreOrder1(BiTree T)
{
    //结点栈的初始化
    //结点栈用来保存遍历过程中 访问过的结点的 右孩子结点
    int MaxSize = 50;
    BiTNode* Stack[MaxSize];
    int top = -1;
    
    BiTNode *p = T;//p指向根结点
    while (p != NULL || top != -1)//当p的指向不为空 或 栈非空时
    {
        if (p != NULL)
        {
            visit(p);//先访问根结点
            if (p->rchild != NULL)
            {
                Stack[++top] = p->rchild;//若根结点的右孩子不为空则将其入栈
            }
            p = p->lchild;//p指向根结点的左孩子
        }
        else//p为空时
        {
            //p为空说明刚刚访问过的结点的左孩子为空，则从栈中将该结点的右孩子出栈进行下一次访问
            p = Stack[top--];
        }
    }
}


//中序遍历
void InOrder(BiTree T)
{
    if (T != NULL)
    {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}


//中序遍历的非递归算法
void InOrder1(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    //结点栈的初始化
    //结点栈用来保存遍历过程中 访问过的结点的 双亲结点
    int MaxSize = 50;
    BiTNode* Stack[MaxSize];
    int top = -1;
    
    BiTNode *p = T;
    while (p != NULL || top != -1)//当p指向结点不空 或 栈非空时
    {
        if (p != NULL)//p指向结点非空时
        {
            Stack[++top] = p;//将p入栈
            p = p->lchild;//p指向其左孩子结点
        }
        else//p指向结点为空但栈非空时
        {
            p = Stack[top--];//栈顶结点出栈,p指向此结点
            visit(p);//访问该结点
            p = p->rchild;//p指向该结点的右孩子结点
        }
    }
}


//后序遍历
void PostOrder(BiTree T)
{
    if (T != NULL)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}


//后序遍历的非递归算法
//后序遍历与其他两种遍历有所不同，后序遍历每个根结点都要入栈两次
void PostOrder1(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    
    typedef struct
    {
        BiTNode *nodeptr;//结点指针
        bool status;     //入栈标志;表示该结点是第几次入栈，false为第1次，true为第2次
    }stackElem;//栈元素类型，保存一个结点指针和这个结点的入栈标志
    
    //结点栈的初始化
    //结点栈用来保存遍历过程中 经过但未访问的 根结点
    int MaxSize = 50;
    stackElem Stack[MaxSize];
    int top = -1;//栈顶指针
    
    BiTNode *p = T;
    stackElem temp;
    
    while (p != NULL || top != -1)
    {
        if (p != NULL)//根结点非空
        {
            temp.nodeptr = p;     //将根结点入栈
            temp.status = false;  //记录此结点为第一次入栈
            Stack[++top] = temp;
            p = p->lchild;        //p指向根结点的左孩子
        }
        else
        {
            temp = Stack[top--];//栈顶结点及其入栈标志出栈
            p = temp.nodeptr;
            
            if (!temp.status)//若此结点为第1次入栈,则将此结点2次入栈,并考察它的右子树
            {
                temp.status = true;
                Stack[++top] = temp;
                p = p->rchild;
            }
            else//若此结点已经为第2此入栈，则直接访问该结点
            {
                visit(p);//访问此结点
                p = NULL;
                //此结点已经访问，下一个要考察的结点是栈中的结点，所以要将p设为空,下一步就强制退栈
            }
        }
    }
}


//层次遍历
void LevelOrder(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    
    int MaxSize = 50;//队列最大存放元素个数
    BiTNode* Queue[MaxSize];//存放结点的队列
    int front = 0, rear = 0;//初始化
    BiTNode *p = T;
    Queue[rear] = p;             //根结点入队
    rear = (rear + 1) % MaxSize;
    while (front != rear)//当队列非空时
    {
        p = Queue[front];//队首元素出队
        front = (front + 1) % MaxSize;
        visit(p);
        if (p->lchild != NULL)
        {
            Queue[rear] = p->lchild;
            rear = (rear + 1) % MaxSize;
        }
        if (p->rchild != NULL)
        {
            Queue[rear] = p->rchild;
            rear = (rear + 1) % MaxSize;
        }
    }
}

//以与层次遍历相反的顺序遍历二叉树
//利用栈，在进行层次遍历时，将出队元素入栈而不访问，等所有结点都入栈了再将栈中结点依次出栈访问
void reLevelOrder(BiTree T)
{
    if (T != NULL)
    {
        int MaxSize = 50;//队列、栈的最大存放元素个数
        //队列的初始化
        BiTNode* Queue[MaxSize];//存放结点的队列
        int front = 0, rear = 0;//初始化
        //栈的初始化
        BiTNode* Stack[MaxSize];
        int top = -1;
        BiTNode *p = T;
        Queue[rear] = p;//根结点入队
        rear = (rear + 1) % MaxSize;
        //将所有结点按层次遍历的顺序依次入栈
        while (front != rear)
        {
            p = Queue[front];//队首元素出队
            front = (front + 1) % MaxSize;
            
            Stack[++top] = p;//将其入栈
            
            if (p->lchild != NULL)
            {
                Queue[rear] = p->lchild;
                rear = (rear + 1) % MaxSize;
            }
            if (p->rchild != NULL)
            {
                Queue[rear] = p->rchild;
                rear = (rear + 1) % MaxSize;
            }
        }
        //将所有结点依次出栈访问
        while (top > -1)
        {
            p = Stack[top--];//栈顶结点出栈
            visit(p);//访问
        }
    }
}


//求二叉树的高度，递归算法
int getHeight(BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    else
    {
        BiTNode *p = T;
        int lHeight = getHeight(p->lchild);
        int rHeight = getHeight(p->rchild);
        if (lHeight > rHeight)
        {
            return 1 + lHeight;
        }
        else
        {
            return 1 + rHeight;
        }
    }
}

//求二叉树的高度，非递归算法
int getHeight1(BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    
    int MaxSize = 50;
    BiTNode* Queue[MaxSize];
    int front = 0, rear = 0;
    
    int last = 1;//下一层的第一个结点在队列中的下标
    int level = 0;
    Queue[rear++] = T;
    BiTNode *p = T;
    while (front != rear)
    {
        p = Queue[front++];
        if (p->lchild)
        {
            Queue[rear++] = p->lchild;
        }
        if (p->rchild)
        {
            Queue[rear++] = p->rchild;
        }
        if (front == last)
        {
            level++;
            last = rear;
        }
    }
    return level;
}


//判断二叉树是否为完全二叉树
//还是利用层次遍历，在遍历过程中，将结点的左右孩子不论是否为空都入队，当出队元素为空时判断队列中此元素
//之后的结点是否都为空，若不是则不是完全二叉树
bool isComplete(BiTree T)
{
    queue<BiTNode *> Queue;//结点队列
    Queue.push(T);//根结点入队
    BiTNode *p = T;
    while (!Queue.empty())
    {
        p = Queue.front();
        Queue.pop();
        if (p)
        {
            Queue.push(p->lchild);
            Queue.push(p->rchild);
        }
        else
        {
            while (!Queue.empty())
            {
                if (Queue.front() != NULL)
                {
                    return false;
                }
                Queue.pop();
            }
        }
    }
    return true;
}


//求一颗二叉树的双分支结点的个数
int DoubleSonNode(BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    else if (T->lchild && T->rchild)//若根结点左右孩子均不为空
    {
        return DoubleSonNode(T->lchild) + DoubleSonNode(T->rchild) + 1;
        //加1是加上根结点自己
    }
    else
    {
        return DoubleSonNode(T->lchild) + DoubleSonNode(T->rchild);
        //此处根结点不是双分支结点，所以不加1
    }
}


//将二叉树的所有结点的左右子树进行交换
void exchange(BiTree T)
{
    if (T)
    {
        exchange(T->lchild);
        exchange(T->rchild);
        BiTNode *temp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = temp;
    }
}


//求二叉树先序遍历过程中第k个访问的结点的值
bool PreOrderNode(BiTree T, ElemType &value, int k)
{
    if (!T)
    {
        return false;
    }
    static int i = 1;
    if (i == k)
    {
        value = T->data;
        return true;
    }
    else
    {
        i++;
        if (PreOrderNode(T->lchild,value,k))
        {
            return true;
        }
        else
        {
            return PreOrderNode(T->rchild,value,k);
        }
    }
}

//求后序遍历的第k个结点值
bool PostOrderNode(BiTree T, ElemType &value, int k)
{
    static int i = 1;
    if (T == NULL)
    {
        return false;
    }
    typedef struct
    {
        BiTNode *nodeptr;
        bool status;
    }stackElem;
    
    int MaxSize = 50;
    stackElem stack[MaxSize];
    int top = -1;
    
    BiTNode *p = T;
    stackElem temp;
    while (p || top != -1)
    {
        if (p)
        {
            temp.nodeptr = p;
            temp.status = false;
            stack[++top] = temp;
            p = p->lchild;
        }
        else
        {
            temp = stack[top--];
            p = temp.nodeptr;
            if (temp.status)
            {
                if (i == k)
                {
                    value = p->data;
                    return true;
                }
                else
                {
                    i++;
                }
                p = NULL;
                
            }
            else
            {
                temp.status = true;
                stack[++top] = temp;
                p = p->rchild;
            }
        }
    }
    return false;
}


//将二叉树中所有 根结点的值为x的子树删除
//层次遍历整棵树，当找到值为x的结点时，将其父结点的左(右)孩子指针置为空
void delXTree(BiTree T, ElemType x)
{
    if (T)
    {
        if (T->data == x)
        {
            destoryBiTree(T);
            return;
        }
        int MaxSize = 50;
        BiTNode * Queue[MaxSize];
        int front = 0, rear = 0;
        BiTNode *p;
        Queue[rear++] = T;
        while (front < rear)
        {
            p = Queue[front++];
            if (p->lchild)
            {
                if (p->lchild->data == x)
                {
                    destoryBiTree(p->lchild);
                    p->lchild = NULL;
                }
                else
                {
                    Queue[rear++] = p->lchild;
                }
            }
            if (p->rchild)
            {
                if (p->rchild->data == x)
                {
                    destoryBiTree(p->rchild);
                    p->rchild = NULL;
                }
                else
                {
                    Queue[rear++] = p->rchild;
                }
            }
        }
    }
}


//打印值为x的结点的所有祖先结点值
//采用非递归的后序遍历，若当前结点值为x，则将栈中所有元素出栈，
//只需把后序遍历中的 visit(p) 改为输出栈中所有结点值即可
void ancestor(BiTree T, ElemType x)
{
    if (T == NULL)
    {
        return;
    }
    
    typedef struct
    {
        BiTNode *nodeptr;//结点指针
        bool status;     //入栈标志;表示该结点是第几次入栈，false为第1次，true为第2次
    }stackElem;//栈元素类型，保存一个结点指针和这个结点的入栈标志
    
    //结点栈的初始化
    //结点栈用来保存遍历过程中 经过但未访问的 根结点
    int MaxSize = 50;
    stackElem Stack[MaxSize];
    int top = -1;//栈顶指针
    
    BiTNode *p = T;
    stackElem temp;
    
    while (p != NULL || top != -1)
    {
        if (p != NULL)//根结点非空
        {
            temp.nodeptr = p;     //将根结点入栈
            temp.status = false;  //记录此结点为第一次入栈
            Stack[++top] = temp;
            p = p->lchild;        //p指向根结点的左孩子
        }
        else
        {
            temp = Stack[top--];//栈顶结点及其入栈标志出栈
            p = temp.nodeptr;
            
            if (!temp.status)//若此结点为第1次入栈,则将此结点2次入栈,并考察它的右子树
            {
                temp.status = true;
                Stack[++top] = temp;
                p = p->rchild;
            }
            else//若此结点已经为第2此入栈，则直接访问该结点
            {
                if (p->data == x)
                {
                    while (top != -1)
                    {
                        cout << Stack[top--].nodeptr->data << " ";
                    }
                    cout << endl;
                }
                p = NULL;
                //此结点已经访问，下一个要考察的结点是栈中的结点，所以要将p设为空,下一步就强制退栈
            }
        }
    }

}


//找到二叉树中p、q结点最近的公共祖先结点
//利用非递归后序遍历中的栈
void commonAncestor(BiTree T, ElemType p, ElemType q)
{
    if (T)
    {
        int MaxSize = 50;
        typedef struct
        {
            BiTNode *ptr;
            bool status;
        }stackElem;
        stackElem st1[MaxSize],st2[MaxSize],st3[MaxSize];//st1为工作栈,st2,st3为辅助栈
        int top1 = -1, top2 = -1, top3 = -1;
        BiTNode *s = T;
        stackElem temp;
        while (s || top1 != -1)
        {
            if (s)
            {
                temp.ptr = s;
                temp.status = false;
                st1[++top1] = temp;
                s = s->lchild;
            }
            else
            {
                temp = st1[top1--];
                s = temp.ptr;
                if (!temp.status)
                {
                    temp.status = true;
                    st1[++top1] = temp;
                    s = s->rchild;
                }
                else
                {
                    //对此结点进行操作
                    if (temp.ptr->data == p)//若此结点为p，则将st1中结点复制到辅助栈st2中
                    {
                        for (int i = 0; i <= top1; i++)
                        {
                            st2[i] = st1[i];
                        }
                        top2 = top1;
                    }
                    if (temp.ptr->data == q)
                        //若此结点为q，则将当前st1中的结点复制到辅助栈st3中
                    {
                        for (int i = 0; i <= top1; i++)
                        {
                            st3[i] = st1[i];
                        }
                        top3 = top1;
                    }
                    
                    if (top2 != -1 && top3 != -1)
                    //若两个辅助栈均非空,则说明p、q均已遍历到，将两个辅助栈进行匹配
                    //找到的第一个公共元素即为所求
                    {
                        for (int i = top3; i >= 0; i--)
                        {
                            for (int j = top2; j >=0; j--)
                            {
                                if (st3[i].ptr == st2[j].ptr)
                                {
                                    visit(st1[i].ptr);
                                    return;
                                }
                            }
                        }
                    }
                    
                    s = NULL;
                }
            }
        }
    }
}


//求二叉树的宽度，即具有结点数最多的那一层的结点个数
int getWidth(BiTree T)
{
    int MaxSize = 50;
    BiTNode * Queue[MaxSize];
    int front = 0, rear = 0;
    int width = 0, count = 0;
    int nextfirst = 1;//表示下一层的第一个结点在队列中的的下标
    Queue[rear++] = T;
    BiTNode *p;
    while (front != rear)
    {
        p = Queue[front++];
        count++;
        if (p->lchild)
        {
            Queue[rear++] = p->lchild;
        }
        if (p->rchild)
        {
            Queue[rear++] = p->rchild;
        }
        //由于下一层第一个结点的位置取决于当前层结点的个数，
        //所以要先把当前结点的左右孩子入队，再判断一层是否遍历完
        if (front == nextfirst)
        {
            if (width < count)
            {
                width = count;
            }
            count = 0;
            nextfirst = rear;
        }
    }
    return width;
}

//已知一颗满二叉树的先序序列pre，求其后序序列post
void PreToPost(ElemType Pre[],int l1,int h1,ElemType Post[],int l2, int h2)
{
    int half;
    if (h1 >= l1)
    {
        Post[h2] = Pre[l1];
        half = (h1 - h1) / 2;
        PreToPost(Pre,l1+1,l1+half,Post,l2,l2+half-1);//转换左子树
        PreToPost(Pre,l1+half+1,h1,Post,l2+half,h2-1);//转换右子树
    }
}


//将二叉树的叶子结点从左至右顺序连成一个单链表，表头指针为head，用叶结点的右指针域存放链表指针
//采用中序遍历，当遍历到叶结点时将其插入到链表尾部
BiTNode * LeafLinkList(BiTree T)
{
    BiTNode *head = NULL;
    if (T)
    {
        int MaxSize = 50;
        BiTNode *st[MaxSize];
        int top = -1;
        BiTNode *p = T;
        BiTNode *pre = NULL;
        while (p || top != -1)
        {
            if (p)
            {
                st[++top] = p;
                p = p->lchild;
            }
            else
            {
                p = st[top--];
                //对此结点进行操作
                if (p->lchild == NULL && p->rchild == NULL)
                {
                    if (pre == NULL)
                    {
                        head = p;
                        pre = p;
                    }
                    else
                    {
                        pre->rchild = p;
                        pre = p;
                    }
                }
                p = p->rchild;
            }
        }
    }
    return head;
}


//判断两棵二叉树是否相似，王道书2020版第127页第17题
bool isSimilar(BiTree T1, BiTree T2)
{
    if (T1 == NULL && T2 == NULL)
    {
        return true;
    }
    if (T1 == NULL || T2 == NULL)
    {
        return false;
    }
    return isSimilar(T1->lchild,T2->lchild) && isSimilar(T1->rchild, T2->rchild);
}


//用递归算法求二叉树的带权路径长度(WPL)
//WPL:树的每个叶结点的权值与其到根结点路径长度乘积的总和
//先序递归遍历
int wpl_PreOrder(BiTree T, int deep)//deep为起始结点的深度
{
    static int wpl = 0;//静态变量，累加的最终值为整棵树的WPL
    if (T->lchild == NULL && T->rchild == NULL)
    {
        wpl += (deep - 1) * T->data;//路径长度为 深度-1
    }
    if (T->lchild != NULL)//将左子树的WPL累加至wpl
    {
        wpl_PreOrder(T->lchild, deep+1);
    }
    if (T->rchild != NULL)//将右子树的WPL累加至wpl
    {
        wpl_PreOrder(T->rchild, deep+1);
    }
    return wpl;
}

int wpl(BiTree root)
{
    return wpl_PreOrder(root,1);//初始结点为根结点，深度为1
}

int wpl_LevelOrder(BiTree T)
{
    int wpl = 0;
    int level = 0, currentlast = 0, nextfirst = 1;
    int MaxSize = 50;
    BiTNode * Queue[MaxSize];
    int front = 0, rear = 0;
    Queue[rear++] = T;
    BiTNode *p;
    while (front != rear)
    {
        p = Queue[front++];
        if (!p->lchild && !p->rchild)//若为叶结点3
        {
            wpl += level * p->data;
        }
        else
        {
            if (p->lchild)
            {
                Queue[rear++] = p->lchild;
            }
            if (p->rchild)
            {
                Queue[rear++] = p->rchild;
            }
        }
        if (front == nextfirst)
        {
            level++;
            currentlast = rear - 1;
            nextfirst = rear;
        }
    }
    return wpl;
}


void BiTreeToExp(BiTree root, int deep)
{
    if (!root)
    {
        return;
    }
    else if (!root->lchild && !root->rchild)
    {
        printf("%c",root->data);
    }
    else
    {
        if (deep > 1)
        {
            printf("(");
        }
        BiTreeToExp(root->lchild,deep + 1);
        printf("%c",root->data);
        BiTreeToExp(root->rchild,deep + 1);
        if (deep > 1)
        {
            printf(")");
        }
    }
}

void TreeToExpress(BiTree tree)
{
    cout << "该树对应的中缀表达式为: ";
    BiTreeToExp(tree, 1);
}
#endif /* BiTree_h */
