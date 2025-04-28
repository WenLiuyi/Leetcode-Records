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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
