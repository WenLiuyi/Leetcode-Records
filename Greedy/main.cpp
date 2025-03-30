//
//  main.cpp
//  Greedy
//
//  Created by 文柳懿 on 2025/3/30.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 1. T455.分发饼干
/* 假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
 
 对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是满足尽可能多的孩子，并输出这个最大数值。*/

// 思路：对饼干和小河胃口的数组，分别降序排序，从高到低逐个满足
// 时间复杂度：O(n*logn)；空间复杂度：O(1)
class Solution_1 {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(),g.end(),greater<int>());
        sort(s.begin(),s.end(),greater<int>());
        int ans=0,j=0;
        for(int i=0;i<g.size() && j<s.size();i++){
            if(g[i]<=s[j]){
                ans++;j++;
            }
        }
        return ans;
    }
};

// 2. T376.摆动序列
/* 如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 摆动序列 。第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。
 
 例如， [1, 7, 4, 9, 2, 5] 是一个 摆动序列 ，因为差值 (6, -3, 5, -7, 3) 是正负交替出现的。

 相反，[1, 4, 7, 2, 5] 和 [1, 7, 4, 5, 5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。
 子序列 可以通过从原始序列中删除一些（也可以不删除）元素来获得，剩下的元素保持其原始顺序。

 给你一个整数数组 nums ，返回 nums 中作为 摆动序列 的 最长子序列的长度 。*/
// 思路一：贪心算法，计算峰值个数；考虑平坡情况：单调中间有平坡，上下中间有平坡
// 时间复杂度：O(n);空间复杂度：O(1)
class Solution_2_1 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n=nums.size();
        if(n==1 || (n==2 && nums[0]!=nums[1])) return n;
        int ans=1,pre=0;    // 默认ans=1

        for(int i=1;i<n;i++){
            int cur=nums[i]-nums[i-1];
            if((pre<=0 && cur>0) || (pre>=0 && cur<0)){
                ans++;
                pre=cur;
            }
        }
        return ans;
    }
};

// 思路二：动态规划
/* 对于我们当前考虑的这个数，要么是作为山峰（即 nums[i] > nums[i-1]），要么是作为山谷（即 nums[i] < nums[i - 1]）。
 设 dp 状态dp[i][0]，表示考虑前 i 个数，第 i 个数作为山峰的摆动子序列的最长长度；
 设 dp 状态dp[i][1]，表示考虑前 i 个数，第 i 个数作为山谷的摆动子序列的最长长度.
 
 dp[i][0] = max(dp[i][0], dp[j][1] + 1)，其中0 < j < i且nums[j] < nums[i];
 dp[i][1] = max(dp[i][1], dp[j][0] + 1)，其中0 < j < i且nums[j] > nums[i]. */
// 时间复杂度：O(n^2);空间复杂度：O(n)
class Solution_2_2 {
private:
    int dp[1005][2];
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n=nums.size();
        if(n==1 || (n==2 && nums[0]!=nums[1])) return n;
        
        memset(dp,0,sizeof(dp));
        dp[0][0]=dp[0][1]=1;
        for(int i=1;i<n;i++){
            dp[i][0]=dp[i][1]=1;
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i]) dp[i][0]=max(dp[i][0],dp[j][1]+1);
            }
            for(int j=0;j<i;j++){
                if(nums[j]>nums[i]) dp[i][1]=max(dp[i][1],dp[j][0]+1);
            }
        }
        return max(dp[nums.size()-1][0],dp[nums.size()-1][1]);
    }
};

// 3. T53.最大子序和
/* 给你一个整数数组 nums，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 子数组 是数组中的一个连续部分。*/
// 贪心算法：不断调整起始位置，若当前累计值ans<0，直接抛弃
class Solution_3 {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        int ans=nums[0],res=nums[0];
        for(int i=1;i<nums.size();i++){
            if(ans<0) ans=nums[i];
            else ans+=nums[i];
            res=max(ans,res);
        }
        return res;
    }
};

// 4. T122.买卖股票的最佳时机II
/* 给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
 在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。返回 你能获得的 最大 利润 。*/
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_4 {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()==1) return 0;
        
        int maxProfit=0,pre=prices[0],ans=0;
        for(int i=1;i<prices.size();i++){
            if(prices[i]>=prices[i-1]){     // 股票持续上涨：继续持有，更新maxProfit
                maxProfit=max(maxProfit,prices[i]-pre);
            }else{      // 股票开始下跌：立即卖出，买入当前价位
                ans+=maxProfit;
                pre=prices[i];maxProfit=0;
            }
        }
        ans+=maxProfit;
        return ans;
    }
};

