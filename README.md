# Leetcode-C++
## 数组
### 2. 二分查找
## 链表
## 哈希表
## 字符串
## 双指针
## 滑动窗口
## 栈与队列
## 二叉树
### 1. 理论基础
#### 1.1 二叉树的种类
##### 1.1.1 满二叉树：
    一棵二叉树只有度为0的结点和度为2的结点，并且度为0的结点在同一层上，则称为满二叉树；
    深度为h，有2^h-1个节点。
##### 1.1.2 完全二叉树：
    除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（h从1开始），则该层包含 1~ 2^(h-1) 个节点。

##### 1.1.3 二叉搜索树
**有序**树。
* 若左子树非空，则左子树上的所有结点的值，均小于根结点的值；
* 若右子树非空，则右子树上的所有结点的值，均大于根结点的值；
* 左、右子树也分别为二叉搜索树

##### 1.1.4 平衡二叉搜索树（AVL）
它是一棵空树，或它的左右两个子树的高度差的绝对值不超过1，并且左右两个子树都是一棵平衡二叉树。
![alt text](20200806190511967.png)
> C++中map、set、multimap，multiset的底层实现都是平衡二叉搜索树，所以map、set的增删操作时间时间复杂度是logn；
> unordered_map、unordered_set，unordered_map、unordered_set底层实现是哈希表。

#### 1.2 二叉树的存储方式
##### 1.2.1 链式存储（指针）

##### 1.2.2 顺序存储（数组）
![alt text](20200920200429452.png)
若父节点的数组下标为i，则**左孩子下标为2*i+1，右孩子下标为2*i+2**。

#### 1.3 二叉树的遍历方式
##### 1.3.1 深度优先遍历（DFS）：栈实现
1. 前序遍历（递归，迭代）：中左右
2. 中序遍历（递归，迭代）：左中右
3. 后序遍历（递归，迭代）：左右中

##### 1.3.2 广度优先遍历（BFS）：队列实现
层次遍历（迭代）

#### 1.4 二叉树的定义
```C
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
    TreeNode(int x,TreeNode *left,TreeNode *right): val(x),left(left),right(right){}
};
```

### 2. 二叉树的遍历
#### 2.1 二叉树的递归遍历
递归三要素：递归函数的参数、返回值；终止条件；单层递归逻辑
前序遍历：
```C
class Solution {
public:
    void preOrder(TreeNode *cur,vector<int> &res){
        if(cur==NULL) return;       // 终止条件
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
```

#### 2.2 二叉树的迭代遍历

#### 2.3 二叉树的层序遍历（BFS）
模版：
```C
class Solution{
public:
    vector<vector<int>> levelOrder(TreeNode *root){
        vector<vector<int>> ret;
        if(!root) return ret;   // 判断非空
        
        queue<TreeNode *> q;    // 创建队列
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
```

### 3. 二叉树的属性

### 4. 二叉树的修改与构造

### 5. 二叉树公共祖先问题

### 6. 二叉搜索树的属性
* 二叉树中序遍历得到升序序列，使用栈模拟实现。

* 频繁查找第k小的元素：记录以每个结点为根结点的子树的结点数，辅助查找
```C
class MyBst{
public:
    MyBst(TreeNode *root){
        this->root=root;
        countNodeNum(root);
    }
    int kthSmallest(int k){
        TreeNode *node=root;
        while(node!=nullptr){
            int left=countNodeNum(root->left);
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
};
```

### 7. 二叉搜索树的修改与改造


## 回溯
## 贪心
## 分治
## 动态规划
## 单调栈
## 图
## 数学
### 1. 位运算