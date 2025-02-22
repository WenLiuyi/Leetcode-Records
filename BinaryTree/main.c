//
//  main.c
//  BinaryTree
//
//  Created by 文柳懿 on 2025/2/6.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "uthash.h"

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Leetcode 114. 二叉树的前序遍历：根节点-左子树-右子树
// 法一：递归
/*
void preorder(struct TreeNode *root, int *res, int *resSize){
    if(root==NULL) return;
    res[(*resSize)++]=root->val;
    preorder(root->left,res,resSize);
    preorder(root->right,res,resSize);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int *res=(int *)malloc(sizeof(int)*2005);
    *returnSize=0;
    preorder(root,res,returnSize);
    return res;
}
*/

// 法二：迭代:
// 设立栈的目的：保存尚未遍历右子树的节点
/*
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *res=(int *)malloc(sizeof(int)*2005);
    *returnSize=0;
    if(root==NULL) return res;
    
    struct TreeNode **stack=(struct TreeNode **)malloc(sizeof(struct TreeNode *)*2005);
    struct TreeNode *curNode=root;
    int top=-1;
    
    while(top>=0 || curNode!=NULL){
        while(curNode!=NULL){
            // 先加入根节点，深入最左节点
            res[(*returnSize)++]=curNode->val;
            stack[++top]=curNode;
            curNode=curNode->left;
        }
        curNode=stack[top--];
        curNode=curNode->right;
    }
    return res;
}
 */

// 法三：Morris遍历
// 时间复杂度：O(n)，没有左子树的节点只被访问一次，有左子树的节点被访问两次。
// 空间复杂度：O(1)
/*
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *res=(int *)malloc(sizeof(int)*2005);
    *returnSize=0;
    if(root==NULL) return res;
    
    struct TreeNode *p1 = root, *p2 = NULL;
    
    while(p1!=NULL){
        p2=p1->left;
        if(p2!=NULL){
            // 1. 当前节点的左子节点非空：在当前节点的左子树中，找到当前节点在中序遍历下的前驱节点p2
            while(p2->right!=NULL && p2->right!=p1){
                // 移动p2，使得：p2是p1的前驱节点
                p2=p2->right;
            }
            if(p2->right==NULL){
                // 1.1 前驱节点的右子节点为空：设置为当前节点
                // 当前节点更新为：当前节点的左子节点
                res[(*returnSize)++]=p1->val;
                p2->right=p1;
                p1=p1->left;
                continue;
            }else{
                // 1.2 前驱节点的右子节点为当前节点：设置为空；
                // 当前节点更新为：当前节点的右子节点
                p2->right=NULL;
            }
        }else{
            // 2. 当前节点的左子节点为空: 将当前节点加入答案
            res[(*returnSize)++]=p1->val;
        }
        p1=p1->right;
    }
    return res;
}
 */


// Leetcode 204. 二叉树的最大深度:max(l,r)+1
// 法一：深度优先搜索，递归遍历左右子树
// 时间复杂度：O(n)；空间复杂度：O(height)

/*
int maxDepth(struct TreeNode* root) {
    if(root==NULL) return 0;
    return fmax(maxDepth(root->left),maxDepth(root->right))+1;
}*/

// 法二：广度优先搜索，逐层遍历，维护队列
//时间复杂度：O(n)；空间复杂度：O(n)
struct QueNode{
    struct TreeNode *p;     // 当前节点
    struct QueNode *next;  // 下一个节点
};

void init(struct QueNode **root,struct TreeNode *t){
    // 初始化队列p的头节点为t
    (*root)=(struct QueNode *)malloc(sizeof(struct QueNode));
    (*root)->p=t;
    (*root)->next=NULL;
}

