//
//  main.cpp
//  BinaryTree_Traversal
//
//  Created by 文柳懿 on 2025/2/22.
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
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

// 法二：迭代
// 前序遍历：中，左，右；节点放入栈的顺序：根节点，右孩子，左孩子
// 时间复杂度：O(n)；空间复杂度：O(n)，取决于栈空间
class Solution1_2 {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode *>stack;
        vector<int> ret;
        
        if(root==nullptr) return ret;
        stack.push(root);
        
        while(!stack.empty()){
            auto node=stack.top();
            stack.pop();    // 弹出栈顶节点
            ret.push_back(node->val);
            if(node->right) stack.push(node->right);
            if(node->left) stack.push(node->left);
        }
        return ret;
    }
};

// 法三：统一迭代
// 加入栈的顺序：右-左-中
class Solution1_3{
public:
    vector<int> preorderTraversal(TreeNode *root){
        vector<int>ret;
        if(root==nullptr) return ret;
        
        stack<TreeNode *>stack;
        stack.push(root);
        
        while(!stack.empty()){
            TreeNode *node=stack.top();
            if(node!=NULL){
                stack.pop();
                if(node->right) stack.push(node->right);    // 右
                if(node->left) stack.push(node->left);      // 左
                stack.push(node);stack.push(nullptr);       // 中
            }else{
                stack.pop();
                node=stack.top();stack.pop();
                ret.push_back(node->val);
            }
        }
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

// 法二：迭代
// 前序遍历（中-左-右），调整代码顺序，中-右-左（节点加入栈的顺序：根节点，左孩子，右孩子）；翻转数组，左-右-中
class Solution2_2 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int>ret;
        if(root==nullptr) return ret;
        
        stack<TreeNode *>stack;
        stack.push(root);
        while(!stack.empty()){
            auto node=stack.top();
            stack.pop();
            ret.push_back(node->val);
            if(node->left) stack.push(node->left);
            if(node->right) stack.push(node->right);
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }
};

// 法三：统一迭代
// 加入栈的顺序：中-右-左
class Solution2_3{
public:
    vector<int> postorderTraversal(TreeNode *root){
        vector<int>ret;
        if(root==nullptr) return ret;
        
        stack<TreeNode *>stack;
        stack.push(root);
        
        while(!stack.empty()){
            TreeNode *node=stack.top();
            if(node!=NULL){
                stack.pop();
                stack.push(node);stack.push(nullptr);       // 中
                if(node->right) stack.push(node->right);    // 右
                if(node->left) stack.push(node->left);      // 左
            }else{
                stack.pop();
                node=stack.top();stack.pop();
                ret.push_back(node->val);
            }
        }
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

// 法二：迭代
class Solution3_2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ret;
        if(root==nullptr) return ret;
        
        stack<TreeNode *>stack;
        while(!stack.empty() || root!=nullptr){
            while(root!=nullptr){
                stack.push(root);
                root=root->left;    // 到达左子树最底部
            }
            root=stack.top();
            stack.pop();
            ret.push_back(root->val);   // 处理当前节点时，其左子树已处理完毕
            root=root->right;
        }
        return ret;
    }
};

// 法三：统一迭代法：解决访问节点（遍历节点）和处理节点（将元素放进结果集）不一致的情况：就将访问的节点放入栈中，把要处理的节点也放入栈中但是要做标记。
// 3.1 空指针标记法：将要处理的节点放入栈后，紧接着放一个空指针标记
// 加入栈的顺序：右-中-左
class Solution3_3{
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ret;
        if(root==nullptr) return ret;
        
        stack<TreeNode *>stack;
        stack.push(root);
        
        while(!stack.empty()){
            TreeNode *node=stack.top();
            if(node!=nullptr){
                stack.pop();    // 栈非空，弹出栈顶节点
                
                if(node->right) stack.push(node->right);    // 添加右节点（空节点不入栈）
                stack.push(node);stack.push(nullptr);   // 添加中节点和空节点（中节点访问过，但尚未处理，加入空节点标记）
                if(node->left) stack.push(node->left);  // 添加左节点（空节点不入栈）
            }else{
                // 只有遇到空节点的时候，才将下一个节点放进结果集
                stack.pop();    // 将空节点弹出
                node=stack.top();stack.pop();   // 重新取出中节点
                ret.push_back(node->val);   // (只有空节点弹出时）节点加入到结果集
            }
        }
        return ret;
    }
};

