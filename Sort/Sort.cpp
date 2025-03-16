//
//  main.cpp
//  Sort
//
//  Created by 文柳懿 on 2025/3/3.
//

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// 1. T347.前K个高频元素
// 你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小
// 时间复杂度：O(n*logk)；空间复杂度：O(n)
class Solution_1 {
public:
    class myCompare{
    public:
        bool operator()(const pair<int,int>&lhs,const pair<int,int>&rhs){
            return lhs.second>rhs.second;   // 满足时返回值1：lhs排在rhs之后
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 1. 统计元素出现的频率：遍历数组nums，使用map记录
        unordered_map<int,int>map;  // key为元素值；value为出现次数
        int n=nums.size();
        for(int i=0;i<n;i++){
            map[nums[i]]++;
        }
        // 2. 建立一个大小为k的小顶堆：每次插入一个新的值，弹出最小的元素（若使用大顶堆，则需要把所有元素都进行排序，而小顶堆只排序k个元素），这是由于：优先队列只能弹出队首（即堆顶）元素
        priority_queue<pair<int,int>,vector<pair<int,int>>,myCompare>queue;
        for(unordered_map<int, int>::iterator it=map.begin();it!=map.end();it++){   // 采用迭代器遍历map
            queue.push(*it);
            if(queue.size()>k) queue.pop();     // 弹出队首（即堆顶的最小元素）
        }
        // 3. 找出前k个高频元素：倒序输出
        vector<int>res(k);
        for(int i=k-1;i>=0;i--){
            res[i]=queue.top().first;
            queue.pop();
        }
        return res;
    }
};

// 2. 数组中的第K个最大元素
/*给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。*/
// 法一：使用快速排序
class Solution_2 {
public:
    int getRandom(int left,int right){
        return rand()%(right-left+1)+left;
    }
    void quickSort(vector<int>&nums,int left,int right){
        int i=left,j=right;
        int pivot=nums[getRandom(left, right)];
        
        while(i<=j){
            while(nums[i]<pivot) i++;
            while(nums[j]>pivot) j--;
            if(i<=j){
                swap(nums[i],nums[j]);
                i++;j--;
            }
        }
        if(left<j) quickSort(nums, left, j);
        if(i<right) quickSort(nums, i, right);
    }
    int findKthLargest(vector<int>& nums, int k) {
        quickSort(nums,0,nums.size()-1);
        return nums[nums.size()-k];
    }
};

// 3. T75.颜色分类
/*给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地 对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
 我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
 必须在不使用库内置的 sort 函数的情况下解决这个问题。*/
// 进阶：你能想出一个仅使用常数空间的一趟扫描算法吗？
class Solution_3 {
public:
    void quickSort(vector<int>&nums,int left,int right){
        int i=left,j=right,tmp;
        int pivot=nums[(left+right)/2];
        
        while(i<=j){
            while(nums[i]<pivot) i++;   // 不再处理中间的重复元素
            while(nums[j]>pivot) j--;
            if(i<=j){
                swap(nums[i],nums[j]);
                i++;j--;
            }
        }
        if(left<j) quickSort(nums, left, j);
        if(i<right) quickSort(nums, i, right);
    }
    void sortColors(vector<int>& nums) {
        quickSort(nums, 0, nums.size()-1);
    }
};

// 4. 根据字符出现频率排序:
/*给定一个字符串 s ，根据字符出现的 频率 对其进行 降序排序 。一个字符出现的 频率 是它出现在字符串中的次数。
 返回 已排序的字符串 。如果有多个答案，返回其中任何一个。*/
// 时间复杂度：O(n+k*logk),其中 n 是字符串 s 的长度，k 是字符串 s 包含的不同字符的个数.
// 空间复杂度：O(n+k)
class Solution_4 {
public:
    class myCompare{
    public:
        bool operator()(const pair<char,int>&lhs,const pair<char,int>&rhs){
            return lhs.second<rhs.second;   // 满足时返回值1：lhs排在rhs之后
        }
    };
    string frequencySort(string s) {
        // 1. 统计每个字符的频率
        unordered_map<char,int>map;
        int len=s.length();
        for(int i=0;i<len;i++){
            map[s[i]]++;
        }
        // 2. 建立大顶堆，按频率降序排序
        string res="";
        priority_queue<pair<char,int>,vector<pair<char,int>>,myCompare>queue;
        for(unordered_map<char,int>::iterator it=map.begin();it!=map.end();it++){
            queue.push({it->first,it->second});
        }
        // 3. 构建字符串
        int size=queue.size();
        for(int i=0;i<size;i++){
            int cnt=queue.top().second;char ch=queue.top().first;
            queue.pop();
            for(int j=0;j<cnt;j++){
                res.push_back(ch);
            }
        }
        return res;
    }
};

// 5. T378.有序矩阵中第K小的元素:给你一个 n x n 矩阵 matrix ，其中每行和每列元素均按升序排序，找到矩阵中第 k 小的元素。请注意，它是 排序后 的第 k 小元素，而不是第 k 个 不同 的元素。你必须找到一个内存复杂度优于 O(n2) 的解决方案
// 法一：直接排序:将这个二维数组转成一维数组，并对该一维数组进行排序
// 时间复杂度：O(n^2 * logn)，对n^2个数排序
// 空间复杂度：O(n^2)
class Solution_5_1 {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        vector<int>rec;
        for(auto &row:matrix){
            for(int it:row){
                rec.push_back(it);
            }
        }
        sort(rec.begin(),rec.end());
        return rec[k-1];
    }
};
// 法二：归并排序:n 个数组归并，用小根堆维护
// 时间复杂度：O(k*logn)，归并k次，每次堆中插入和弹出的操作时间复杂度均为 logn
// 空间复杂度：O(n)，堆的大小始终为n
class Solution_5_2 {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        struct point{
            int val,x,y;
            point(int _val,int _x,int _y):val(_val),x(_x),y(_y){}
            bool operator > (const point &a)const{return this->val>a.val;} // 定义>
        };
        priority_queue<point, vector<point>, greater<point>>queue;  // 小根堆：要定义>符号
        
