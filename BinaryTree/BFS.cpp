//
//  main.cpp
//  BinaryTree_BFS
//
//  Created by 文柳懿 on 2025/2/21.
//

#include <iostream>
#include<vector>
#include<queue>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *left,*right;
    TreeNode(): val(0),left(nullptr),right(nullptr){}
    TreeNode(int x): val(x),left(nullptr),right(nullptr){}
    TreeNode(int x,TreeNode *left,TreeNode *right): val(x),left(left),right(right){}
};

// 1. T102. 二叉树的层序遍历（BFS）:逐层将左右子树加入队列，FIFO
// 时间复杂度：O(n)，每个节点进出队列各一次；空间复杂度：O(n)，队列中元素不超过n个
class Solution_1{
public:
    vector<vector<int>> levelOrder(TreeNode *root){
        vector<vector<int>> ret;
        if(!root) return ret;
        
        queue<TreeNode *> q;
        q.push(root);
        
        while(!q.empty()){
            int size=q.size();  // 当前队列中元素个数=当前层的节点个数
            ret.push_back(vector<int>());     // ret中每个子树组，存储当前层的所有节点
            for(int i=0;i<size;i++){
                auto node=q.front();q.pop();    // 1. 取出队列首个元素
                ret.back().push_back(node->val);    // 2. ret中最后一个数组，加入当前节点的值
                // 3. 将当前元素的左右节点，加入队尾
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return ret;
    }
};

// 2. T107.二叉树的层序遍历II：给你二叉树的根节点 root ，返回其节点值 自底向上的层序遍历 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）
// 翻转数组
// 时间复杂度：O)n)；空间复杂度：O(n)
class Solution_2{
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ret;
        if(!root) return ret;
        
        queue<TreeNode *>q;
        q.push(root);
        
        while(!q.empty()){
            int size=q.size();
            vector<int> level;
            for(int i=0;i<size;i++){
                auto node=q.front();q.pop();
                level.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            ret.push_back(level);
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }
};

// 3. T199.二叉树的右视图：给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
// 题意为：取每一层的最右节点，即在每次遍历开始前，取当前数组中的最后一个节点，即为该层的最右节点
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_3 {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        
        queue<TreeNode *>q;
        q.push(root);
        
        while(!q.empty()){
            ret.push_back(q.back()->val);    // 加入当前层的最右节点
            int size=q.size();
            for(int i=0;i<size;i++){
                auto node=q.front();q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return ret;
    }
};

// 4. T637.二叉树的层平均值：给定一个非空二叉树的根节点 root , 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。
// 时间复杂度：O(n)；空间复杂度：O(n).
class Solution_4 {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double>ret;
        if(!root) return ret;
        
        queue<TreeNode *> q;
        q.push(root);
        
        while(!q.empty()){
            int size=q.size();
            double sum=0;
            for(int i=0;i<size;i++){
                auto node=q.front();q.pop();
                sum+=node->val;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            ret.push_back(sum/size);
        }
        return ret;
    }
};

// 5. T429.N叉树的层序遍历:给定一个 N 叉树，返回其节点值的层序遍历。（即从左到右，逐层遍历）
/*
class Node{
public:
    int val;
    vector<Node *>children;
    Node(){}
    Node(int _val){
        val=_val;
    }
    Node(int _val,vector<Node *>_children){
        val=_val;
        children=_children;
    }
};
class Solution_5{
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> ret;
        if(!root) return ret;
        
        queue<Node *>q;
        q.push(root);
        
        while(!q.empty()){
            int size=q.size();
            ret.push_back(vector<int>());
            for(int i=0;i<size;i++){
                auto node=q.front();q.pop();
                ret.back().push_back(node->val);
                
                // 将当前节点node的所有子节点加入队列
                for(Node *child:node->children){
                    q.push(child);
                }
            }
        }
        return ret;
    }
};
 */

// 6. T515.在每个树行中找最大值
class Solution_6{
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        
        queue<TreeNode *>q;
        q.push(root);
        
        while(!q.empty()){
            int size=q.size();
            int max=INT_MIN;
            for(int i=0;i<size;i++){
                auto node=q.front();q.pop();
                if(node->val>max) max=node->val;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            ret.push_back(max);
        }
        return ret;
    }
};

// 7. T116.填充每个节点的下一个右侧节点指针:给定一个完美二叉树，其所有叶子节点都在同一层
// 填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
struct Node{
    int val;
    Node *left;
    Node *right;
    Node *next;
};

// 法一：层次遍历
// 时间复杂度：O(n)；空间复杂度：O(n)，队列最长有n/2个节点
class Solution_7_1{
public:
    Node* connect(Node* root) {
        if(!root) return root;
        queue<Node *>q;
        q.push(root);
        
        while(!q.empty()){
            int size=q.size();
            for(int i=0;i<size;i++){    // 遍历当前层的所有节点
                auto node=q.front();q.pop();
                if(i<size-1) node->next=q.front();
                if(node->left!=nullptr) q.push(node->left);
                if(node->right!=nullptr) q.push(node->right);
            }
        }
        return root;
    }
};

// 法二：空间复杂度优化：只使用常量级的额外空间
// 使用已经建立的next指针：使用第N层的next指针，为第N+1层建立next指针
// 有两种类型的next指针：
// 1. 两个子节点，属于同一个父节点，直接通过父节点建立：子节点指向右节点的next指针
// 2. 连接第一个父节点的右孩子，和第二个父节点的左孩子，此时：两个父节点之间已经建立next指针

//
class Solution_7_2{
public:
    Node* connect(Node* root) {
        if(!root) return root;
        Node *leftmost=root;    // 当前层的最左节点
        
        while(leftmost->left!=nullptr){
            // 从左到右，通过next指针的连接，遍历当前层的所有节点，为下一层建立连接；head为当前遍历到的节点
            Node *head=leftmost;
            while(head!=nullptr){
                head->left->next=head->right;
                if(head->next!=nullptr){
                    head->right->next=head->next->left;
                }
                head=head->next;
            }
            leftmost=leftmost->left;    // 去下一层的最左节点
        }
        return root;
    }
};

// 8. T117.填充每个节点的下一个右侧节点指针:不一定是完美二叉树
// 采用方法二：时间复杂度：O(n)；空间复杂度：O(1)
class Solution_8{
public:
    Node* connect(Node *root){
        if(!root) return root;
        
        Node *start=root;
        while(start){
            Node *pre=nullptr,*nextStart=nullptr;   // pre为下一层建立next连接时，前一个节点；mextStart为下一层的最左节点
            for(Node *p=start;p!=nullptr;p=p->next){
                // 遍历当前层
                if(p->left!=nullptr){
                    if(pre!=nullptr) pre->next=p->left;
                    if(nextStart==nullptr) nextStart=p->left;
                    pre=p->left;    // 更新前驱节点
                }
                if(p->right!=nullptr){
                    if(pre!=nullptr) pre->next=p->right;
                    if(nextStart==nullptr) nextStart=p->right;
                    pre=p->right;
                }
            }
            start=nextStart;    // start为当前层的最左节点，此时更新为nextStart
        }
        return root;
    }
};

// 9. T114. 二叉树的最大深度
// 法一：深度优先搜索：递归求出左、右子树的最大深度
// 时间复杂度：O(n)；空间复杂度：O(height)
class Solution_9_1{
public:
    int maxDepth(TreeNode* root){
        if(root==nullptr) return 0;
        return max(maxDepth(root->left),maxDepth(root->right))+1;
    }
};

// 法二：广度优先搜索
// 时间复杂度：O(n)；空间复杂度：取决于队列存储的元素数量，最坏情况O(n)
class Solution_9_2{
public:
    int maxDepth(TreeNode* root){
        if(root==nullptr) return 0;
        queue<TreeNode*>q;
        q.push(root);
        
        int depth=0;
        while(!q.empty()){
            int size=q.size();
            for(int i=0;i<size;i++){
                auto node=q.front();q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            depth++;
        }
        return depth;
    }
};

// 10. T111.二叉树的最小深度
// 注意：一定要遍历到叶子节点，才能形成路径

// 法一：DFS，递归
// 时间复杂度：O(n)；空间复杂度：O(height)，平均情况下为O(log N).
class Solution_10_1 {
public:
    int minDepth(TreeNode* root) {
        if(root==nullptr) return 0;
        if(root->left==nullptr && root->right==nullptr) return 1;   // 叶子节点
        int depth=INT_MAX;
        if(root->left!=nullptr){
            depth=min(depth,minDepth(root->left));
        }
        if(root->right!=nullptr){
            depth=min(depth,minDepth(root->right));
        }
        return depth+1;
    }
};

// 法二：BFS：找到一个叶子节点时，直接返回
class Solution_10_2 {
public:
    int minDepth(TreeNode* root) {
        if(root==nullptr) return 0;
        queue<pair<TreeNode *,int>>q;
        q.emplace(root,1);
        
        while(!q.empty()){
            auto node=q.front().first;
            int depth=q.front().second;
            q.pop();
            
            if(node->left==nullptr && node->right==nullptr) return depth;   // 找到叶子节点
            if(node->left!=nullptr) q.emplace(node->left,depth+1);
            if(node->right!=nullptr) q.emplace(node->right,depth+1);
        }
        return 0;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
