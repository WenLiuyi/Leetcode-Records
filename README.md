# Leetcode-C++
## STL数据结构
### 1. 优先队列(priority_queue)
* 容器适配器：对外接口只是从队头取元素，从队尾添加元素，再无其他取元素的方式。
* 其中的元素按照某种优先级顺序排列，每次访问或删除的元素都是优先级最高的元素。
#### 1.1 基本特性
1. 默认行为：std::priority_queue 是一个**最大堆**，即优先级最高的元素是最大的元素。
2. 底层容器：std::priority_queue 默认使用 **std::vector**作为底层容器，但也可以指定其他容器（如 std::deque）。
3. 核心操作：
    * `push()`：插入元素--O(logn)
    * `pop()`：删除优先级最高的元素--O(logn)
    * `top()`：访问优先级最高的元素--O(1)
    * `empty()`：检查队列是否为空--O(1)
    * `size()`：返回队列中元素的数量--O(1)
#### 1.2 定义与初始化
1. 默认最大堆：
```C
#include<queue>
using namespace std;
priority_queue<int>maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap; // 通过传递自定义比较函数（如 std::greater）实现最小堆
```
2. 自定义优先级规则：
* 注意：left>right建立小顶堆（快排：快排的cmp函数的时候，return left>right 就是从大到小，return left<right 就是从小到大）
```C
#include <queue>
#include <functional>
using namespace std;
auto cmp = [](int a, int b) { return a > b; }; // 自定义比较函数
priority_queue<int, vector<int>, decltype(cmp)> customHeap(cmp);
```
#### 1.3 应用场景
1. Top K问题：使用优先队列可以高效地找到数组中最大或最小的 K 个元素。
    * 时间复杂度：O(n*logk)；空间复杂度：O(n)
    ```C
    class Solution_7 {
    public:
    class myCompare{
    public:
        bool operator()(const pair<int,int>&lhs,const pair<int,int>&rhs){
            return lhs.second>rhs.second;   // 满足时返回值1：lhs排在rhs之后
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 1. 统计元素出现的频率：遍历数组nums，使用map记录
        unordered_map<int,int>map;  // key为元素值；value为出现次数
        int n=nums.size();
        for(int i=0;i<n;i++){
            map[nums[i]]++;
        }
        // 2. 建立一个大小为k的小顶堆：每次插入一个新的值，弹出最小的元素（若使用大顶堆，则需要把所有元素都进行排序，而小顶堆只排序k个元素），这是由于：优先队列只能弹出队首（即堆顶）元素
        priority_queue<pair<int,int>,vector<pair<int,int>>,myCompare>queue;
        for(unordered_map<int, int>::iterator it=map.begin();it!=map.end();it++){   // 采用迭代器遍历map
            queue.push(*it);
            if(queue.size()>k) queue.pop();     // 弹出队首（即堆顶的最小元素）
        }
        // 3. 找出前k个高频元素：倒序输出
        vector<int>res(k);
        for(int i=k-1;i>=0;i--){
            res[i]=queue.top().first;
            queue.pop();
        }
        return res;
    }
    };
    ```

### 2. 映射(map,multimap,unordered_map)
* 遍历map(采用迭代器)：
    ```C
    for(unordered_map<int, int>::iterator it=map.begin();it!=map.end();it++){   // 采用迭代器遍历map
        // *it获取map中的键值对
        }
    ```

## 排序
### 1. 快速排序(QuickSort)
> 参考：https://zh.wikipedia.org/wiki/快速排序
* 基于**分治法**：通过选择一个基准元素(pivot)，将数组分为两部分：一部分小于基准元素，另一部分大于基准元素，然后递归地对这两部分进行排序。
1. 挑选基准值：从数列中挑出一个元素，称为“基准”（pivot），
2. 分割：重新排序数列，所有比基准值小的元素摆放在基准前面，所有比基准值大的元素摆在基准后面（与基准值相等的数可以到任何一边）。在这个分割结束之后，对基准值的排序就已经完成，
3. 递归排序子序列：递归地将小于基准值元素的子序列、大于基准值元素的子序列排序。
> 递归到最底部的判断条件是数列的大小是零或一，此时该数列显然已经有序。
### 2. 复杂度
* 平均时间复杂度：O(n*logn)
* 最坏时间复杂度：O(n^2)（当每次选择的基准元素都是最大或最小值时）
* 空间复杂度：O(logn)（递归调用栈的深度）
### 3. 实现
#### 3.1 递归实现
```C
// 1. 快速排序（递归）
template<typename T>
void quickSort(T A[],int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = A[(left + right) / 2];

    while (i <= j) {
        while (A[i] < pivot) i++;
        while (A[j] > pivot) j--;
        if (i <= j) {
            swap(A[i], A[j]);
            i++;
            j--;
        }
    };

    if (left < j) quickSort(A,left, j);
    if (i < right) quickSort(A,i, right);
}
```
### 4. 优化
#### 4.1 随机选择基准元素
朴素快排的缺陷：
1. **基准元素选择不当**：比如快排一个有序序列1234567，首先划分1和右区间234567接着划分2和右区间34567，以此类推，直到划分到n层，在做数组划分的时候会遍历整个数组一遍，此时时间复杂度就是O(N)级别；
```C
//优化一：随机选择基准元素
#include <ctime>
srand(time(0));
int get_random(int left, int right){
    return a[rand() % (right - left + 1) + left];   // 在 [left，right]区间内，随机选择一个数
}
```
#### 4.2 
2. **有大量重复元素时，递归层数也会增加**：比如数组里面全都是6，不管选择哪一个位置的6为基准元素，选择完后都会划分大于等于6的区间出来，之后再选择再划分，一直划分到数组元素个数的层数就和上面的情况一样了。
    * 例：荷兰国旗问题(Leetcode.T75)

