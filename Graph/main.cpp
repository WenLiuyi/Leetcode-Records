//
//  main.cpp
//  Graph
//
//  Created by 文柳懿 on 2025/4/28.
//

#include <iostream>
#include <vector>
using namespace std;

// 1. T797.所有可能的路径
/* 给你一个有 n 个节点的 有向无环图（DAG），请你找出所有从节点 0 到节点 n-1 的路径并输出（不要求按特定顺序）
 graph[i] 是一个从节点 i 可以访问的所有节点的列表（即从节点 i 到节点 graph[i][j]存在一条有向边）。 */

/* 提示：
 n == graph.length
 2 <= n <= 15
 0 <= graph[i][j] < n
 graph[i][j] != i（即不存在自环）
 graph[i] 中的所有元素 互不相同
 保证输入为 有向无环图（DAG）*/

// 邻接表存储
// 时间复杂度：O(n*2^n)，可以找到一种最坏情况，即每一个点都可以去往编号比它大的点。此时路径数为 O(2^n)，且每条路径长度为 O(n)
// 空间复杂度：O(n)
class Solution_1{
private:
    vector<vector<int>>res;
    vector<int>path;
    
    void dfs(vector<vector<int>>& graph, int x, int n){
        if(x==n-1){
            res.push_back(path);
            return;
        }
        for(auto const &node:graph[x]){
            path.push_back(node);
            dfs(graph,node,n);
            path.pop_back();
        }
    }
public:
    
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n=graph.size();
        path.push_back(0);
        dfs(graph,0,n);
        return res;
    }
};

// 2.T200.岛屿数量
// 法一：DFS
// 时间复杂度：O(mn)；空间复杂度：O(mn)，最坏情况下，全部都是陆地，DFS深度为O(mn)
class Solution_2_1{
private:
    int dir[4][2]={0,1,0,-1,1,0,-1,0};
    void dfs(const vector<vector<char>>&grid, vector<vector<bool>>&visited, int x, int y){
        // (x,y)为当前位置坐标
        if(visited[x][y] || grid[x][y]=='0'){     // 终止条件：当前位置已访问/不是陆地
            return;
        }
        visited[x][y]=true;
        for(int i=0;i<4;i++){
            int nextX=x+dir[i][0];
            int nextY=y+dir[i][1];
            if(nextX<0||nextX>=grid.size()||nextY<0||nextY>=grid[0].size()){
                continue;   // 越界跳过
            }
            dfs(grid,visited,nextX,nextY);
        }
    }
    
public:
    int numIslands(vector<vector<char>>&grid){
        int m=grid.size(),n=grid[0].size();
        int res=0;
        vector<vector<bool>>visited(m,vector<bool>(n,false));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(!visited[i][j] && grid[i][j]=='1'){
                    res++;
                    dfs(grid,visited,i,j);
                }
            }
        }
        return res;
    }
};

// 法二：BFS
// 时间复杂度：O(mn)；空间复杂度：O(min(m,n))
class Solution2_2{
private:
    int dir[4][2]={0,1,0,-1,1,0,-1,0};
    void bfs(const vector<vector<char>>&grid, vector<vector<bool>>&visited, int x, int y){
        queue<pair<int, int>>que;
        que.push({x,y});        // 当前节点进入队列
        visited[x][y]=true;
        
        while(!que.empty()){
            pair<int, int>cur=que.front();que.pop();
            for(int i=0;i<4;i++){
                int nextX=cur.first+dir[i][0];
                int nextY=cur.second+dir[i][1];
                if(nextX<0||nextX>=grid.size()||nextY<0||nextY>=grid[0].size()){
                    continue;   // 越界跳过
                }
                if(!visited[nextX][nextY] && grid[nextX][nextY]=='1'){
                    que.push({nextX, nextY});
                    visited[nextX][nextY]=true;     // 假如队列立即标记
                }
            }
        }
    }
public:
    int numIslands(vector<vector<char>>&grid){
        int m=grid.size(),n=grid[0].size();
        int res=0;
        vector<vector<bool>>visited(m,vector<bool>(n,false));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(!visited[i][j] && grid[i][j]=='1'){
                    res++;
                    bfs(grid, visited, i, j);
                }
            }
        }
        return res;
    }
};

// 3. T695.岛屿的最大面积
/* 给你一个大小为 m x n 的二进制矩阵 grid 。
 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
 岛屿的面积是岛上值为 1 的单元格的数目。
 计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。*/
