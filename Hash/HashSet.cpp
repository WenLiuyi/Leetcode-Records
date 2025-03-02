//
//  main.cpp
//  HashSet
//
//  Created by 文柳懿 on 2025/2/28.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <set>
#include <unordered_set>
using namespace std;

// 1. T242.有效的字母异位词:给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
// 字母异位词是通过重新排列不同单词或短语的字母而形成的单词或短语，并使用所有原字母一次。
// 思路：判断s，t中每个字母的出现次数是否相同（使用数组模拟哈希表）
// 时间复杂度：O(n)，遍历每个字母；空间复杂度：O(1)
class Solution_1 {
public:
    bool isAnagram(string s, string t) {
        if(s.size()!=t.size()) return false;
        
        int record[26]={0};
        for(int i=0;i<s.size();i++){
            record[s[i]-'a']++;
        }
        for(int i=0;i<t.size();i++){
            record[t[i]-'a']--;
        }
        
        for(int i=0;i<26;i++){
            if(record[i]!=0) return false;
        }
        return true;
    }
};

// 2. T49.字母异位词分组:给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
// 思路：对每个字符串中的字母出现次数计数，哈希表的键为升序排列的字符串；值为原字符串数组
class Solution_2 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>>map;
        
        for(string str:strs){
            int counts[26]={0};
            for(char ch:str){
                counts[ch-'a']++;
            }
            string key="";  // 将字符升序排列，例：a2b1c3
            for(int i=0;i<26;i++){
                key.push_back('a'+i);key.push_back(counts[i]);
            }
            map[key].push_back(str);
        }
        vector<vector<string>>res;
        for(auto &pair:map){
            res.push_back(pair.second);
        }
        return res;
    }
};

// 3. 两个数组的交集:给定两个数组 nums1 和 nums2 ，返回 它们的 交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
// 思路：使用unordered_set，分别记录：nums1,nums2中出现过的字母
// 时间复杂度：O(n+m)，m是因为要将set转为vector
// 空间复杂度：O(n)
class Solution_3 {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int>result_set;
        unordered_set<int>nums_set(nums1.begin(),nums1.end());  // 将nums1中的所有元素，放入nums_set（使用迭代器）
        for(int num:nums2){
            if(nums_set.find(num)!=nums_set.end()){     // nums_set中找到了num
                result_set.insert(num);
            }
        }
        return vector<int>(result_set.begin(),result_set.end());
    }
};

// 4. T202.快乐数
/*编写一个算法来判断一个数 n 是不是快乐数。
 「快乐数」 定义为：
 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
 如果这个过程 结果为 1，那么这个数就是快乐数。
 如果 n 是 快乐数 就返回 true ；不是，则返回 false 。*/

// 思路：看似会无限循环，说明求和的过程中，sum会重复出现；建立哈希表，判断是否重复出现
// 时间复杂度：O(logn)；空间复杂度：O(logn)
/*查找给定数字的下一个值的成本为 O(logn)，因为我们正在处理数字中的每位数字，而数字中的位数由 logn 给定。*/
class Solution_4 {
public:
    int getSum(int n){
        int sum=0;
        while(n){
            sum+=(n%10)*(n%10);
            n/=10;
        }
        return sum;
    }
    
    bool isHappy(int n) {
        unordered_set<int>set;
        while(1){
            int sum=getSum(n);
            if(sum==1) return true;
            else if(set.find(sum)!=set.end()) return false; // sum曾经出现过
            else set.insert(sum);
            
            n=sum;
        }
    }
};

// 5. T1.两数之和
/*给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
 你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。*/
class Solution_5 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>map;  // key为数值；value为下标
        for(int i=0;i<nums.size();i++){
            auto iter=map.find(target-nums[i]);
            if(iter!=map.end()){    // 找到了
                return {iter->second,i};
            }
            map.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }
};

// 6. T15.三数之和
/* 双指针法：
 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。*/
