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

// 递归：
class Solution_1 {
private:
    TreeNode *traversal(vector<int>& inorder,int inorderBegin,int inorderEnd, vector<int>& postorder,int postorderBegin,int postorderEnd){
        // 返回值：当前序列还原出的树；参数：中序区间：[inorderBegin, inorderEnd)，后序区间[postorderBegin, postorderEnd)
        if(postorderBegin==postorderEnd) return nullptr;    // 当前为空节点
        
        int rootValue=postorder[postorderEnd-1];
        TreeNode *root=new TreeNode(rootValue);   // 1. 后序数组的最后一个元素，为根节点
        
        if(postorderEnd-postorderBegin==1) return root; // 叶子节点
        
        // 2. 在中序遍历序列中，查找根节点位置
        int delimiter;
        for(delimiter=inorderBegin;delimiter<inorderEnd;delimiter++){
            if(inorder[delimiter]==rootValue) break;
        }
        
        // 3. 切割中序数组
        int leftInorderBegin=inorderBegin;
        int leftInorderEnd=delimiter;
        int rightInorderBegin=delimiter+1;
        int rightInorderEnd=inorderEnd;
        
        // 4. 切割后序数组
        int leftPostorderBegin=postorderBegin;
        int leftPostorderEnd=postorderBegin+delimiter-inorderBegin;
        int rightPostorderBegin=leftPostorderEnd;
        int rightPostorderEnd=postorderEnd-1;   // 排除最后一个节点（根节点）
        
        root->left=traversal(inorder,leftInorderBegin,leftInorderEnd,postorder,leftPostorderBegin,leftPostorderEnd);
        root->right=traversal(inorder,rightInorderBegin,rightInorderEnd,postorder,rightPostorderBegin,rightPostorderEnd);
        
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size()==0 || postorder.size()==0) return nullptr;
        return traversal(inorder, 0, inorder.size(), postorder, 0, postorder.size());   // 左闭右开
    }
};

// 2. T654.最大二叉树
/*
 给定一个不重复的整数数组 nums 。 最大二叉树 可以用下面的算法从 nums 递归地构建:
 1. 创建一个根节点，其值为 nums 中的最大值。
 2. 递归地在最大值 左边 的 子数组前缀上 构建左子树。
 3. 递归地在最大值 右边 的 子数组后缀上 构建右子树。
 返回 nums 构建的 最大二叉树 。
 */

class Solution_2 {
private:
    TreeNode *traversal(vector<int>&nums, int left, int right){
        if(left>=right) return nullptr;
        
        // 返回值：构造后二叉树的根节点；参数：左闭右开区间[left,right)
        int maxIndex=left,maxNum=INT_MIN;
        // 1. 找到值最大的点
        for(int i=left;i<right;i++){
            if(nums[i]>maxNum){
                maxIndex=i;maxNum=nums[i];
            }
        }
        TreeNode *root=new TreeNode(maxNum);
        
        // 2. 左子树
        root->left=traversal(nums,left,maxIndex);
        // 3. 右子树
        root->right=traversal(nums, maxIndex+1, right);
        
        return root;
    }
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return traversal(nums, 0, nums.size());
    }
};

// 3. T617.合并二叉树
/*给你两棵二叉树： root1 和 root2 。
 想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，不为 null 的节点将直接作为新二叉树的节点。
 返回合并后的二叉树。
 注意: 合并过程必须从两个树的根节点开始。
 */
// 法一：递归
class Solution_3_1 {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(root1==nullptr && root2==nullptr) return nullptr;
        else if(root1!=nullptr && root2==nullptr) return root1;
        else if(root1==nullptr && root2!=nullptr) return root2;
        
        TreeNode *root=new TreeNode(root1->val+root2->val);
        root->left=mergeTrees(root1->left,root2->left);
        root->right=mergeTrees(root1->right,root2->right);
        
        return root;
    }
};
// 法二：也是递归，但可以不创建新的树，而是修改root1的树的结构
// 法三：迭代，层序遍历
class Solution_3_2 {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == NULL) return t2;
        if (t2 == NULL) return t1;
        queue<TreeNode*> que;
        que.push(t1);
        que.push(t2);
        while(!que.empty()) {
            TreeNode* node1 = que.front(); que.pop();
            TreeNode* node2 = que.front(); que.pop();
            // 此时两个节点一定不为空，val相加
            node1->val += node2->val;

            // 如果两棵树左节点都不为空，加入队列
            if (node1->left != NULL && node2->left != NULL) {
                que.push(node1->left);
                que.push(node2->left);
            }
            // 如果两棵树右节点都不为空，加入队列
            if (node1->right != NULL && node2->right != NULL) {
                que.push(node1->right);
                que.push(node2->right);
            }

            // 当t1的左节点 为空 t2左节点不为空，就赋值过去
            if (node1->left == NULL && node2->left != NULL) {
                node1->left = node2->left;
            }
            // 当t1的右节点 为空 t2右节点不为空，就赋值过去
            if (node1->right == NULL && node2->right != NULL) {
                node1->right = node2->right;
            }
        }
        return t1;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