int maxDepth(struct TreeNode *root){
    if(root==NULL) return 0;
    struct QueNode *head, *tail;    // head为当前节点；tail为队列尾节点
    init(&head,root);   // 根节点加入队列
    tail=head;
    int ans=0,size=1,tmp=0; // ans为当前层高度；size为下一层的节点数；tmp用于统计当前层所有节点的所有左右节点数目
    while(head!=NULL){
        tmp=0;
        while(size>0){
            // 依次遍历当前节点的左右节点，若存在，加入队尾
            if(head->p->left!=NULL){
                init(&tail->next,head->p->left);    // 队尾加入一个节点
                tail=tail->next;
                tmp++;
            }
            if(head->p->right!=NULL){
                init(&tail->next,head->p->right);
                tail=tail->next;
                tmp++;
            }
            head=head->next;
            size--;
        }
        size+=tmp;
        ans++;
    }
    return ans;
}
/*
int main(){
    struct TreeNode *tree=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    tree->val=3;
    tree->left=(struct TreeNode *)malloc(sizeof(struct TreeNode));tree->right=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    tree->left->val=9;tree->right->val=20;
    tree->right->left=(struct TreeNode *)malloc(sizeof(struct TreeNode));tree->right->right=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    tree->right->left->val=15;tree->right->right->val=7;
    printf("%d",maxDepth(tree));
    return 0;
}
*/

// Leetcode 100. 相同的树: 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同
// 法一：深度优先搜索
// 时间复杂度：O(min(m,n))，其中 m,n 分别是两个二叉树的节点数;
// 空间复杂度：O(min(m,n))，其中 m 和 n 分别是两个二叉树的节点数。空间复杂度取决于递归调用的层数，递归调用的层数不会超过较小的二叉树的最大高度，最坏情况下，二叉树的高度等于节点数。

/*
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if(p==NULL && q==NULL) return true;
    else if(p==NULL || q==NULL) return false;   // 结构不同
    else if(p->val!=q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);  // 递归判断左右子树
}
*/

// 法二：广度优先搜索
bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    if(p==NULL && q==NULL) return true;
    else if(p==NULL || q==NULL) return false;   // 结构不同
    struct TreeNode** que1 = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    struct TreeNode** que2 = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    int head1 = 0, tail1 = 0;
    int head2 = 0, tail2 = 0;
    que1[tail1++]=p;que2[tail2++]=q;
    
    while(head1<tail1 && head2<tail2){
        struct TreeNode *node1=que1[head1++],*node2=que2[head2++];
        if(node1->val!=node2->val) return false;
        else if((node1->left==NULL)^(node2->left==NULL)) return false;
        else if((node1->right==NULL)^(node2->right==NULL)) return false;
        
        // 当前节点的非空子节点加入队尾
        if(node1->left!=NULL){
            tail1++;
            que1=realloc(que1,sizeof(struct TreeNode *)*tail1);
            que1[tail1-1]=node1->left;
        }
        if(node2->left!=NULL){
            tail2++;
            que2=realloc(que2,sizeof(struct TreeNode *)*tail2);
            que2[tail2-1]=node2->left;
        }
        if(node1->right!=NULL){
            tail1++;
            que1=realloc(que1,sizeof(struct TreeNode *)*tail1);
            que1[tail1-1]=node1->right;
        }
        if(node2->right!=NULL){
            tail2++;
            que2=realloc(que2,sizeof(struct TreeNode *)*tail2);
            que2[tail2-1]=node2->right;
        }
    }
    
    // 搜索结束时，两个队列需同时为空
    return head1==tail1 && head2==tail2;
}

// Leetcode 226. 翻转二叉树：自底向上翻转，先递归，再交换左右节点（此时左右子树均已完成翻转）
struct TreeNode* invertTree(struct TreeNode* root) {
    if(root==NULL) return NULL;
    struct TreeNode *left=invertTree(root->left);
    struct TreeNode *right=invertTree(root->right);
    root->left=right;root->right=left;
    return root;
}


// Leetcode 101. 对称二叉树：给你一个二叉树的根节点 root，检查它是否轴对称
// 1. 递归：自顶向下，维护两个指针，分别指向左右子树
// 时间复杂度：这里遍历了这棵树，渐进时间复杂度为 O(n)。
// 空间复杂度：这里的空间复杂度和递归使用的栈空间有关，这里递归层数不超过 n，故渐进空间复杂度为 O(n)
/*
bool check(struct TreeNode *p,struct TreeNode *q){
    if(p==NULL && q==NULL) return true;
    if((p==NULL)||(q==NULL)) return false;
    return (p->val==q->val) && check(p->left,q->right) && check(p->right,q->left);
}

bool isSymmetric(struct TreeNode* root) {
    return check(root,root);
}
*/

