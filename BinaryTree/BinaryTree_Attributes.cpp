//
//  main.cpp
//  BinaryTree_Attributes
//
//  Created by 文柳懿 on 2025/2/24.
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 1. 对称二叉树:给你一个二叉树的根节点 root ， 检查它是否轴对称。
// 法一：递归，采用后序遍历思路：一个子树左右中，一个子树右左中，通过递归函数的返回值，才能判断两个子树的内侧节点、外侧节点是否相等
class Solution_1_1 {
public:
    bool compare(TreeNode *root1,TreeNode *root2){
        if(root1==nullptr && root2==nullptr) return true;
        else if(root1==nullptr || root2==nullptr) return false;
        else if(root1->val!=root2->val) return false;
        return compare(root1->left,root2->right) && compare(root1->right,root2->left);
    }
    bool isSymmetric(TreeNode* root) {
        return compare(root->left,root->right);
    }
};

// 法二：迭代，不是前中后序的迭代写法，不满足二叉树遍历的前中后序的关系。
// 使用队列来比较两个树（根节点的左右子树）是否相互翻转
class Solution_1_2 {
public:
    bool isSymmetric(TreeNode* root) {
        if(root==nullptr) return true;
        queue<TreeNode *>queue;
        queue.push(root->left);queue.push(root->right);
        
        while(!queue.empty()){
            auto leftNode=queue.front();queue.pop();
            auto rightNode=queue.front();queue.pop();
            if(leftNode==nullptr && rightNode==nullptr) continue;
            else if(leftNode==nullptr || rightNode==nullptr || leftNode->val!=rightNode->val) return false;
            
            queue.push(leftNode->left);queue.push(rightNode->right);
            queue.push(leftNode->right);queue.push(rightNode->left);
        }
        return true;
    }
};

// 2. T572.另一棵树的子树：给你两棵二叉树 root 和 subRoot 。检验 root 中是否包含和 subRoot 具有相同结构和节点值的子树。如果存在，返回 true ；否则，返回 false 。
// 法一：递归：采用前序遍历，DFS暴力匹配
// 时间复杂度：最坏情况，对于每一个s上的点，都需要做一次深度优先搜索来和 t 匹配，匹配一次的时间代价是 O(∣t∣)，那么渐进时间代价就是 O(∣s∣×∣t∣).

class Solution_2_1 {
public:
    bool check(TreeNode *root1,TreeNode *root2){
        if(root1==nullptr && root2==nullptr) return true;
        else if(root1==nullptr || root2==nullptr) return false;
        else if(root1->val!=root2->val) return false;
        return check(root1->left,root2->left) && check(root1->right,root2->right);
    }
    
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        stack<TreeNode *>stack;
        stack.push(root);
        
        while(!stack.empty()){
            auto node=stack.top();stack.pop();
            if(node->val==subRoot->val && check(node,subRoot)) return true;
            if(node->right!=nullptr) stack.push(node->right);
            if(node->left!=nullptr) stack.push(node->left);
        }
        return false;
    }
};

// 法二：将s,t转换为前序遍历的序列，运用KMP字符串匹配算法，判断t序列是否是s序列的子串
// 法三：将树转为哈希

// 3. T104.二叉树的最大深度：从根节点到最远叶子节点的最长路径上的节点数
// 法一：最大深度=根节点的高度，采用后序遍历求，自底向上
// 当前节点的高度=左右子树的最大高度+1
// 时间复杂度：O(n)；空间复杂度：取决于栈深度，O(height)
class Solution_3_1{
public:
    int getHeight(TreeNode *root){
        if(root==nullptr) return 0;     // 空节点高度为0，已到底
        return 1+max(getHeight(root->left),getHeight(root->right));
    }
    int maxDepth(TreeNode* root){
        return getHeight(root);
    }
};

// 法二：迭代
class Solution_3_2{
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int depth = 0;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            depth++; // 记录深度
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
        }
        return depth;
    }
};

