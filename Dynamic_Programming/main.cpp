//
//  main.cpp
//  Dynamic_program
//
//  Created by 文柳懿 on 2025/4/18.
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// 1. T509.斐波那契数列
/* 斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列 。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：
 F(0) = 0，F(1) = 1
 F(n) = F(n - 1) + F(n - 2)，其中 n > 1
 给定 n ，请计算 F(n) 。*/

// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_1 {
public:
    int fib(int n) {
        if(n<2) return n;
        int first=0,second=0,cur=1;
        for(int i=2;i<=n;i++){
            first=second;
            second=cur;
            cur=first+second;
        }
        return cur;
    }
};

// 2. T70.爬楼梯
/* 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？*/
// 递推：dp[i]=dp[i-1]+dp[i-2]
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_2 {
public:
    int climbStairs(int n) {
        if(n<=1) return n;
        vector<int>dp(n+1);     // dp[0...n]
        dp[1]=1;dp[2]=2;
        for(int i=3;i<=n;i++){
            dp[i]=dp[i-1]+dp[i-2];
        }
        return dp[n];
    }
};

// 3. T746.使用最小花费爬楼梯
/* 给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。
 你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
 请你计算并返回达到楼梯顶部的最低花费。*/

// dp[i]表示：到达阶梯i的最小花费
// 初始化：dp[0]=dp[1]=0
// 状态转移：dp[i]=min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2])
// 时间复杂度：O(n)；空间复杂度：O(n)，可优化为O(1)
class Solution_3 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n=cost.size();
        vector<int>dp(n+1);
        dp[0]=dp[1]=0;
        for(int i=2;i<=n;i++){
            dp[i]=min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]);
        }
        return dp[n];
    }
};

// 4. T62.不同路径
/* 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
 问总共有多少条不同的路径？ */

// 法一：动态规划
// dp[i][j]:到达当前位置的路径数
class Solution_4_1 {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m,vector<int>(n));
        for(int i=0;i<m;i++){
            dp[i][0]=1;
        }
        for(int j=0;j<n;j++){
            dp[0][j]=1;
        }
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

// 法二：数论
// 一共m+n-2步，向下m-1步.结果为：C_(m+n-2)^(m-1)或C_(m+n-2)^(n-1)
// 时间复杂度：O(m)，可降低至O(min(m,n))；空间复杂度：O(1)
class Solution_4_2 {
public:
    int uniquePaths(int m, int n) {
        long long numerator=1;      // 分子
        int i=m+n-2,j=m-1;      // j为分母
        
        for(;i>=n;i--){
            numerator*=i;
            while(j!=0 && numerator%j==0){
                numerator/=j;
                j--;
            }
        }
        return numerator;
    }
};

// 5. T63.不同路径II
/* 给定一个 m x n 的整数数组 grid。一个机器人初始位于 左上角（即 grid[0][0]）。机器人尝试移动到 右下角（即 grid[m - 1][n - 1]）。机器人每次只能向下或者向右移动一步。
 网格中的障碍物和空位置分别用 1 和 0 来表示。机器人的移动路径中不能包含 任何 有障碍物的方格。
 返回机器人能够到达右下角的不同路径数量。
 测试用例保证答案小于等于 2 * 109。*/

// 与上一题的不同：将障碍物处dp对应值设为0

// 时间复杂度：O(m*n)；空间复杂度：O(m*n)
class Solution_5 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size(),n=obstacleGrid[0].size();
        if(obstacleGrid[0][0]==1 || obstacleGrid[m-1][n-1]==1){
            return 0;
        }
        vector<vector<int>>dp(m,vector<int>(n,0));
        // 1. 初始化
        for(int i=0;i<m && obstacleGrid[i][0]==0;i++){
            dp[i][0]=1;
        }
        for(int j=0;j<n && obstacleGrid[0][j]==0;j++){
            dp[0][j]=1;
        }
        // 2. 状态转移
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                if(obstacleGrid[i][j]==1) dp[i][j]=0;
                else dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

