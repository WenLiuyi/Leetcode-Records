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

// 5. T700.二叉搜索树中的搜索:给定二叉搜索树（BST）的根节点 root 和一个整数值 val。
// 你需要在 BST 中找到节点值等于 val 的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 null 。
// 思路：二叉搜索树有序，中序遍历得到升序序列

// 法一：递归
class Solution_5_1 {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root==nullptr || root->val==val) return root;
        else if(val<root->val) return searchBST(root->left,val);
        else return searchBST(root->right,val);
    }
};
// 法二：迭代
class Solution_5_2 {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root != NULL) {
            if (root->val > val) root = root->left;
            else if (root->val < val) root = root->right;
            else return root;
        }
        return NULL;
    }
};

// 6. T501.二叉搜索树中的众数
/*给你一个含重复值的二叉搜索树（BST）的根节点 root ，找出并返回 BST 中的所有 众数（即，出现频率最高的元素）。
 如果树中有不止一个众数，可以按 任意顺序 返回。
 */
// 法一：递归:中序遍历，形成升序序列，
class Solution_6_1 {
private:
    TreeNode *pre=nullptr;
    int count=0,maxCount=0;     // count为cur出现频率；maxCount为最大频率
    vector<int>ret;     // 结果：众数集合
    
    void searchBST(TreeNode *cur){
        if(cur==nullptr) return;
        
        searchBST(cur->left);      // 1. 左
        
        // 2. 中
        if(pre==nullptr) count=1;
        else if(pre->val==cur->val){    // 与前一个节点数值相同
            count+=1;
        }else{
            count=1;
        }
        pre=cur;    // 更新前一个节点
        
        if(count==maxCount) ret.push_back(cur->val);
        else if(count>maxCount){    // 清空结果集，更新最大频率
            maxCount=count;
            ret.clear();
            ret.push_back(cur->val);
        }
        // 3. 右
        searchBST(cur->right);
        return;
    }
public:
    vector<int> findMode(TreeNode* root) {
        ret.clear();
        searchBST(root);
        return ret;
    }
};

// 法二：迭代
class Solution_6_2 {
public:
    vector<int> findMode(TreeNode* root) {
        TreeNode *pre=nullptr;
        int count=0,maxCount=0;     // count为cur出现频率；maxCount为最大频率
        vector<int>ret;     // 结果：众数集合
        
        stack<TreeNode *>stack;
        while(!stack.empty() || root!=nullptr){
            while(root!=nullptr){   // 左
                stack.push(root);
                root=root->left;
            }
            
            root=stack.top();stack.pop();   // 中
            if(pre==nullptr) count=1;
            else if(pre->val==root->val) count+=1;
            else count=1;
            
            if(count==maxCount) ret.push_back(root->val);
            if(count>maxCount){
                maxCount=count;
                ret.clear();
                ret.push_back(root->val);
            }
            
            // 右
            pre=root;
            root=root->right;
        }
        return ret;
    }
};

// 7. T235.二叉搜索树的最近公共祖先
// 法一：递归：公共祖先一定在[p,q]区间内
class Solution_7_1 {
private:
    TreeNode *traversal(TreeNode *root,TreeNode *p,TreeNode *q){
        if(root==nullptr) return root;
        
        if(p->val<root->val && q->val<root->val){
            // p,q均在当前节点root的左侧
            TreeNode *left=traversal(root->left,p,q);
            if(left!=nullptr) return left;  // 直接返回，保障是最近公共祖先
        }
        if(p->val>root->val && q->val>root->val){
            // p,q均在当前节点root的右侧
            TreeNode *right=traversal(root->right,p,q);
            if(right!=nullptr) return right;
        }
        // 当前节点root在[p,q]区间内：root是p,q的公共祖先
        return root;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return traversal(root,p,q);
    }
};

// 法二：迭代（利用有序性）
class Solution_7_2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while(root!=nullptr){
            if(p->val<root->val&&q->val<root->val) root=root->left;
            else if(p->val>root->val&&q->val>root->val) root=root->right;
            else return root;
        }
        return nullptr;
    }
};

// 8. T701.二叉搜索树中的插入操作
/*给定二叉搜索树（BST）的根节点 root 和要插入树中的值 value ，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 输入数据 保证 ，新值和原始二叉搜索树中的任意节点值都不同。
 注意，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。 你可以返回 任意有效的结果 。*/
// 1. 所有值 Node.val 是 独一无二 的; 2. 保证 val 在原始BST中不存在.
class Solution_8 {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==nullptr){
            TreeNode *newNode=new TreeNode(val);
            return newNode;
        }
        TreeNode *cur=root;
        while(cur!=nullptr){
            if(val<cur->val){  // 加入cur的左子树
                if(cur->left==nullptr){
                    TreeNode *newNode=new TreeNode(val);
                    cur->left=newNode;
                    return root;
                }else{
                    cur=cur->left;
                }
            }else{      // 加入cur的右子树
                if(cur->right==nullptr){
                    TreeNode *newNode=new TreeNode(val);
                    cur->right=newNode;
                    return root;
                }else{
                    cur=cur->right;
                }
            }
        }
        return root;
    }
};

// 9. T450.删除二叉搜索树中的节点
/*
 给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。
 一般来说，删除节点可分为两个步骤：
 1. 首先找到需要删除的节点；2. 如果找到了，删除它。
 */

// 法一：递归
class Solution_9 {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==nullptr) return root;  // 没找到要删除的节点
        if(root->val==key){
            // 1. 叶子节点
            if(root->left==nullptr && root->right==nullptr){
                delete root;    // 内存释放
                return nullptr;
            }
            else if(root->left==nullptr){   // 2. 左孩子为空，右孩子非空：直接用右孩子替代
                auto rightNode=root->right;
                delete root;
                return rightNode;
            }
            else if(root->right==nullptr){  // 3. 右孩子为空，左孩子非空：直接用左孩子替代
                auto leftNode=root->left;
                delete root;
                return leftNode;
            }
            else{   // 4. 左右孩子非空：将删除节点的左子树，放到删除节点的右子树的最左面节点的左孩子的位置
                TreeNode *cur=root->right;
                while(cur->left!=nullptr){
                    cur=cur->left;
                }
                cur->left=root->left;
                TreeNode *tmp=root;
                root=root->right;
                delete tmp;
                return root;
            }
        }
        if(root->val>key) root->left=deleteNode(root->left, key);
        if(root->val<key) root->right=deleteNode(root->right, key);
        return root;
    }
};

// 10. T108.

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
