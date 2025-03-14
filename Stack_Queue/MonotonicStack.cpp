//
//  main.cpp
//  MonotonicStack
//
//  Created by 文柳懿 on 2025/3/13.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 1. T739.每日温度：给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
// 法一：暴力解法，O(n^2)
// 法二：单调栈：一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_1 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n=temperatures.size();
        vector<int>ret(temperatures.size(),0);
        if(n==0) return ret;
        
        stack<int>temp_stack;
        temp_stack.push(0);
        
        for(int i=1;i<n;i++){
            if(temperatures[i]<=temperatures[temp_stack.top()]){    // 当前温度 <= 栈顶温度：入栈
                temp_stack.push(i);
            }else{
                while(!temp_stack.empty() && temperatures[i]>temperatures[temp_stack.top()]){
                    // 当前温度 > 栈顶温度：不断从栈顶弹出元素，直至当前温度 <= 栈顶温度，再将当前下标入栈
                    ret[temp_stack.top()]=i-temp_stack.top();
                    temp_stack.pop();
                }
                temp_stack.push(i);
            }
        }
        return ret;
    }
};

// 2. T496.下一个更大元素I
/*nums1 中数字 x 的 下一个更大元素 是指 x 在 nums2 中对应位置 右侧 的 第一个 比 x 大的元素。
 给你两个 没有重复元素 的数组 nums1 和 nums2 ，下标从 0 开始计数，其中nums1 是 nums2 的子集。
 对于每个 0 <= i < nums1.length ，找出满足 nums1[i] == nums2[j] 的下标 j ，并且在 nums2 确定 nums2[j] 的 下一个更大元素 。如果不存在下一个更大元素，那么本次查询的答案是 -1 。
 返回一个长度为 nums1.length 的数组 ans 作为答案，满足 ans[i] 是如上所述的 下一个更大元素 。*/

/* nums1和nums2中所有整数 互不相同
 nums1 中的所有整数同样出现在 nums2 中*/

// 单调栈：1. 先遍历nums1，用哈希表记录：每个元素值对应的下标
// 时间复杂度：O(nums1.length + nums2.length)
class Solution_2 {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size(),m=nums2.size();
        vector<int>ret(n,-1);
        if(n==0||m==0) return ret;
        
        unordered_map<int, int>map;     // key为元素值；value为nums1中对应下标
        for(int i=0;i<n;i++){
            map[nums1[i]]=i;
        }
        
        stack<int>st;
        st.push(0);
        for(int i=1;i<m;i++){
            if(nums2[i]<=nums2[st.top()]){
                st.push(i);
            }else{
                while(!st.empty() && nums2[i]>nums2[st.top()]){
                    if(map.find(nums2[st.top()])!=map.end()){   // unordered_map支持迭代器（map不支持）
                        int index=map[nums2[st.top()]];     // index为：num1中，元素值为nums2[st.top()]的对应下标
                        ret[index]=nums2[i];
                    }
                    st.pop();
                }
                st.push(i);
            }
        }
        return ret;
    }
};

// 3. T503.下一个更大元素II
/* 给定一个循环数组 nums （ nums[nums.length - 1] 的下一个元素是 nums[0] ），返回 nums 中每个元素的 下一个更大元素 。
 数字 x 的下一个更大的元素 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1 */
// 思路：由于要循环查找，因此遍历两遍
class Solution_3 {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n=nums.size();
        vector<int>ret(n,-1);
        if(n==0) return ret;
        
        stack<int>st;
        st.push(0);
        for(int i=1;i<n;i++){   // 遍历第一遍
            if(nums[i]<=nums[st.top()]){
                st.push(i);
            }else{
                while(!st.empty() && nums[i]>nums[st.top()]){
                    ret[st.top()]=nums[i];
                    st.pop();
                }
                st.push(i);
            }
        }
        for(int i=0;i<n-1;i++){ // 遍历第二遍
            if(nums[i]<=nums[st.top()]){
                st.push(i);
            }else{
                while(!st.empty() && nums[i]>nums[st.top()]){
                    ret[st.top()]=nums[i];
                    st.pop();
                }
                st.push(i);
            }
            if(st.empty()) break;
        }
        return ret;
    }
};

