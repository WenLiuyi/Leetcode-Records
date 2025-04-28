//
//  main.cpp
//  Codetop_practice_1
//
//  Created by 文柳懿 on 2025/4/24.
//

#include <iostream>
#include <cstring>
#include <unordered_set>
#include <queue>
#include <stack>
using namespace std;

// 1. 无重复字符的最长子串（连续非空序列）
class Solution_1{
private:
    unordered_set<int>uset; // 记录每个字符是否出现过
    bool check(char ch){        // 判断：uset是否包含ch，即当前区间不符合题意，需要缩短左边界
        if(uset.contains(ch)){
            return true;
        }
        return false;
    }
    
public:
    int len(const string &s){   // 滑动窗口
        int n=s.length(),res=0;
        for(int l=0,r=0;r<n;r++){       // 外层循环扩展右边界
            char ch=s[r];   // 考虑加入的元素
            while(l<=r && check(ch)){   // 内层循环缩短左边界
                uset.erase(s[l++]); // 移除左边界字符
            }
            uset.insert(ch);
            res=max(res,r-l+1);
        }
        return res;
    }
};

// 2. T146.LRU缓存
/* 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
 实现 LRUCache 类：
 LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
 int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
 void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。*/

// 链表：头部为最新使用的；尾部为最早使用的。每次讲新使用的插到头部
struct DLinkedNode{
    int key,value;
    DLinkedNode *prev,*next;
    DLinkedNode():key(0),value(0),prev(nullptr),next(nullptr){}
    DLinkedNode(int _key,int _value):key(_key),value(_value),prev(nullptr),next(nullptr){}
};
class LRUCache{
private:
    int size,capacity;      // size为元素数量；capacity为容量
    unordered_map<int, DLinkedNode *>cache;     // 键为key，值为对应节点
    DLinkedNode *dummyHead,*dummyTail;
    
public:
    LRUCache(int _capacity):size(0),capacity(_capacity){
        // 创建头部/尾部dummy节点
        dummyHead=new DLinkedNode();
        dummyTail=new DLinkedNode();
        dummyHead->next=dummyTail;dummyTail->prev=dummyHead;
    }
    int get(int key){   // 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1
        if(!cache.contains(key)){
            return -1;
        }
        // 如果key存在，通过哈希表，找到对应节点
        DLinkedNode *node=cache[key];
        moveToHead(node);   // 移到头部
        
        return node->value;
    }
    void put(int key, int value){
        unordered_map<int, DLinkedNode *>::iterator it=cache.find(key);
        if(it!=cache.end()){    // key存在
            DLinkedNode *node=it->second;
            node->value=value;
            moveToHead(node);
        }else{                  // key不存在
            DLinkedNode *node=new DLinkedNode(key,value);
            cache[key]=node;
            size++;
            addToHead(node);
            
            if(size>capacity){      // 超出容量：移除尾部节点
                DLinkedNode *lastNode=removeTail();
                cache.erase(lastNode->key);
                delete lastNode;
                size--;
            }
        }
    }
    
    void addToHead(DLinkedNode *node){      // 将node插到链表头部（哑节点之后）
        node->prev=dummyHead;node->next=dummyHead->next;
        node->next->prev=node;dummyHead->next=node;
    }
    void removeNode(DLinkedNode *node){
        node->prev->next=node->next;
        node->next->prev=node->prev;
        node->prev=nullptr;node->next=nullptr;
    }
    void moveToHead(DLinkedNode *node){     // 将node移到头部（从当前位置移除+插到头部）
        removeNode(node);
        addToHead(node);
    }
    DLinkedNode *removeTail(){
        DLinkedNode *lastNode=dummyTail->prev;
        removeNode(lastNode);
        return lastNode;
    }
};

// 3. T206.反转链表
// 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
struct ListNode{
    int val;
    ListNode *next;
    ListNode():val(0),next(nullptr){}
    ListNode(int x):val(x),next(nullptr){}
    ListNode(int x, ListNode *_next):val(x),next(_next){}
};
class Solution_3{
public:
    ListNode *reverseList(ListNode *head){
        if(head==nullptr || head->next==nullptr) return head;
        ListNode *pre=head,*cur=head->next;
        while(cur!=nullptr){
            ListNode *nextNode=cur->next;
            cur->next=pre;  // 反转指针
            pre=cur;cur=nextNode;
        }
        head->next=nullptr;
        return pre;
    }
};

