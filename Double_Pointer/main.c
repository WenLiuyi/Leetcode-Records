//
//  main.c
//  Summer_Practices
//
//  Created by 文柳懿 on 2023/7/1.
//

#include<stdio.h>
#include<stdlib.h>
#include <uthash.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

//T1(Leetcode1).两数之和I--无序数组：数组num中，找出两个和为target的数下标
//法一:暴力枚举：两两匹配，时间复杂度O(n^2)
/*
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    for(int i=0;i<numsSize;i++)
    {
        for(int j=i+1;j<numsSize;j++)
        {
            if(nums[i]+nums[j]==target)
            {
                int *ret=(int *)malloc(sizeof(int)*2);
                ret[0]=i;ret[1]=j;
                *returnSize=2;
                return ret;
            }
        }
    }
    *returnSize=0;
    return NULL;
}
 */

//法二：hash表：快速寻找target-x:键为元素值，值为元素下标
//时间复杂度:O(n);空间复杂度:O(n).
/*
struct hashTable{
    int key;
    int val;
    UT_hash_handle hh;
};
struct hashTable* hashtable;

struct hashTable *find(int ikey){
    struct hashTable *tmp;
    HASH_FIND_INT(hashtable,&ikey,tmp);     //在hashtable中，寻找关键字ikey对应值，储存在tmp中
    return tmp;
}

void insert(int ikey,int ival){
    struct hashTable *it=find(ikey);
    if(it==NULL)
    {
        struct hashTable *tmp=malloc(sizeof(struct hashTable));
        tmp->key=ikey;tmp->val=ival;
        HASH_ADD_INT(hashtable,key,tmp);
    }
    else it->val=ival;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    hashtable=NULL;
    for(int i=0;i<numsSize;i++)
    {
        struct hashTable *it=find(target-nums[i]);
        if(it!=NULL)
        {
            int *ret=(int *)malloc(sizeof(int)*2);
            ret[0]=i;ret[1]=it->val;
            *returnSize=2;
            return ret;
        }
        insert(nums[i],i);
    }
    *returnSize=0;
    return NULL;
}
*/

//变式：两数之和II-有序数组：
//法一：二分查找:固定第一个数，在第一个数右侧寻找第二个数
//时间复杂度:O(n*logn);空间复杂度:O(1).
/*
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize){
    int *ret=(int *)malloc(sizeof(int)*2);
    *returnSize=2;
    
    for(int i=0;i<numbersSize;i++)
    {
        int low=i+1,high=numbersSize-1;
        while(low<=high)
        {
            int mid=(low+high)/2;
            if(numbers[i]+numbers[mid]==target)
            {
                ret[0]=i+1;ret[1]=mid+1;        //两元素位置
                return ret;
            }
            else if(numbers[mid]<target-numbers[i]) low=mid+1;
            else high=mid-1;
        }
    }
    ret[0]=-1;ret[1]=-1;
    return ret;
}
*/

//双指针法：大于左指针右移，小于右指针左移
//原理:numbers[i]+numbers[j]=target.左指针先达到i时,会大于,此时右指针不断左移.
int *twoSum(int *numbers,int numbersSize,int target,int *returnSize){
    int *ret=(int *)malloc(sizeof(int)*2);
    *returnSize=2;
    
    int left=0,right=numbersSize-1;
    while(left<right)
    {
        int sum=numbers[left]+numbers[right];
        if(sum==target)
        {
            ret[0]=left+1;ret[1]=right+1;
            return ret;
        }
        else if(sum>target) right--;
        else left++;
    }
    ret[0]=-1;ret[1]=-1;
    return ret;
}

//T2(Leetcode4).寻找两个正序数组的中位数
//法一：我的解法：插入排序，合并两个数组
//时间复杂度:O(m*n);空间复杂度:O(m+n).
/*
void insertItem(double ret[],double item,int len){
    for(int i=len-1;i>=0;i--)
    {
        if(item>=ret[i])
        {
            for(int j=len-1;j>=i+1;j--) ret[j+1]=ret[j];
            ret[i+1]=item;return;
        }
    }
    for(int j=len-1;j>=0;j--) ret[j+1]=ret[j];
    ret[0]=item;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    double *ret=(double *)malloc(sizeof(double)*(nums1Size+nums2Size));
    for(int i=0;i<nums1Size;i++) ret[i]=nums1[i];
    for(int j=0;j<nums2Size;j++) insertItem(ret,nums2[j],nums1Size+j);
    if((nums1Size+nums2Size)%2) return ret[(nums1Size+nums2Size-1)/2];
    else return (ret[(nums1Size+nums2Size)/2]+ret[(nums1Size+nums2Size-2)/2])/2;
}
 */

//法二：归并方式，两指针在两数组中移动合并
//时间复杂度:O(m+n);空间复杂度：O(1)

