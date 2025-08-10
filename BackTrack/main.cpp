//
//  main.cpp
//  backTrack
//
//  Created by 文柳懿 on 2025/3/17.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;

// 1. T77.组合:给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。你可以按 任何顺序 返回答案。
// 法一：使用回溯，n相当于树的宽度，k相当于树的深度（递归解决多层嵌套循环问题）
// 1. 全局变量：res存储所有结果，path存储单一结果；参数：startIndex来记录下一层递归，搜索的起始位置（避免重复）
// 2. 终止条件：path数组的大小达到k
// 时间复杂度: O(n * 2^n)
// 空间复杂度: O(n)
class Solution_1_1 {
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(int n,int k,int startIndex){
        if(path.size()==k){         // 终止条件
            res.push_back(path);
            return;
        }
        for(int i=startIndex;i<=n;i++){
            path.push_back(i);      // 加入当前节点
            backTrack(n, k, i+1);   // 递归
            path.pop_back();        // 回溯，撤销当前节点
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        res.clear();path.clear();
        backTrack(n, k, 1);
        return res;
    }
};

// 法二：剪枝优化
// 如果for循环选择的起始位置之后的元素个数 已经不足 我们需要的元素个数了，那么就没有必要搜索了。
// 还需要的元素个数为: k - path.size();在集合n中至多要从该起始位置 : n - (k - path.size()) + 1，开始遍历
class Solution_1_2 {
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(int n,int k,int startIndex){
        if(path.size()==k){         // 终止条件
            res.push_back(path);
            return;
        }
        for(int i=startIndex;i<=n-(k-path.size())+1;i++){
            path.push_back(i);      // 加入当前节点
            backTrack(n, k, i+1);   // 递归
            path.pop_back();        // 回溯，撤销当前节点
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        res.clear();path.clear();
        backTrack(n, k, 1);
        return res;
    }
};

// 2. T216.组合总和
/* 找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：
 只使用数字1到9
 每个数字 最多使用一次
 返回 所有可能的有效组合的列表 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。*/
/*2 <= k <= 9
 1 <= n <= 60 */
// 时间复杂度: O(n * 2^n)
// 空间复杂度: O(n)
class Solution_2 {
private:
    vector<vector<int>> res;
    vector<int>path;
    
    void backTrack(int n,int k,int start,int &sum){     // cnt为当前cur中的数字个数
        if(path.size()==k){
            if(sum==n) res.push_back(path);
            return;
        }
        for(int i=start;i<=min(9,n-sum) && i<=(9-(k-path.size()))+1;i++){   // 剪枝优化
            path.push_back(i);
            sum+=i;
            backTrack(n, k, i+1, sum);
            sum-=i;
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        res.clear();path.clear();
        int sum=0,cnt=0;
        backTrack(n, k, 1, sum);
        return res;
    }
};

// 3. T17.电话号码的字母组合
/* 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。*/
// 时间复杂度: O(3^m * 4^n)，其中 m 是对应三个字母的数字个数，n 是对应四个字母的数字个数
// 空间复杂度: O(3^m * 4^n)
// 求不同集合之间的组合
class Solution_3 {
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
    vector<string> res;
    string s;
    
