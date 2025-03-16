//
//  main.cpp
//  Array
//
//  Created by 文柳懿 on 2025/3/4.
//

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

// 1. T704.二分查找：给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
// 写法一：[left,right]区间
class Solution_1_1 {
public:
    int search(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if(nums[mid]>target){
                right=mid-1;
            }else if(nums[mid]<target){
                left=mid+1;
            }else{
                return mid;
            }
        }
        return -1;
    }
};

// 写法二：[left,right)区间
class Solution_1_2 {
public:
    int search(vector<int>& nums, int target) {
        int left=0,right=nums.size();
        while(left<right){
            int mid=left+(right-left)/2;
            if(nums[mid]>target){
                right=mid;
            }else if(nums[mid]<target){
                left=mid+1;
            }else{
                return mid;
            }
        }
        return -1;
    }
};

// 2. T35.搜索插入位置： 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
// 写法一：[left,right]
class Solution_2_1 {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1;
        while(left<=right){
            int mid=left+((right-left)>>1);
            if(nums[mid]>target){
                right=mid-1;
            }else if(nums[mid]<target){
                left=mid+1;
            }else{
                return mid;
            }
        }
        /* 4种情况：
         1. 目标值在数组所有元素之前: [0,-1]
         2. 目标值等于数组中的元素: mid
         3. 目标在数组[left,right]中: right+1
         4. 目标值在数组所有元素之后 [left, right]， 因为是右闭区间，所以 right + 1
         */
        return right+1;
    }
};

// 写法二：[left,right)
class Solution_2_2 {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left=0,right=nums.size();
        while(left<right){
            int mid=left+((right-left)>>1);
            if(nums[mid]>target){
                right=mid;
            }else if(nums[mid]<target){
                left=mid+1;
            }else{
                return mid;
            }
        }
        return right;
    }
};

// 3. T34.在排序数组中查找元素的第一个和最后一个位置:给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
//如果数组中不存在目标值 target，返回 [-1, -1]。
/* 三种情况：
 1. target 在数组范围的右边或者左边，例如数组{3, 4, 5}，target为2或者数组{3, 4, 5},target为6，此时应该返回[-1, -1];
 2. target 在数组范围中，且数组中不存在target，例如数组{3,6,7},target为5，此时应该返回[-1, -1];
 3. target 在数组范围中，且数组中存在target，例如数组{3,6,7},target为6，此时应该返回[-1, -1].
 */
class Solution_3 {
private:
    int getLeftBorder(vector<int>&nums,int target){     // 寻找左边界:不包含target的左边界
        int left=0,right=nums.size()-1;
        int leftBorder=-2;
        while(left<=right){
            int mid=left+((right-left)>>1);
            if(nums[mid]>=target){  // 此时nums[mid-1]<=target，设为新的左边界
                right=mid-1;leftBorder=right;
            }else{
                left=mid+1;
            }
        }
        return leftBorder;
    }
    int getRightBorder(vector<int>&nums,int target){    // 寻找右边界:不包含target的右边界
        int left=0,right=nums.size()-1;
        int rightBorder=-2;
        while(left<=right){
            int mid=left+((right-left)>>1);
            if(nums[mid]<=target){  // 此时nums[mid+1]>=target，设为新的右边界
                left=mid+1;rightBorder=left;
            }else{
                right=mid-1;
            }
        }
        return rightBorder;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftBorder=getLeftBorder(nums,target);
        int rightBorder=getRightBorder(nums,target);
        
        if(leftBorder==-2||rightBorder==-2) return {-1,-1};
        else if(rightBorder-leftBorder>1) return {leftBorder+1,rightBorder-1};
        return {-1,-1};
    }
};