// 6. T343.整数拆分
/* 给定一个正整数 n ，将其拆分为 k 个 正整数 的和（ k >= 2 ），并使这些整数的乘积最大化。
 返回 你可以获得的最大乘积 。*/
// 1. dp数组：dp[i]为分拆数字i，获得的最大乘积
// 2. 状态转移：dp[i] = max(dp[i], max((i-j)*j, dp[i-j]*j));
//  即拆分为：i*1 或 (i-j)*j, i-j可继续拆分
// 3. 初始化：

// 时间复杂度：O(n^2)；空间复杂度：O(n)
class Solution_6 {
public:
    int integerBreak(int n) {
        vector<int>dp(n+1);
        dp[2]=1;
        for(int i=3;i<=n;i++){
            for(int j=1;j<=i/2;j++){
                dp[i]=max(dp[i],max((i-j)*j, dp[i-j]*j));
            }
        }
        return dp[n];
    }
};

// 数学解释：尽量拆分为多个3

// 7. T96.不同的二叉搜索树
// 给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。
// dp数组：1～i为节点组成的二叉搜索树个数
// 状态转移：dp[i]=sum(dp[j为头节点左子树节点数量]*dp[j为头节点右子树节点数量])

// 时间复杂度：O(n^2)；空间复杂度：O(n)
class Solution_7 {
public:
    int numTrees(int n) {
        vector<int>dp(n+1,0);
        dp[0]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++){
                dp[i]+=dp[j-1]*dp[i-j];
            }
        }
        return dp[n];
    }
};

// 8. T118.杨辉三角
/* 给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
 在「杨辉三角」中，每个数是它左上方和右上方的数的和。*/
// 时间复杂度：O(numRows^2)；空间复杂度：O(1)
class Solution_8 {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>res(numRows);    // 一共numRows行
        for(int i=0;i<numRows;i++){
            res[i].resize(i+1);     // 第i行长度为：i+1
            res[i][0]=res[i][i]=1;
            for(int j=1;j<i;j++){
                res[i][j]=res[i-1][j-1]+res[i-1][j];
            }
        }
        return res;
    }
};

// 9. T198.打家劫舍
/*你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。*/

// dp[i]：下标0~i，可偷窃的最大金额
// 状态转移：dp[i]=max(dp[i-1],dp[i-2]+nums[i]); 即前一个房间偷/不偷
// 初始化：dp[0]=0, dp[1]=max(nums[0], nums[1]).

// 时间复杂度：O(n)；空间复杂度：O(n).
class Solution_9 {
public:
    int rob(vector<int>& nums) {
        if(nums.size()==0) return 0;
        if(nums.size()==1) return nums[0];
        vector<int>dp(nums.size());
        dp[0]=nums[0];
        dp[1]=max(nums[0],nums[1]);
        for(int i=2;i<nums.size();i++){
            dp[i]=max(dp[i-1],dp[i-2]+nums[i]);
        }
        return dp[nums.size()-1];
    }
};

// 10. T213.打家劫舍II
/* 你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。
 
 给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。*/

// 注意：成环考虑三种情况：
// 1. 不包含收尾元素；2. 包含首元素，不含尾元素；3. 包含尾元素，不含首元素
class Solution_10 {
public:
    int robRange(vector<int>& nums, int start, int end){
        if(start==end) return nums[start];
        vector<int>dp(nums.size());
        dp[start]=nums[start];
        dp[start+1]=max(nums[start],nums[start+1]);
        for(int i=2;i<=end;i++){
            dp[i]=max(dp[i-2]+nums[i],dp[i-1]);
        }
        return dp[end];
    }
    
    int rob(vector<int>& nums) {
        if(nums.size()==0) return 0;
        if(nums.size()==1) return nums[0];
        int res1=robRange(nums, 0, nums.size()-2);
        int res2=robRange(nums, 1, nums.size()-1);
        return max(res1,res2);
    }
};