// 2. 迭代：维护队列，每次插入两个节点，判断连续两节点是否满足：值相等，子树互为镜像
bool isSymmetric(struct TreeNode* root) {
    struct TreeNode **queue=(struct TreeNode **)malloc(sizeof(struct TreeNode *)*1005);
    int head=0,tail=0;
    queue[tail++]=root->left;queue[tail++]=root->right;
    while(head!=tail){
        struct TreeNode *cur1=queue[head++],*cur2=queue[head++];
        if(cur1==NULL && cur2==NULL) continue;
        if((cur1==NULL)^(cur2==NULL)) return false;
        if(cur1->val!=cur2->val) return false;
        queue[tail++]=cur1->left;queue[tail++]=cur2->right;
        queue[tail++]=cur1->right;queue[tail++]=cur2->left;
    }
    return true;
}

// Leetcode 105. 从前序与中序遍历序列构造二叉树:给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
// 前序遍历：根节点-左子树-右子树
// 中序遍历：左子树-根节点-右子树

// 法一：暴力递归，在中序序列中找到根节点位置，拆成左右子树
// 注：可以初始扫描中序序列，构建哈希映射：键表示一个元素（节点的值），值表示其在中序遍历中的出现位置
/*
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    // preorder指向当前根节点的位置；inorder指向
    struct TreeNode *root=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    if(preorderSize==0) return 0;
    root->val=preorder[0];  //根节点
    
    int i=0;
    for(;i<inorderSize;i++){
        // 遍历中序数组，直至找到根节点，左侧为左子树，右侧为右子树
        if(inorder[i]==root->val) break;
    }
    root->left=buildTree(preorder+1,i,inorder,i);
    root->right=buildTree(preorder+i+1,preorderSize-i-1,inorder+i+1,inorderSize-i-1);
    return root;
}
 */

// 法二：迭代
// 前序遍历：两个连续节点，后一个是前一个的左儿子，或者前一个某祖先节点的右儿子
// 建立一个栈维护：当前节点的所有还没有考虑过右儿子的祖先节点；栈顶为当前节点
// 指针index指向：当前节点不断往左走达到的最终节点

/*
 思路：
 1. 初始：栈中存放：前序遍历的第一个节点；指针指向：中序遍历的第一个节点
 2. 按顺序扫描前序序列，将对应元素压入栈：
    若指针指向元素的值等于栈顶节点：将指针右移，并弹出栈顶节点，直至：栈顶节点不等于指针指向的元素。此时，将当前指针指向的元素，作为最后弹出节点的右儿子，入栈
 */

// 时间复杂度：O(n)，节点个数
// 空间复杂度：O(n)，除去返回的答案需要的 O(n) 空间之外，我们还需要使用 O(h)（其中 h 是树的高度）的空间存储栈。这里 h<n，所以（在最坏情况下）总空间复杂度为 O(n)

/*
 struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
     if(preorderSize==0) return 0;
     struct TreeNode *root=(struct TreeNode *)malloc(sizeof(struct TreeNode));
     root->val=preorder[0];  //根节点
     root->left=NULL;root->right=NULL;
     
     struct TreeNode **stack=(struct TreeNode **)malloc(sizeof(struct TreeNode *)*3005);
     int top=-1;
     stack[++top]=root;  // 根节点压入栈
     
     int index=0,i;
     for(i=1;i<preorderSize;i++){        // 按顺序扫描前序序列
         struct TreeNode *curNode=stack[top];    // 当前栈顶节点
         if(curNode->val==inorder[index]){
             while(top>=0 && stack[top]->val==inorder[index]){
                 // 将指针右移，并弹出栈顶节点，直至：栈顶节点不等于指针指向的元素
                 curNode=stack[top];     // 被弹出的最新栈节点
                 index++;    // 指针右移
                 top--;  // 从栈顶弹出元素
             }
             struct TreeNode *rightChild=(struct TreeNode *)malloc(sizeof(struct TreeNode));
             rightChild->val=preorder[i];rightChild->left=NULL;rightChild->right=NULL;
             curNode->right=rightChild;
             stack[++top]=rightChild;
         }
         else{   // 当前节点是上一个节点的左儿子
             struct TreeNode *leftChild=(struct TreeNode *)malloc(sizeof(struct TreeNode));
             leftChild->val=preorder[i];leftChild->left=NULL;leftChild->right=NULL;
             curNode->left=leftChild;
             stack[++top]=leftChild;
         }
     }
     return root;
 }
*/

