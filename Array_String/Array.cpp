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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