// 11. T337.打家劫舍III
/* 小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。
 除了 root 之外，每栋房子有且只有一个“父“房子与之相连。
 一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。如果 两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

 给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。*/

struct TreeNode{
    int val;
    TreeNode *left,*right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
    TreeNode(int x, TreeNode *left, TreeNode *right):val(x),left(left),right(right){}
};
// 法一：记忆化递推
// 时间复杂度：O(n)；空间复杂度：O(logn)
class Solution_11_1 {
public:
    unordered_map<TreeNode *, int>umap;
    int rob(TreeNode* root) {
        if(root==nullptr) return 0;
        if(root->left==nullptr && root->right==nullptr) return root->val;
        if(umap[root]) return umap[root];       // 直接返回当前节点对应的值
        
        // 偷当前节点
        int val1=root->val;
        if(root->left) val1+=rob(root->left->left)+rob(root->left->right);
        if(root->right) val1+=rob(root->right->left)+rob(root->right->right);
        
        // 不偷当前节点
        int val2=rob(root->left)+rob(root->right);
        
        umap[root]=max(val1,val2);
        return max(val1,val2);
    }
};

// 法二：动态规划
// 1. dp数组：包含2个值：偷、不偷当前节点的最大价值
// 2. 遍历顺序：后序遍历
// 时间复杂度：O(n)；空间复杂度：O(logn)
class Solution_11_2 {
public:
    vector<int>robTree(TreeNode *cur){      // 返回值为数组：下标0:偷；下标1：不偷
        if(cur==nullptr) return vector<int>{0,0};
        vector<int>left=robTree(cur->left);
        vector<int>right=robTree(cur->right);
        // 偷cur节点
        int val0=cur->val+left[1]+right[1];
        // 不偷cur节点
        int val1=max(left[0],left[1])+max(right[0],right[1]);
        return {val0,val1};
    }
    
    int rob(TreeNode* root) {
        vector<int>res=robTree(root);
        return max(res[0],res[1]);
    }
};

// 12. T279.完全平方数
/* 给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。*/
// dp[i]:和为i的完全平方数的最少数量
// 状态转移：dp[i]=min(1+f[i-j^2], j=1,...,sqrt(i).

// 时间复杂度：O(n*sqrt(n))；空间复杂度：O(n).
class Solution_12 {
public:
    int numSquares(int n) {
        vector<int>dp(n+1);
        for(int i=1;i<=n;i++){
            dp[i]=INT_MAX;
            for(int j=1;j*j<=i;j++){
                dp[i]=min(dp[i],1+dp[i-j*j]);
            }
        }
        return dp[n];
    }
};

// 13. T416.分割等和子集
/* 给你一个 只包含正整数 的 非空 数组 nums 。
 请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。*/

// 集合中每个元素只能使用1次：0-1背包问题
// dp[j]:容量为j的背包中，所背物品的最大价值；
// 状态转移：dp[j]=max(dp[j],dp[j-weight[i]]+value[i]);这里，物品i的重量、价值均为nums[i]；
// 初始化：总和不大于20000，最大价值为其中的一半，初始化为：vector<int> dp(10001, 0);
// 遍历顺序：1. 外层循环遍历每个物品； 2. 内层循环遍历背包，从最大空间减少到当前物品所占空间

// 时间复杂度：O(n^2)；空间复杂度：O(n)
class Solution_13 {
public:
    bool canPartition(vector<int>& nums) {
        int sum=0;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
        }
        if(sum%2) return false;
        int target=sum/2;
        // 0-1背包
        vector<int>dp(10001,0);
        for(int i=0;i<nums.size();i++){
            for(int j=target;j>=nums[i];j--){
                dp[j]=max(dp[j],dp[j-nums[i]]+nums[i]);
            }
        }
        if(dp[target]==target) return true;
        else return false;
    }
};