// Leetcode 106. 从中序与后序遍历序列构造二叉树：给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， postorder 是同一棵树的后序遍历，请你构造并返回这颗二叉树
// 中序遍历：左子树-根节点-右子树；后序遍历：左子树-右子树-根节点
/*
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    // postorder最后一个元素对应根节点；inorder指向
    struct TreeNode *root=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    if(postorderSize==0) return 0;
    root->val=postorder[postorderSize-1];  //根节点
    
    int i=0;
    for(;i<inorderSize;i++){
        // 遍历中序数组，直至找到根节点，左侧为左子树，右侧为右子树:
        // 左子树：[0,i-1]；右子树：[i+1,inorderSize-1]
        if(inorder[i]==root->val) break;
    }
    root->right=buildTree(inorder+i+1,inorderSize-i-1,postorder+i,postorderSize-i-1);
    root->left=buildTree(inorder,i,postorder,i);
    return root;
}
*/

// 法二：迭代
// 中序遍历反序：右子树-根节点-左子树
// 后序遍历反序：根节点-右子树-左子树
// 建立一个栈维护：当前节点的所有还没有考虑过左儿子的祖先节点；栈顶为当前节点
// 指针index指向：当前节点不断往右走达到的最终节点

/*
 思路：
 1. 初始：栈中存放：后序遍历的最后一个节点；指针指向：中序遍历的最后一个节点
 2. 按反序扫描后序序列，将对应元素压入栈：
    若指针指向元素的值等于栈顶节点：将指针左移，并弹出栈顶节点，直至：栈顶节点不等于指针指向的元素。此时，将当前指针指向的元素，作为最后弹出节点的左儿子，入栈
 */

// 时间复杂度：O(n)，节点个数
// 空间复杂度：O(n)，除去返回的答案需要的 O(n) 空间之外，我们还需要使用 O(h)（其中 h 是树的高度）的空间存储栈。这里 h<n，所以（在最坏情况下）总空间复杂度为 O(n)

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize){
    if(postorderSize==0) return 0;
    struct TreeNode *root=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val=postorder[postorderSize-1];  //根节点
    root->left=NULL;root->right=NULL;
    
    struct TreeNode **stack=(struct TreeNode **)malloc(sizeof(struct TreeNode *)*3005);
    int top=-1;
    stack[++top]=root;  // 根节点压入栈
    
    int index=postorderSize-1,i;
    for(i=postorderSize-2;i>=0;i--){        // 按反序扫描后序序列
        struct TreeNode *curNode=stack[top];    // 当前栈顶节点
        if(curNode->val==inorder[index]){
            while(top>=0 && stack[top]->val==inorder[index]){
                // 将指针左移，并弹出栈顶节点，直至：栈顶节点不等于指针指向的元素
                curNode=stack[top];     // 被弹出的最新栈节点
                index--;    // 指针左移
                top--;  // 从栈顶弹出元素
            }
            struct TreeNode *leftChild=(struct TreeNode *)malloc(sizeof(struct TreeNode));
            leftChild->val=postorder[i];leftChild->left=NULL;leftChild->right=NULL;
            curNode->left=leftChild;
            stack[++top]=leftChild;
        }
        else{   // 当前节点是栈顶节点的右儿子
            struct TreeNode *rightChild=(struct TreeNode *)malloc(sizeof(struct TreeNode));
            rightChild->val=postorder[i];rightChild->left=NULL;rightChild->right=NULL;
            curNode->right=rightChild;
            stack[++top]=rightChild;
        }
    }
    return root;
}

