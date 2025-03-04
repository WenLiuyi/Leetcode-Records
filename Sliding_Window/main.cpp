//
//  main.cpp
//  Sliding_Window
//
//  Created by 文柳懿 on 2025/3/4.
//

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

// 1. T209.长度最小的子数组
/* 给定一个含有 n 个正整数的数组和一个正整数 target 。
 找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。*/
// 法一：暴力法：超出时间限制
// 时间复杂度：O(n^2)；空间复杂度：O(1)
class Solution_9 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n=nums.size();
        if(n==0) return 0;
        int ans=INT_MAX;
        for(int i=0;i<n;i++){
            int sum=0;
            for(int j=i;j<n;j++){
                sum+=nums[j];
                if(sum>=target) {
                    ans=min(ans,j-i+1);
                    break;
                }
            }
        }
        return ans==INT_MAX?0:ans;
    }
};

// 法二：滑动窗口
// 窗口：满足其和>=s的长度最小的连续子数组
// 窗口起始位置移动：如果当前窗口的值大于等于s了，窗口向前移动；
// 窗口的结束位置移动：窗口的结束位置就是遍历数组的指针，也就是for循环里的索引

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