// 4. T226.翻转二叉树
// 法一：递归：采用前序遍历，先交换左右孩子节点，再翻转左子树、右子树
class Solution4_1 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root==nullptr) return root;
        swap(root->left,root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

// 法二：迭代：模仿前序遍历：中-左-右
// 节点加入栈的顺序：右-左
class Solution4_2{
public:
    TreeNode* invertTree(TreeNode* root){
        if(root==nullptr) return root;
        stack<TreeNode *>stack;
        stack.push(root);
        
        while(!stack.empty()){
            TreeNode *node=stack.top();
            stack.pop();
            swap(node->left,node->right);   // 交换左右孩子节点
            if(node->right) stack.push(node->right);    // 右
            if(node->left) stack.push(node->left);      // 左
        }
        return root;
    }
};

// 法三：统一迭代写法，模仿前序遍历：中-左-右；节点加入栈的顺序：右-左-中
class Solution4_3{
public:
    TreeNode* invertTree(TreeNode* root){
        if(root==nullptr) return root;
        stack<TreeNode *>stack;
        stack.push(root);
        
        while(!stack.empty()){
            TreeNode *node=stack.top();
            if(node!=nullptr){
                stack.pop();
                if(node->right) stack.push(node->right);
                if(node->left) stack.push(node->left);
                stack.push(node);stack.push(nullptr);
            }
            else{
                stack.pop();
                node=stack.top();stack.pop();
                swap(node->left,node->right);
            }
        }
        return root;
    }
};

// 5. T2415.反转二叉树的奇数层:给你一棵 完美 二叉树的根节点 root ，请你反转这棵树中每个 奇数 层的节点值。
// 注：节点的 层数 等于该节点到根节点之间的边数。

// 法一：DFS
// 时间复杂度：O(n)；空间复杂度：取决于递归深度，O(logn)
class Solution_5_1 {
public:
    void dfs(TreeNode *root1,TreeNode *root2,bool isOdd){   // root1, root2轴对称
        if(root1==nullptr) return;
        if(isOdd) swap(root1->val,root2->val);  // 奇数层：交换root1,root2的值
        dfs(root1->left,root2->right,!isOdd);
        dfs(root1->right,root2->left,!isOdd);
    }
    
    TreeNode* reverseOddLevels(TreeNode* root) {
        if(root==nullptr) return root;
        dfs(root->left,root->right,true);
        return root;
    }
};

// 法二：BFS（层序遍历，反转每个奇数层）
// 时间复杂度：O(n)；空间复杂度：O(n)，队列中最多存在ceil(n/2)个节点
class Solution_5_2 {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        if(root==nullptr) return root;
        queue<TreeNode *>queue;
        queue.emplace(root);
        bool isOdd=false;
        
        while(!queue.empty()){
            int size=queue.size();  // 当前层的节点个数
            vector<TreeNode *>arr;  // arr存储奇数层的节点
            for(int i=0;i<size;i++){
                auto node=queue.front();
                queue.pop();
                
                if(isOdd) arr.push_back(node);
                
                if(node->left) queue.emplace(node->left);
                if(node->right) queue.emplace(node->right);
            }
            if(isOdd){
                for(int l=0,r=size-1;l<r;l++,r--){
                    swap(arr[l]->val,arr[r]->val);
                }
            }
            isOdd^=true;
        }
        return root;
    }
};

// 6. N叉树的前序遍历：给定一个 n 叉树的根节点  root ，返回 其节点值的 前序遍历 。
// n 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔
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

// 法一：递归
class Solution6_1 {
public:
    void preorder_traversal(Node *root,vector<int> &ret){
        if(root==nullptr) return;
        ret.push_back(root->val);   // 中
        vector<Node *>children=root->children;
        
        for(auto child:root->children){
            preorder_traversal(child,ret);
        }
    }
    vector<int> preorder(Node* root) {
        vector<int>ret;
        if(root==nullptr) return ret;
        preorder_traversal(root,ret);
        return ret;
    }
};

// 法二：迭代
class Solution6_2 {
public:
    vector<int> preorder(Node* root) {
        vector<int>ret;
        if(root==nullptr) return ret;
        stack<Node *>stack;
        stack.push(root);
        
        while(!stack.empty()){
            auto node=stack.top();
            if(node!=nullptr){
                stack.pop();
                int size=(node->children).size();
                for(int i=size-1;i>=0;i--){     // 从右到左加入子节点
                    stack.push(node->children[i]);
                }
                stack.push(node);stack.push(nullptr);   // 加入当前节点和空节点
            }else{
                stack.pop();
                node=stack.top();stack.pop();
                ret.push_back(node->val);
            }
        }
        return ret;
    }
};

// 7. N叉树的后序遍历:给定一个 n 叉树的根节点 root ，返回 其节点值的 后序遍历
// n 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔。
class Solution7_1 {
public:
    void post_traversal(Node *root,vector<int> &ret){
        if(root==nullptr) return;
        vector<Node *>children=root->children;
        
        for(auto child:root->children){
            post_traversal(child,ret);
        }
        ret.push_back(root->val);   // 中
    }
    vector<int> postorder(Node* root) {
        vector<int>ret;
        if(root==nullptr) return ret;
        post_traversal(root,ret);
        return ret;
    }
};

// 法二：迭代
class Solution7_2 {
public:
    vector<int> postorder(Node* root) {
        vector<int>ret;
        if(root==nullptr) return ret;
        stack<Node *>stack;
        stack.push(root);
        
        while(!stack.empty()){
            auto node=stack.top();
            if(node!=nullptr){
                stack.pop();
                stack.push(node);stack.push(nullptr);   // 加入当前节点和空节点
                int size=(node->children).size();
                for(int i=size-1;i>=0;i--){     // 从右到左加入子节点
                    stack.push(node->children[i]);
                }
            }else{
                stack.pop();
                node=stack.top();stack.pop();
                ret.push_back(node->val);
            }
        }
        return ret;
    }
};

// 8. T103.二叉树的锯齿形层序遍历:给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
// 广度优先遍历:用队列维护当前层的所有元素
// 使用双端队列：可以满足：先从左往右，再从右往左
class Solution_8 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>res;
        if(root==nullptr) return res;
        
        queue<TreeNode *>queue;
        queue.push(root);
        bool isLeft=true;
        
        while(!queue.empty()){
            deque<int>levelList;
            int size=queue.size();
            
            for(int i=0;i<size;i++){
                auto node=queue.front();
                queue.pop();
                // 根据当前层，进行：从左到右/从右到左的插入
                if(isLeft){
                    levelList.push_back(node->val);
                }else{
                    levelList.push_front(node->val);
                }
                if(node->left) queue.push(node->left);
                if(node->right) queue.push(node->right);
            }
            res.push_back(vector<int>{levelList.begin(),levelList.end()});
            isLeft=!isLeft;
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