## 数组
### 2. 二分查找
## 链表

## 哈希表
### 1. 理论基础
* 场景：**要快速判断一个元素是否出现集合里的时候**
* 本质：牺牲了空间、换取了时间：因为我们要使用额外的数组，set或者是map来存放数据，才能实现快速的查找
* 使用：要使用集合来解决哈希问题的时候：
    1. 优先使用`unordered_set`，查询和增删效率最优（均为O(1)）；
    2. 如果需要集合有序，则使用`set`；
    3. 如果要求不仅有序还要有重复数据的话，则使用`multiset`.

| 集合               | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
|--------------------|----------|----------|------------------|--------------|----------|----------|
| std::set           | 红黑树   | 有序     | 否               | 否           | O(log n) | O(log n) |
| std::multiset      | 红黑树   | 有序     | 是               | 否           | O(log n) | O(log n) |
| std::unordered_set | 哈希表   | 无序     | 否               | 否           | O(1)     | O(1)     |

* std::unordered_map 底层实现为哈希表，std::map 和std::multimap 的底层实现是红黑树。同理，std::map 和std::multimap 的key也是有序的。

| 映射                | 底层实现 | 是否有序   | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
|---------------------|----------|------------|------------------|--------------|----------|----------|
| std::map           | 红黑树   | key 有序   | key 不可重复     | key 不可修改 | O(log n) | O(log n) |
| std::multimap      | 红黑树   | key 有序   | key 可重复       | key 不可修改 | O(log n) | O(log n) |
| std::unordered_map | 哈希表   | key 无序   | key 不可重复     | key 不可修改 | O(1)     | O(1)     |

#### 1.1 常见的三种哈希结构
1. 数组（数组大小已知时使用，如字母异位词；不适用于哈希值少、特别分散、跨度很大的题目）
2. set（集合）
> 直接使用set，占用空间比数组大，而且速度要比数组慢，set将数值映射到key上的步骤需要做hash计算。
> 因此优先用数组。
    * 例：两数组的交集
    ```C
    // 2. 两个数组的交集:给定两个数组 nums1 和 nums2 ，返回 它们的 交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
    // 思路：使用unordered_set，分别记录：nums1,nums2中出现过的字母
    // 时间复杂度：O(n+m)，m是因为要将set转为vector
    // 空间复杂度：O(n)
    class Solution_2 {
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
    ```
3. map（映射）
    * 例：字母异位词分组
    ```C
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
    ```
#### 1.2 两数之和
> 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
```C
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
```
#### 1.3 三数之和
> 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
```C
// 使用双指针：首先将数组排序，然后有一层for循环，i从下标0的地方开始，同时定一个下标left 定义在i+1的位置上，定义下标right 在数组结尾的位置上。
// 如果nums[i] + nums[left] + nums[right] > 0 ，left向右移动；
// 如果 nums[i] + nums[left] + nums[right] < 0 ，right向左移动。
// 时间复杂度：O(n^2)；空间复杂度：O(1)
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
```
* 拓展：四数之和
> 三数之和的双指针解法是一层for循环num[i]为确定值，然后循环内有left和right下标作为双指针，找到nums[i] + nums[left] + nums[right] == 0。
> 四数之和的双指针解法是两层for循环nums[k] + nums[i]为确定值，依然是循环内有left和right下标作为双指针，找出nums[k] + nums[i] + nums[left] + nums[right] == target的情况，三数之和的时间复杂度是O(n^2)，四数之和的时间复杂度是O(n^3) 。

* std::unordered_set底层实现为哈希表，std::set 和std::multiset 的底层实现是红黑树。红黑树是一种平衡二叉搜索树，所以key值是有序的，但key不可以修改，改动key值会导致整棵树的错乱，所以只能删除和增加。

## 字符串
## 双指针
## 滑动窗口
* 滑动窗口最大值
    > 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。返回 滑动窗口中的最大值 。
    * 滑动窗口每向右移动一位，则最左侧的元素移除，如何维护最大值？
        1. 采用大根堆实时维护一系列元素中的最大值（优先队列实现），为了保证堆顶的元素在滑动窗口中：不断地移除堆顶的元素，直到其确实出现在滑动窗口中
        2. 设置单调队列（严格递减）：
            * 最大值：队首元素
            * 移除最左侧元素：与队首元素相等时移除（即为最大值），否则不影响；
            * 加入最右侧元素：从队尾往前，淘汰队中所有小于当前元素的元素
        ```C
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
        ```
