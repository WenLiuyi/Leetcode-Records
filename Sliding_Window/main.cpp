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
class Solution_1_1 {
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
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_1_2 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n=nums.size(),sum=0,res=INT32_MAX;
        for(int l=0,r=0;r<n;r++){   // 外层循环扩展右边界
            sum+=nums[r];
            while(sum>=target){     // 区间[l,r]内元素之和已经达到target
                res=min(r-l+1,res);
                sum-=nums[l++]; //内层循环收缩左边界
            }
        }
        return res==INT32_MAX?0:res;
    }
};

// 法三：前缀和+二分查找（这道题保证了数组中每个元素都为正，所以前缀和一定是递增的）
class Solution_1_3 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n=nums.size();
        if(n==0) return 0;
        int ans=INT_MAX;
        
        // 1. 建立前缀和数组
        vector<int>sums(n+1,0);
        for(int i=1;i<=n;i++){
            sums[i]=sums[i-1]+nums[i-1];
        }
        for (int i = 1; i <= n; i++) {
            int sum = target + sums[i - 1];
            auto bound = lower_bound(sums.begin(), sums.end(), sum);
            if (bound != sums.end()) {
                ans = min(ans, static_cast<int>((bound - sums.begin()) - (i - 1)));
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

// 2. T904.水果成篮
/* fruits[i] 是第 i 棵树上的水果 种类 。
 你想要尽可能多地收集水果。然而，农场的主人设定了一些严格的规矩，你必须按照要求采摘水果：
 1. 你只有 两个 篮子，并且每个篮子只能装 单一类型 的水果。每个篮子能够装的水果总量没有限制。
 2. 你可以选择任意一棵树开始采摘，你必须从 每棵 树（包括开始采摘的树）上 恰好摘一个水果。采摘的水果应当符合篮子中的水果类型。每采摘一次，你将会向右移动到下一棵树，并继续采摘。
 3. 一旦你走到某棵树前，但水果不符合篮子的水果类型，那么就必须停止采摘。
 给你一个整数数组 fruits ，返回你可以收集的水果的 最大 数目。
 */
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_2 {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int,int>map;  // key为水果编号；value为该种类水果的个数
        int ans=0;
        
        for(int l=0,r=0;r<fruits.size();r++){
            map[fruits[r]]++;   // 采摘一个水果
            while(l<=r && map.size()>2){    // 区间不合题意
                auto it=map.find(fruits[l]);
                it->second--;l++;    // 移除窗口最左侧的这个水果
                if(it->second==0) map.erase(it);
            }
            ans=max(ans,r-l+1);
        }
        return ans;
    }
};

// 3. T76.最小覆盖子串:给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
// 采用哈希表记录：当前窗口内，某个字符出现次数
// 时间复杂度：O(|s|+|t|)；空间复杂度：O(C),C为字符集的大小
class Solution_3 {
public:
    bool check(){       // s_char_map是否包括所有t_char_map中字符
        for(const auto &pair:t_char_map){
            if(s_char_map[pair.first]<pair.second) return false;
        }
        return true;
    }
    
    unordered_map<char,int>t_char_map,s_char_map;
    string minWindow(string s, string t) {
        int len=INT_MAX,ansL=-1;
        // 1. 统计字符串t中每个字符的出现次数
        for(int i=0;i<t.size();i++){
            t_char_map[t[i]]++;
        }
        // 2. 滑动窗口
        for(int l=0,r=0;r<s.size();r++){    // 外层循环扩展右边界
            // 2.1 判断当前字符是否在t中出现：若出现，进行统计
            if(t_char_map.find(s[r])!=t_char_map.end()){
                s_char_map[s[r]]++;
            }
            while(l<=r && check()){
                if(r-l+1<len){
                    len=r-l+1;
                    ansL=l;
                }
                // 2.2 内层循环收缩左边界
                if(s_char_map.find(s[l])!=s_char_map.end()){
                    s_char_map[s[l]]--;
                }
                l++;
            }
        }
        return ansL==-1?string():s.substr(ansL,len);
    }
};

// 4. 串联所有单词的子串
/* 给定一个字符串 s 和一个字符串数组 words。 words 中所有字符串 长度相同。
 s 中的 串联子串 是指一个包含  words 中所有字符串以任意顺序排列连接起来的子串。
例如，如果 words = ["ab","cd","ef"]， 那么 "abcdef"， "abefcd"，"cdabef"， "cdefab"，"efabcd"， 和 "efcdab" 都是串联子串。 "acdbef" 不是串联子串，因为他不是任何 words 排列的连接。
返回所有串联子串在 s 中的开始索引。你可以以 任意顺序 返回答案。*/

/*输入：s = "barfoothefoobarman", words = ["foo","bar"]
 输出：[0,9]
 解释：因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
 子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
 子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
 输出顺序无关紧要。返回 [9,0] 也是可以的。*/

// 采用哈希表记录：窗口中单词频次、words中单词频次之差
// 窗口总大小恒定为：m*n；窗口大小划分方法共n种
class Solution_4 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int>res;
        int m=words.size(),n=words[0].size(),len=s.size();  // 串联子串长度为：m*n
        int i;
        for(i=0;i<n && i+m*n<=len;i++){     // [i,i+m*n-1]
            unordered_map<string,int>differ;    // 窗口中有：长度为n的字符串m个
            
            // 初始窗口，初始化differ
            for(int j=0;j<m;j++){
                differ[s.substr(i+j*n,n)]++;
            }
            for(string &word:words){
                if(--differ[word]==0) differ.erase(word);   // 抵消
            }
            if(differ.empty()){
                res.emplace_back(i);
            }
            
            // 滑动窗口：每次右边界扩展n，左边界收缩n，移动一个单词的距离
            for(int start=i;start+m*n<=len;start+=n){   // 当前移至：[start+n,start+(m+1)*n-1]
                string word_added=s.substr(start+m*n,n);
                if(++differ[word_added]==0) differ.erase(word_added);
                
                string word_subbed=s.substr(start,n);
                if(--differ[word_subbed]==0) differ.erase(word_subbed);
                
                if(differ.empty()){
                    res.emplace_back(start+n);
                }
            }
        }
        return res;
    }
};

// 5. T438.找到字符串中所有异位词
// 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
// 滑动窗口：在s中构造一个与p长度相同的滑动窗口，维护窗口中每个字符的数量
class Solution_5 {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int>pCount(26,0),sCount(26,0);
        vector<int>res;
        if(s.length()<p.length()) return res;
        for(int i=0;i<p.length();i++){
            pCount[p[i]-'a']++;
        }
        for(int l=0,r=0;r<s.size();r++){      // 外层扩展右边界
            sCount[s[r]-'a']++;
            if(r-l+1==p.length()){
                if(sCount==pCount) res.push_back(l);
                sCount[s[l]-'a']--;
                l++;
            }
        }
        return res;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
