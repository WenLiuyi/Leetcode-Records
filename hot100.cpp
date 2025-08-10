//
//  main.cpp
//  hot100
//
//  Created by 文柳懿 on 2025/7/28.
//

#include <iostream>
#include <vector>

using namespace std;

// 普通数组-T56.合并区间
/*
 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
 */
// 如何按顺序合并？对左端点升序排序
// 时间复杂度：O(n*logn)，排序时间开销；O(logn)，排序所需空间复杂度
class Solution_1{
public:
    vector<vector<int>>merge(vector<vector<int>>&intervals){
        vector<vector<int>>res;
        int n=intervals.size();
        sort(intervals.begin(), intervals.end());
        
        for(int i=0;i<n;i++){
            if(res.size()==0 || res.back()[1]<intervals[i][0]){
                // 1. ret中最后一个区间的右端点 < 当前区间的左端点：新增一个区间
                res.push_back(intervals[i]);
            }else{
                // 2. ret最后一个区间与当前区间合并
                res.back()[1]=max(res.back()[1], intervals[i][1]);
            }
        }
        return res;
    }
};

// 普通数组-T189.轮转数组
// 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
// 思路：当我们将数组的元素向右移动 k 次后，尾部 kmodn 个元素会移动至数组头部，其余元素向后移动 kmodn 个位置。
// 我们可以先将所有元素翻转，这样尾部的 kmodn 个元素就被移至数组头部，然后我们再翻转 [0,kmodn−1] 区间的元素和 [kmodn,n−1] 区间的元素即能得到最后的答案。
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_2{
    void reverse(vector<int>&nums, int left, int right){
        while(left<right){
            swap(nums[left],nums[right]);
            left++;right--;
        }
    }
    void rotate(vector<int>& nums, int k) {
        int n=nums.size();
        k%=n;
        reverse(nums,0,n-1);
        reverse(nums,0,k-1);
        reverse(nums,k,n-1);
    }
};

// 普通数组-T289.除自身以外数组的乘积
/*
 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。
 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。
 */
// L[i] 代表的是 i 左侧所有数字的乘积，R[i] 代表的是 i 右侧所有数字的乘积。通过两个循环来填充：
// 先把输出数组当作 L 数组来计算，然后再动态构造 R 数组得到结果。
// 空间复杂度：O(1)
class Solution_3{
public:
    vector<int> productExceptSelf(vector<int>& nums){
        int n=nums.size();
        vector<int>res(n);
        res[0]=1;
        for(int i=1;i<n;i++){
            res[i]=nums[i-1]*res[i-1];
        }
        int R=1;
        for(int i=n-1;i>=0;i--){
            res[i]=res[i]*R;
            R*=nums[i];
        }
        return res;
    }
};

// 普通数组-T41.缺失的第一个正数
/* 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
 请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。*/
/*
 一种朴素的想法：将数组的所有数放入哈希表，从1开始遍历判断是否在哈希表中；但时间复杂度为O(n)
 对于长度为N的数组，答案只可能在[1, N+1]中。在数组中设计一个标记，以取代哈希表。
 流程：
 1. 将数组中所有小于等于 0 的数修改为 N+1;（排除负数）
 2. 遍历数组中的每一个数 x，它可能已经被打了标记，因此原本对应的数为 ∣x∣。如果 ∣x∣∈[1,N]，那么我们给数组中的第 ∣x∣−1 个位置的数添加一个负号。注意如果它已经有负号，不需要重复添加；
 3. 在遍历完成之后，如果数组中的每一个数都是负数，那么答案是 N+1，否则答案是第一个正数的位置加 1.
 */
class Solution_4{
public:
    int firstMissingPositive(vector<int>& nums) {
        int n=nums.size();
        for(int i=0;i<n;i++){
            // 1. 小于等于0的数设置为N+1
            if(nums[i]<=0) nums[i]=n+1;
        }
        for(int i=0;i<n;i++){
            // 2. 对于[1,n]之间的数打标记 (nums[i]的正负与i+1是否在数组中出现有关)
            int num=abs(nums[i]);
            if(num<=n){
                nums[num-1]=-abs(nums[num-1]);
            }
        }
        for(int i=0;i<n;i++){
            if(nums[i]>0) return i+1;
        }
        return n+1;
    }
};

