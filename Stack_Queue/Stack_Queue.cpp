//
//  main.cpp
//  Stack_Queue
//
//  Created by 文柳懿 on 2025/3/2.
//

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// 1. T232. 用栈实现队列
/*请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
 实现 MyQueue 类：
 void push(int x) 将元素 x 推到队列的末尾
 int pop() 从队列的开头移除并返回元素
 int peek() 返回队列开头的元素
 boolean empty() 如果队列为空，返回 true ；否则，返回 false.*/
// 时间复杂度：都为O(1)；pop和peek在一个循环n中使用n次，均摊复杂度为O(1)
// 空间复杂度：O(n)
class MyQueue_1 {
public:
    stack<int>stIn;
    stack<int>stOut;   // 用两个栈实现队列
    
    MyQueue_1() {}
    void push(int x) {
        stIn.push(x);   // x放入stIn
    }
    int pop() { // stOut为空时：从stIn中弹出所有元素，依次压入stOut，再从stOut栈顶弹出顶端元素（该元素为stIn底部元素）
        if(stOut.empty()){
            while(!stIn.empty()){
                auto node=stIn.top();
                stOut.push(node);stIn.pop();
            }
        }
        int res=stOut.top();stOut.pop();
        return res;
    }
    int peek() {
        int res=this->pop();    // peek相对于pop，返回的元素相同，但不弹出
        stOut.push(res);
        return res;
    }
    bool empty() {
        return stIn.empty() && stOut.empty();
    }
};

// 2. T225.用队列实现栈
/*请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。
 实现 MyStack 类:
 void push(int x) 将元素 x 压入栈顶。
 int pop() 移除并返回栈顶元素。
 int top() 返回栈顶元素。
 boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。*/
// 优化：使用一个队列实现。模拟栈弹出元素时：将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部
// 时间复杂度: pop为O(n)，top为O(n)，其他为O(1)
// 空间复杂度: O(n)
class MyStack {
public:
    queue<int> queue;
    MyStack() {}
    void push(int x) {
        queue.push(x);
    }
    int pop() {
        int size=queue.size();
        for(int i=0;i<size-1;i++){
            queue.push(queue.front());queue.pop();
        }
        int res=queue.front();
        queue.pop();
        return res;
    }
    int top() {
        int res=this->pop();
        queue.push(res);
        return res;
    }
    bool empty() {
        return queue.empty();
    }
};

// 3. T20.有效的括号
/*给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
 有效字符串需满足：
 左括号必须用相同类型的右括号闭合。
 左括号必须以正确的顺序闭合。
 每个右括号都有一个对应的相同类型的左括号。*/
// 建立栈：遇到左括号时，将对应的右括号入栈；遇到右括号时，从栈顶弹出元素，观察是否匹配
class Solution_3 {
public:
    bool isValid(string s) {
        int len=s.length();
        if(len%2) return false;
        stack<char>stack;
        
        for(int i=0;i<len;i++){
            if(s[i]=='(') stack.push(')');
            else if(s[i]=='[') stack.push(']');
            else if(s[i]=='{') stack.push('}');
            else if(stack.empty()||stack.top()!=s[i]) return false;
            else stack.pop();
        }
        return stack.empty();
    }
};

// 4. 删除字符串中的所有相邻重复项: 相当于括号匹配问题
/*示例：
 输入："abbaca"
 输出："ca"
 解释：
 例如，在 "abbaca" 中，我们可以删除 "bb" 由于两字母相邻且相同，这是此时唯一可以执行删除操作的重复项。之后我们得到字符串 "aaca"，其中又只有 "aa" 可以执行重复项删除操作，所以最后的字符串为 "ca"。*/
// 栈：顶端元素为前一个相邻的元素
// 法一：建立栈
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_4_1 {
public:
    string removeDuplicates(string s) {
        stack<char>stack;
        int len=s.length();
        
        for(int i=0;i<len;i++){
            if(stack.empty()||stack.top()!=s[i]){     // 当前字符与栈顶字符不匹配
                stack.push(s[i]);
            }else{
                stack.pop();    // 删除重复项
            }
        }
        string res="";
        while(!stack.empty()){
            res+=stack.top();
            stack.pop();
        }
        reverse(res.begin(),res.end());     // 翻转res字符串
        return res;
    }
};
// 法二：直接采用结果字符串作为栈，降低空间复杂度
class Solution_4_2{
public:
    string removeDuplicates(string s) {
        string res="";
        for(char ch:s){
            if(res.empty()||res.back()!=ch){
                res.push_back(ch);
            }else{
                res.pop_back();
            }
        }
        return res;
    }
};