// 使用双指针：首先将数组排序，然后有一层for循环，i从下标0的地方开始，同时定一个下标left 定义在i+1的位置上，定义下标right 在数组结尾的位置上。
// 如果nums[i] + nums[left] + nums[right] > 0 ，left向右移动；
// 如果 nums[i] + nums[left] + nums[right] < 0 ，right向左移动。
class Solution_6 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());  // 升序排序
        
        for(int i=0;i<nums.size();i++){
            if(nums[i]>0) return res;
            if(i>0 && nums[i]==nums[i-1]) continue;     // 对a去重
            
            int left=i+1,right=nums.size()-1;
            while(left<right){
                if(nums[i]+nums[left]+nums[right]>0) right--;
                else if(nums[i]+nums[left]+nums[right]<0) left++;
                else{
                    res.push_back(vector<int>{nums[i],nums[left],nums[right]});
                    while(right>left && nums[right]==nums[right-1]) right--;    // 对b,c去重
                    while(right>left && nums[left]==nums[left+1]) left++;
                    right--;left++;
                }
            }
        }
        return res;
    }
};

// 7. 四数之和
/*给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：
 0 <= a, b, c, d < n
 a、b、c 和 d 互不相同
 nums[a] + nums[b] + nums[c] + nums[d] == target*/
class Solution_7 {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());  // 升序排列
        
        for(int i=0;i<nums.size();i++){
            if(nums[i]>target && nums[i]>=0){   // 剪枝：最小的元素超过了target
                return res;
            }
            if(i>0 && nums[i]==nums[i-1]) continue;     // 对nums[i]去重
            
            for(int j=i+1;j<nums.size();j++){
                if(nums[i]+nums[j]>target && nums[i]+nums[j]>=0) break; // 2级剪枝
                if(j>i+1 && nums[j]==nums[j-1]) continue;   // 对nums[j]去重
                
                int left=j+1,right=nums.size()-1;
                while(left<right){
                    if((long)nums[i]+nums[j]+nums[left]+nums[right]>target) right--;
                    else if((long)nums[i]+nums[j]+nums[left]+nums[right]<target) left++;
                    else{
                        res.push_back(vector<int>{nums[i],nums[j],nums[left],nums[right]});
                        // 对nums[left],nums[right]去重
                        while(left<right && nums[right]==nums[right-1]) right--;
                        while(left<right && nums[left]==nums[left+1]) left++;
                        
                        right--;left++;
                    }
                }
            }
        }
        return res;
    }
};

// 8. 四数相加II
/*给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n ，请你计算有多少个元组 (i, j, k, l) 能满足：
 0 <= i, j, k, l < n
 nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0*/
// -228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2^28, 最终结果不会超过 2^31 - 1 .
// 注：可以包含重复的四元组
// 思路：定义unordered_map,key为a,b两数之和,value为a+b两数之和出现的次数。

// 时间复杂度：O(n^2)；空间复杂度：O(n^2)
class Solution_8 {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int,int>map;
        for(int i=0;i<nums1.size();i++){
            for(int j=0;j<nums2.size();j++){
                map[nums1[i]+nums2[j]]++;
            }
        }
        // count统计a+b+c+d=0的次数
        int count=0;
        for(int i=0;i<nums3.size();i++){
            for(int j=0;j<nums4.size();j++){
                if(map.find(0-nums3[i]-nums4[j])!=map.end()){
                    count+=map[0-nums3[i]-nums4[j]];
                }
            }
        }
        return count;
    }
};

// 9. T383.赎金信:
/*给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。
 如果可以，返回 true ；否则返回 false .
 magazine 中的每个字符只能在 ransomNote 中使用一次。
 */
// 思路：用数组记录magazine中，每个小写字母的出现次数
// 时间复杂度：O(n)；空间复杂度:O(1)
class Solution_9 {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int record[26]={0};
        if(ransomNote.size()>magazine.size()) return false;
        for(int i=0;i<magazine.length();i++){
            record[magazine[i]-'a']++;
        }
        for(int j=0;j<ransomNote.size();j++){
            record[ransomNote[j]-'a']--;
            if(record[ransomNote[j]-'a']<0) return false;
        }
        return true;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