// Leetcode 117. 填充每个节点的下一个右侧节点指针II:
// 填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。
struct Node{
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

// 法一：基于层次遍历
struct Node* connecting(struct Node* root) {
    if(root==NULL) return NULL;
    struct Node **queue=(struct Node **)malloc(sizeof(struct Node *)*10005);
    int head=0,tail=0;
    
    queue[tail++]=root;
    while(head<tail){
        int cnt=tail-head;  // 当前层次的节点个数
        struct Node *pre=NULL;
        for(int i=0;i<cnt;i++){
            // 当前节点的左右节点加入队列
            struct Node *curNode=queue[head++];   // pre为当前节点curNode的前序节点
            if(curNode->left!=NULL) queue[tail++]=curNode->left;
            if(curNode->right!=NULL) queue[tail++]=curNode->right;
            
            if(i!=0) pre->next=curNode;
            pre=curNode;
        }
    }
    return root;
}

// Leetcode 114. 二叉树展开为链表
/*
 给你二叉树的根结点 root ，请你将它展开为一个单链表：
 1. 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
 2. 展开后的单链表应该与二叉树 先序遍历 顺序相同。
 */

// 1. 递归
/*
void preorderTraversal(struct TreeNode* root, struct TreeNode ***list,int *returnSize){
    if(root==NULL) return;
    (*returnSize)++;
    *list=(struct TreeNode **)realloc(*list,sizeof(struct TreeNode *)*(*returnSize));
    (*list)[*returnSize-1]=root;
    preorderTraversal(root->left, list, returnSize);
    preorderTraversal(root->right, list, returnSize);
}
void flatten(struct TreeNode *root){
    struct TreeNode **list=(struct TreeNode **)malloc(0);
    int resSize=0;
    preorderTraversal(root,&list,&resSize);     // 前序遍历：list中记录前序遍历的序列
    int i=1;
    for(;i<resSize;i++){
        struct TreeNode *prev=list[i-1],*cur=list[i];
        prev->left=NULL;
        prev->right=cur;
    }
    free(list);
}
 */

// 2. 寻找前驱节点: 需要从左子树的最右节点，转到右子树的根节点
// 步骤：前序遍历：根节点-左子树-右子树
// 单链表：将右子树连在左子树中最右节点的右侧；将左子树改至右侧
void flatten(struct TreeNode *root){
    struct TreeNode *cur=root;
    while(cur!=NULL){
        if(cur->left!=NULL){
            struct TreeNode * next=cur->left;
            struct TreeNode * pre=next;
            while(pre->right!=NULL){
                pre=pre->right;
            }
            pre->right=cur->right;  // 前驱节点的右子树为：当前节点的右子树
            cur->left=NULL;
            cur->right=next;
        }
        cur=cur->right;
    }
}

// Leetcode 112. 路径总和:给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。
// 法一：递归
// 时间复杂度：O(n)；空间复杂度：O(height)
bool hasPathSum(struct TreeNode* root, int targetSum) {
    if(root==NULL) return false;
    else if(root->left==NULL && root->right==NULL && targetSum==root->val) return true;
    return hasPathSum(root->left, targetSum-root->val)||hasPathSum(root->right, targetSum-root->val);
}

// Leetcode 129. 求根节点到叶节点数字之和
/*给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
 每条从根节点到叶节点的路径都代表一个数字：

 例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
 计算从根节点到叶节点生成的 所有数字之和 。*/

// 法一：DFS：每个节点的值等于：父节点*10+当前节点
// 自顶向下，每个叶节点的值为：当前路径的值；自底向上：每个中间节点/根节点的值为：左右节点的值相加
int dfs(struct TreeNode *root,int preSum){
    if(root==NULL) return 0;
    int sum=preSum*10+root->val;
    if(root->left==NULL && root->right==NULL){
        return sum;
    }else{
        return dfs(root->left,sum)+dfs(root->right,sum);
    }
}

int sumNumbers(struct TreeNode* root) {
    return dfs(root,0);
}

// 法二：BFS

// Leetcode 124. 二叉树中的最大路径和
/*
 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径至少包含一个节点，且不一定经过根节点。
 路径和 是路径中各节点值的总和；给你一个二叉树的根节点 root ，返回其 最大路径和 。
 */
int mainGain(struct TreeNode * root,int *maxSum){
    // 在以root为根节点的树中，寻找以该节点为起点的路径，使得节点总和最大
    if(root==NULL) return 0;
    int leftGain=fmax(mainGain(root->left,maxSum),0);
    int rightGain=fmax(mainGain(root->right,maxSum),0);
    int priceNewPath=root->val+leftGain+rightGain;
    
    if(priceNewPath>*maxSum) *maxSum=priceNewPath;
    return root->val+fmax(leftGain,rightGain);
}

int maxPathSum(struct TreeNode* root) {
    int maxSum=root->val;
    mainGain(root,&maxSum);
    return maxSum;
}

// Leetcode 173. 二叉搜索树迭代器
/*
 实现一个二叉搜索树迭代器类BSTIterator ，表示一个按中序遍历二叉搜索树（BST）的迭代器：
 BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。BST 的根节点 root 会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST 中的数字，且该数字小于 BST 中的任何元素。
 boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。
 int next()将指针向右移动，然后返回指针处的数字。
 注意，指针初始化为一个不存在于 BST 中的数字，所以对 next() 的首次调用将返回 BST 中的最小元素。

 你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST 的中序遍历中至少存在一个下一个数字。
 */

// 法一：扁平化：获取中序遍历的全部结果并保存在数组中
/*
typedef struct {
    int *res;
    int size;
    int idx;
} BSTIterator;

void inOrder(int *ret,int *retSize,struct TreeNode *root){
    if(root==NULL) return;
    inOrder(ret,retSize,root->left);
    ret[(*retSize)++]=root->val;
    inOrder(ret,retSize,root->right);
}

int getTreeSize(struct TreeNode* root) {    // 获取树的节点个数
    if (root == NULL) return 0;
    return 1 + getTreeSize(root->left) + getTreeSize(root->right);
}

int *inOrderTraversal(struct TreeNode *root,int *retSize){
    *retSize=0;
    int *ret=(int *)malloc(sizeof(int)*getTreeSize(root));
    inOrder(ret,retSize,root);
    return ret;
}

BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
    BSTIterator* ret=(BSTIterator*)malloc(sizeof(BSTIterator));
    ret->res=inOrderTraversal(root,&(ret->size));
    ret->idx=0;
    return ret;
}

int bSTIteratorNext(BSTIterator* obj) {
    return obj->res[(obj->idx)++];
}

bool bSTIteratorHasNext(BSTIterator* obj) {
    return (obj->idx<obj->size);
}

void bSTIteratorFree(BSTIterator* obj) {
    free(obj->res);
    free(obj);
}
*/

// 法二：迭代：利用栈
typedef struct{
    struct TreeNode *cur;
    struct TreeNode *stack[128];
    int stackSize;
}BSTIterator;

BSTIterator *bSTIteratorCreate(struct TreeNode *root){
    BSTIterator *ret=(BSTIterator *)malloc(sizeof(BSTIterator));
    ret->cur=root;
    ret->stackSize=0;
    return ret;
}

// 考虑到 n 次调用 next() 函数总共会遍历全部的 n 个节点，因此总的时间复杂度为 O(n)，因此单次调用平均下来的均摊复杂度为 O(1)。
int bSTIteratorNext(BSTIterator *obj){
    while(obj->cur!=NULL){
        obj->stack[(obj->stackSize)++]=obj->cur;    // 当前节点压入栈
        obj->cur=obj->cur->left;
    }
    // 从栈中弹出元素，遍历其右子树
    obj->cur=obj->stack[--(obj->stackSize)];
    int ret=obj->cur->val;
    obj->cur=obj->cur->right;
    
    return ret;
}

bool bSTIteratorHasNext(BSTIterator *obj){
    return obj->cur!=NULL || obj->stackSize;
}

void bSTIteratorFree(BSTIterator *obj){
    free(obj);
}

// Leetcode 222. 完全二叉树的节点个数
/*完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（从第 0 层开始），则该层包含 1~ 2h 个节点。*/


// 完全二叉树的最左边的节点一定位于最底层,经过的路径长度为：最大层数h
// 最底层包含1个节点：共2^h个；最底层包含2^h个节点：共2^(h+1)-1个.

/*
 时间复杂度：O(log2n)，其中 n 是完全二叉树的节点数。
 首先需要 O(h) 的时间得到完全二叉树的最大层数，其中 h 是完全二叉树的最大层数。
 使用二分查找确定节点个数时，需要查找的次数为 O(log2^h)=O(h)，每次查找需要遍历从根节点开始的一条长度为 h 的路径，需要 O(h) 的时间，因此二分查找的总时间复杂度是 O(h^2)。
 因此总时间复杂度是 O(h^2)。由于完全二叉树满足 2^h≤n<2^(h+1)，因此有 O(h)=O(logn)，O(h^2)=O(log2n)。

 空间复杂度：O(1)。只需要维护有限的额外空间。
 */

bool exists(struct TreeNode *root,int level,int k){
    int bits=1<<(level-1);  // 2^h
    struct TreeNode *curNode=root;
    
    while(curNode!=NULL && bits>0){
        if(!(bits&k)){  // 当前位为0，采用左节点
            curNode=curNode->left;
        }else{
            curNode=curNode->right;
        }
        bits>>=1;
    }
    return curNode!=NULL;
}

int countNodes(struct TreeNode* root) {
    if(root==NULL) return 0;
    int level=0;    // 最大层数
    struct TreeNode *cur=root;
    
    while(root->left!=NULL){
        level++;cur=cur->left;
    }
    
    int low=1<<level,high=(1<<(level+1))-1;
    while(low<high){
        int mid=(high-low+1)/2+low;
        if(exists(root,level,mid)){
            low=mid;
        }
        else{
            high=mid-1;
        }
    }
    return low;
}

// Leetcode 236. 二叉树的最近公共祖先: 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先
// 法一：存储父节点
// 创建哈希表：键为当前节点的值，值为指向父节点的指针
typedef struct{
    int val;
    struct TreeNode *parent;
    UT_hash_handle hh;
}parentHashTable;
parentHashTable *parents=NULL;

typedef struct{
    int val;
    bool visited;
    UT_hash_handle hh;
}visHashTable;
visHashTable *vis=NULL;

void DFS(struct TreeNode *root){
    // DFS:遍历树，将所有节点的值和父节点插入哈希表
    if(root->left!=NULL){
        parentHashTable *tmp=(parentHashTable *)malloc(sizeof(parentHashTable));
        tmp->val=root->left->val;tmp->parent=root;
        HASH_ADD_INT(parents,val,tmp);
        DFS(root->left);
    }
    if(root->right!=NULL){
        parentHashTable *tmp=(parentHashTable *)malloc(sizeof(parentHashTable));
        tmp->val=root->right->val;tmp->parent=root;
        HASH_ADD_INT(parents,val,tmp);
        DFS(root->right);
    }
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    parentHashTable *tmp=(parentHashTable *)malloc(sizeof(parentHashTable));
    tmp->val=root->val;tmp->parent=NULL;
    HASH_ADD_INT(parents,val,tmp);  // 根节点的父节点为空
    
    DFS(root);
    
    while(p!=NULL){
        // 将当前节点标记为已访问
        visHashTable *tmp=(visHashTable *)malloc(sizeof(visHashTable));
        tmp->val=p->val;tmp->visited=true;
        HASH_ADD_INT(vis,val,tmp);
        
        parentHashTable *tmp1=NULL,*el=NULL;
        int cur=0;
        HASH_ITER(hh,parents,el,tmp1)   // el为val匹配的项，即p对应的项
        {
            if(el->val==p->val) p=el->parent;   // 从p不断向祖先移动
        }
    }
    
    while(q!=NULL){
        visHashTable *tmp1=NULL,*el=NULL;
        parentHashTable *tmp2=NULL,*el2=NULL;
        HASH_ITER(hh,vis,el,tmp1)
        {
            if(el->val==q->val) return q;
        }
        HASH_ITER(hh,parents,el2,tmp2)
        {
            if(el2->val==q->val) q=el2->parent;   // 从q不断向祖先移动
        }
    }
    return NULL;
}