// 二分查找-T35.搜索插入位置
/* 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
 请必须使用时间复杂度为 O(log n) 的算法。*/
// 目标：找第一个大于等于target的数的位置
// 插入位置：nums[pos-1]<target<=nums[pos]
class Solution_5{
public:
    int searchInsert(vector<int>& nums, int target) {
        int n=nums.size();
        if(n==0) return 0;
        int left=0, right=n-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if(nums[mid]<target){
                left=mid+1;
            }else if(nums[mid]>target){
                right=mid-1;
            }else{
                return mid; // 等于target的情况
            }
        }
        return right+1;     // 大于target的情况：right+1=mid, 满足:nums[mid]>target
    }
};

// 二分查找-T74.搜索二维矩阵
/*给你一个满足下述两条属性的 m x n 整数矩阵：
 
 每行中的整数从左到右按非严格递增顺序排列。
 每行的第一个整数大于前一行的最后一个整数。
 给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。*/
class Solution_6{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(), n=matrix[0].size();
        int left=0, right=m*n-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            int row=mid/n, col=mid%n;
            if(matrix[row][col]<target){
                left=mid+1;
            }else if(matrix[row][col]>target){
                right=mid-1;
            }else{
                return true;
            }
        }
        return false;
    }
};

// 二分查找-T34.在排序数组中查找元素的第一个和最后一个位置
/* 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
 如果数组中不存在目标值 target，返回 [-1, -1]。
 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。*/
class Solution_7{
private:
    /* 3种情况：
     1. target超出数组范围，返回：[-1, -1]
     2. target在数组范围中，但数组中不存在target，返回：[-1, -1]
     3. target在数组范围中，且数组中存在target，返回：[leftBorder, rightBorder]
     */
    int getLeftBorder(vector<int>&nums, int target){    // 寻找左边界:不包含target的左边界，即：小于target的最大数
        int left=0, right=nums.size()-1, leftBorder=-2;
        while(left<=right){
            int mid=left+((right-left)>>1);
            if(nums[mid]>=target){
                right=mid-1;    // 排除大于等于target的范围
                leftBorder=right;
            }else{
                left=mid+1;
            }
        }
        return leftBorder;
    }
    int getRightBorder(vector<int>&nums, int target){   // 寻找右边界:不包含target的右边界，即：大于target的最小数
        int left=0, right=nums.size()-1, rightBorder=-2;
        while(left<=right){
            int mid=left+((right-left)>>1);
            if(nums[mid]<=target){
                left=mid+1;
                rightBorder=left;
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

// 二分查找-T33.搜索旋转排序数组
/*
 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
 若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
 若旋转 7 次，则可以得到 [0,1,2,4,5,6,7]
 注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。

 给你一个元素值 互不相同 的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。

 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
 */
// 思路：
class Solution_8{
public:
    int findMin(vector<int>& nums) {
        int left=0, right=nums.size()-1;
        while(left<right){
            int mid=left+((right-left)>>1);
            if(nums[mid]<nums[right]){
                right=mid;
            }else{
                left=mid+1;
            }
        }
        return nums[left];    // left==right的情况
    }
};

// 9. 二分查找-T4.搜索旋转排序数组
/*整数数组 nums 按升序排列，数组中的值 互不相同 。
 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。*/
class Solution_9 {
public:
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        if(n==0) return -1;
        else if(n==1) return nums[0]==target?0:-1;
        int left=0, right=n-1;
        while(left<=right){
            int mid=left+((right-left)>>1);
            if(nums[mid]==target){
                return mid;
            }else if(nums[0]<=nums[mid]){    // nums[0...mid]为递增区间
                if(nums[0]<=target && target<nums[mid]){
                    right=mid-1;        // 对应：target<nums[mid]
                }else{                      // nums[mid, n-1]为递增区间
                    left=mid+1;
                }
            }else{
                if(nums[mid]<target && target<=nums[n-1]){
                    left=mid+1;         // 对应：nums[mid]<target
                }else{
                    right=mid-1;
                }
            }
        }
        return -1;
    }
};

// 10. 矩阵-T73.矩阵置零
/* 给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。*/
// 法一：使用标记数组：记录每一行、每一列是否有0出现
// 时间复杂度：O(mn)；空间复杂度：O(m+n)
class Solution_10_1{
public:
    void setZeroes(vector<vector<int>>&matrix){
        int m=matrix.size(), n=matrix[0].size();
        vector<bool>row(m), col(n);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(!matrix[i][j]){
                    row[i]=col[j]=true;
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(row[i]||col[j]){
                    matrix[i][j]=0;
                }
            }
        }
    }
};

// 法二：用矩阵的第一行和第一列代替方法一中的两个标记数组，以达到 O(1) 的额外空间。但这样会导致原数组的第一行和第一列被修改，无法记录它们是否原本包含 0。因此我们需要额外使用两个标记变量分别记录第一行和第一列是否原本包含 0。
// 空间复杂度：O(1)
class Solution_10_2{
public:
    void setZeroes(vector<vector<int>>&matrix){
        int m=matrix.size(), n=matrix[0].size();
        bool flag_row=false, flag_col=false;
        for(int i=0;i<m;i++){
            if(!matrix[i][0]){
                flag_col=true;break;
            }
        }
        for(int j=0;j<n;j++){
            if(!matrix[0][j]){
                flag_row=true;break;
            }
        }
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                if(!matrix[i][j]){
                    matrix[i][0]=matrix[0][j]=0;
                }
            }
        }
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                if(!matrix[i][0]||!matrix[0][j]){
                    matrix[i][j]=0;
                }
            }
        }
        if(flag_col){
            for(int i=0;i<m;i++){
                matrix[i][0] = 0;
            }
        }
        if(flag_row){
            for(int j=0;j<n;j++){
                matrix[0][j] = 0;
            }
        }
    }
};