// 5. T55.跳跃游戏
/* 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标。数组中的每个元素代表你在该位置可以跳跃的最大长度。
 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。*/
// 贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围）
// 整体最优解：最后得到整体最大覆盖范围，看是否能到终点。

// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_5 {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size()==1) return true;
        
        int cover=0;
        for(int i=0;i<=cover;i++){
            cover=max(cover,i+nums[i]);
            if(cover>=nums.size()-1) return true;
        }
        return false;
    }
};

// 6. T45.跳跃游戏II
/* 给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。
 每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处:
 (1) 0 <= j <= nums[i]
 (2) i + j < n
 返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。*/

// 思路：以最小的步数，最大程度增加覆盖范围
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_6 {
public:
    int jump(vector<int>& nums) {
        if(nums.size()==1) return 0;
        
        int ans=0;
        int curDis=0,nextDis=0;
        
        for(int i=0;i<nums.size();i++){
            nextDis=max(nextDis,nums[i]+i);     // 更新下一步覆盖的最远下标
            if(i==curDis){      // 必须往下走一步
                curDis=nextDis;
                ans++;
                if(nextDis>=nums.size()-1) break;
            }
        }
        return ans;
    }
};

// 7. T1306.跳跃游戏III
/* 这里有一个非负整数数组 arr，你最开始位于该数组的起始下标 start 处。当你位于下标 i 处时，你可以跳到 i + arr[i] 或者 i - arr[i]。
 请你判断自己是否能够跳到对应元素值为 0 的 任一 下标处。
 注意，不管是什么情况下，你都无法跳到数组之外。*/

// 思路：使用BFS
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_7 {
public:
    bool canReach(vector<int>& arr, int start) {
        if(arr[start]==0) return true;
        queue<int>q;
        q.push(start);
        
        int n=arr.size();
        vector<bool>visited(n,false);
        visited[start]=true;
        
        while(!q.empty()){
            int cur=q.front();q.pop();      // 队首弹出元素
            if(cur+arr[cur]<n && !visited[cur+arr[cur]]){
                if(arr[cur+arr[cur]]==0){
                    return true;
                }
                q.push(cur+arr[cur]);
                visited[cur+arr[cur]]=true;
            }
            if(cur-arr[cur]>=0 && !visited[cur-arr[cur]]){
                if(arr[cur-arr[cur]]==0){
                    return true;
                }
                q.push(cur-arr[cur]);
                visited[cur-arr[cur]]=true;
            }
        }
        return false;
    }
};

// 8. T1005.K 次取反后最大化的数组和
/* 给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：
 选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
 重复这个过程恰好 k 次。可以多次选择同一个下标 i 。
 以这种方式修改数组后，返回数组 可能的最大和 。*/

// 第一次贪心：让绝对值大的负数变为正数；
// 第二次贪心：如果将负数都转变为正数了，K依然大于0，只找数值最小的正整数进行反转
// 写法一：
class Solution_8_1 {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int sum=0,cnt=0;
        for(int i=0;i<nums.size();i++){
            if(cnt>=k){
                sum+=nums[i];
            }else if(nums[i]<0){
                sum+=(-nums[i]);cnt++;
            }else if(nums[i]==0){
                cnt=k;
            }else{
                if((k-cnt)%2){
                    if(i>0 && -nums[i-1]<=nums[i]){
                        sum-=2*(-nums[i-1]);sum+=nums[i];cnt=k;
                    }else{
                        sum+=-nums[i];cnt=k;
                    }
                }else{
                    sum+=nums[i];cnt=k;
                }
            }
        }
        if(cnt<k){      // 数组中所有数均为负数
            if((k-cnt)%2){
                sum-=2*(-nums[nums.size()-1]);
            }
        }
        return sum;
    }
};

// 写法二：将数组按照绝对值大小从大到小排序
// 时间复杂度：O(n*logn)；空间复杂度：O(1)
class Solution_8_2 {
public:
    static bool cmp(int a, int b){
        return abs(a)>abs(b);
    }
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end(),cmp);
        for(int i=0;i<nums.size();i++){
            if(nums[i]<0 && k>0){
                nums[i]*=-1;k--;
            }
        }
        if(k%2) nums[nums.size()-1]*=-1;
        int sum=0;
        for(int elem:nums) sum+=elem;
        return sum;
    }
};

// 9. T134.加油站
/* 在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
 你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
 给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。*/
class Solution_9 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
