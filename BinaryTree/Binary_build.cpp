//
//  main.cpp
//  BinaryTree_Build
//
//  Created by 文柳懿 on 2025/2/26.
//

#include <iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 1. T106.从中序、后序遍历序列构造二叉树（没有重复元素）
// (1) 以后序遍历最后一个节点作为元素，找到其在中序遍历序列中的位置，作为切割点
// (2) 切割中序数组；
// (3) 切割后序数组(利用中序左数组大小，等于后序左数组大小)
class Solution_1 {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