// 5. T150.逆波兰表达式求值
/*给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。
 请你计算该表达式。返回一个表示表达式值的整数。
 注意：
 有效的算符为 '+'、'-'、'*' 和 '/' 。
 每个操作数（运算对象）都可以是一个整数或者另一个表达式。
 两个整数之间的除法总是 向零截断 。
 表达式中不含除零运算。
 输入是一个根据逆波兰表示法表示的算术表达式。
 答案及所有中间计算结果可以用 32 位 整数表示。*/

// 注：逆波兰表达式相当于是二叉树中的后序遍历
class Solution_5 {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long>stack;      // 操作数栈
        for(int i=0;i<tokens.size();i++){
            if(tokens[i]=="+"||tokens[i]=="-"||tokens[i]=="*"||tokens[i]=="/"){
                // 遇到运算符时：从栈中弹出两个操作数，计算后，将结果压入栈
                long long num1=stack.top();stack.pop();     // 第二个操作数
                long long num2=stack.top();stack.pop();     // 第一个操作数
                if(tokens[i]=="+") stack.push(num2+num1);
                else if(tokens[i]=="-") stack.push(num2-num1);
                else if(tokens[i]=="*") stack.push(num2*num1);
                else if(tokens[i]=="/") stack.push(num2/num1);
            }else{
                stack.push(stoll(tokens[i]));   // stoll函数：将字符串转为long long型
            }
        }
        return stack.top();
    }
};

// 6. T239.滑动窗口最大值
// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
// 返回 滑动窗口中的最大值 。
// 法一：暴力解法：时间复杂度O((n-k+1)k)=O(nk)，超出限制

// 法二：优先队列：采用大根堆实时维护一系列元素中的最大值
// 为了保证堆顶的元素在滑动窗口中：不断地移除堆顶的元素，直到其确实出现在滑动窗口中
// 时间复杂度：O(nlogn):将一个元素放入优先队列，时间复杂度为O(logn)；
// 空间复杂度：O(n)，优先队列需要的空间
class Solution_6_1 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int,int>>q;   // (num,index),num为元素值；index为元素在数组中的下标（帮助判断：是否在滑动窗口中）
        // 1. 加入前k个元素
        for(int i=0;i<k;i++) q.emplace(nums[i],i);
        
        vector<int>ans={q.top().first};     // 下标在[0,k-1]之间的最大值
        int n=nums.size();
        for(int i=k;i<n;i++){   // 下标在[i-k+1,i]之间
            q.emplace(nums[i],i);
            while(q.top().second<=i-k){
                q.pop();
            }
            ans.push_back(q.top().first);
        }
        return ans;
    }
};

// 法三：单调队列
// 时间复杂度：O(n)；空间复杂度：O(k)
class Solution_6_2 {
private:
    class MyQueue{      // 单调队列：从大到小
    public:
        deque<int>que;
        void pop(int x){        // 比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出
            // 当且仅当：队列中最大值，是需要从滑动窗口中移除的值时，才弹出
            if(!que.empty()&&que.front()==x){
                que.pop_front();
            }
        }
        void push(int x){   // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止
            while(!que.empty()&&x>que.back()){
                que.pop_back();
            }
            que.push_back(x);
        }
        int front(){        // 查询队列的最大值：直接返回队首的元素
            return que.front();
        }
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue queue;  // queue为单调队列，其中的值从大到小存放
        for(int i=0;i<k;i++) queue.push(nums[i]);
        
        vector<int>ans;
        int n=nums.size();
        ans.push_back(queue.front());
        for(int i=k;i<n;i++){
            queue.pop(nums[i-k]);
            queue.push(nums[i]);
            ans.push_back(queue.front());
        }
        return ans;
    }
};