// 4. T215.数组中的第K个最大元素
/* 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。*/
class Solution_4_1{
public:
    int partition(vector<int>&nums, int left, int right){
        int pivotIndex=left+rand()%(right-left+1);
        swap(nums[pivotIndex],nums[right]);     // 基准元素移至最右侧
        int pivot=nums[right];
        
        int i=left;     // 指向小于等于pivot的最后一个元素，下一个位置
        for(int j=left;j<right;j++){
            if(nums[j]<=pivot){
                swap(nums[i],nums[j]);
                i++;
            }
        }
        swap(nums[i],nums[right]);      // 将pivot还原到位置i
        return i;
    }
    int findKthLargest(vector<int>&nums, int k){    // 对快排剪枝
        int left=0,right=nums.size()-1;
        while(left<=right){
            int pivotIndex=partition(nums,left,right);
            if(pivotIndex==nums.size()-k){
                return nums[pivotIndex];
            }else if(pivotIndex<nums.size()-k){
                left=pivotIndex+1;
            }else{
                right=pivotIndex-1;
            }
        }
        return -1;
    }
};

class Solution_4_2{
public:
    void maxHeapify(vector<int>&nums,int i,int heapSize){    // nums[i]的左右子树均为最大堆，调整为以a[i]为根节点的最大堆
        int l=2*i+1,r=2*i+2,largest=i;
        if(l<heapSize && nums[l]>nums[largest]){    // 从i节点的左右节点中，找一个最大的
            largest=l;
        }
        if(r<heapSize && nums[r]>nums[largest]){
            largest=r;
        }
        if(largest!=i){
            swap(nums[largest],nums[i]);
            maxHeapify(nums, largest, heapSize);
        }
    }
    void buildMaxHeap(vector<int>&nums, int heapSize){
        for(int i=heapSize/2-1;i>=0;i--){
            maxHeapify(nums, i, heapSize);
        }
    }
    
    int findKthLargest(vector<int>&nums, int k){
        int heapSize=nums.size();
        buildMaxHeap(nums, heapSize);
        // 删掉当前最大元素（与底部元素交换），重复操作k-1次
        for(int i=nums.size()-1;i>=nums.size()-k+1;i--){
            swap(nums[0],nums[i]);
            heapSize--;
            maxHeapify(nums, 0, heapSize);  // 重新调整
        }
        return nums[0];
    }
};

// 5. T25.K个一组翻转链表
/* 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
 k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。*/
class Solution_5 {
public:
    pair<ListNode *,ListNode *>reverseList(ListNode *head,ListNode *tail){
        ListNode *pre=head,*cur=head->next;
        while(pre!=tail){
            ListNode *nextNode=cur->next;
            cur->next=pre;
            pre=cur;cur=nextNode;
        }
        return {tail,head};
    }
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *dummy=new ListNode(0);
        dummy->next=head;
        
        // 假设翻转[m*k,(m+1)*k-1]之间的链表
        // 1. mk-1指向(m+1)*k-1；
        // 2. 翻转[m*k,(m+1)*k-1]之间的指针指向，共k-1个
        // 3. mk指向(m+1)k
        
        ListNode *curHead=dummy->next, *curTail=dummy, *pre=dummy;
        while(curTail!=nullptr){
            for(int i=1;i<=k;i++){
                curTail=curTail->next;
                if(curTail==nullptr){       // 剩余部分凑不够k个节点，则保持原有顺序，此时直接返回
                    return dummy->next;
                }
            }
            ListNode *nextNode=curTail->next;
            auto pair=reverseList(curHead, curTail);
            pre->next=pair.first;
            pair.second->next=nextNode;
            
            pre=curTail=pair.second;
            curHead=pair.second->next;
        }
        return dummy->next;
    }
};

// 6. T15.三数之和
/* 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
 注意：答案中不可以包含重复的三元组。 */
// 时间复杂度：O(n^2)
class Solution_6 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>>res;
        sort(nums.begin(), nums.end());
        
        for(int i=0;i<nums.size();i++){
            if(nums[i]>0) return res;       // 剪枝：至少有一个非正数
            // 对a去重
            if(i>0 && nums[i]==nums[i-1]) continue;
            
            int left=i+1,right=nums.size()-1;   // 双指针
            while(left<right){
                if(nums[i]+nums[left]+nums[right]==0){
                    res.push_back(vector<int>{nums[i],nums[left],nums[right]});
                    // 对b,c去重
                    while(left<right && nums[left]==nums[left+1]) left++;
                    while(left<right && nums[right]==nums[right-1]) right--;
                    left++;right--;
                }else if(nums[i]+nums[left]+nums[right]<0){
                    left++;
                }
                else {
                    right--;
                }
            }
        }
        return res;
    }
};