// 14. T322.零钱兑换
/* 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
 你可以认为每种硬币的数量是无限的。*/

// dp[j]：凑足金额j，所需的最少硬币个数
// 状态转移：dp[j]=min(dp[j-coins[i]]+1,dp[j]);
// 初始化：dp[0]=0
class Solution_14 {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int>dp(amount+1,INT_MAX);
        dp[0]=0;
        for(int i=0;i<coins.size();i++){
            for(int j=coins[i];j<=amount;j++){
                if(dp[j-coins[i]]!=INT_MAX){
                    dp[j]=min(dp[j],dp[j-coins[i]]+1);
                }
            }
        }
        if(dp[amount]==INT_MAX) return -1;
        return dp[amount];
    }
};

// 15. T518.零钱兑换II
/* 给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。
 请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。
 假设每一种面额的硬币有无限个。
 题目数据保证结果符合 32 位带符号整数。*/

// 法一：二维dp数组
// dp[i][j]: 使用下标0~i的coins[i]，能够凑满容量为j的背包，有dp[i][j]种方法；
// 状态转移（完全背包）：dp[i][j]=max(dp[i-1][j], dp[i][j-weight[i]]+value[i]);
// 本题中，组合数：dp[i][j]=dp[i-1][j]（不装第i个物品）+dp[i][j-weight[i]]（装入第i个物品）
class Solution_15_1 {
public:
    int change(int amount, vector<int>& coins) {
        vector<vector<uint64_t>>dp(coins.size(),vector<uint64_t>(amount+1,0));
        // 初始化i=0的行
        for(int j=0;j<=amount;j++){     // 当前金额为：coins[i]的整数倍
            if(j%coins[0]==0) dp[0][j]=1;
        }
        // 初始化j=0的列
        for(int i=0;i<coins.size();i++){    // 一种方案：啥也不放
            dp[i][0]=1;
        }
        for(int i=1;i<coins.size();i++){    // 行：遍历物品
            for(int j=0;j<=amount;j++){     // 列：遍历背包容量
                if(j<coins[i]) dp[i][j]=dp[i-1][j];
                else dp[i][j]=dp[i-1][j]+dp[i][j-coins[i]];
            }
        }
        return dp[coins.size()-1][amount];
    }
};

// 法二：一维dp数组
// dp[j]: 凑成总金额j的货币组合数为dp[j]
// 时间复杂度：O(m*n)；空间复杂度：O(m). m为amount，n为coins的长度
class Solution_15_2 {
public:
    int change(int amount, vector<int>& coins) {
        vector<uint64_t>dp(amount+1,0);
        dp[0]=1;
        for(int i=0;i<coins.size();i++){        // 行：遍历物品
            for(int j=coins[i];j<=amount;j++){  // 列：遍历背包容量
                if(dp[j]+dp[j-coins[i]]<INT_MAX){
                    dp[j]=dp[j]+dp[j-coins[i]];
                }
            }
        }
        return dp[amount];
    }
};

// 16. T139.单词拆分
/* 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。
 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。*/

// 法一：回溯
// 优化：记忆化递归，使用memory数组保存每次计算的以startIndex起始的计算结果
// 时间复杂度：O(2^n)
class Solution_16_1 {
public:
    bool backTrack(const string &s, const unordered_set<string>& wordSet,
                   vector<bool>&memory,int startIndex){
        if(startIndex>=s.size()){
            return true;
        }
        if(!memory[startIndex]) return memory[startIndex];
        for(int i=startIndex;i<s.size();i++){
            string word=s.substr(startIndex,i-startIndex+1);
            if(wordSet.find(word)!=wordSet.end() && backTrack(s,wordSet,memory,i+1)){
                return true;
            }
        }
        memory[startIndex]=false;
        return false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>wordSet(wordDict.begin(),wordDict.end());
        vector<bool>memory(s.size(),true);
        return backTrack(s,wordSet,memory,0);
    }
};