// 4. x的平方根:给你一个非负整数 x ，计算并返回 x 的 算术平方根
// 二分查找：x平方根的整数部分k，是满足k^2<=x的最大k值
// 0 <= x <= 2^31 - 1
// 时间复杂度：O(log x)；空间复杂度：O(1)
class Solution_4 {
public:
    int mySqrt(int x) {
        int left=0,right=x,k=-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if((long long)mid*mid<=x){
                k=mid;left=mid+1;
            }else{
                right=mid-1;
            }
        }
        return k;
    }
};

// 5. T367.有效的完全平方数:给你一个正整数 num 。如果 num 是一个完全平方数，则返回 true ，否则返回 false 。
class Solution_5 {
public:
    bool isPerfectSquare(int num) {
        int left=0,right=num;
        while(left<=right){
            int mid=left+((right-left)>>1);
            long n=(long)mid*mid;
            if(n>num){
                right=mid-1;
            }else if(n<num){
                left=mid+1;
            }else{
                return true;
            }
        }
        return false;
    }
};

// 6. T27.移除元素
/*给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素。元素的顺序可能发生改变。然后返回 nums 中与 val 不同的元素的数量。
 假设 nums 中不等于 val 的元素数量为 k，要通过此题，您需要执行以下操作：
 更改 nums 数组，使 nums 的前 k 个元素包含不等于 val 的元素。nums 的其余元素和 nums 的大小并不重要。
 返回 k。*/
// 双指针法：时间复杂度：O(n);空间复杂度：O(1)
class Solution_6 {
public:
    int removeElement(vector<int>& nums, int val) {
        int cnt=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]!=val){
                if(cnt!=i) nums[cnt++]=nums[i];
                else cnt++;
            }
        }
        return cnt;
    }
};

// 7. T844.比较含退格的字符串:给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，如果两者相等，返回 true 。# 代表退格字符。
// 注意：如果对空文本输入退格字符，文本继续为空。
// 法一：使用栈：普通字符压入；遇到退格字符，从栈顶弹出一个元素
class Solution_7 {
public:
    string build(string s){
        string res;
        int n=s.length();
        for(int i=0;i<n;i++){
            if(s[i]!='#'){  // 普通字符
                res.push_back(s[i]);
            }else if(!res.empty()){
                res.pop_back();
            }
        }
        return res;
    }
    bool backspaceCompare(string s, string t) {
        return build(s)==build(t);
    }
};
// 法二：双指针法：一个字符是否会被删掉，只取决于该字符后面的退格符；逆序地遍历字符串，就可以立即确定当前字符是否会被删掉。

// 8. T977.有序数组的平方:给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。
/*1 <= nums.length <= 104
 -104 <= nums[i] <= 104 */
// 法一：直接平方再排序
// 时间复杂度：O(n*logn)；空间复杂度：O(logn)--排序所需的栈空间
class Solution_8_1 {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int>ans;
        for(int num:nums){
            ans.push_back(num*num);
        }
        sort(ans.begin(),ans.end());
        return ans;
    }
};

// 法二：双指针，找到数组 nums 中负数与非负数的分界线，使用归并排序
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_8_2 {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n=nums.size(),negIndex=-1;
        for(int i=0;i<n;i++){
            if(nums[i]<0) negIndex=i;
            else break;
        }
        vector<int>ans;
        int i=negIndex,j=negIndex+1;
        while(i>=0 || j<n){
            if(i<0){
                ans.push_back(nums[j]*nums[j]);
                j++;
            }else if(j>=n){
                ans.push_back(nums[i]*nums[i]);
                i--;
            }else if(nums[i]*nums[i]<nums[j]*nums[j]){
                ans.push_back(nums[i]*nums[i]);
                i--;
            }else{
                ans.push_back(nums[j]*nums[j]);
                j++;
            }
        }
        return ans;
    }
};