## 栈与队列
### 1. 理论基础
栈和队列是STL（C++标准库）里面的两个数据结构。
三个普遍的STL版本：
1. HP STL 其他版本的C++ STL，一般是以HP STL为蓝本实现出来的，HP STL是C++ STL的第一个实现版本，而且开放源代码。
2. P.J.Plauger STL 由P.J.Plauger参照HP STL实现出来的，被Visual C++编译器所采用，不是开源的。
3. SGI STL 由Silicon Graphics Computer Systems公司参照HP STL实现，被Linux的C++编译器GCC所采用，SGI STL是开源软件，源码可读性甚高。

#### std::stack, std::queue
* std::stack 是 C++ 标准库中的一个容器适配器，它基于其他容器（默认是 std::deque）实现栈的功能（对外提供统一的接口，底层容器是可插拔的）不提供走访功能，也不提供迭代器(iterator)。 不像是set 或者map 提供迭代器iterator来遍历所有元素。
![alt text](20210104235459376.png)

> 常用的SGI STL，如果没有指定底层实现的话，默认是以deque为缺省情况下栈的底层结构。
> 指定vector为栈的底层实现：`std::stack<int, std::vector<int> > third;  // 使用vector为底层容器的栈`
* STL 队列也不被归类为容器，而被归类为container adapter（ 容器适配器）。

##### 核心操作
* push()：将元素压入栈顶，调用底层容器的 push_back() 方法。
* pop()：移除栈顶元素，调用底层容器的 pop_back() 方法。
* top()：返回栈顶元素的引用，调用底层容器的 back() 方法。
* empty()：判断栈是否为空，调用底层容器的 empty() 方法。
* size()：返回栈中元素的数量，调用底层容器的 size() 方法。

##### 性能分析
性能取决于底层容器的实现。
* 如果使用 std::deque 作为底层容器：
    * push() 和 pop() 的时间复杂度为 O(1)。
    * top() 的时间复杂度为 O(1)。
* 如果使用 std::vector 作为底层容器：
    * push() 的时间复杂度为 O(1)（均摊时间复杂度，可能触发动态扩容）。
    * pop() 的时间复杂度为 O(1)。
    * top() 的时间复杂度为 O(1)。

##### 特点
* 后进先出（LIFO）：栈只允许在顶部插入和删除元素；
* 不支持随机访问：不能通过索引访问栈中的元素；
* 灵活性：可以通过更换底层容器来调整栈的行为和性能。

### 2. 括号匹配
* 栈实现的经典问题:遇到左括号时，将对应的右括号入栈；遇到右括号时，从栈顶弹出元素，观察是否匹配
* 类题：删除字符串中所有相邻重复项（当前字符与栈顶字符相同时，从栈中弹出）
    ```C
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
    ```
### 3. 逆波兰表达式求值
* 逆波兰表达式相当于是二叉树中的后序遍历。设立操作数栈
```C
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
```

## 二叉树
### 1. 理论基础
#### 1.1 二叉树的种类
##### 1.1.1 满二叉树：
    一棵二叉树只有度为0的结点和度为2的结点，并且度为0的结点在同一层上，则称为满二叉树；
    深度为h，有2^h-1个节点。
##### 1.1.2 完全二叉树：
    除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（h从1开始），则该层包含 1~ 2^(h-1) 个节点。
    * 完全二叉树，一定是：平衡二叉树

##### 1.1.3 二叉搜索树
**有序**树。
* 若左子树非空，则左子树上的所有结点的值，均小于根结点的值；
* 若右子树非空，则右子树上的所有结点的值，均大于根结点的值；
* 左、右子树也分别为二叉搜索树

##### 1.1.4 平衡二叉搜索树（AVL）
它是一棵空树；或它的左右两个子树的高度差的绝对值不超过1，并且左右两个子树都是一棵平衡二叉树。
平衡二叉树是一个：二叉搜索树
![alt text](20200806190511967.png)
> C++中map、set、multimap，multiset的底层实现都是平衡二叉搜索树，所以**map、set的增删操作时间时间复杂度是logn**；
> unordered_map、unordered_set，unordered_map、unordered_set底层实现是哈希表。

##### 最小失衡树：平衡二叉树插入新结点导致失衡的子树
###### (1)LL型：右旋
![alt text](3e080aaf06ba34b27ea0ae16ff1198bf.gif)
###### (2)RR型：左旋
![alt text](734f0281433dc39cc5224d045d094315.gif)
###### (3)LR型：以被破坏节点的L节点为基础左旋，再以被破坏节点为基础右旋
###### (4)RL型：以被破坏节点的R节点为基础右旋，再以被破坏节点为基础左旋

##### 1.1.5 红黑树
> 参考：https://cloud.tencent.com/developer/article/1879082
###### 特征
1. 节点是红色/黑色；
2. 根节点是黑色；
3. 所有叶子节点都是黑色；
4. 每个红色节点：必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）（新增节点的父节点必须相同）
5. 从任一节点，到其每个叶子的所有简单路径都包含相同数目的黑色节点。（新增节点必须为红）

###### 调整
变色；左旋；右旋

###### 应用
* 关联数组：如 STL 中的 map、set