// 法二：动态规划
// dp[i]=true:字符串[0,i]可以使用字典中单词拼接而成
// 若dp[j]=true，且[j,i]区间的字符串出现在字典中，则：dp[i]=true(j<i)
// 时间复杂度：O(n^3)，因为substr返回子串的副本是O(n)的复杂度（这里的n是substring的长度）
// 空间复杂度：O(n)
class Solution_16_2 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>wordSet(wordDict.begin(),wordDict.end());
        vector<bool>dp(s.size()+1,false);
        dp[0]=true;
        
        for(int i=1;i<=s.size();i++){       // 遍历背包容量
            for(int j=0;j<i;j++){           // 遍历物品
                string word=s.substr(j,i-j);    // word区间：[j,i)
                if(dp[j] && wordSet.find(word)!=wordSet.end()){
                    dp[i]=true;
                }
            }
        }
        return dp[s.size()];
    }
};

// 17. T52.乘积最大子数组
/* 给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
 测试用例的答案是一个 32-位 整数。*/

// 法一：动态规划
// maxDp[i]: 以第i个元素结尾的最大子数组乘积；minDp[i]: 以第i个元素结尾的最小子数组乘积
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_17_1 {
public:
    int maxProduct(vector<int>& nums) {
        vector<long>maxDp(nums.size(),0), minDp(nums.size(),0);
        maxDp[0]=minDp[0]=nums[0];
        
        for(int i=1;i<nums.size();i++){
            maxDp[i]=max((long)nums[i],max(maxDp[i-1]*nums[i],minDp[i-1]*nums[i]));
            minDp[i]=min((long)nums[i],min(maxDp[i-1]*nums[i],minDp[i-1]*nums[i]));
            if(minDp[i]<INT_MIN){
                minDp[i]=nums[i];
            }
        }
        return *max_element(maxDp.begin(),maxDp.end());
    }
};

// 法二：动态规划（优化空间）
// 第i个状态，只与第i-1个状态相关：maxF,minF记录以当前元素为结尾的最大/最小乘积
// 空间复杂度：O(1)
class Solution_17_2 {
public:
    int maxProduct(vector<int>& nums) {
        long maxF=nums[0],minF=nums[0],ans=nums[0];
        for(int i=1;i<nums.size();i++){
            long pre_maxF=maxF, pre_minF=minF;
            maxF=max((long)nums[i],max(pre_maxF*nums[i],pre_minF*nums[i]));
            minF=min((long)nums[i],min(pre_maxF*nums[i],pre_minF*nums[i]));
            if(minF<INT_MIN){
                minF=nums[i];
            }
            ans=max(maxF,ans);
        }
        return ans;
    }
};

// 18. 最长递增子序列
/* 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。*/

// dp[i]: i之前包括i的，以nums[i]结尾的最长递增子序列的长度
// 状态转移：dp[i]=max(dp[i], dp[j]+1), 其中：nums[j]<nums[i]且j<i
// 初始化：dp[i]=1

// 时间复杂度：O(n^2)；空间复杂度：O(n)
class Solution_18 {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.size()<=1) return nums.size();
        vector<int>dp(nums.size(),1);
        int res=0;
        for(int i=1;i<nums.size();i++){
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i]) dp[i]=max(dp[i],dp[j]+1);
            }
            if(dp[i]>res) res=dp[i];
        }
        return res;
    }
};

// 19. T32.最长有效括号
/* 给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。*/