//法三：二分查找
//查找两有序数组A,B的第k个元素：比较A[k/2-1],B[k/2-1](其中较小值,最多k-2个元素比它小,一定不是第k个元素),排除k/2个元素
#define min(a,b) a<b?a:b
int getElement(int *nums1,int *nums2,int nums1Size,int nums2Size,int k){
    int i=0,j=0;
    while(1)
    {
        //printf("%d %d %d\n",i,j,k);
        if(k==1) return min(nums1[i],nums2[j]);     //k=1时,返回两数组首元素最小值
        if(i==nums1Size) return nums2[j+k-1];
        if(j==nums2Size) return nums1[i+k-1];
        
        int newNum1=min(i+k/2-1,nums1Size-1),newNum2=min(j+k/2-1,nums2Size-1);
        if(nums1[newNum1]<=nums2[newNum2])
        {
            k-=(newNum1-i+1);
            i=newNum1+1;
        }
        else
        {
            k-=(newNum2-j+1);
            j=newNum2+1;
        }
    }
}

double findMedianSortedArrays(int* nums1,int nums1Size,int* nums2,int nums2Size){
    int len=nums1Size+nums2Size;
    if(len%2) return getElement(nums1,nums2,nums1Size,nums2Size,(len+1)/2);
    else
    {
        double mid=(getElement(nums1,nums2,nums1Size,nums2Size,len/2)+getElement(nums1,nums2,nums1Size,nums2Size,len/2+1))/2.0;
    return mid;
    }
}

//T3.(Leetcode5).三数之和:找到不重复且和为0的三元组
//解法：排序+双指针--排序后，顺序序列在循环时便于去重；双指针--a+b+c=0,固定a,b从小至大枚举，对应c从大至小枚举.
//排序复杂度：O(N*logN);第一重循环中,双指针复杂度O(N),总复杂度O(N^2).
int cmp(const void *e1,const void *e2){
    int *a=(int *)e1,*b=(int *)e2;
    return *a-*b;
}

//returnSize为三元组组数;returnColumnSizes为int型数组,记录每行数组的列数
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int base=100;           //数组初始长度
    int **res=(int **)malloc(sizeof(int *)*base);       //元素为int **类型的数组(二维数组)
    *returnColumnSizes=(int *)malloc(sizeof(int)*base);
    *returnSize=0;
    
    qsort(nums,numsSize,sizeof(int),cmp);       //升序排列
    for(int i=0;i<numsSize;i++)
    {
        if(i>0&&nums[i]==nums[i-1]) continue;       //相邻两次，变更元素值不相同，避免重复
        int j=i+1,k=numsSize-1;
        while(j<k)
        {
            if(nums[i]+nums[j]+nums[k]==0)
            {
                res[*returnSize]=(int *)malloc(sizeof(int)*3);
                (*returnColumnSizes)[*returnSize]=3;
                
                res[*returnSize][0]=nums[i];
                res[*returnSize][1]=nums[j];
                res[*returnSize][2]=nums[k];
                
                (*returnSize)++;
                
                if(*returnSize==base)       //进行扩容
                {
                    base*=2;
                    res=(int **)realloc(res,sizeof(int *)*base);
                    *returnColumnSizes=(int *)realloc(*returnColumnSizes,sizeof(int)*base);
                }
                //移动双指针，进行去重
                int num1=nums[j],num2=nums[k];
                while(nums[j]==num1&&j<k) j++;
                while(nums[k]==num2&&j<k) k--;
            }
            else if(nums[i]+nums[j]+nums[k]<0) j++;
            else k--;
        }
    }
    return res;
}

//T4(LeetCode 283).移动0:至末尾，并保持其他非0数字相对位置不变
//我的解法：最坏时间复杂度：O(N^2)
/*
void moveZeroes(int* nums, int numsSize){
    int k=numsSize-1;
    for(int i=0;i<numsSize;)
    {
        if(i==k) break;
        if(nums[i]==0)
        {
            for(int j=i;j<numsSize-1;j++) nums[j]=nums[j+1];
            nums[k]=0;k--;
        }
        else i++;
    }
}
 */

//双指针法：左指针指向已处理的序列尾部；右指针指向待处理的序列头部
//时间复杂度：O(N),空间复杂度：O(1).
void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;*b=tmp;
}
void moveZeroes(int *nums,int numsSize){
    int left=0,right=0;
    while(right<numsSize)
    {
        if(nums[right])         //右指针指向非0元素时，移置左侧
        {
            swap(nums+left,nums+right);
            left++;
        }
        right++;
    }
}

//T5(LeetCode 11).盛水最多的容器
//暴力解法：两层循环，时间复杂度O(N^2)
int minNum(int a,int b){
    if(a<b) return a;
    else return b;
}
/*
int maxArea(int* height, int heightSize){
    int max=0;
    for(int i=0;i<heightSize-1;i++)
    {
        for(int j=i+1;j<heightSize;j++)
        {
            if((j-i)*minNum(height[i],height[j])>max) max=(j-i)*minNum(height[i],height[j]);
        }
    }
    return max;
}
*/