// 7. 简化路径
/*给你一个字符串 path ，表示指向某一文件或目录的 Unix 风格 绝对路径 （以 '/' 开头），请你将其转化为 更加简洁的规范路径。
 在 Unix 风格的文件系统中规则如下：
 1. 一个点 '.' 表示当前目录本身。
 2. 此外，两个点 '..' 表示将目录切换到上一级（指向父目录）。
 3. 任意多个连续的斜杠（即，'//' 或 '///'）都被视为单个斜杠 '/'。
 4. 任何其他格式的点（例如，'...' 或 '....'）均被视为有效的文件/目录名称。
 
 返回的 简化路径 必须遵循下述格式：
 1. 始终以斜杠 '/' 开头。
 2. 两个目录名之间必须只有一个斜杠 '/' 。
 3. 最后一个目录名（如果存在）不能 以 '/' 结尾。
 4. 此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 '.' 或 '..'）。
 5. 返回简化后得到的 规范路径 。*/

// 思路：用栈存储目录名:遇到目录名，压入栈；遇到两个连续的.，从栈中弹出一个目录名（返回到上一级）
class Solution_7 {
public:
    vector<string> split(const string &s, char delim){  // 使用delim划分字符串s
        vector<string>res;
        string cur="";
        int len=s.length();
        for(int i=0;i<len;i++){
            if(s[i]==delim){
                res.push_back(cur);
                cur.clear();
            }else{
                cur+=s[i];
            }
        }
        res.push_back(cur);
        return res;
    }
    string simplifyPath(string path) {
        vector<string>names=split(path,'/');
        vector<string>stack;
        // 1. 将目录名压入栈
        for(string &name:names){
            if(name==".."){
                if(!stack.empty()) stack.pop_back();
            }else if(!name.empty() && name!="."){
                stack.push_back(move(name));
                /*std::move函数：实现 移动语义。它的作用是将一个对象的资源所有权从一个对象转移到另一个对象，而不是进行深拷贝。*/
            }
        }
        
        string ans="";
        if(stack.empty()) return "/";
        else{
            for(string &name:stack){
                ans+="/"+move(name);
            }
        }
        return ans;
    };
};

// 8. T224.基本计算器:给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
/*
 1 <= s.length <= 3 * 105
 s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
 s 表示一个有效的表达式
 '+' 不能用作一元运算(例如， "+1" 和 "+(2 + 3)" 无效)
 '-' 可以用作一元运算(即 "-1" 和 "-(2 + 3)" 是有效的)
 输入中不存在两个连续的操作符
 每个数字和运行的计算将适合于一个有符号的 32位 整数*/

// 关键：确定当前的符号为+或-：设立操作符栈，记录：当前括号层级的sign
// 时间复杂度：O(n)；空间复杂度：O(n)
class Solution_8 {
public:
    int calculate(string s) {
        stack<int>ops;     // 记录：当前括号层级的sign
        int n=s.length(),res=0,sign=1;
        ops.push(sign);
        
        int i=0;
        while(i<n){
            if(s[i]==' ') i++;
            else if(s[i]=='+') {sign=ops.top();i++;}
            else if(s[i]=='-') {sign=-ops.top();i++;}
            else if(s[i]=='(') {
                ops.push(sign);     // 将当前的 sign 取值压入栈中
                i++;
            }
            else if(s[i]==')') {    // 从栈中弹出一个元素
                ops.pop();
                i++;
            }
            else{
                long long num=0;
                while(i<n && '0'<=s[i] && s[i]<='9'){
                    num=num*10+(s[i]-'0');
                    i++;
                }
                res+=sign*num;
            }
        }
        return res;
    }
};

// 9. T155.最小栈
/*设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
 实现 MinStack 类:
 MinStack() 初始化堆栈对象。
 void push(int val) 将元素val推入堆栈。
 void pop() 删除堆栈顶部的元素。
 int top() 获取堆栈顶部的元素。
 int getMin() 获取堆栈中的最小元素。*/
// 思路：设置一个辅助栈，与元素栈同步插入与删除，用于存储与每个元素对应的最小值。
// 时间复杂度：对于题目中的所有操作，时间复杂度均为 O(1)
// 空间复杂度：O(n)
class MinStack {
public:
    stack<int>stack,min_stack;
    MinStack() {
        min_stack.push(INT_MAX);
    }
    void push(int val) {
        stack.push(val);
        min_stack.push(min(val,min_stack.top()));
    }
    void pop() {
        stack.pop();
        min_stack.pop();
    }
    int top() {
        return stack.top();
    }
    int getMin() {
        return min_stack.top();
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