// 11. 矩阵-T54.螺旋矩阵
/*给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。*/
// 思路：每一圈为一个循环；每一条边采取左闭右开
class Solution_11{
public:
    vector<int>spiralOrder(vector<vector<int>>& matrix) {
        int m=matrix.size(), n=matrix[0].size();
        int loop=min(m/2, n/2);     // 循环个数
        int startX=0, startY=0;     // 当前循环的起始点坐标
        int offset=1;
        int i=0, j=0;   // 当前坐标
        vector<int>res;
        
        while(loop--){
            i=startX;j=startY;
            // 上排：从左到右
            for(;j<n-offset;j++){
                res.push_back(matrix[i][j]);
            }
            // 右列：从上到下
            for(;i<m-offset;i++){
                res.push_back(matrix[i][j]);
            }
            // 下排：从右到左
            for(;j>startY;j--){
                res.push_back(matrix[i][j]);
            }
            // 左列：从下到上
            for(;i>startX;i--){
                res.push_back(matrix[i][j]);
            }
            startX++;startY++;
            offset++;
        }
        if(min(m, n)%2){
            i=startX;j=startY;
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

// 12. 矩阵-T48.旋转图像
/* 给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
 你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。
 */
/* 思路: matrix_new[col][n-row-1]=matrix[row][col]
 1. temp=matrix[col][n-row-1], matrix[col][n-row-1]=matrix[row][col];
 
 2. temp=matrix[n-row-1][n-col-1], matrix[n-row-1][n-col-1]=matrix[col][n-row-1], matrix[col][n-row-1]=matrix[row][col];
 
 3. temp=matrix[n-col-1][row], matrix[n-col-1][row]=matrix[n-row-1][n-col-1],
    matrix[n-row-1][n-col-1]=matrix[col][n-row-1], matrix[col][n-row-1]=matrix[row][col];
 
 4. temp=matrix[row][col], matrix[row][col]=matrix[n-col-1][row], matrix[n-col-1][row]=matrix[n-row-1][n-col-1],
 matrix[n-row-1][n-col-1]=matrix[col][n-row-1], matrix[col][n-row-1]=temp.
 
 n为偶数时，需要枚举n^2/4个位置；n为奇数时，需要枚举(n^2-1)/4个位置。
 */
// 空间复杂度：O(1)
class Solution_12{
public:
    void rotate(vector<vector<int>>& matrix) {
        int n=matrix.size();
        for(int i=0;i<n/2;i++){
            for(int j=0;j<(n+1)/2;j++){
                int temp=matrix[i][j];
                matrix[i][j]=matrix[n-j-1][i];
                matrix[n-j-1][i]=matrix[n-i-1][n-j-1];
                matrix[n-i-1][n-j-1]=matrix[j][n-i-1];
                matrix[j][n-i-1]=temp;
            }
        }
    }
};
// 另一种思路：先水平翻转，再沿主对角线翻转
// matrix[row][col]->matrix[n-row-1][col]->matrix[col][n-row-1]

// 13. T240.搜索二维矩阵II
/* 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：
 
 每行的元素从左到右升序排列。
 每列的元素从上到下升序排列。*/
// 法一：二分查找，每一行元素都升序排列
// 时间复杂度：O(mlogn)；空间复杂度：O(1)
class Solution_13_1{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for(const auto& row:matrix){
            auto it=lower_bound(row.begin(), row.end(), target);    // it是一个迭代器；将指向target
            if(it!=row.end() && *it==target){
                return true;
            }
        }
        return false;
    }
};

// 法二：Z字形查找
// 对于[x, y]，搜寻：行[x, n-1]，列[0, y]组成的矩阵
// 1. matrix[x, y]==target: 找到；
// 2. matrix[x, y]<target: x++;(matrix[x, y]是第x行最大元素)
// 3. matrix[x, y]>target: y--;(matrix[x, y]是第y列最小元素)
// 时间复杂度：O(m+n)
class Solution_13_2{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(), n=matrix[0].size();
        int x=0, y=n-1;
        while(x<m && y>=0){
            if(matrix[x][y]==target){
                return true;
            }else if(matrix[x][y]<target){
                x++;
            }else{
                y--;
            }
        }
        return false;
    }
};

// 14. 回溯-T46.全排列
// 时间复杂度：O(n!)；空间复杂度：O(n)
class Solution_14{
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(vector<int>& nums, vector<bool>& used){
        if(path.size()==nums.size()){   // 终止条件
            res.push_back(path);
            return;
        }
        for(int i=0;i<nums.size();i++){
            if(used[i]==true) continue;     // 已经使用：跳过
            used[i]=true;
            path.push_back(nums[i]);
            backTrack(nums, used);
            used[i]=false;      // 回溯
            path.pop_back();
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        res.clear();path.clear();
        vector<bool>used(nums.size(), false);
        backTrack(nums, used);
        return res;
    }
};

// 15. 回溯-T78.子集
/* 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。*/
// 时间复杂度：O(n*2^n)
class Solution_15{
private:
    vector<vector<int>>res;
    vector<int>path;
    