//双指针法：左右指针，向内移动当前对应数字较小的指针
//时间复杂度：O(N)
int maxArea(int* height, int heightSize){
    int left=0,right=heightSize-1,max=0;
    while(left<right)
    {
        int ans=(right-left)*minNum(height[left],height[right]);
        if(ans>max) max=ans;
        if(height[left]<height[right]) left++;
        else right--;
    }
    return max;
}

//T6(LeetCode 88).合并两个有序数组
//双指针法:时间复杂度O(m+n)
/*
void merge(int *nums1,int nums1Size,int m,int *nums2,int nums2Size,int n){
    int *sorted=(int *)malloc(sizeof(int)*(m+n)),p1=0,p2=0;
    while(p1<m&&p2<n)
    {
        if(nums1[p1]<nums2[p2]) {sorted[p1+p2]=nums1[p1];p1++;}
        else {sorted[p1+p2]=nums2[p2];p2++;}
    }
    while(p1<m) {sorted[p1+p2]=nums1[p1];p1++;}
    while(p2<n) {sorted[p1+p2]=nums2[p2];p2++;}
    
    for(int i=0;i<m+n;i++) nums1[i]=sorted[i];
}
 */

//逆向双指针:从后向前遍历，避免nums1中元素被覆盖
void merge(int *nums1,int nums1Size,int m,int *nums2,int nums2Size,int n){
    int p1=m-1,p2=n-1,tail=m+n-1;
    while(p1>=0||p2>=0)
    {
        if(p1==-1) nums1[tail--]=nums2[p2--];
        else if(p2==-1) nums1[tail--]=nums1[p1--];
        else if(nums1[p1]>nums2[p2]) nums1[tail--]=nums1[p1--];
        else nums1[tail--]=nums2[p2--];
    }
}

//T7(Leetcode27).移除元素：原地移除数组nums中值为val的元素(不考虑相对位置)，返回操作后数组长度
//法一：双指针法：时间复杂度O(n),空间复杂度O(1).
/*
int removeElement(int *nums,int numsSize,int val){
    int left=0;
    for(int right=0;right<numsSize;right++)
    {
        if(nums[right]!=val) nums[left++]=nums[right];      //left记录保留的元素
            //存在保留元素的重复赋值操作
    }
    return left;
}
 */

//法二：双指针优化:从左向右遍历，将val元素，交换至数组末尾
int removeElement(int *nums,int numsSize,int val){
    int left=0,right=numsSize-1;
    while(left<=right)
    {
        if(nums[left]==val) nums[left]=nums[right--];
        else left++;
    }
    return left;
}

//T8(Leetcode125).验证回文串
//双指针：时间复杂度O(|s|),空间复杂度O(1).
bool isPalindrome(char *s){
    int len=strlen(s),left=0,right=len-1;
    while(left<right)
    {
        if(isalnum(s[left])&&isalnum(s[right]))
        {
            if(tolower(s[left])!=tolower(s[right])) return false;
            left++;right--;
        }
        else if(!isalnum(s[left])&&!isalnum(s[right])) {left++;right--;}
        else if(isalnum(s[left])) right--;
        else left++;
    }
    return true;
}

//T9(Leetcode392).判断子序列
//判断:s是否为t删除部分字符，但不改变相对位置的子序列
//法一：双指针法(贪心匹配):时间复杂度O(m+n),空间复杂度O(1).
/*
bool isSubsequence(char *s,char *t){
    int n=strlen(s),m=strlen(t),i=0,j=0;
    while(i<n&&j<m)
    {
        if(s[i]==t[j]) i++;
        j++;
    }
    return i==n;
}
 */

//法二：动态规划
//预处理：f[i][j]为t的位置i往后，字符j第一次出现的位置
//状态转移方程：f[i][j]=i(t[i]=j);f[i][j]=f[i+1][j](t[i]!=j)
//时间复杂度：预处理：O(m*|sigma|),sigma为字符集；判断子序列：O(n).
//空间复杂度：O(m*|sigma|).
bool isSubsequence(char *s,char *t){
    int n=strlen(s),m=strlen(t);
    int f[m+1][26];         //f[i][j]记录:字符串t中，位置i后字符j第一次出现的位置
    memset(f,0,sizeof(f));
    
    for(int j=0;j<26;j++) f[m][j]=m;        //置f[m][..]为m
    for(int i=m-1;i>=0;i--)
    {
        for(int j=0;j<26;j++)
        {
            if(t[i]=='a'+j) f[i][j]=i;
            else f[i][j]=f[i+1][j];
        }
    }
    int add=0;
    for(int i=0;i<n;i++)
    {
        if(f[add][s[i]-'a']==m) return false;
        add=f[add][s[i]-'a']+1;     //add为字符串t中，匹配的字符
    }
    return true;
}

