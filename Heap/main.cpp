//
//  main.cpp
//  Heap
//
//  Created by 文柳懿 on 2025/3/14.
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// 1. T215.数组中的第K个最大元素
/*给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。*/

// 法一：快排->快速选择：从递归两个区间，优化为只递归一个区间
/*快速排序的性能和「划分」出的子数组的长度密切相关。直观地理解如果每次规模为 n 的问题我们都划分成 1 和 n−1，每次递归的时候又向 n−1 的集合中递归，这种情况是最坏的，时间代价是 O(n^2)。我们可以引入随机化来加速这个过程，它的时间代价的期望是O(n)，证明过程可以参考「《算法导论》9.2：期望为线性的选择算法」。需要注意的是，这个时间复杂度只有在 随机数据 下才成立，而对于精心构造的数据则可能表现不佳。*/
class Solution_1_1 {
public:
    int getRandom(int i,int j){
        return rand()%(j-i+1)+i;
    }
    int quickSelect(vector<int>&nums,int left,int right, int k){
        if(left==right) return nums[k];
        int i=left,j=right;
        int pivot=nums[getRandom(i, j)];
        
        while(i<=j){
            while(nums[i]<pivot) i++;
            while(nums[j]>pivot) j--;
            if(i<=j){
                swap(nums[i],nums[j]);
                i++;j--;
            }
        }
        if(k<=j) return quickSelect(nums, left, j, k);
        else return quickSelect(nums, j+1, right, k);
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        int n=nums.size();
        return quickSelect(nums,0,n-1,n-k);
    }
};

// 法二：堆排序：建立一个大根堆，取 k−1 次删除操作后堆顶元素
// 时间复杂度：建堆的时间代价是 O(n)，删除的总代价是 O(klogn)；总时间复杂度O(n*logn)
class Solution_1_2{
public:
    void maxHeapify(vector<int>&a, int i, int heapSize){
        int l=i*2+1,r=i*2+2,largest=i;
        if(l<heapSize && a[l]>a[largest]){
            largest=l;
        }
        if(r<heapSize && a[r]>a[largest]){
            largest=r;
        }
        if(largest!=i){
            swap(a[i],a[largest]);
            maxHeapify(a, largest, heapSize);
        }
    }
    void buildMaxHeap(vector<int>&a,int heapSize){
        for(int i=heapSize/2-1;i>=0;i--){
            maxHeapify(a, i, heapSize);
        }
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        int heapSize=nums.size();
        buildMaxHeap(nums,heapSize);
        
        for(int i=nums.size()-1;i>=nums.size()-k+1;i--){
            swap(nums[0],nums[i]);  // 删掉当前最大的元素，即堆顶元素
            heapSize--;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};

// 2. T502.IPO
/*给你 n 个项目。对于每个项目 i ，它都有一个纯利润 profits[i] ，和启动该项目需要的最小资本 capital[i] 。
 最初，你的资本为 w 。当你完成一个项目时，你将获得纯利润，且利润将被添加到你的总资本中。
 总而言之，从给定项目中选择 最多 k 个不同项目的列表，以 最大化最终资本 ，并输出最终可获得的最多资本。
 答案保证在 32 位有符号整数范围内。*/
class Solution_2 {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