// 9. 螺旋矩阵
class Solution_9 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int>res;
        int startX=0,startY=0;  // 每一层循环的起始位置
        int m=matrix.size(),n=matrix[0].size();
        int loop=min(m/2,n/2);  // 循环个数
        int count=1,offset=1;   // offset为每一条边的遍历长度
        int i=0,j=0;
        
        while(loop--){
            i=startX;j=startY;
            for(;j<n-offset;j++){       // 模拟上行从左到右
                res.push_back(matrix[i][j]);
            }
            for(;i<m-offset;i++){       // 模拟右列从上到下
                res.push_back(matrix[i][j]);
            }
            for(;j>startY;j--){         // 模拟下行从右到左
                res.push_back(matrix[i][j]);
            }
            for(;i>startX;i--){         // 模拟左列从下到上
                res.push_back(matrix[i][j]);
            }
            startX++;startY++;
            offset++;
        }
        
        if(min(m,n)%2){
            i=startX,j=startY;
            if(m<=n){
                for(;j<=n-offset;j++){       // 从左到右
                    res.push_back(matrix[i][j]);
                }
            }else{      // 从上到下
                for(;i<=m-offset;i++){       // 从上到下
                    res.push_back(matrix[i][j]);
                }
            }
        }
        return res;
    }
};

// 10. T59.螺旋矩阵II:给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
/*填充上行从左到右
 填充右列从上到下
 填充下行从右到左
 填充左列从下到上*/
class Solution_10 {
public:
    vector<vector<int>> generateMatrix(int n) {     // 矩阵n行n列
        int startX=0,startY=0;  // 每一层循环的起始位置
        vector<vector<int>> res(n,vector<int>(n, 0));
        int loop=n/2;  // 循环个数
        int count=1,offset=1;   // offset为每一条边的遍历长度
        int i=0,j=0;
        
        while(loop--){
            i=startX;j=startY;
            for(;j<n-offset;j++){       // 模拟上行从左到右
                res[i][j]=count++;
            }
            for(;i<n-offset;i++){       // 模拟右列从上到下
                res[i][j]=count++;
            }
            for(;j>startY;j--){         // 模拟下行从右到左
                res[i][j]=count++;
            }
            for(;i>startX;i--){         // 模拟左列从下到上
                res[i][j]=count++;
            }
            startX++;startY++;
            offset++;
        }
        if(n%2){
            int mid=n/2;
            res[mid][mid]=count++;
        }
        return res;
    }
};

// 11.. T135.分发糖果
/*n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。
 你需要按照以下要求，给这些孩子分发糖果：
 1. 每个孩子至少分配到 1 个糖果。
 2. 相邻两个孩子评分更高的孩子会获得更多的糖果。
 3. 请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。*/

// 法一：分别将当前元素，与左右两个相邻元素比较，求出满足规则时的最小值；每个人最终分得的糖果数量即为这两个数量的最大值。
// 从左到右贪心一遍；从右到左贪心一遍
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_11_1 {
public:
    int candy(vector<int>& ratings) {
        int n=ratings.size();
        vector<int>left(n);
        for(int i=0;i<n;i++){
            if(i>0&&ratings[i]>ratings[i-1]){
                left[i]=left[i-1]+1;    // 比左边的元素，多分一个糖果
            }else{
                left[i]=1;
            }
        }
        int right=0,ans=0;
        for(int i=n-1;i>=0;i--){
            if(i<n-1 && ratings[i]>ratings[i+1]){
                right++;    // 比右边的元素，多分一个糖果
            }else{
                right=1;
            }
            ans+=max(left[i],right);
        }
        return ans;
    }
};