// 4. T110.平衡二叉树:给定一个二叉树，判断它是否是 平衡二叉树。平衡二叉树 是指该树所有节点的左右子树的高度相差不超过 1。
// 法一：递归
// 判断高度：采用后序遍历，自底向上，求左、右子树的高度；用-1标记不平衡树，直接返回
class Solution_4 {
public:
    int getHeight(TreeNode *root){      // 返回：以root为根节点的二叉树高度，用-1标记
        if(root==nullptr) return 0;
        int leftHeight=getHeight(root->left);
        if(leftHeight==-1) return -1;
        int rightHeight=getHeight(root->right);
        if(rightHeight==-1) return -1;
        
        if(abs(leftHeight-rightHeight)>1) return -1;
        return 1+max(leftHeight,rightHeight);
    }
    bool isBalanced(TreeNode* root) {
        if(root==nullptr) return true;
        return getHeight(root)!=-1;
    }
};

// 5. T257.二叉树的所有路径:按 任意顺序 ，返回所有从根节点到叶子节点的路径。
// 采用前序遍历，方便获得父节点指向子节点的路径
class Solution_5 {
private:
    void traversal(TreeNode *cur,string path,vector<string>& result){
        path+=to_string(cur->val);  // 中(最后一个叶节点需要加入path)
        /* 注：这一步不用回溯，因为：使用的是 string path，没有加上引用& ，即本层递归中，path + 该节点数值，但该层递归结束，上一层path的数值并不会受到任何影响。
         不带引用，不做地址拷贝，只做内容拷贝的效果。
         */
        if(cur->left==nullptr && cur->right==nullptr){
            // 终止处理逻辑：遇到叶子节点
            result.push_back(path);
            return;
        }
        if(cur->left){
            path+="->";
            traversal(cur->left, path, result);
            // 回溯和递归是一一对应的
            path.pop_back();    // 回溯'>'
            path.pop_back();    // 回溯'-'
        }
        if(cur->right){
            path+="->";
            traversal(cur->right, path, result);
            path.pop_back();    // 回溯'>'
            path.pop_back();    // 回溯'-'
        }
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string>result;
        string path;
        if(root==nullptr) return result;
        traversal(root,path,result);
        return result;
    }
};

// 6. T404.左叶子之和:给定二叉树的根节点 root ，返回所有左叶子之和。
// 注：判断左叶子：通过节点的父节点判断本节点的属性
// 法一：递归，后序遍历（左-右-中），通过递归函数的返回值，累加求取左叶子的数值之和
class Solution_6_1 {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(root==nullptr) return 0;
        if(root->left==nullptr && root->right==nullptr) return 0;   // 当前遍历到父节点，判断其左孩子是否为叶节点
        
        int leftValue=0;
        if(root->left!=nullptr && root->left->left==nullptr && root->left->right==nullptr){
            leftValue=root->left->val;
        }else{
            leftValue=sumOfLeftLeaves(root->left);  // 左
        }
        int rightValue=sumOfLeftLeaves(root->right);    // 右
        return leftValue+rightValue;    // 中
    }
};

// 法二：迭代:
class Solution_6_2 {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(root==nullptr) return 0;
        stack<TreeNode *>stack;
        stack.push(root);
        int sum=0;
        
        while(!stack.empty()){
            auto node=stack.top();stack.pop();  // 中
            if(node->left!=nullptr && node->left->left==nullptr && node->left->right==nullptr){
                sum+=node->left->val;
            }
            if(node->right) stack.push(node->right);    // 右
            if(node->left) stack.push(node->left);      // 左
        }
        return sum;
    }
};

// 7. T513.找树左下角的值：给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值
// 法一：迭代，层序遍历，记录最后一层的第一个元素
class Solution_7_1{
public:
    int findBottomLeftValue(TreeNode* root) {
        int ret=0;
        if(root==nullptr) return ret;
        queue<TreeNode *>queue;
        queue.push(root);
        
        while(!queue.empty()){
            int size=queue.size();
            for(int i=0;i<size;i++){
                auto node=queue.front();queue.pop();
                if(i==0) ret=node->val;
                if(node->left) queue.push(node->left);
                if(node->right) queue.push(node->right);
            }
        }
        return ret;
    }
};

