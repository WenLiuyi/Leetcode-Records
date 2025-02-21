//
//  main.c
//  BinarySearch
//
//  Created by 文柳懿 on 2023/8/20.
//

//二分查找

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

//T1(Leetcode35).搜索插入位置
//法一：递归：时间复杂度:O(logn);空间复杂度:O(logn).
/*
int insertWhere(int *nums,int left,int right,int target){
    if(left==right)
    {
        if(nums[left]>=target) return left;
        else return left+1;
    }
    int mid=(left+right)>>1;
    if(nums[mid]==target) return mid;
    else if(nums[mid]<target) return insertWhere(nums,mid+1,right,target);  //注意!这里用mid+1:因为left!=right时,永远有mid<right,不用mid+1,可能陷入无限递归
    else return insertWhere(nums,left,mid,target);
}
int searchInsert(int *nums,int numsSize,int target){
    if(numsSize==0) return 0;
    return insertWhere(nums,0,numsSize-1,target);
}
int main(){
    int a[4]={1,3,5,6};
    printf("%d",searchInsert(a,4,2));
    return 0;
}
 */

//法二:空间复杂度:O(1).
//问题本质：nums数组中,寻找大于等于target的下标。
int searchInsert(int *nums,int numsSize,int target){
    int left=0,right=numsSize-1,ans=numsSize;
    while(left<=right)
    {
        int mid=(left+right)>>1;
        if(nums[mid]>=target)       //大于等于时，才会更新ans值
        {
            ans=mid;
            right=mid-1;
        }
        else left=mid+1;
    }
    return ans;
}

//T2(Leetcode74).搜索二维矩阵
//每行非递减排列;下一行首元素大于前一行尾元素.

//寻找小于等于target的最大行首元素(仿T1思路)
int searchRow(int **matrix,int up,int down,int target){
    int ans=up-1;
    while(up<=down)
    {
        int mid=(up+down)>>1;
        if(matrix[mid][0]<=target)
        {
            ans=mid;
            up=mid+1;
        }
        else down=mid-1;
    }
    return ans;
}

bool searchCol(int *matrixRow,int left,int right,int target){
    while(left<=right)
    {
        int mid=(left+right)>>1;
        if(matrixRow[mid]==target) return true;
        else if(matrixRow[mid]<target) left=mid+1;
        else right=mid-1;
    }
    return false;
}

//两次二分查找：
//时间复杂度:O(logm+logn);空间复杂度:O(1).
bool searchMatrix(int **matrix,int matrixSize,int *matrixColSize,int target){
    if(matrixSize==0) return false;
    int row=searchRow(matrix,0,matrixSize-1,target);
    if(row<0) return false;
    return searchCol(matrix[row],0,*matrixColSize-1,target);
}

//T3.寻找峰值元素:其值严格大于左右相邻值(包括端点),返回索引元素
//法一：单次遍历
//法二：迭代爬坡:从一个位置起,不断向高处走
//时间复杂度:O(n);空间复杂度:O(1).
/*
int findPeakElement(int *nums,int numsSize){
    if(numsSize==1) return 0;
    int i=rand()%numsSize;
    while(1)
    {
        if(i==0)
        {
            if(nums[i]>nums[i+1]) return i;
            else i++;
        }
        else if(i==numsSize-1)
        {
            if(nums[i-1]<nums[i]) return i;
            else i--;
        }
        else if(nums[i-1]<nums[i]&&nums[i]>nums[i+1]) break;
        else if(nums[i-1]<nums[i]) i++;
        else i--;
    }
    return i;
}
*/

//法三:法二的二分查找优化:
//法二中,若由i->i+1,在后续迭代中,不会再走到i左侧的位置
//时间复杂度:O(logn).
int findPeakElement(int *nums,int numsSize){
    if(numsSize==1) return 0;
    int left=0,right=numsSize-1,ans=-1;
    while(left<=right)
    {
        int mid=(left+right)/2;
        if(mid==0&&nums[mid]>nums[mid+1]) {ans=mid;break;}
        else if(mid==0&&nums[mid]<nums[mid+1]) left=mid+1;
        else if(mid==numsSize-1&&nums[mid-1]<nums[mid]) {ans=mid;break;}
        else if(mid==numsSize-1&&nums[mid-1]>nums[mid]) right=mid-1;
        else if(nums[mid-1]<nums[mid]&&nums[mid]>nums[mid+1]) {ans=mid;break;}
        else if(nums[mid-1]<nums[mid]) left=mid+1;
        else right=mid-1;
    }
    return ans;
}

//T4.搜索旋转排序数组
//思路：二分得以运用的原因：除断点外，保持升序排序，可确定target范围(递归/迭代)
//时间复杂度:O(logn);空间复杂度:O(logn)--递归;O(1)--迭代
//写法一：递归解法
/*
int searchNums(int *nums,int left,int right,int target){
    if(left>right) return -1;
    else if(left==right)
    {
        if(nums[left]==target) return left;
        else return -1;
    }
    int mid=(left+right)/2;
    if(nums[mid]>=nums[left])       //left~mid升序
    {
        if(nums[left]<=target&&target<=nums[mid]) return searchNums(nums,left,mid,target);
        else return searchNums(nums,mid+1,right,target);
    }
    else
    {
        if(nums[mid]<=target&&target<=nums[right]) return searchNums(nums,mid,right,target);
        else return searchNums(nums,left,mid-1,target);
    }
}
int search(int* nums, int numsSize, int target){
    if(numsSize==0) return -1;
    return searchNums(nums,0,numsSize-1,target);
}
*/