// 法二：常数空间遍历：要么在递增序列，要么在递减序列
// 1. 处于递增序列：比上一个元素糖果数+1；
// 2. 处于递减序列：分配给当前同学一个糖果，并把该同学所在的递减序列中所有的同学都再多分配一个糖果
class Solution_11_2 {
public:
    int candy(vector<int>& ratings) {
        int n=ratings.size();
        int inc=1,dec=0,pre=1;  // inc,dec分别为递增、递减序列的长度
        int ret=1;
        
        for(int i=1;i<n;i++){
            if(ratings[i]>=ratings[i-1]){   // 递增序列中
                dec=0;
                pre = ratings[i] == ratings[i- 1] ? 1 : pre+1;  //当前同学和上一个同学分数相等时，直接分配1个就行，这样满足最小
                ret+=pre;
                inc=pre;
            }else{
                dec++;
                if(dec==inc) dec++; // 当递减序列长度和递增序列长度相等时，把递增序列的最后一个同学分配到递减序列中
                ret+=dec;
                pre=1;
            }
        }
        return ret;
    }
};

// 12. T42.接雨水:给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
// 法一：动态规划:
// 数组leftMax, rightMax分别记录：leftMax[i] 表示下标 i 及其左边的位置中，height 的最大高度；rightMax[i] 表示下标 i 及其右边的位置中，height 的最大高度。
// 初始状态：leftMax[0]=height[0]，rightMax[n−1]=height[n−1]
// 转移方程：
// 1. 当 1≤i≤n−1 时，leftMax[i]=max(leftMax[i−1],height[i])；
// 2. 当 0≤i≤n−2 时，rightMax[i]=max(rightMax[i+1],height[i])
// 位置i处接的雨水量：min(leftMax[i],rightMax[i])−height[i].
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution12_1 {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        if(n==0) return 0;
        
        vector<int>leftMax(n,0);
        leftMax[0]=height[0];
        for(int i=1;i<n;i++){
            leftMax[i]=max(leftMax[i-1],height[i]);
        }
        
        vector<int>rightMax(n,0);
        rightMax[n-1]=height[n-1];
        for(int i=n-2;i>=0;i--){
            rightMax[i]=max(rightMax[i+1],height[i]);
        }
        int ret=0;
        for(int i=0;i<n;i++){
            ret+=min(leftMax[i],rightMax[i])-height[i];
        }
        return ret;
    }
};

// 13. T719.找出第K小的数对距离
/* 数对 (a,b) 由整数 a 和 b 组成，其数对距离定义为 a 和 b 的绝对差值。
 给你一个整数数组 nums 和一个整数 k ，数对由 nums[i] 和 nums[j] 组成且满足 0 <= i < j < nums.length 。返回 所有数对距离中 第 k 小的数对距离。 */
// 思路：排序+二分查找
// 第 k 小的数对距离必然在区间 [0,max(nums)−min(nums)] 内，在此区间进行二分；
// 对于当前搜索的距离 mid，计算所有距离小于等于 mid 的数对数目 cnt，如果 cnt≥k，那么 right=mid−1，否则 left=mid+1。当 left>right 时，终止搜索，那么第 k 小的数对距离为 left。
//给定距离 mid，计算所有距离小于等于 mid 的数对数目 cnt ,使用二分查找：枚举所有数对的右端点 j，二分查找大于等于 nums[j]−mid 的最小值的下标 i，那么右端点为 j 且距离小于等于 mid 的数对数目为 j−i，计算这些数目之和。

// 外层二分查找：O(logD);内层二分查找:O(n*logn). 总时间复杂度：O(nlogn*logD)
class Solution_13 {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int n=nums.size(),left=0,right=nums[n-1]-nums[0];
        
        while(left<=right){     // 1. 先对距离区间[left,right]进行二分
            int mid=(left+right)/2,cnt=0;
            // 计算所有距离小于等于mid的数组
            for(int j=0;j<n;j++){   // 2. 再对排序后的数组二分，查找和nums[j]的距离不超过mid的下标范围
                int i=lower_bound(nums.begin(), nums.begin()+j, nums[j]-mid)-nums.begin();
                cnt+=j-i;
            }
            if(cnt>=k){
                right=mid-1;
            }else{
                left=mid+1;     // 对于left，有：cnt<k才会更新
            }
        }
        return left;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
