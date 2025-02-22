//
//  main.cpp
//  BinarySearchTree
//
//  Created by 文柳懿 on 2025/2/22.
//

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
    TreeNode(int x,TreeNode *left,TreeNode *right):val(0),left(left),right(right){}
};

// 1. T530.二叉搜索树的最小绝对差：给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。
// 法一：中序遍历，转为升序数组，求相邻两个节点的数值之差
class Solution_1 {
public:
    int getMinimumDifference(TreeNode* root) {
        stack <TreeNode *>stack;
        int differ=INT_MAX,pre=-1;
        
        while(!stack.empty() || root!=nullptr){
            while(root!=nullptr){   // 左
                stack.push(root);
                root=root->left;
            }
            root=stack.top();stack.pop();   // 中
            if(pre>=0 && root->val-pre<differ) differ=root->val-pre;
            pre=root->val;
            // 右
            root=root->right;
        }
        return differ;
    }
};

// 2. T98.验证二叉搜索树：给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
/*有效 二叉搜索树定义如下：
 节点的左子树只包含 小于 当前节点的数。
 节点的右子树只包含 大于 当前节点的数。
 所有左子树和右子树自身必须也是二叉搜索树。
 */
// 法一：递归函数：设置一个区间
// 时间复杂度：O(n)；空间复杂度：取决于递归深度，最坏情况下为O(n)
class Solution_2_1 {
public:
    bool checkValid(TreeNode *root,long long lower,long long upper){
        if(root==nullptr) return true;
        if(root->val<=lower || root->val>=upper) return false;  // root->val超出(lower,upper)区间
        return checkValid(root->left,lower,root->val) && checkValid(root->right,root->val,upper);
    }
    
    bool isValidBST(TreeNode* root) {
        return checkValid(root,LONG_MIN,LONG_MAX);
    }
};

// 法二：迭代：二叉树中序遍历得到升序序列，使用栈模拟实现
// 时间复杂度：O(n)；空间复杂度：O(n)，栈空间
class Solution_2_2 {
public:
    bool isValidBST(TreeNode* root) {
        stack <TreeNode *>stack;
        long long inOrder=(long long)INT_MIN-1;    // inOrder记录前一个节点的值
        
        while(!stack.empty() || root!=nullptr){
            // 1. 左
            while(root!=nullptr){   // 不断将左节点压入栈
                stack.push(root);
                root=root->left;
            }
            // 2. 中
            root=stack.top();stack.pop();   // 从栈顶弹出
            if(root->val<=inOrder) return false;    // 当前节点的值，小于前一个节点的值
            inOrder=root->val;
            // 3. 右
            root=root->right;
        }
        return true;
    }
};

// 3. 二叉搜索树中第k小的元素:给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（从 1 开始计数）。
// 法一：中序遍历，迭代实现
// 时间复杂度：O(H+k)，H为树的高度，开始遍历前，需要O(H)到达叶节点；树是平衡树时，取得最小值O(logN)；树是线性树时，时间复杂度取O(N+k)；
// 空间复杂度：O(H)，取决于栈空间
class Solution_3_1 {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode *>stack;
        while(!stack.empty() || root!=nullptr){
            while(root!=nullptr){
                stack.push(root);
                root=root->left;
            }
            root=stack.top();stack.pop();
            k--;
            if(k==0) break;     // 找到第k小的元素
            root=root->right;
        }
        return root->val;
    }
};

// 法二：需要频繁查找第k小的值，进行优化：记录下以每个结点为根结点的子树的结点数，辅助查找
class MyBst{
public:
    MyBst(TreeNode *root){
        this->root=root;
        countNodeNum(root);
    }
    int kthSmallest(int k){
        TreeNode *node=root;
        while(node!=nullptr){
            int left=getNodeNum(node->left);
            if(left<k-1){
                // 1. 在node的右子树中
                node=node->right;
                k-=left+1;
            }else if(left==k-1) break;  // 2. node
            else{
                node=node->left;    // 3. 在node的左子树中
            }
        }
        return node->val;
    }
    
private:
    TreeNode *root;
    unordered_map<TreeNode *, int>nodeNum;  // 节点-节点对应子树的节点数

    int countNodeNum(TreeNode *root){
        // 统计以root为根节点的子树节点数
        if(root==nullptr) return 0;
        nodeNum[root]=1+countNodeNum(root->left)+countNodeNum(root->right);
        return nodeNum[root];
    }
    int getNodeNum(TreeNode *node){
        // 获取以node为根节点的子树节点数
        if(node!=nullptr && nodeNum.count(node)) return nodeNum[node];
        else return 0;
    }
};
class Solution_3_2 {
public:
    int kthSmallest(TreeNode* root, int k) {
        MyBst mybst(root);
        return mybst.kthSmallest(k);
    }
};


// 4. T671.二叉树中第二小的节点
/*给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 2 或 0。如果一个节点有两个子节点的话，那么该节点的值等于两个子节点中较小的一个。
 更正式地说，即 root.val = min(root.left.val, root.right.val) 总成立。
 给出这样的一个二叉树，你需要输出所有节点中的 第二小的值 ；如果第二小的值不存在的话，输出 -1 。
 */
// 注：每个节点的值，为以该节点为根节点的子树中的最小值；根节点为所有节点中的最小值；
// 时间复杂度：O(n)；空间复杂度：O(n)，递归，栈空间
class Solution_4 {
public:
    void dfs(TreeNode *root,int rootValue,int *ans){
        if(root==nullptr) return;
        if(*ans!=-1 && root->val>=*ans) return;  // 以当前节点root为根节点的子树，所有节点一定大于等于ans
        if(root->val>rootValue) *ans=root->val;  // ans更新为当前节点的值
        dfs(root->left,rootValue,ans);
        dfs(root->right,rootValue,ans);
    }
    
    int findSecondMinimumValue(TreeNode* root) {
        int ans=-1,rootValue=root->val;
        dfs(root,rootValue,&ans);
        return ans;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