// 7. T53.最大子数组和
/* 给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 子数组 是数组中的一个连续部分。*/
// dp[i]:以下标i结尾的子数组最大和
// 状态转移：dp[i]=max(nums[i],dp[i-1]+nums[i]);
// 初始化：dp[0]=nums[i];
class Solution_7 {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int>dp(nums.size(),0);
        dp[0]=nums[0];
        int res=dp[0];
        cout<<nums.size()<<endl;
        for(int i=1;i<nums.size();i++){
            dp[i]=max(nums[i],dp[i-1]+nums[i]);
            res=max(res,dp[i]);
        }
        return res;
    }
};

// 8. T102.二叉树的层序遍历
/* 给你二叉树的根节点 root ，返回其节点值的 层序遍历 。（即逐层地，从左到右访问所有节点）。*/
struct TreeNode{
    int val;
    TreeNode *left,*right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int _val):val(_val),left(nullptr),right(nullptr){}
    TreeNode(int _val,TreeNode *_left,TreeNode *_right):val(_val),left(_left),right(_right){}
};
class Solution_8{
public:
    vector<vector<int>>levelOrder(TreeNode* root){
        vector<vector<int>>res;
        if(root==nullptr) return res;
        queue<TreeNode *>que;
        que.push(root);
        
        while(!que.empty()){        // que中存的是当前层的节点
            int size=que.size();
            vector<int>curLevel;
            
            for(int i=0;i<size;i++){
                auto cur=que.front();que.pop();
                curLevel.push_back(cur->val);
                if(cur->left) que.push(cur->left);
                if(cur->right) que.push(cur->right);
            }
            res.push_back(curLevel);
        }
        return res;
    }
};

// 9. T94.二叉树的中序遍历
// 加入栈的顺序：右-中-左
class Solution_9{
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int>res;
        if(root==nullptr) return res;
        stack<TreeNode *>stk;
        stk.push(root);
        
        while(!stk.empty()){
            TreeNode *node=stk.top();
            if(node!=nullptr){
                stk.pop();
                if(node->right) stk.push(node->right);  // 右节点
                stk.push(node);stk.push(nullptr);       // 当前节点
                if(node->left) stk.push(node->left);    // 左节点
            }else{
                stk.pop();
                node=stk.top();stk.pop();
                res.push_back(node->val);
            }
        }
        return res;
    }
};

// 10. T236.二叉树的最近公共祖先
// 后序遍历：左-右-中
class Solution_10 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==p||root==q||root==nullptr) return root;
        TreeNode *left=lowestCommonAncestor(root->left,p,q);
        TreeNode *right=lowestCommonAncestor(root->right,p,q);
        
        if(left!=nullptr&&right!=nullptr) return root;
        else if(left!=nullptr) return left;
        else if(right!=nullptr) return right;
        else return nullptr;
    }
};

// 11. T46.全排列
class Solution_11 {
private:
    vector<vector<int>>res;
    vector<int>path;
    void backTrack(vector<int>&nums,vector<bool>&used){
        if(path.size()==nums.size()){   // 终止条件
            res.push_back(path);
            return;
        }
        for(int i=0;i<nums.size();i++){
            if(used[i]==true) continue;
            used[i]=true;
            path.push_back(nums[i]);
            backTrack(nums, used);
            path.pop_back();
            used[i]=false;
        }
    }
public:
    vector<vector<int>>permute(vector<int>&nums){
        vector<bool>used(nums.size(),false);
        backTrack(nums, used);
        return res;
    }
};

// 12. T912.排序数组：手撕快排
// 法一：有大量重复元素时，TLE
class Solution_12_1{
public:
    int partition(vector<int>&nums, int left, int right){
        int pivotIndex=left+rand()%(right-left+1);
        swap(nums[pivotIndex],nums[right]);     // 移到最右侧
        int pivot=nums[right];
        
        int i=left;
        for(int j=left;j<right;j++){
            if(nums[j]<=pivot){
                swap(nums[i],nums[j]);
                i++;
            }
        }
        swap(nums[i],nums[right]);
        return i;
    }
    
    void quickSort(vector<int>&nums, int left, int right){
        if(left>=right) return;
        int pivot=partition(nums, left, right);
        quickSort(nums, left, pivot-1);
        quickSort(nums, pivot+1, right);
    }
    
