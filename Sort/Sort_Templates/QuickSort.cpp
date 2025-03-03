//
//  main.cpp
//  Sort_QuickSort_Templates
//
//  Created by 文柳懿 on 2025/3/3.
//

#include <iostream>
#include <vector>
using namespace std;

/*（小数，基准元素，大数）。在区间中随机挑选一个元素作基准，将小于基准的元素放在基准之前，大于基准的元素放在基准之后，再分别对小数区与大数区进行排序。
快速排序思路：
1. 选取第一个数为基准
2. 将比基准小的数交换到前面，比基准大的数交换到后面
3. 对左右区间重复第二步，直到各区间只有一个数*/

// 1. 快速排序（迭代）
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

// 2. 快速排序（递归）
template<typename T>
void quickSort_recursive(T arr[],int start,int end){
    if(start>=end) return;      // 1. 递归终止条件：当前子数组已经有序（长度为 0 或 1），直接返回
    T mid=arr[end];     // 设置最后一个为基准
    int left=start,right=end-1;
    
    // 2. 分区过程：
    while(left<right){
        while(left<right && arr[left]<mid) left++;  // 找到左侧>=基准元素的第一个值
        while(left<right && arr[right]>=mid) right--;   // 找到右侧<基准元素的第一个值
        swap(arr[left],arr[right]);     // 交换左右指针指向的元素
    }
    // 3. 处理基准元素：
    if(arr[left]>arr[end]) swap(arr[left],arr[end]);    // 将基准元素放到正确的位置
    else left++;        // 如果基准元素已经是最大的，left 指针右移。
    // 4. 递归调用
    quickSort_recursive(arr, start, left-1);
    quickSort_recursive(arr, left+1, end);
}

template<typename T>
void QuickSort(T arr[],int len){
    quickSort_recursive(arr, 0, len-1);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