###### 红黑树、B 树、B+ 树的区别？
红黑树的深度比较大，而 B 树和 B+ 树的深度则相对要小一些
B+ 树则将数据都保存在叶子节点，同时通过链表的形式将他们连接在一起。

##### 1.1.6 B树，B+树
![alt text](68747470733a2f2f692e737461636b2e696d6775722e636f6d2f6c365579462e706e67.png)
###### 特点
* 一般化的二叉查找树
* “矮胖”，内部（非叶子）节点可以拥有可变数量的子节点（数量范围预先定义好）

###### 应用
* 大部分文件系统、数据库系统都采用B树、B+树作为索引结构

###### 区别
* B+树中只有叶子节点会带有指向记录的指针（ROWID），而B树则所有节点都带有，在内部节点出现的索引项不会再出现在叶子节点中。
* B+树中所有叶子节点都是通过指针连接在一起，而B树不会。

###### B树的优点
对于在内部节点的数据，可直接得到，不必根据叶子节点来定位。

###### B+树的优点
非叶子节点不会带上 ROWID，这样，一个块中可以容纳更多的索引项，一是可以降低树的高度。二是一个内部节点可以定位更多的叶子节点。
叶子节点之间通过指针来连接，范围扫描将十分简单，而对于B树来说，则需要在叶子节点和内部节点不停的往返移动。

#### 1.2 二叉树的存储方式
##### 1.2.1 链式存储（指针）

##### 1.2.2 顺序存储（数组）
![alt text](20200920200429452.png)
若父节点的数组下标为i，则**左孩子下标为2*i+1，右孩子下标为2*i+2**。

