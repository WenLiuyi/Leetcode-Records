//
//  main.cpp
//  BinaryTree_Attributes
//
//  Created by 文柳懿 on 2025/2/24.
//

#include <iostream>

// 1. T110.平衡二叉树:给定一个二叉树，判断它是否是 平衡二叉树 ，指该树所有节点的左右子树的高度相差不超过 1。
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode():val(0),left(nullptr),right(nullptr) {}
    TreeNode(int x):val(x),left(nullptr),right(nullptr) {}
    TreeNode(int x,TreeNode *left,TreeNode *right):val(x),left(left),right(right){}
};

class Solution_1 {
public:
    bool isBalanced(TreeNode* root) {
        if(root==nullptr) return true;
        
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
