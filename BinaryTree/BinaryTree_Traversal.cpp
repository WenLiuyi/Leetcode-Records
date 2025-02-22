//
//  main.cpp
//  BinaryTree_Traversal
//
//  Created by 文柳懿 on 2025/2/22.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
    TreeNode(int x,TreeNode *left,TreeNode *right):val(0),left(left),right(right){}
};

// 1. T144.二叉树的前序遍历
// 法一：递归
// 时间复杂度：O(n)；空间复杂度：O(n)，递归过程栈的开销，平均为O(logn），最坏情况为O(n)
class Solution1_1 {
public:
    void preOrder(TreeNode *cur,vector<int> &res){
        if(cur==NULL) return;
        res.push_back(cur->val);    // 中
        preOrder(cur->left,res);   // 左
        preOrder(cur->right,res);  // 右
    }
    
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        preOrder(root,ret);
        return ret;
    }
};

// 2. T145. 二叉树的后序遍历
// 法一：递归
class Solution2_1 {
public:
    void postOrder(TreeNode *cur,vector<int> &res){
        if(cur==NULL) return;
        postOrder(cur->left, res);
        postOrder(cur->right, res);
        res.push_back(cur->val);
    }
    
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        postOrder(root,ret);
        return ret;
    }
};

// 3. T94. 二叉树的中序遍历
// 法一：递归
class Solution3_1 {
public:
    void inOrder(TreeNode *cur,vector<int> &res){
        if(cur==NULL) return;
        inOrder(cur->left, res);
        res.push_back(cur->val);
        inOrder(cur->right, res);
    }
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        inOrder(root,ret);
        return ret;
    }
};



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