    void backTrack(vector<int>&nums, int startIndex){
        res.push_back(path);
        if(startIndex>=nums.size()){
            return;
        }
        for(int i=startIndex;i<nums.size();i++){
            path.push_back(nums[i]);     // 当前元素加入集合
            backTrack(nums, i+1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        res.clear();path.clear();
        backTrack(nums, 0);
        return res;
    }
};

// 16. 回溯-T17.电话号码的字母组合
/* 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。*/

class Solution_16{
private:
    const string letterMap[10]={
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz", // 9
    };
    vector<string>res;
    string path;
    
    void backTrack(const string &digits, int index) {   // index为当前遍历到的元素
        if(index==digits.size()){       // 终止条件
            res.push_back(path);
            return;
        }
        string letters=letterMap[digits[index]-'0'];    // 当前数字对应的可选字符
        for(int i=0;i<letters.size();i++){
            path.push_back(letters[i]);
            backTrack(digits, index+1);     // 递归
            path.pop_back();                // 回溯
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        res.clear();path.clear();
        if(digits.size()==0) return res;
        backTrack(digits, 0);
        return res;
    }
};

// 17. 回溯-T39.组合总和
/*
 给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。
 candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。
 对于给定的输入，保证和为 target 的不同组合数少于 150 个。 */
class Solution_17{
private:
    vector<vector<int>>res;
    vector<int>path;
    
    void backTrack(vector<int> &candidates, int target, int sum, int startIndex){
        if(sum==target){
            res.push_back(path);
            return;
        }
        for(int i=startIndex;i<candidates.size() && sum+candidates[i]<=target;i++){
            sum+=candidates[i];
            path.push_back(candidates[i]);
            backTrack(candidates, target, sum, i);  // 依然是i，表示可以重复读取当前的数
            sum-=candidates[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target){
        res.clear();path.clear();
        sort(candidates.begin(), candidates.end());
        backTrack(candidates, target, 0, 0);
        return res;
    }
};

// 18. 回溯-T22.括号生成
/* 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。 */
class Solution_18{
private:
    vector<string>res;
    string s;
    
    void backTrack(int left, int right, int n){     // left为当前已有的左括号个数；right为当前已有的右括号个数
        if(s.size()==2*n){
            res.push_back(s);
            return;
        }
        if(left<right){
            return;
        }else{
            if(left<n){
                s.push_back('(');
                backTrack(left+1, right, n);
                s.pop_back();
            }
            if(right<n){
                s.push_back(')');
                backTrack(left, right+1, n);
                s.pop_back();
            }
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        res.clear();s.clear();
        backTrack(0, 0, n);
        return res;
    }
};

// 19. 回溯-T39.单词搜索
/* 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。*/

/*
 check(i, j, k)表示: 从board[i][j]出发，是否能找到word[k...]，即word从第k个字符开始的后缀子串
 */
class Solution_19{
private:
    vector<vector<bool>> visited;
    
    void init(int m, int n){
        visited=vector<vector<bool>>(m, vector<bool>(n, false));
    }
    
    bool check(vector<vector<char>>& board, string word, int i, int j, int k){
        if(board[i][j]!=word[k]){
            return false;
        }else if(k==word.length()-1){
            return true;
        }
        visited[i][j]=true;
        vector<pair<int, int>> directions={{0, 1}, {0, -1}, {1,0}, {-1, 0}};
        bool found=false;
        for(const auto &dir:directions){
            int nextX=i+dir.first, nextY=j+dir.second;
            if(0<=nextX && nextX<board.size() && 0<=nextY && nextY<board[0].size()){
                if(!visited[nextX][nextY]){
                    bool flag=check(board, word, nextX, nextY, k+1);
                    if(flag){
                        found=true;break;
                    }
                }
            }
        }
        visited[i][j]=false;
        return found;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m=board.size(), n=board[0].size();
        init(m, n);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                bool flag=check(board, word, i, j, 0);
                if(flag) return true;
            }
        }
        return false;
    }
};

// 20. 回溯-T131.分割回文串
/* 给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。*/
class Solution_20{
private:
    vector<vector<string>>res;
    vector<string>path;
    vector<vector<bool>>isPalindrome;
    
    void computePalindrome(const string &s){
        // s[i,j]是回文串的充要条件：s[i]==s[j], s[i+1, j-1]是回文串
        isPalindrome.resize(s.size(), vector<bool>(s.size(), false));
        for(int i=s.size()-1;i>=0;i--){     // i倒序遍历：确保i+1已经计算过
            for(int j=i;j<s.size();j++){
                if(i==j) isPalindrome[i][j]=true;
                else if(j==i+1) isPalindrome[i][j]=(s[i]==s[j]);
                else{
                    isPalindrome[i][j]=(s[i]==s[j] && isPalindrome[i+1][j-1]);
                }
            }
        }
    }
    
    void backTrack(const string &s, int startIndex){
        // 1. 终止条件
        if(startIndex>=s.size()){
            res.push_back(path);
            return;
        }
        // 2. 遍历切割点
        for(int i=startIndex;i<s.size();i++){
            if(!isPalindrome[startIndex][i]){
                continue;
            }
            string str=s.substr(startIndex, i-startIndex+1);
            path.push_back(str);
            backTrack(s, i+1);
            path.pop_back();    // 回溯
        }
    }
    
public:
    vector<vector<string>> partition(string s){
        res.clear();path.clear();
        computePalindrome(s);
        backTrack(s, 0);
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