// 法一：动态规划
// dp[i]:以下标i字符结尾的最长有效括号的长度
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_19_1 {
public:
    int longestValidParentheses(string s) {
        int res=0,n=s.length();
        vector<int>dp(n,0);
        for(int i=1;i<n;i++){
            if(s[i]==')'){
                if(s[i-1]=='('){
                    dp[i]=(i>=2?dp[i-2]:0)+2;   // 前一个字符为'(':dp[i]=dp[i-2]+2
                }else{  // 前一个字符为')',字符串形如"...))"
                    if(i-dp[i-1]>0 && s[i-dp[i-1]-1]=='('){
                        // 刨除dp[i-1]的部分，下标i-dp[i-1]-1和i分别为'(',')'，加上这两个
                        dp[i]=dp[i-1]+((i-dp[i-1])>=2 ? dp[i-dp[i-1]-2]:0)+2;
                    }
                }
            }
            res=max(res,dp[i]);
        }
        return res;
    }
};

// 法二：栈
// '('：下标压入栈；')'：弹出栈顶元素
// 保持栈底元素为：最后一个未匹配的右括号下标
class Solution_19_2 {
public:
    int longestValidParentheses(string s) {
        int res=0;
        stack<int>stk;
        stk.push(-1);
        
        for(int i=0;i<s.length();i++){
            if(s[i]=='('){
                stk.push(i);
            }else{
                stk.pop();
                if(stk.empty()) {
                    // 1. 栈为空：当前右括号尚未匹配
                    stk.push(i);
                }
                else{
                    res=max(res,i-stk.top());
                }
            }
        }
        return res;
    }
};

// 20. T64.最小路径和
/* 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 说明：每次只能向下或者向右移动一步。*/

// dp[i][j]:(0,0)到(i,j)的最小路径和
// 时间复杂度：O(mn)；空间复杂度：O(mn)
class Solution_20_1 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.size()==0 || grid[0].size()==0){
            return 0;
        }
        int rows=grid.size(),cols=grid[0].size();
        vector<vector<int>>dp(rows,vector<int>(cols,0));
        dp[0][0]=grid[0][0];
        
        // 状态转移：3种情况
        for(int i=1;i<rows;i++){
            dp[i][0]=dp[i-1][0]+grid[i][0];
        }
        for(int j=1;j<cols;j++){
            dp[0][j]=dp[0][j-1]+grid[0][j];
        }
        for(int i=1;i<rows;i++){
            for(int j=1;j<cols;j++){
                dp[i][j]=min(dp[i-1][j],dp[i][j-1])+grid[i][j];
            }
        }
        return dp[rows-1][cols-1];
    }
};

// 空间复杂度优化:
// dp[j]:到达横坐标为j的点的最小路径和
class Solution_20_2 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.size()==0 || grid[0].size()==0){
            return 0;
        }
        int rows=grid.size(),cols=grid[0].size();
        vector<int>dp(cols,0);
        
        // 初始化：第一行
        dp[0]=grid[0][0];
        for(int j=1;j<cols;j++){
            dp[j]=dp[j-1]+grid[0][j];
        }
        
        for(int i=1;i<rows;i++){
            dp[0]+=grid[i][0];      // 第一列只能从上面来
            for(int j=1;j<cols;j++){
                dp[j]=min(dp[j],dp[j-1])+grid[i][j];
            }
        }
        return dp[cols-1];
    }
};

// 21. T5.最长回文子串
/* 给你一个字符串 s，找到 s 中最长的 回文 子串。*/
// dp[i][j]:下标区间为[i,j]的子串是否是回文串
class Solution_21 {
public:
    string longestPalindrome(string s) {
        int n=s.length(),res_i=0,res_j=0,resLen=1;
        vector<vector<bool>>dp(n,vector<bool>(n,false));
        
        for(int i=n-1;i>=0;i--){
            // 需要倒序计算, 保证在i行时, i+1行已经计算好了
            for(int j=i;j<n;j++){
                if(i==j) dp[i][j]=true;
                else if(j-i==1){
                    dp[i][j]=(s[i]==s[j]);
                }else{
                    dp[i][j]=(s[i]==s[j] && dp[i+1][j-1]);
                    if(dp[i][j] && j-i+1>resLen){
                        resLen=j-i+1;
                        res_i=i;res_j=j;
                    }
                }
            }
        }
        return s.substr(res_i,resLen);
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