    vector<int>sortArray(vector<int>&nums){
        quickSort(nums, 0, nums.size()-1);
        vector<int>res;
        for(int i=0;i<nums.size();i++){
            res.push_back(nums[i]);
        }
        return res;
    }
};

// 法二：
class Solution_12_2{
public:
    void quickSort(vector<int>&nums, int left, int right){
        if(left>=right) return;
        int pivotIndex=left+rand()%(right-left+1);
        swap(nums[right],nums[pivotIndex]);     // 将基准元素移至最右侧
        int pivot=nums[right],i=left,j=right;
        
        while(i<=j){
            while(nums[i]<pivot) i++;
            while(nums[j]>pivot) j--;
            if(i<=j){
                swap(nums[i++],nums[j--]);
            }
        }
        if(left<j) quickSort(nums, left, j);
        if(i<right) quickSort(nums, i, right);
    }
    
    vector<int>sortArray(vector<int>&nums){
        quickSort(nums, 0, nums.size()-1);
        vector<int>res;
        for(int i=0;i<nums.size();i++){
            res.push_back(nums[i]);
        }
        return res;
    }
};

// 13. T93.复原IP地址
class Solution_13 {
private:
    vector<string>res;
    void backTrack(string &s, int startIndex, int pointerNum){
        if(pointerNum==3){      // 终止条件
            if(isValid(s, startIndex, s.size()-1)){
                res.push_back(s);
            }
            return;
        }
        for(int i=startIndex;i<s.size();i++){
            if(isValid(s, startIndex, i)){
                s.insert(s.begin()+i+1,'.');
                pointerNum++;
                backTrack(s, i+2, pointerNum);
                pointerNum--;
                s.erase(s.begin()+i+1);
            }else{
                break;
            }
        }
    }
    bool isValid(string &s, int start, int end){
        if(start>end) return false;
        if(s[start]=='0' && start!=end){
            return false;
        }
        int num=0;
        for(int i=start;i<=end;i++){
            if(s[i]<'0' || s[i]>'9'){
                return false;
            }
            num=num*10+(s[i]-'0');
            if(num>255) return false;
        }
        return true;
    }
    
public:
    vector<string> restoreIpAddresses(string s) {
        res.clear();
        if(s.size()<4||s.size()>12) return res;
        backTrack(s, 0, 0);
        return res;
    }
};

//

int main(int argc, const char * argv[]) {
    
    // insert code here...
    /* Solution_1 sol;
     string s1="abcde";
     cout<<sol.len(s1)<<endl; */
    
    /* LRUCache cache(2);
     cache.put(1,2);
     cache.put(3,7);
     cout<<cache.get(3)<<endl;
     cache.put(3,5);
     cout<<cache.get(3)<<endl;
     cache.put(4,4);
     cout<<cache.get(1)<<endl;*/
    
    /* Solution_3 sol3;
     ListNode *head=new ListNode(1),*cur=head;
     for(int i=2;i<=5;i++){
         ListNode *newNode=new ListNode(i);
         cur->next=newNode;
         cur=cur->next;
     }
     ListNode *reversedList=sol3.reverseList(head);
     cur=reversedList;
     while(cur!=nullptr){
         cout<<cur->val<<endl;
         cur=cur->next;
     } */
    
    /* vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
     Solution_4_1 sol4;
         
     cout << "排序前: ";
     for (int num : nums) cout << num << " ";
     cout << endl;
         
     int ans=sol4.findKthLargest(nums,3);
     cout << "第K个最大元素为: "<<ans<<endl; */
    
    /* Solution_5 sol5;
     ListNode *head=new ListNode(1),*cur=head;
     for(int i=2;i<=6;i++){
         ListNode *newNode=new ListNode(i);
         cur->next=newNode;
         cur=cur->next;
     }
     head=sol5.reverseKGroup(head,2);
     cur=head;
     while(cur!=nullptr){
         cout<<cur->val<<endl;
         cur=cur->next;
     } */
    
    /* Solution_6 sol6;
     vector<int>nums={-4,1,0,-2,1,3};
     vector<vector<int>>res=sol6.threeSum(nums);
     for(int i=0;i<res.size();i++){
         vector<int>cur=res[i];
         cout<<cur[0]<<" "<<cur[1]<<" "<<cur[2]<<endl;
     } */
    
    /* Solution_7 sol7;
     vector<int>nums={5,4,-1,7,8};
     int res=sol7.maxSubArray(nums);
     cout<<"res:"<<res<<endl; */

    return 0;
}