//写法二：迭代写法
int search(int *nums,int numsSize,int target){
    if(numsSize==0) return -1;
    else if(numsSize==1) return nums[0]==target?0:-1;
    int left=0,right=numsSize-1;
    while(left<=right)
    {
        int mid=(left+right)/2;     //left,right用于圈定范围,用mid逼近target
        if(nums[mid]==target) return mid;
        if(nums[0]<=nums[mid])      //0～mid升序
        {
            if(nums[0]<=target&&target<nums[mid]) right=mid-1;      //注意target<nums[mid],不写等号
            else left=mid+1;
        }
        else                //mid~(n-1)升序
        {
            if(nums[mid]<target&&target<=nums[numsSize-1]) left=mid+1;
            else right=mid-1;
        }
    }
    return -1;
}

//T5.在(非递减)排序数组中，查找元素的第一个/最后一个位置
//转化：寻找leftIdx--第一个大于等于target下标;rightIdx--第一个大于target下标-1.
//时间复杂度:O(logn)
int lowBound(int *nums,int left,int right,int target){
    while(left<right)
    {
        int mid=(left+right)/2;
        if(nums[mid]<target) left=mid+1;
        else right=mid;         //维持nums[right]=target.
    }
    return right;
}
int upBound(int *nums,int left,int right,int target){
    while(left<right)
    {
        int mid=(left+right+1)/2;       //注意这里和:mid=(left+right)/2的区别--能结束循环
        if(nums[mid]>target) right=mid-1;
        else left=mid;          //维持nums[left]=target.
    }
    return left;
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize){
    int *ret=(int *)malloc(sizeof(int)*2);
    *returnSize=2;
    if(numsSize==0)
    {
        ret[0]=ret[1]=-1;
        return ret;
    }
    else if(numsSize==1)
    {
        if(nums[0]==target) {ret[0]=ret[1]=0;return ret;}
        else {ret[0]=ret[1]=-1;return ret;}
    }
    int left=0,right=numsSize-1;
    while(left<=right)
    {
        if(nums[left]>target||target>nums[right])
        {
            ret[0]=ret[1]=-1;
            return ret;
        }
        int mid=(left+right)/2;
        if(nums[mid]<target) left=mid+1;
        else if(nums[mid]>target) right=mid-1;
        else
        {
            ret[0]=lowBound(nums,left,mid,target);
            ret[1]=upBound(nums,mid,right,target);
            return ret;
        }
    }
    ret[0]=ret[1]=-1;
    return ret;
}

//T6.寻找旋转排序数组最小值:
//数组分为两段升序，寻找最小元素
//时间复杂度:O(logn)--二分查找
int findMin(int *nums,int numsSize){
    if(numsSize==1) return nums[0];
    int left=0,right=numsSize-1;
    while(1)
    {
        if(right==left+1) break;
        int mid=(left+right)/2;
        if(nums[left]<nums[mid]&&nums[mid]<nums[right]) return nums[left];
        if(nums[left]<nums[mid]) left=mid;
        else if(nums[left]>nums[mid]) right=mid;
    }
    if(nums[left]<nums[right]) return nums[left];
    else return nums[right];
}

//T7.寻找两个正序数组的中位数
//思路一：合并数组,直接找下标对应:时间O(m+n),空间O(m+n).
//思路二:维护两指针,遍历数组:空间O(1).
//思路三:寻找有序数组第k小的数:
//比较A[k/2-1],B[k/2-1];对于较小值,最多k-2个元素比它小,非第k小的数.单词查找排除k/2个数
//特殊情况：A[k/2-1]/B[k/2-1]越界，选取最后一个元素;一个数组为空，直接返回;k=1,返回首元素较小值.
#define min(a,b) a<b?a:b
double getKthElement(int *nums1,int *nums2,int nums1Size,int nums2Size,int k){
    int id1=0,id2=0,kthElement=0;
    int m=nums1Size,n=nums2Size;
    while(true)
    {
        if(id1==m) return nums2[id2+k-1];
        if(id2==n) return nums1[id1+k-1];
        if(k==1) return min(nums1[id1],nums2[id2]);
        
        int half=k/2;
        int newId1=min(id1+half-1,m-1),newId2=min(id2+half-1,n-1);      //数组越界时,取最后一个元素
        if(nums1[newId1]<=nums2[newId2])
        {
            k-=newId1-id1+1;    //寻找第k小的数：排除k-1个数
            id1=newId1+1;
        }
        else
        {
            k-=newId2-id2+1;
            id2=newId2+1;
        }
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int m=nums1Size,n=nums2Size;
    if((m+n)%2)
    {
        int mid=(m+n)/2;        //mid为下标(从0开始）
        return getKthElement(nums1,nums2,m,n,mid+1);
    }
    else
    {
        int mid1=(m+n)/2-1,mid2=(m+n)/2;
        return (getKthElement(nums1,nums2,m,n,mid1+1)+getKthElement(nums1,nums2,m,n,mid2+1))/2.0;
    }
}
