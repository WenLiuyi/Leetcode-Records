//
//  main.cpp
//  Interval
//
//  Created by 文柳懿 on 2025/3/12.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 1. T228.汇总区间
/* 给定一个  无重复元素 的 有序 整数数组 nums 。
 返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。
 列表中的每个区间范围 [a,b] 应该按如下格式输出：
 "a->b" ，如果 a != b
 "a" ，如果 a == b */
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_1 {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string>ret;
        int n=nums.size();
        if(n==0) return ret;
        
        int i=0;
        while(i<n){
            int left=nums[i];
            i++;
            while(i<n && nums[i]==nums[i-1]+1) i++;
            int right=nums[i-1];
            
            if(left==right){
                ret.push_back(to_string(left));
            }else{
                ret.push_back(to_string(left)+"->"+to_string(right));
            }
        }
        return ret;
    }
};

// 2. T56.合并区间:以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
// 法一：排序：对区间的左端点升序排序
// 时间复杂度：O(n*logn)，排序时间开销；O(logn)，排序所需空间复杂度
class Solution_2 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ret;
        int n=intervals.size();
        if(n==0) return ret;
        
        sort(intervals.begin(),intervals.end());
        for(int i=0;i<n;i++){
            if(ret.size()==0 || ret.back()[1]<intervals[i][0]){
                // 1. ret中最后一个区间的右端点 < 当前区间的左端点：新增一个区间
                ret.push_back({intervals[i][0],intervals[i][1]});
            }else{
                // 2. ret最后一个区间与当前区间合并
                ret.back()[1]=max(ret.back()[1],intervals[i][1]);
            }
        }
        return ret;
    }
};

// 3. T57.插入区间
/*给你一个 无重叠的 ，按照区间起始端点排序的区间列表 intervals，其中 intervals[i] = [starti, endi] 表示第 i 个区间的开始和结束，并且 intervals 按照 starti 升序排列。同样给定一个区间 newInterval = [start, end] 表示另一个区间的开始和结束。
 在 intervals 中插入区间 newInterval，使得 intervals 依然按照 starti 升序排列，且区间之间不重叠（如果有必要的话，可以合并区间）。
 返回插入之后的 intervals。
 注意 你不需要原地修改 intervals。你可以创建一个新数组然后返回它。*/
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_3 {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ret;
        int left=newInterval[0],right=newInterval[1];
        bool placed=false;  // newInterval是否已经完成合并
        
        for(const auto &interval: intervals){   // 传入interval的常量引用（需要新建区间，不改变原有interval）
            if(right<interval[0]){      // [left,right]<[li,ri]
                if(!placed){
                    ret.push_back({left,right});   // 加入新区间的时机：right<当前区间左端点，不再有新的合并可能性
                    placed=true;
                }
                ret.push_back(interval);
                
            }else if(interval[1]<left){ // [li,ri]<[left,right]
                ret.push_back(interval);
            }else{
                left=min(left,interval[0]);     // left,right记录：当前待合并区间
                right=max(right,interval[1]);
            }
        }
        if(!placed) ret.push_back({left,right});
        return ret;
    }
};

// 4. T452.用最少数量的箭引爆气球
/* 有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，其中points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。
 
 一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。

 给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。*/

// 思路：求区间的交集；射出位置，当前可引爆的所有区间中，右边界的最小值
// 时间复杂度（排序）：O(n*logn)；空间复杂度：O(n*logn)
class Solution_4 {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.size()==0) return 0;
        sort(points.begin(),points.end(),[](const vector<int>&p1,const vector<int>&p2){
            return p1[1]<p2[1];     // 按右边界升序排序
        });
        int pos=points[0][1],ans=1;     // points不为空：至少需要一支箭
        for(const vector<int> &ballon:points){
            if(ballon[0]>pos){      // 当前区间左端点超过pos，不能引爆：此时开一个新的引爆点
                pos=ballon[1];
                ans++;
            }
        }
        return ans;
    }
};

// 5. T435.无重叠区间
/* 给定一个区间的集合 intervals ，其中 intervals[i] = [starti, endi] 。返回 需要移除区间的最小数量，使剩余区间互不重叠 。
 注意 只在一点上接触的区间是 不重叠的。例如 [1, 2] 和 [2, 3] 是不重叠的。*/
// 思路：与"用最少数量的箭引爆气球"非常相像，弓箭的数量等于非交叉区间的数量（只要将射爆气球的判断条件加一个等号）
class Solution_5{
public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals){
        if(intervals.size()==0) return 0;
        sort(intervals.begin(), intervals.end(), [](const vector<int>&p1, const vector<int>&p2){
            return p1[1]<p2[1];     // 按右边界升序排序
        });
        int pos=intervals[0][1],ans=1;
        for(const vector<int> &interval:intervals){
            if(interval[0]>=pos){    // 当前区间左端点超过pos，新开一个非交叉区间
                pos=interval[1];
                ans++;
            }
        }
        return intervals.size()-ans;
    }
};

// 6. T763.划分字母区间
/* 字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。返回一个表示每个字符串片段的长度的列表。
 示例：
 输入：S = "ababcbacadefegdehijhklij"
 输出：[9,7,8] 解释： 划分结果为 "ababcbaca", "defegde", "hijhklij"。 每个字母最多出现在一个片段中。 像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。
 提示：
 S的长度在[1, 500]之间。
 S只包含小写字母 'a' 到 'z' 。*/

// 思路一：如何把同一字母都圈在同一个区间内呢？寻找每一个字母最后出现的下标位置
// 贪心的思想：从头开始，寻找每个片段可能的最小结束下标
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_6_1{
private:
    unordered_map<char, int>map;    // 记录每一个字母最后出现的下标位置
public:
    vector<int> partitionLabels(string s){
        int n=s.length();
        for(int i=0;i<n;i++){
            map[s[i]]=i;
        }
        vector<int>res;
        int left=0, right=0;
        for(int i=0;i<n;i++){
            right=max(right, map[s[i]]);
            if(i==right){   // 当前片段的右边界
                res.push_back(right-left+1);
                left=i+1;
            }
        }
        return res;
    }
};

// 思路二：转化为非交叉区间的问题：统计每个字母出现的左右边界。然后将所有区间划分为互不重叠的组
class Solution_6_2{
private:
    vector<int> res;
    vector<vector<int>> intervals;
    void countLabels(string s){  // 统计每个字母出现的区间
        vector<vector<int>> map(26, vector<int>(2, INT_MIN));
        int n=s.length();
        for(int i=0;i<n;i++){
            if(map[s[i]-'a'][0]==INT_MIN){
                map[s[i]-'a'][0]=i;
            }
            map[s[i]-'a'][1]=i;
        }
        for(int i=0;i<26;i++){
            if(map[i][0]!=INT_MIN){
                intervals.push_back(map[i]);
            }
        }
    };
public:
    vector<int> partitionLabels(string s){
        intervals.clear();
        countLabels(s);
        if(intervals.size()==0) return res;
        sort(intervals.begin(), intervals.end(), [](const vector<int>&p1, const vector<int>&p2){
            return p1[0]<p2[0];     // 按左边界升序排序
        });
        int pos=intervals[0][1],left=0;
        for(const vector<int>&interval:intervals){
            if(interval[0]>pos){    // 新开一个非交叉区间
                res.push_back(pos-left+1);
                left=interval[0];
            }
            pos=max(pos, interval[1]);
        }
        res.push_back(pos-left+1);  // 最右端
        return res;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