// 4. T42.接雨水:给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
// 分析：下标i处的雨水量：下标 i 两边的最大高度的最小值，减去下标i处高度：min(leftMax[i],rightMax[i])−height[i]
// 关键点：如何求下标i两侧的最大高度

// 法一：动态规划，建立两个数组表示：
// leftMax[i] 表示下标 i 及其左边的位置中，height 的最大高度，rightMax[i] 表示下标 i 及其右边的位置中，height 的最大高度。
// 递推：leftMax[i]=max(leftMax[i−1],height[i])；rightMax[i]=max(rightMax[i+1],height[i])
class Solution_4_1 {
public:
    int trap(vector<int>& height){
        int n=height.size();
        if(n==0) return 0;
        
        vector<int>leftMax(n);
        leftMax[0]=height[0];
        for(int i=1;i<n;i++){
            leftMax[i]=max(leftMax[i-1],height[i]);
        }
        
        vector<int>rightMax(n);
        rightMax[n-1]=height[n-1];
        for(int i=n-2;i>=0;i--){
            rightMax[i]=max(rightMax[i+1],height[i]);
        }
        
        int ans=0;
        for(int i=0;i<n;i++){
            ans+=min(leftMax[i],rightMax[i])-height[i];
        }
        return ans;
    }
};

// 法二：单调栈：从栈底到栈顶单调递减
/* height[i]>height[st.top()]时：
 1. 栈顶元素：凹槽（弹出栈顶元素）
 2. 新的栈顶元素：凹槽的左侧位置
 3. 当前遍历的元素i：凹槽的右侧位置
 */
class Solution_4_2 {
public:
    int trap(vector<int>& height){
        if(height.size()<=2) return 0;
        stack<int>st;
        st.push(0);
        
        int sum=0;
        for(int i=1;i<height.size();i++){
            if(height[i]<height[st.top()]){    // 当前高度低于左侧高度，压入栈
                st.push(i);
            }else if(height[i]==height[st.top()]){  // 相同高度时，需要用最右侧的柱子计算宽度
                st.pop();
                st.push(i);
            }
            else{      // 当前高度高于左侧高度，从栈中弹出元素
                while(!st.empty() && height[i]>height[st.top()]){
                    int mid=st.top();st.pop();
                    if(!st.empty()){
                        int h=min(height[st.top()],height[i])-height[mid];
                        int w=i-st.top()-1;     // 宽度
                        sum+=h*w;
                    }
                }
                st.push(i);
            }
        }
        return sum;
    }
};

// 5. T84.柱状图中最大的矩形:给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
// 求在该柱状图中，能够勾勒出来的矩形的最大面积。

// 法一：单调栈：对于每个柱子（高度为h），找其左右两侧，第一个高度小于h的柱子的下标
// 从栈头到栈顶：递减
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_5 {
public:
    int largestRectangleArea(vector<int>& heights) {
        if(heights.size()==0) return 0;
        heights.insert(heights.begin(),0);  // 数组头部加入0：避免降序时，找不到开头的left
        heights.push_back(0);       // 数组尾部加入0：避免数组恰好升序排列时，一直不进入从栈中弹出元素的
        stack<int>st;
        st.push(0);     // 首个下标加入栈
        
        int ans=0;
        for(int i=1;i<heights.size();i++){
            if(heights[i]>heights[st.top()]){  // 当前元素 > 栈顶元素：入栈
                st.push(i);
            }else if(heights[i]==heights[st.top()]){
                st.pop();
                st.push(i);
            }else{
                while(!st.empty() && heights[i]<heights[st.top()]){
                    // 不断从栈中移除大于当前高度的柱子，目标是：找到第一个高度小于当前柱子的下标
                    int mid=st.top();
                    st.pop();
                    if(!st.empty()){
                        int h=heights[mid];
                        int w=i-st.top()-1;
                        ans=max(ans,h*w);
                    }
                }
                st.push(i);
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