#### 1.3 二叉树的遍历方式
##### 1.3.1 深度优先遍历（DFS）：栈实现
1. 前序遍历（递归，迭代）：中左右
2. 中序遍历（递归，迭代）：左中右
3. 后序遍历（递归，迭代）：左右中
* 时间复杂度：O(n)；空间复杂度：O(n)，递归过程栈的开销，平均为O(logn），最坏情况为O(n)

##### 1.3.2 广度优先遍历（BFS）：队列实现
层次遍历（迭代）

#### 1.4 二叉树的定义
```C
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
    TreeNode(int x,TreeNode *left,TreeNode *right): val(x),left(left),right(right){}
};
```

#### 1.5 二叉树的性质
1. 非空二叉树第i层最多:2^(i-1)个节点(i>=1)
2. 深度为k的二叉树最多:2^k-1个节点
3. 度为 0 的结点数为 n0，度为 2 的结点数为 n2，则 n0 = n2 + 1
4. 有 n 个结点的完全二叉树深度 k = ⌊ log2(n) ⌋ + 1
5. 对于含 n 个结点的完全二叉树中编号为 i （1 <= i <= n） 的结点
    * 若 i = 1，为根，否则双亲为 ⌊ i / 2 ⌋
    * 若 2i > n，则 i 结点没有左孩子，否则孩子编号为 2i
    * 若 2i + 1 > n，则 i 结点没有右孩子，否则孩子编号为 2i + 1

### 2. 二叉树的遍历
#### 2.1 二叉树的递归遍历
递归三要素：递归函数的参数、返回值；终止条件；单层递归逻辑
前序遍历：
```C
class Solution {
public:
    void preOrder(TreeNode *cur,vector<int> &res){
        if(cur==NULL) return;       // 终止条件
        res.push_back(cur->val);    // 中
        preOrder(cur->left,res);   // 左
        preOrder(cur->right,res);  // 右
    }
    
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        preOrder(root,ret);
        return ret;
    }
};
```

#### 2.2 二叉树的迭代遍历
递归的实现就是：每一次递归调用都会把函数的局部变量、参数值和返回地址等压入调用栈中，然后递归返回的时候，从栈顶弹出上一次递归的各项参数，所以这就是递归为什么可以返回上一层位置的原因。
迭代过程包括两个操作：
1. 处理：将元素放进result数组
2. 访问：遍历节点

##### 2.2.1 前序遍历的迭代
中-左-右：处理和访问的顺序一致
入栈顺序：根节点-右孩子-左孩子，出栈时反向

##### 2.2.2 中序遍历的迭代
左中右：先访问的是二叉树顶部的节点，然后一层一层向下访问，直到到达树左面的最底部，再开始处理节点（也就是在把节点的数值放进result数组中），这就造成了处理顺序和访问顺序是不一致的。

##### 2.2.3 后序遍历的迭代
前序遍历（中-左-右），调整代码顺序，中-右-左（节点加入栈的顺序：根节点，左孩子，右孩子）；翻转数组，左-右-中

#### 2.3 二叉树的统一迭代法（统一前序，中序，后序遍历的写法）
使用栈的话，无法同时解决访问节点（遍历节点）和处理节点（将元素放进结果集）不一致的情况。
就将访问的节点放入栈中，把要处理的节点也放入栈中但是要做标记。
如何标记呢？
1. 方法一：就是要处理的节点放入栈之后，紧接着放入一个空指针作为标记。 这种方法可以叫做空指针标记法。
2. 方法二：加一个 boolean 值跟随每个节点，false (默认值) 表示需要为该节点和它的左右儿子安排在栈中的位次，true 表示该节点的位次之前已经安排过了，可以收割节点了。 这种方法可以叫做boolean 标记法，样例代码见下文C++ 和 Python 的 boolean 标记法。 这种方法更容易理解，在面试中更容易写出来。

#
```C
// 前序遍历：中-左-右；加入栈的顺序：右-左-中
// 空指针标记法
class Solution1_3{
public:
    vector<int> preorderTraversal(TreeNode *root){
        vector<int>ret;
        if(root==nullptr) return ret;
        
        stack<TreeNode *>stack;
        stack.push(root);
        
        while(!stack.empty()){
            TreeNode *node=stack.top();
            if(node!=NULL){
                stack.pop();
                if(node->right) stack.push(node->right);    // 右
                if(node->left) stack.push(node->left);      // 左
                stack.push(node);stack.push(nullptr);       // 中
            }else{
                stack.pop();
                node=stack.top();stack.pop();
                ret.push_back(node->val);
            }
        }
        return ret;
    }
};
```

#### 2.4 二叉树的层序遍历（BFS）
模版：
```C
class Solution{
public:
    vector<vector<int>> levelOrder(TreeNode *root){
        vector<vector<int>> ret;
        if(!root) return ret;   // 判断非空
        
        queue<TreeNode *> q;    // 创建队列
        q.push(root);
        
        while(!q.empty()){
            int size=q.size();  // 当前队列中元素个数=当前层的节点个数
            ret.push_back(vector<int>());     // ret中每个子树组，存储当前层的所有节点
            for(int i=0;i<size;i++){
                auto node=q.front();q.pop();    // 1. 取出队列首个元素
                ret.back().push_back(node->val);    // 2. ret中最后一个数组，加入当前节点的值
                // 3. 将当前元素的左右节点，加入队尾
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return ret;
    }
};
```

### 3. 二叉树的属性
#### 深度和高度
![alt text](20210203155515650.png)
* 求深度：从上到下，可使用前序遍历
* 求高度：从底向上，采用后序遍历

* 二叉树的最大深度：
    1. 递归：即根节点的高度（通过后序遍历求）
    2. 迭代：使用层序遍历，最大深度为二叉树层数

* T226. 翻转二叉树：
    1. 递归：采用前序遍历：先交换左右孩子节点，再反转左子树，反转右子树。
    2. 迭代：
        （1）DFS：前序遍历的统一迭代，栈依次压入：右-左-中；弹出节点时，交换左右节点
        （2）BFS：把每一个节点的左右孩子翻转一遍
    > 同类题：T2415.反转二叉树的奇数层

* 平衡二叉树：
    > 判断它是否是 平衡二叉树。平衡二叉树 是指该树所有节点的左右子树的高度相差不超过 1。
    1. 递归：判断高度：采用后序遍历，自底向上，求左、右子树的高度；用-1标记不平衡树，直接返回。

* 二叉树的所有路径：按 任意顺序 ，返回所有从根节点到叶子节点的路径。
    * 采用前序遍历，递归+回溯
```C
class Solution {
private:
    void traversal(TreeNode *cur,string path,vector<string>& result){
        path+=to_string(cur->val);  // 中(最后一个叶节点需要加入path)
        /* 注：这一步不用回溯，因为：使用的是 string path，没有加上引用& ，即本层递归中，path + 该节点数值，但该层递归结束，上一层path的数值并不会受到任何影响。
         不带引用，不做地址拷贝，只做内容拷贝的效果。
         */
        if(cur->left==nullptr && cur->right==nullptr){
            // 终止处理逻辑：遇到叶子节点
            result.push_back(path);
            return;
        }
        if(cur->left){
            path+="->";
            traversal(cur->left, path, result);
            // 回溯和递归是一一对应的
            path.pop_back();    // 回溯'>'
            path.pop_back();    // 回溯'-'
        }
        if(cur->right){
            path+="->";
            traversal(cur->right, path, result);
            path.pop_back();    // 回溯'>'
            path.pop_back();    // 回溯'-'
        }
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string>result;
        string path;
        if(root==nullptr) return result;
        traversal(root,path,result);
        return result;
    }
};
```

* 二叉树的路径之和I和II：
    1. 递归：叶子节点时返回；单层逻辑：递归、回溯
    > 递归函数是否需要返回值：
    > 1. 需要搜索整棵二叉树，且不用处理递归返回值：递归函数就不要返回值；（路径之和II）
    > 2. 需要搜索整棵二叉树，且需要处理递归返回值：递归函数就需要返回值；
    > 3. 要搜索其中一条符合条件的路径：那么递归一定需要返回值（路径之和I）

### 4. 二叉树的修改与构造
* T106.从中序、后序遍历序列构造二叉树（没有重复元素）
    (1) 以后序遍历最后一个节点作为元素，找到其在中序遍历序列中的位置，作为切割点
    (2) 切割中序数组；
    (3) 切割后序数组(利用中序左数组大小，等于后序左数组大小)

> 前序和中序可以唯一确定一棵二叉树。
> 后序和中序可以唯一确定一棵二叉树。
> 前序和后序不能唯一确定一棵二叉树！，因为没有中序遍历无法确定左右部分，也就是无法分割。
```C
// 递归：
class Solution_1 {
private:
    TreeNode *traversal(vector<int>& inorder,int inorderBegin,int inorderEnd, vector<int>& postorder,int postorderBegin,int postorderEnd){
        // 返回值：当前序列还原出的树；参数：中序区间：[inorderBegin, inorderEnd)，后序区间[postorderBegin, postorderEnd)
        if(postorderBegin==postorderEnd) return nullptr;    // 当前为空节点
        
        int rootValue=postorder[postorderEnd-1];
        TreeNode *root=new TreeNode(rootValue);   // 1. 后序数组的最后一个元素，为根节点
        
        if(postorderEnd-postorderBegin==1) return root; // 叶子节点
        
        // 2. 在中序遍历序列中，查找根节点位置
        int delimiter;
        for(delimiter=inorderBegin;delimiter<inorderEnd;delimiter++){
            if(inorder[delimiter]==rootValue) break;
        }
        
        // 3. 切割中序数组
        int leftInorderBegin=inorderBegin;
        int leftInorderEnd=delimiter;
        int rightInorderBegin=delimiter+1;
        int rightInorderEnd=inorderEnd;
        
        // 4. 切割后序数组
        int leftPostorderBegin=postorderBegin;
        int leftPostorderEnd=postorderBegin+delimiter-inorderBegin;
        int rightPostorderBegin=leftPostorderEnd;
        int rightPostorderEnd=postorderEnd-1;   // 排除最后一个节点（根节点）
        
        root->left=traversal(inorder,leftInorderBegin,leftInorderEnd,postorder,leftPostorderBegin,leftPostorderEnd);
        root->right=traversal(inorder,rightInorderBegin,rightInorderEnd,postorder,rightPostorderBegin,rightPostorderEnd);
        
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size()==0 || postorder.size()==0) return nullptr;
        return traversal(inorder, 0, inorder.size(), postorder, 0, postorder.size());   // 左闭右开
    }
};
```

* 删除二叉树的节点
```C
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;
        if (root->val == key) {
            if (root->right == nullptr) { // 这里第二次操作目标值：最终删除的作用
                return root->left;
            }
            TreeNode *cur = root->right;
            while (cur->left) {
                cur = cur->left;
            }
            swap(root->val, cur->val); // 这里第一次操作目标值：交换目标值其右子树最左面节点。
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }
};
```

### 5. 二叉树公共祖先问题
* 二叉树的最近公共祖先
>  给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
    * 递归：自底向上查找公共祖先，后序遍历（左-右-中）是天然回溯，根据左右子树的返回值，确定中节点的处理逻辑(左右子树是否找到p,q)

若递归函数有返回值，区分要搜索一条边，还是搜索整个树：
> 注：求二叉树的最近公共祖先，需要搜索整棵树；求二叉搜索树的最近公共祖先，搜索一条边即可
1. 搜索一条边：
```C
if (递归函数(root->left)) return ;
if (递归函数(root->right)) return ;
```
2. 搜索整棵树：
```C
left = 递归函数(root->left);
right = 递归函数(root->right);
left与right的逻辑处理;
```

```C
// 递归：自底向上查找公共祖先，后序遍历（左-右-中）是天然回溯，根据左右子树的返回值，确定中节点的处理逻辑(左右子树是否找到p,q)
// 终止条件：p，q节点或空节点
class Solution_10 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 返回值：找到的p或q；若没找到，返回nullptr
        // 终止条件：如果遇到p或者q，就把q或者p返回；返回值不为空，就说明找到了q或者p
        if(root==p || root==q || root==nullptr) return root;
        TreeNode *left=lowestCommonAncestor(root->left,p,q);
        TreeNode *right=lowestCommonAncestor(root->right,p,q);
        
        if(left!=nullptr&&right!=nullptr) return root;
        
        // 左，右子树中，有一边找到了：把该节点的结果照原样返回上去
        if(left!=nullptr&&right==nullptr) return left;
        else if(left==nullptr&&right!=nullptr) return right;
        
        else return nullptr;
    }
};
```

* 二叉搜索树的最近公共祖先
```C
// 递归：公共祖先一定在[p,q]区间内
class Solution_7 {
private:
    TreeNode *traversal(TreeNode *root,TreeNode *p,TreeNode *q){
        if(root==nullptr) return root;
        
        if(p->val<root->val && q->val<root->val){
            // p,q均在当前节点root的左侧
            TreeNode *left=traversal(root->left,p,q);
            if(left!=nullptr) return left;  // 直接返回，保障是最近公共祖先
        }
        if(p->val>root->val && q->val>root->val){
            // p,q均在当前节点root的右侧
            TreeNode *right=traversal(root->right,p,q);
            if(right!=nullptr) return right;
        }
        // 当前节点root在[p,q]区间内：root是p,q的公共祖先
        return root;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return traversal(root,p,q);
    }
};
```

### 6. 二叉搜索树的属性
* 二叉树中序遍历得到升序序列，使用栈模拟实现。

* 频繁查找第k小的元素：记录以每个结点为根结点的子树的结点数，辅助查找
```C
class MyBst{
public:
    MyBst(TreeNode *root){
        this->root=root;
        countNodeNum(root);
    }
    int kthSmallest(int k){
        TreeNode *node=root;
        while(node!=nullptr){
            int left=countNodeNum(root->left);
            if(left<k-1){
                // 1. 在node的右子树中
                node=node->right;
                k-=left+1;
            }else if(left==k-1) break;  // 2. node
            else{
                node=node->left;    // 3. 在node的左子树中
            }
        }
        return node->val;
    }
    
private:
    TreeNode *root;
    unordered_map<TreeNode *, int>nodeNum;  // 节点-节点对应子树的节点数

    int countNodeNum(TreeNode *root){
        // 统计以root为根节点的子树节点数
        if(root==nullptr) return 0;
        nodeNum[root]=1+countNodeNum(root->left)+countNodeNum(root->right);
        return nodeNum[root];
    }
};
```

* 查找树的众数（不是二叉搜索树）
```C
class Solution {
private:
    void searchBST(TreeNode* cur, unordered_map<int, int>& map) { // 前序遍历
        if (cur == NULL) return ;
        map[cur->val]++; // 统计元素频率
        searchBST(cur->left, map);
        searchBST(cur->right, map);
        return ;
    }
    bool static cmp (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
public:
    vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> map; // key:元素，value:出现频率
        vector<int> result;
        if (root == NULL) return result;

        // 1. 遍历整个树，统计每个值的出现频率
        searchBST(root, map);

        // 2. 把统计的出来的出现频率（即map中的value）排个序
        /*
            C++中如果使用std::map或者std::multimap可以对key排序，但不能对value排序；
            要把map转化数组即vector，再进行排序
        */
        vector<pair<int, int>> vec(map.begin(), map.end());
        sort(vec.begin(), vec.end(), cmp); // 给频率排个序

        // 3. 取前面的高频元素
        result.push_back(vec[0].first);
        for (int i = 1; i < vec.size(); i++) {
            // 取最高的放到result数组中
            if (vec[i].second == vec[0].second) result.push_back(vec[i].first);
            else break;
        }
        return result;
    }
};
```

### 7. 二叉搜索树的修改与改造
* 删除二叉搜索树的节点
```C
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==nullptr) return root;  // 没找到要删除的节点
        if(root->val==key){
            // 1. 叶子节点
            if(root->left==nullptr && root->right==nullptr){
                delete root;    // 内存释放
                return nullptr;
            }
            else if(root->left==nullptr){   // 2. 左孩子为空，右孩子非空：直接用右孩子替代
                auto rightNode=root->right;
                delete root;
                return rightNode;
            }
            else if(root->right==nullptr){  // 3. 右孩子为空，左孩子非空：直接用左孩子替代
                auto leftNode=root->left;
                delete root;
                return leftNode;
            }
            else{   // 4. 左右孩子非空：将删除节点的左子树，放到删除节点的右子树的最左面节点的左孩子的位置
                TreeNode *cur=root->right;
                while(cur->left!=nullptr){
                    cur=cur->left;
                }
                cur->left=root->left;
                TreeNode *tmp=root;
                root=root->right;
                delete tmp;
                return root;
            }
        }
        if(root->val>key) root->left=deleteNode(root->left, key);
        if(root->val<key) root->right=deleteNode(root->right, key);
        return root;
    }
};
```

* 修剪二叉搜索树：给你二叉搜索树的根节点 root ，同时给定最小边界low 和最大边界 high。通过修剪二叉搜索树，使得所有节点的值在[low, high]中。修剪树 不应该 改变保留在树中的元素的相对结构 (即，如果没有被移除，原有的父代子代关系都应当保留)。 
    1. 递归剪枝：返回修改后的子树根节点
    ```C
    // 时间复杂度：O(n)，其中 n 为二叉树的结点数目。
    // 空间复杂度：O(n)。递归栈最坏情况下需要 O(n) 的空间。
    class Solution10_1 {
    public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        // 返回值：返回修改后的子树根节点
        // 终止条件：空节点
        if(root==nullptr) return root;
        if(root->val<low){  // 保留右子树，删除当前节点和左子树
            TreeNode *right=trimBST(root->right,low,high);
            return right;
        }
        if(root->val>high){ // 保留左子树，删除当前节点和右子树
            TreeNode *left=trimBST(root->left, low, high);
            return left;
        }
        root->left=trimBST(root->left, low, high);
        root->right=trimBST(root->right, low, high);
        return root;
    }
    };
    ```
    2. 迭代：剪枝范围：[low,high]：将root移到[low,high]之间，在其左右子树中分别截取一部分
    ```C
    class Solution10_2{
    public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(root==nullptr) return root;
        while(root!=nullptr && (root->val<low||root->val>high)){
            if(root->val<low) root=root->right;
            else root=root->left;
        }
        TreeNode *cur=root;
        while(cur!=nullptr){    // 修剪左子树：去掉小于low的部分：获取左子树中，大于等于low的最小元素
            while(cur->left!=nullptr && cur->left->val<low){
                cur->left=cur->left->right;
            }
            cur=cur->left;
        }
        cur=root;
        while(cur!=nullptr){    // 修剪右子树：去掉大于high的部分：获取右子树中，小于等于high的最大元素
            while(cur->right!=nullptr && cur->right->val>high){
                cur->right=cur->right->left;
            }
            cur=cur->right;
        }
        return root;
    }
    };
    ```

### 8. 总结
> * 涉及到二叉树的构造，无论普通二叉树还是二叉搜索树一定前序，都是先构造中节点。
> * 求普通二叉树的属性，一般是后序，一般要通过递归函数的返回值做计算（单纯求深度就用前序，二叉树：找所有路径 (opens new window)也用了前序，这是为了方便让父节点指向子节点）
> * 求二叉搜索树的属性，使用中序，利用有序性。
> ![alt text](20211030125421.png)
#### 8.1 求二叉树的属性
* 二叉树：是否对称 
    * 递归：后序，比较的是根节点的左子树与右子树是不是相互翻转
    * 迭代：使用队列/栈将两个节点顺序放入容器中进行比较
* 二叉树：求最大深度
    * 递归：后序，求根节点最大高度就是最大深度，通过递归函数的返回值做计算树的高度
    * 迭代：层序遍历
* 二叉树：求最小深度
    * 递归：后序，求根节点最小高度就是最小深度，注意最小深度的定义
    * 迭代：层序遍历
* 二叉树：求有多少个节点
    * 递归：后序，通过递归函数的返回值计算节点数量
    * 迭代：层序遍历
* 二叉树：是否平衡
    * 递归：后序，注意后序求高度和前序求深度，递归过程判断高度差
    * 迭代：效率很低，不推荐
* 二叉树：找所有路径
    * 递归：前序，方便让父节点指向子节点，涉及回溯处理根节点到叶子的所有路径
    * 迭代：一个栈模拟递归，一个栈来存放对应的遍历路径
* 二叉树：找所有路径
    * 递归如何隐藏着回溯
* 二叉树：求左叶子之和
    * 递归：后序，必须三层约束条件，才能判断是否是左叶子。
    * 迭代：直接模拟后序遍历
* 二叉树：求左下角的值
    * 递归：顺序无所谓，优先左孩子搜索，同时找深度最大的叶子节点。
    * 迭代：层序遍历找最后一行最左边
* 二叉树：求路径总和
    * 递归：顺序无所谓，递归函数返回值为bool类型是为了搜索一条边，没有返回值是搜索整棵树。
    * 迭代：栈里元素不仅要记录节点指针，还要记录从头结点到该节点的路径数值总和

#### 8.2 二叉树的修改与构造
* 翻转二叉树
    * 递归：前序，交换左右孩子
    * 迭代：直接模拟前序遍历
* 构造二叉树
    * 递归：前序，重点在于找分割点，分左右区间构造
    * 迭代：比较复杂，意义不大
* 构造最大的二叉树
    * 递归：前序，分割点为数组最大值，分左右区间构造
    * 迭代：比较复杂，意义不大
* 合并两个二叉树
    * 递归：前序，同时操作两个树的节点，注意合并的规则
    * 迭代：使用队列，类似层序遍历

#### 8.3 求二叉搜索树的属性
* 二叉搜索树中的搜索
    * 递归：二叉搜索树的递归是有方向的
    * 迭代：因为有方向，所以迭代法很简单
* 是不是二叉搜索树
    * 递归：中序，相当于变成了判断一个序列是不是递增的
    * 迭代：模拟中序，逻辑相同
* 求二叉搜索树的最小绝对差
    * 递归：中序，双指针操作
    * 迭代：模拟中序，逻辑相同
* 求二叉搜索树的众数
    * 递归：中序，清空结果集的技巧，遍历一遍便可求众数集合
* 二叉搜索树转成累加树
    * 递归：中序，双指针操作累加
    * 迭代：模拟中序，逻辑相同

#### 8.4 二叉树公共祖先问题
* 二叉树的公共祖先问题
    * 递归：后序，回溯，找到左子树出现目标值，右子树节点目标值的节点。
    * 迭代：不适合模拟回溯
* 二叉搜索树的公共祖先问题
    * 递归：顺序无所谓，如果节点的数值在目标区间就是最近公共祖先
    * 迭代：按序遍历

#### 8.5 二叉搜索树的修改与构造
* 二叉搜索树中的插入操作
    * 递归：顺序无所谓，通过递归函数返回值添加节点
    * 迭代：按序遍历，需要记录插入父节点，这样才能做插入操作
* 二叉搜索树中的删除操作
    * 递归：前序，想清楚删除非叶子节点的情况
    * 迭代：有序遍历，较复杂
* 修剪二叉搜索树
    * 递归：前序，通过递归函数返回值删除节点
    * 迭代：有序遍历，较复杂
* 构造二叉搜索树
    * 递归：前序，数组中间节点分割
    * 迭代：较复杂，通过三个队列来模拟


## 回溯
## 贪心
## 分治
## 动态规划
## 单调栈
单调队列：队中元素按严格递减排列
## 图
## 数学
### 1. 位运算