        int n=matrix.size();
        for(int i=0;i<n;i++){
            queue.emplace(matrix[i][0],i,0);    // 将每行的第一个元素加入队列
        }
        for(int i=0;i<k-1;i++){
            point cur=queue.top();queue.pop();  // 弹出堆顶元素；加入对应行中的下一个元素
            if(cur.y!=n-1){
                queue.emplace(matrix[cur.x][cur.y+1],cur.x,cur.y+1);
            }
        }
        return queue.top().val;
    }
};

// 法三：二分查找
// 整个二维数组中 matrix[0][0] 为最小值，matrix[n−1][n−1] 为最大值，现在我们将其分别记作 l 和 r
/* 1. 初始位置在 matrix[n−1][0]（即左下角）；
 2. 设当前位置为 matrix[i][j]。若 matrix[i][j]≤mid，则将当前所在列的不大于 mid 的数的数量（即 i+1）累加到答案中，并向右移动，否则向上移动；
 3. 不断移动直到走出格子为止。*/
class Solution_5_3 {
public:
    bool check(vector<vector<int>>& matrix, int mid, int k, int n){
        int i=n-1,j=0;
        int cnt=0;      // 统计整个矩阵中，<=mid的元素个数
        while(i>=0 && j<n){
            if(matrix[i][j]<=mid){
                cnt+=i+1;   // 当前列中,<=mid的元素个数
                j++;
            }else{
                i--;
            }
        }
        return cnt>=k;
    }
    
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n=matrix.size();
        int left=matrix[0][0],right=matrix[n-1][n-1];
        while(left<right){      // 采用了二分查找的写法二
            int mid=left+((right-left)>>1);
            if(check(matrix,mid,k,n)){
                right=mid;
            }else{
                left=mid+1;
            }
        }
        return left;
    }
};

/*
 总结：第一种没有利用矩阵的性质，所以时间复杂度最差；第二种解法只利用了一部分性质（每一行是一个有序数列，而忽视了列之间的关系）；第三种解法则利用了全部性质，所以时间复杂度最佳。
 */

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