// 法二：递归
// 1. 最底层：找深度最大的叶子节点；
// 2. 最左：前序遍历，左优先搜索
// 全局变量：maxDepth记录最大深度；result记录最大深度左节点的数值
class Solution_7_2{
public:
    int maxDepth=INT_MIN;
    int res=0;
    
    void traversal(TreeNode *root,int depth){
        // 中
        if(root->left==nullptr && root->right==nullptr){    // 叶子节点
            if(depth>maxDepth){
                maxDepth=depth;
                res=root->val;
            }
            return;
        }
        if(root->left){     // 左
            depth++;
            traversal(root->left, depth);
            depth--;
        }
        if(root->right){    // 右
            depth++;
            traversal(root->right, depth);
        }
        return;
    }
    
    int findBottomLeftValue(TreeNode* root) {
        traversal(root, 0);
        return res;
    }
};

// 8. T112.路径总和:
/*给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。
 */
// 法一：递归：需要找一条符合的路径
// 终止条件：遇到叶子节点：count==0，找到；count!=0，没找到
// 单层逻辑：判断叶子节点（空节点不进入递归）；回溯，后撤找另一条路径
class Solution_8_1 {
public:
    bool traversal(TreeNode *root,int count){   // count为减去已有路径中节点后，剩余的值
        if(root->left==nullptr && root->right==nullptr){    // 叶子节点
            if(count==root->val) return true;
            else return false;
        }
        // 单层逻辑
        if(root->left){
            count-=root->val;
            bool res=traversal(root->left,count);
            if(res) return true;
            count+=root->val;
        }
        if(root->right){
            count-=root->val;
            bool res=traversal(root->right,count);
            if(res) return true;
            count+=root->val;
        }
        return false;
    }
    
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==nullptr) return false;
        return traversal(root,targetSum);
    }
};

// 法二：迭代：用栈模拟遍历，做回溯时：设置一个数组，记录根节点到当前节点的路径之和
class Solution_8_2 {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==nullptr) return false;
        stack<pair<TreeNode *,int>>stack;   //<节点，路径数值>
        stack.push(pair<TreeNode *,int>(root,root->val));
        
        while(!stack.empty()){
            pair<TreeNode *,int>node_pair=stack.top();
            stack.pop();
            
            if(node_pair.first->left==nullptr && node_pair.first->right==nullptr && node_pair.second==targetSum){  // 叶子节点
                return true;
            }
            if(node_pair.first->right){    // 右节点，压入时添加该节点数值
                stack.push(pair<TreeNode *,int>(node_pair.first->right,node_pair.second+node_pair.first->right->val));
            }
            if(node_pair.first->left){    // 左节点，压入时添加该节点数值
                stack.push(pair<TreeNode *,int>(node_pair.first->left,node_pair.second+node_pair.first->left->val));
            }
        }
        return false;
    }
};

// 9. T113.路径总和II:给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。
// 需要遍历整个树，找到所有路径，找到单条路径并不能直接返回，因此递归函数无需返回值
class Solution_9 {
private:
    vector<vector<int>> res;
    vector<int>path;
    
    void traversal(TreeNode *root,int count){
        if(root->left==nullptr && root->right==nullptr){    // 叶子节点:返回
            if(count==0) res.push_back(path);
            return;
        }
        if(root->left){
            path.push_back(root->left->val);
            count-=root->left->val;
            traversal(root->left,count);
            count+=root->left->val;
            path.pop_back();
        }
        if(root->right){
            path.push_back(root->right->val);
            count-=root->right->val;
            traversal(root->right,count);
            count+=root->right->val;
            path.pop_back();
        }
        return;
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        res.clear();path.clear();
        if(root==nullptr) return res;
        path.push_back(root->val);
        traversal(root,targetSum-root->val);
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