class Solution_3 {
private:
    int count=0;
    int dir[4][2]={0,1,0,-1,1,0,-1,0};
    void dfs(const vector<vector<int>>&grid, vector<vector<bool>>&visited, int x, int y){
        // (x,y)为当前位置坐标
        if(visited[x][y] || grid[x][y]==0){     // 终止条件：当前位置已访问/不是陆地
            return;
        }
        visited[x][y]=true;count++;     // 访问当前节点(i,j)
        for(int i=0;i<4;i++){
            int nextX=x+dir[i][0];
            int nextY=y+dir[i][1];
            if(nextX<0||nextX>=grid.size()||nextY<0||nextY>=grid[0].size()){
                continue;   // 越界跳过
            }
            dfs(grid,visited,nextX,nextY);
        }
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m=grid.size(),n=grid[0].size();
        int res=0;
        vector<vector<bool>>visited(m,vector<bool>(n,false));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(!visited[i][j] && grid[i][j]==1){
                    count=0;
                    dfs(grid,visited,i,j);
                    res=max(res,count);
                }
            }
        }
        return res;
    }
};

// 4. T994.腐烂的橘子
/* 在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：
 
 值 0 代表空单元格；
 值 1 代表新鲜橘子；
 值 2 代表腐烂的橘子。
 每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。

 返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。*/

// BFS
// 时间复杂度：O(mn)；空间复杂度：O(mn)

class Solution_4{
private:
    int min=-1;
    int dir[4][2]={0,1,0,-1,1,0,-1,0};
    void bfs(vector<vector<int>>&grid, queue<pair<int,int>>que){
        while(!que.empty()){
            min++;
            int n=que.size();
            for(int i=0;i<n;i++){
                auto cur=que.front();que.pop();
                for(int i=0;i<4;i++){
                    int nextX=cur.first+dir[i][0];
                    int nextY=cur.second+dir[i][1];
                    if(nextX<0||nextX>=grid.size()||nextY<0||nextY>=grid[0].size()){
                        continue;
                    }
                    if(grid[nextX][nextY]==1){      // 当前轮新腐烂的橘子
                        que.push({nextX,nextY});
                        grid[nextX][nextY]=2;
                    }
                }
            }
        }
    }
public:
    int orangesRotting(vector<vector<int>>&grid){
        queue<pair<int, int>>que;   // 保存上一轮刚刚腐烂的橘子坐标
        int m=grid.size(),n=grid[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){
                    que.push({i,j});
                }
            }
        }
        bfs(grid,que);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    return -1;      // 有新鲜橘子永远不腐烂
                }
            }
        }
        return min>=0?min:0;
    }
};

// 5. T208.实现Trie（前缀树）
/* Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。
 
 请你实现 Trie 类：
 Trie() 初始化前缀树对象。
 void insert(String word) 向前缀树中插入字符串 word 。
 boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
 boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。 */

/* 1 <= word.length, prefix.length <= 2000
 word 和 prefix 仅由小写英文字母组成
 insert、search 和 startsWith 调用次数 总计 不超过 3 * 104 次 */
// 时间复杂度：初始化O(1)，其余操作O(|S|), 其中|S|是每次插入或查询的字符串的长度；
// 空间复杂度：O(∣T∣⋅Σ)，其中∣T∣为所有插入字符串的长度之和，Σ 为字符集的大小，本题 Σ=26.
class Trie{
private:
    vector<Trie*>children;
    bool isEnd;
    
    Trie *searchPrefix(string prefix){
        Trie *cur=this;
        int n=prefix.size();
        for(int i=0;i<n;i++){
            int ch=prefix[i]-'a';
            if(cur->children[ch]==nullptr){
                return nullptr;
            }
            cur=cur->children[ch];
        }
        return cur;
    }
    
public:
    Trie():children(26),isEnd(false){}
    
    void insert(string word){
        Trie *cur=this;
        int n=word.size();
        for(int i=0;i<n;i++){   // 遍历单词的每个字符
            int ch=word[i]-'a';
            if(cur->children[ch]==nullptr){
                cur->children[ch]=new Trie();
            }
            cur=cur->children[ch];  // 递推
        }
        cur->isEnd=true;
    }
    bool search(string word){
        Trie *node=searchPrefix(word);
        return node!=nullptr && node->isEnd;
    }
    bool startsWith(string prefix){
        return this->searchPrefix(prefix)!=nullptr;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