    void backTrack(const string &digits, int index){    // 不改变digits，因此传入常量引用
        if(index==digits.size()){   // 终止条件：遍历完字符串
            res.push_back(s);
            return;
        }
        int digit=digits[index]-'0';   // 当前数字
        string letters=letterMap[digit];
        for(int i=0;i<letters.size();i++){
            s.push_back(letters[i]);    // 处理
            backTrack(digits, index+1); // 递归
            s.pop_back();       // 回溯
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        res.clear();s.clear();
        if(digits.size()==0) return res;
        backTrack(digits, 0);
        return res;
    }
};

// 4. T39.组合总和
/* 给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。
 candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。
 对于给定的输入，保证和为 target 的不同组合数少于 150 个。*/

// 时间复杂度: O(n * 2^n)，注意这只是复杂度的上界，因为剪枝的存在，真实的时间复杂度远小于此
// 空间复杂度: O(target)
class Solution_4 {
private:
    vector<vector<int>> res;
    vector<int> path;
    void backTrack(vector<int>& candidates, int target, int sum, int startIndex){
        if(sum==target){
            res.push_back(path);
            return;
        }
        for(int i=startIndex;i<candidates.size() && sum+candidates[i]<=target;i++){ // 剪枝
            sum+=candidates[i];
            path.push_back(candidates[i]);
            backTrack(candidates, target, sum, i);  // 关键点:不用i+1了，表示可以重复读取当前的数
            sum-=candidates[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        res.clear();path.clear();
        sort(candidates.begin(),candidates.end());
        backTrack(candidates, target, 0, 0);
        return res;
    }
};

// 5. T40.组合总和II
/* 给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 candidates 中的每个数字在每个组合中只能使用 一次 。
 注意：解集不能包含重复的组合。 */
// 去重逻辑：
// 1. 树层去重：集合candidates中包含相同元素，要去除同一树层上使用过的元素：如果candidates[i] == candidates[i - 1] 并且 used[i - 1] == false，就说明：前一个树枝，使用了candidates[i - 1]，也就是说同一树层使用过candidates[i - 1].
// 2. 树枝无需去重：同一树枝上的都是一个组合里的元素，不用去重
// 时间复杂度: O(n * 2^n)
// 空间复杂度: O(n)
class Solution_5 {
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(vector<int>& candidates, int target, int sum, int startIndex, vector<bool> &used){
        if(sum==target){
            res.push_back(path);
            return;
        }
        for(int i=startIndex;i<candidates.size() && sum+candidates[i]<=target;i++){
            if(i>0 && candidates[i]==candidates[i-1] && used[i-1]==false){
                continue;
            }
            sum+=candidates[i];
            used[i]=true;
            path.push_back(candidates[i]);
            backTrack(candidates, target, sum, i+1, used);
            used[i]=false;
            path.pop_back();
            sum-=candidates[i];
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<bool>used(candidates.size(),false);
        res.clear();path.clear();
        sort(candidates.begin(),candidates.end());  // 排序：让相同的元素挨在一起
        backTrack(candidates, target, 0, 0, used);
        return res;
    }
};

// 6. T31.分割回文串:给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。
// 子字符串 是字符串中连续的 非空 字符序列。
// 1 <= s.length <= 16

/* 切割问题类似组合问题:
 对于字符串abcdef：
 组合问题：选取一个a之后，在bcdef中再去选取第二个，选取b之后在cdef中再选取第三个.....。
 切割问题：切割一个a之后，在bcdef中再去切割第二段，切割b之后在cdef中再切割第三段.....。
 */
/*时间复杂度: O(n * 2^n)
 空间复杂度: O(n^2) */
class Solution_6 {
private:
    vector<vector<string>>res;
    vector<string> path;
    
    void backTrack(const string &s, int startIndex){
        if(startIndex>=s.size()){
            res.push_back(path);
            return;
        }
        for(int i=startIndex;i<s.size();i++){
            if(isPalindrome(s, startIndex, i)){     // s[startIndex, i]是回文子串
                string str=s.substr(startIndex, i-startIndex+1);    // i-startIndex+1为子串长度
                path.push_back(str);
            }else{
                continue;
            }
            backTrack(s, i+1);
            path.pop_back();    // 回溯
        }
    }
    
    bool isPalindrome(const string &s, int start, int end){
        int i=start, j=end;
        while(i<=j){
            if(s[i]!=s[j]) return false;
            i++;j--;
        }
        return true;
    }
public:
    vector<vector<string>> partition(string s) {
        res.clear();path.clear();
        backTrack(s, 0);
        return res;
    }
};

// 7. T132.分割回文串II:给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文串。
// 返回符合要求的 最少分割次数 。

/* 设 f[i] 表示字符串的前缀 s[0..i] 的最少分割次数。
 枚举分割出的最右边那段子串的长度, 即s[0..i] 分割出的最后一个回文串.
 状态转移方程：f[i]=(0≤j<i)min{f[j]}+1,其中 s[j+1..i] 是一个回文串 */
// 时间复杂度：O(n^2)
// 空间复杂度：O(n^2)
class Solution_7 {
private:
    vector<vector<bool>>isPalindrome;
    void computePalindrome(const string &s){
        isPalindrome.resize(s.size(), vector<bool>(s.size(),false));
        for(int i=s.size()-1;i>=0;i--){
            for(int j=i;j<s.size();j++){
                if(i==j) isPalindrome[i][j]=true;
                else if(j-i==1) isPalindrome[i][j]=(s[i]==s[j]);
                else{
                    isPalindrome[i][j]=(s[i]==s[j] && isPalindrome[i+1][j-1]);
                }
            }
        }
    }
public:
    int minCut(string s) {
        computePalindrome(s);
        int n=s.size();
        vector<int>f(n,INT_MAX);
        
        for(int i=0;i<n;i++){
            if(isPalindrome[0][i]){     // s[0...i]本身是回文串
                f[i]=0;
            }else{
                for(int j=0;j<i;j++){
                    if(isPalindrome[j+1][i]){
                        f[i]=min(f[i],f[j]+1);
                    }
                }
            }
        }
        return f[n-1];
    }
};

// 8. T93.复原IP地址
/* 有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。
 
 例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
 给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，这些地址可以通过在 s 中插入 '.' 来形成。你 不能 重新排序或删除 s 中的任何数字。你可以按 任何 顺序返回答案。*/
/* 时间复杂度: O(3^4)，IP地址最多包含4个数字，每个数字最多有3种可能的分割方式，则搜索树的最大深度为4，每个节点最多有3个子节点。
 空间复杂度: O(n) */
class Solution_8 {
private:
    vector<string>res;
    bool isValid(const string &s, int start, int end){
        if(start>end) return false;
        else if(s[start]=='0' && start!=end){
            return false;
        }
        int num=0;
        for(int i=start;i<=end;i++){
            if(s[i]<'0' || s[i]>'9'){
                return false;
            }
            num=num*10+s[i]-'0';
            if(num>255) return false;
        }
        return true;
    }
    void backTrack(string &s, int startIndex, int pointerNum){
        if(pointerNum==3){      // 终止条件：有3个逗号
            if(isValid(s, startIndex, s.size()-1)){
                res.push_back(s);
            }
            return;
        }
        for(int i=startIndex;i<s.size();i++){
            if(isValid(s, startIndex, i)){      // [startIndex, i]的子串是否合法
                s.insert(s.begin()+i+1, '.');
                pointerNum++;
                backTrack(s,i+2,pointerNum);
                pointerNum--;
                s.erase(s.begin()+i+1);
            }else{
                break;
            }
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        res.clear();
        if(s.size()<4 || s.size()>12) return res;
        backTrack(s, 0, 0);
        return res;
    }
};

// 9. T78.子集
/* 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。*/
// 数组的 子集 是从数组中选择一些元素（可能为空）

// 时间复杂度：O(n*2^n)
// 空间复杂度：O(n)
class Solution_9 {
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(vector<int>&nums, int startIndex){
        res.push_back(path);        // 收集当前子集(不加入当前startIndex)
        if(startIndex>=nums.size()){
            return;
        }
        for(int i=startIndex;i<nums.size();i++){
            path.push_back(nums[i]);    // 将当前元素加入集合
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

// 10. T90.子集II
/* 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的 子集（幂集）。
 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。*/
/* 类似于组合II:
 去重逻辑：
 1. 树层去重：集合nums中包含相同元素，要去除同一树层上使用过的元素：如果nums[i] == nums[i - 1] 并且 used[i - 1] == false，就说明：前一个树枝，使用了nums[i - 1]，也就是说同一树层使用过nums[i - 1].
 2. 树枝无需去重：同一树枝上的都是一个组合里的元素，不用去重
 */
// 时间复杂度: O(n * 2^n)
// 空间复杂度: O(n)
class Solution_10 {
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(vector<int>&nums, int startIndex, vector<bool>& used){
        res.push_back(path);
        for(int i=startIndex;i<nums.size();i++){
            if(i>0 && nums[i]==nums[i-1] && used[i-1]==false){
                continue;
            }
            path.push_back(nums[i]);
            used[i]=true;
            backTrack(nums, i+1, used);
            used[i]=false;
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        res.clear();path.clear();
        vector<bool>used(nums.size(),false);
        sort(nums.begin(),nums.end());
        backTrack(nums, 0, used);
        return res;
    }
};

// 11. T491.非递增子序列
/* 给你一个整数数组 nums ，找出并返回所有该数组中不同的递增子序列，递增子序列中 至少有两个元素。你可以按 任意顺序 返回答案。
 数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。*/
// 时间复杂度：O(n*2^n)；空间复杂度：O(n)
class Solution_11_1 {
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(vector<int>&nums, int startIndex){
        if(path.size()>1){
            res.push_back(path);
        }
        unordered_set<int>uset;
        for(int i=startIndex;i<nums.size();i++){
            if((uset.find(nums[i])!=uset.end() || (!path.empty() && nums[i]<path.back()))){
                continue;   // 重复元素/递减：跳过
            }
            uset.insert(nums[i]);
            path.push_back(nums[i]);
            backTrack(nums,i+1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        res.clear();path.clear();
        backTrack(nums,0);
        return res;
    }
};
// 优化：数值范围[-100,100]，所以完全可以用数组来做哈希
class Solution_11_2 {
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(vector<int>&nums, int startIndex){
        if(path.size()>1){
            res.push_back(path);
        }
        int used[201]={0};
        for(int i=startIndex;i<nums.size();i++){
            if((used[nums[i]+100]==1 || (!path.empty() && nums[i]<path.back()))){
                continue;   // 重复元素/递减：跳过
            }
            used[nums[i]+100]=1;
            path.push_back(nums[i]);
            backTrack(nums,i+1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        res.clear();path.clear();
        backTrack(nums,0);
        return res;
    }
};

// 12. T46.全排列：给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。
// 时间复杂度：O(n!)；空间复杂度：O(n)
class Solution_12 {
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(vector<int>& nums, vector<bool> &used){
        if(path.size()==nums.size()){
            res.push_back(path);
            return;
        }
        for(int i=0;i<nums.size();i++){
            if(used[i]==true) continue;
            used[i]=true;
            path.push_back(nums[i]);
            backTrack(nums, used);
            used[i]=false;
            path.pop_back();
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        res.clear();path.clear();
        vector<bool>used(nums.size(),false);
        backTrack(nums, used);
        return res;
    }
};

// 13. 全排列II：给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列
// 时间复杂度：O(n!*n)；空间复杂度：O(n)
class Solution_13 {
private:
    vector<vector<int>> res;
    vector<int> path;
    
    void backTrack(vector<int>&nums, vector<bool>&used){
        if(nums.size()==path.size()){
            res.push_back(path);
            return;
        }
        for(int i=0;i<nums.size();i++){
            if(i>0 && nums[i]==nums[i-1] && used[i-1]==false){
                continue;   // 同一树层去重
            }
            if(used[i]==true) continue;
            used[i]=true;
            path.push_back(nums[i]);
            backTrack(nums, used);
            used[i]=false;
            path.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        res.clear();path.clear();
        vector<bool>used(nums.size(),false);
        sort(nums.begin(),nums.end());
        backTrack(nums, used);
        return res;
    }
};

// 14. T51.N皇后
/* 按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
 n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。*/

// 时间复杂度：O(n!)；空间复杂度：O(n).
class Solution_14 {
private:
    vector<vector<string>> res;
    void backTrack(vector<string>chessBoard, int n, int row){
        if(row==n){
            res.push_back(chessBoard);
            return;
        }
        for(int col=0;col<n;col++){     // 检查(row,col)处是否可以放置棋子
            if(isValid(chessBoard, n, row, col)){
                chessBoard[row][col]='Q';   // 放置棋子
                backTrack(chessBoard, n, row+1);
                chessBoard[row][col]='.';   // 回溯
            }
        }
    }
    bool isValid(vector<string>&chessBoard, int n, int row, int col){
        for(int i=0;i<row;i++){
            if(chessBoard[i][col]=='Q'){    // 检查本列
                return false;
            }
        }
        for(int i=row-1,j=col-1;i>=0&&j>=0;i--,j--){    // 检查45度射线
            if(chessBoard[i][j]=='Q'){
                return false;
            }
        }
        for(int i=row-1,j=col+1;i>=0&&j<n;i--,j++){     // 检查135度射线
            if(chessBoard[i][j]=='Q'){
                return false;
            }
        }
        return true;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        res.clear();
        vector<string>chessBoard(n,string(n,'.'));      // 初始化所有行:n个'.'
        backTrack(chessBoard, n, 0);
        return res;
    }
};

// 15. T37.解数独
/* 编写一个程序，通过填充空格来解决数独问题。
 数独的解法需 遵循如下规则：
 数字 1-9 在每一行只能出现一次。
 数字 1-9 在每一列只能出现一次。
 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
 数独部分空格内已填入了数字，空白格用 '.' 表示。*/
class Solution_15 {
private:
    bool backTrack(vector<vector<char>>& board){
        for(int i=0;i<board.size();i++){    // 遍历行
            for(int j=0;j<board[0].size();j++){
                if(board[i][j]=='.'){
                    for(char k='1';k<='9';k++){
                        if(isValid(board, i, j, k)){
                            board[i][j]=k;
                            if(backTrack(board)) return true;   // 找到一组即可
                            board[i][j]='.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    bool isValid(vector<vector<char>>& board, int row, int col, char val){
        for(int i=0;i<9;i++){   // 判断行内元素是否重复
            if(board[row][i]==val){
                return false;
            }
        }
        for(int j=0;j<9;j++){   // 判断列内元素是否重复
            if(board[j][col]==val){
                return false;
            }
        }
        int startRow=(row/3)*3, startCol=(col/3)*3;
        for(int i=startRow;i<startRow+3;i++){
            for(int j=startCol;j<startCol+3;j++){
                if(board[i][j]==val){
                    return false;
                }
            }
        }
        return true;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        backTrack(board);
    }
};

// 16. T212. 单词搜索II
/* 给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words， 返回所有二维网格上的单词 。
 单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。*/

/* 思路：
 1. 与单词搜索I只找一个word相比，单词搜索II需要逐一比对所有words。每次遍历判断时间复杂度太大，改用字典树；
 2. 采用dfs，搜索满足条件的单元格
 3. 注意：同一个word可能在多个路径中出现，需要使用set去重
 */
struct TrieNode{
    string word;        // 只有叶子节点才有值
    unordered_map<char, TrieNode *>children;    // 通过哈希表记录
    TrieNode(){
        this->word="";
    }
};
class Solution_16{
private:
    void insertTrieNode(TrieNode *root, const string &word){
        TrieNode *cur=root;
        for(const auto &ch:word){
            if(!cur->children.contains(ch)){
                cur->children[ch]=new TrieNode();
            }
            cur=cur->children[ch];
        }
        cur->word=word;     // 叶子节点
    }
    
    vector<vector<bool>> visited;
    set<string>res;
    void init(int m, int n){
        visited=vector<vector<bool>>(m, vector<bool>(n, false));
    }
    
    vector<pair<int, int>>directions={{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    void backTrack(vector<vector<char>>& board, TrieNode *pre, int i, int j){   // 进入之前，used[i][j]已经设置为true
        // 从board[i][j]开始遍历:到cur的当前路径是否是某个word的前缀
        // 1. 终止条件
        char ch=board[i][j];
        if(!pre->children.contains(ch)){
            return;
        }
        pre=pre->children[ch];      // 移动指向的节点
        if(pre->word.size()>0){
            res.insert(pre->word);   // 遍历到叶子节点，将当前word加入res
            // 此处不要返回，可以再接着找（没说不同word不能共用相同的单元格）
        }
        // 2. 遍历，寻找下一个节点
        for(const auto &dir:directions){
            int nextX=i+dir.first, nextY=j+dir.second;
            if(0<=nextX && nextX<board.size() && 0<=nextY && nextY<board[0].size()){
                if(visited[nextX][nextY]){
                    continue;   // 已经使用，跳过
                }
                visited[nextX][nextY]=true;
                backTrack(board, pre, nextX, nextY);
                visited[nextX][nextY]=false;
            }
        }
    };
    
public:
    vector<string>findWords(vector<vector<char>> &board, vector<string> &words){
        // 1. 将words中所有单词插入Trie
        TrieNode *root=new TrieNode();
        for(const auto &word: words){
            insertTrieNode(root, word);
        }
        int m=board.size(), n=board[0].size();
        init(m, n);
        
        res.clear();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                visited[i][j]=true;
                backTrack(board, root, i, j);
                visited[i][j]=false;
            }
        }
        vector<string>ans;
        for(const auto &word: res){
            ans.push_back(word);
        }
        return ans;
    }
};

// 17. T1278.分割回文串III
/* 给你一个由小写字母组成的字符串 s，和一个整数 k。
 请你按下面的要求分割字符串：
 首先，你可以将 s 中的部分字符修改为其他的小写英文字母。
 接着，你需要把 s 分割成 k 个非空且不相交的子串，并且每个子串都是回文串。
 请返回以这种方式分割字符串所需修改的最少字符数。*/

/* 思路：动态规划: f[i][j]表示将s[0,i-1]（前i个字符）分割为j个回文串，所需要的最小修改次数.
 状态转移: f[i][j]=min(f[t][j-1]+cost(s, t, i-1). cost(s, t, i)表示将s[t, i-1]组成的子串修改为回文串所需的最小次数
 优化：记cost[i][j]=cost(s, i, j)，有：
    1. cost[i][j]=cost[i+1, j-1], if s[i]==s[j].
    2. cost[i][j]=cost[i+1, j-1]+1, if s[i]!=s[j].
    3. cost[i][j]=0, if i>=j.
 */
class Solution_17{
private:
    vector<vector<int>>cost;
    int n;
    void computeCost(const string &s){
        n=s.size();
        cost.resize(n, vector<int>(n, 0));
        for(int i=n-1;i>=0;i--){
            for(int j=i;j<n;j++){
                if(i>=j) continue;
                else if(s[i]==s[j]){
                    cost[i][j]=cost[i+1][j-1];
                }else{
                    cost[i][j]=cost[i+1][j-1]+1;
                }
            }
        }
    }
    
    vector<vector<int>>f;
    int solve(string s, int k){
        f.resize(n+1, vector<int>(k+1, INT_MAX));
        f[0][0]=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=min(k, i);j++){
                if(j==1){
                    f[i][j]=cost[0][i-1];
                    continue;
                }
                for(int t=j-1;t<i;t++){
                    f[i][j]=min(f[i][j], f[t][j-1]+cost[t][i-1]);
                }
            }
        }
        return f[n][k];
    }
    
public:
    int palindromePartition(string s, int k) {
        computeCost(s);
        return solve(s, k);
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
