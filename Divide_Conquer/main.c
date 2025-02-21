//
//  main.c
//  Divide_Conquer
//
//  Created by 文柳懿 on 2023/8/12.
//

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//T1(Leetcode108).将有序数组转换为二叉搜索树(高度平衡)
//时间复杂度:O(n);空间复杂度:O(logn),递归栈深度
struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };

struct TreeNode* buildBST(int *nums,int left,int right){
    if(left>right) return NULL;
    int mid=(left+right)/2;
    struct TreeNode *root=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val=nums[mid];
    root->left=buildBST(nums,left,mid-1);
    root->right=buildBST(nums,mid+1,right);
    return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    if(numsSize==0) return NULL;
    return buildBST(nums,0,numsSize-1);
}

//变式(Leetcode1382).将二叉搜索树变平衡(每个节点的两棵子树高度差不超过1):
//思路:当前搜索树转为升序数组,再构造平衡的二叉搜索树

//T2(Leetcode148).排序链表
struct ListNode{
    int val;
    struct ListNode *next;
};

//思路一:暴力解法,将链表化为数组,O(nlogn)排序,再构造新链表
//思路二:插入排序,时间复杂度O(n^2)
//思路三:链表适用归并排序(基于分治算法)
//法一:自顶向下归并排序:
//1,快慢指针找到链表中点;2.对两子链分别排序(head,tail);3.再合并有序链表(dummy引入)
//时间复杂度:O(nlogn);空间复杂度:(logn)--递归深度
/*
struct ListNode *merge(struct ListNode *head1,struct ListNode *head2){
    struct ListNode *dummy=(struct ListNode *)malloc(sizeof(struct ListNode));
    dummy->val=0;       //哑节点
    struct ListNode *tmp=dummy,*p1=head1,*p2=head2;
    while(p1!=NULL&&p2!=NULL)
    {
        if(p1->val<p2->val)
        {
            tmp->next=p1;
            p1=p1->next;
        }
        else
        {
            tmp->next=p2;
            p2=p2->next;
        }
        tmp=tmp->next;
    }
    if(p1!=NULL) tmp->next=p1;
    else if(p2!=NULL) tmp->next=p2;
    return dummy->next;
}

struct ListNode *toSortedList(struct ListNode *head,struct ListNode *tail){
    if(head==NULL) return NULL;
    else if(head->next==tail) {head->next=NULL;return head;}
    
    struct ListNode *fast=head,*slow=head;
    while(fast!=tail)
    {
        fast=fast->next;
        slow=slow->next;
        if(fast!=tail) fast=fast->next;
    }
    return merge(toSortedList(head,slow),toSortedList(slow,tail));
}
struct ListNode *sortList(struct ListNode *head){
    return toSortedList(head,NULL);
}
 */

//法二:自底向上归并排序
//初始subLen=1,每两个子链表合并为2*subLen的有序子链表,再不断将subLen*2.
//时间复杂度:O(n*logn);空间复杂度:O(1).
struct ListNode *merge(struct ListNode *head1,struct ListNode *head2){
    struct ListNode *dummy=(struct ListNode *)malloc(sizeof(struct ListNode));
    dummy->val=0;
    struct ListNode *tmp=dummy,*p1=head1,*p2=head2;
    while(p1!=NULL&&p2!=NULL)
    {
        if(p1->val<=p2->val)
        {
            tmp->next=p1;
            p1=p1->next;
        }
        else
        {
            tmp->next=p2;
            p2=p2->next;
        }
        tmp=tmp->next;
    }
    if(p1!=NULL) tmp->next=p1;
    else if(p2!=NULL) tmp->next=p2;
    return dummy->next;
}

struct ListNode *sortList(struct ListNode *head){
    if(head==NULL) return NULL;
    int len=0;
    struct ListNode *tmp=head;
    while(tmp!=NULL) {tmp=tmp->next;len++;}         //len为链表长度
    
    struct ListNode *dummy=(struct ListNode *)malloc(sizeof(struct ListNode));
    dummy->next=head;
    for(int subLen=1;subLen<len;subLen<<=1)
    {
        struct ListNode *prev=dummy,*cur=dummy->next;       //注意！这里dummy为链表头前哑节点,cur调整位置后,可能不是head,不能写作:cur=head;
        while(cur!=NULL)
        {
            struct ListNode *head1=cur;
            for(int i=1;i<subLen&&cur->next!=NULL;i++) cur=cur->next;   //链表head1,长度为subLen
            
            struct ListNode *head2=cur->next;
            cur->next=NULL;cur=head2;                   //链表head1与head2断开
            for(int i=1;i<subLen&&cur!=NULL&&cur->next!=NULL;i++) cur=cur->next;    //链表head2,长度为subLen
            
            struct ListNode *follow=NULL;
            if(cur!=NULL)
            {
                follow=cur->next;       //follow记录下一个链表头节点,再将head2尾断开
                cur->next=NULL;
            }
            prev->next=merge(head1,head2);     //有序排列,拼接head1与head2
            while(prev->next!=NULL) prev=prev->next;        //prev为已归并排序的链表尾
            cur=follow;
        }
    }
    return dummy->next;
}

//T3.买卖股票的最佳时机I(买入一次)
//分治思路:change数组储存相邻两天变化.change[low,high]的最大值(change[j]-change[i])来自:
//change[low,mid]最大值;change[mid+1,high]最大值;横跨mid的最大值.
//时间复杂度：O(n*logn).
#define INFINITY -2147483647
int findMaxCrossingSubarray(int *changes,int low,int mid,int high){
    int left_sum=INFINITY,right_sum=INFINITY,sum=0;
    for(int i=mid;i>=low;i--)
    {
        sum+=changes[i];
        if(sum>left_sum) left_sum=sum;
    }
    sum=0;
    for(int j=mid+1;j<=high;j++)
    {
        sum+=changes[j];
        if(sum>right_sum) right_sum=sum;
    }
    return left_sum+right_sum;
}
int findMaxSubarray(int *changes,int low,int high){
    if(low==high) return changes[low];
    int mid=(low+high)/2;
    int leftSum=findMaxSubarray(changes,low,mid),rightSum=findMaxSubarray(changes,mid+1,high),crossSum=findMaxCrossingSubarray(changes,low,mid,high);
    if(leftSum>=rightSum&&leftSum>=crossSum) return leftSum;
    else if(rightSum>=leftSum&&rightSum>=crossSum) return rightSum;
    else return crossSum;
}

int maxProfit(int *prices,int pricesSize){
    if(pricesSize==0||pricesSize==1) return 0;
    int *changes=(int *)malloc(sizeof(int)*(pricesSize-1));
    for(int i=0;i<pricesSize-1;i++) changes[i]=prices[i+1]-prices[i];
    return findMaxSubarray(changes,0,pricesSize-2)>0?findMaxSubarray(changes,0,pricesSize-2):0;
}

//T4.二维区域和检索-矩阵不可变
//法一：一维前缀和
//时间复杂度:初始化前缀和O(mn),每次检索O(m)(m行,分别检测每行的前缀和)
//空间复杂度:O(mn):m行n+1列的前缀和数组sums
/*
typedef struct{
    int **sums;     //sums为二维数组,sums[i][j]记录第i行,第1~j个元素之和
    int sumsSize;
}NumMatrix;

NumMatrix *numMatrixCreate(int **matrix,int matrixSize,int *matrixColSize){
    NumMatrix *ret=malloc(sizeof(NumMatrix));
    ret->sums=malloc(sizeof(int *)*matrixSize);
    ret->sumsSize=matrixSize;
    for(int i=0;i<matrixSize;i++)
    {
        ret->sums[i]=malloc(sizeof(int)*(matrixColSize[i]+1));
        ret->sums[i][0]=0;
        for(int j=0;j<matrixColSize[i];j++) ret->sums[i][j+1]=ret->sums[i][j]+matrix[i][j];
    }
    return ret;
}

int numMatrixSumRegion(NumMatrix *obj,int r1,int c1,int r2,int c2){
    int sum=0;
    for(int i=r1;i<=r2;i++)
    {
        sum+=obj->sums[i][c2+1]-obj->sums[i][c1];
    }
    return sum;
}

void numMatrixFree(NumMatrix *obj){
    for(int i=0;i<obj->sumsSize;i++) free(obj->sums[i]);
    free(obj->sums);
}
*/

//二维前缀和:f[i][j]为以(i,j)为右下角的矩阵元素之和,创建(m+1)行(n+1)列的二维数组
//时间复杂度:每次检索降至O(1)
typedef struct{
    int **sums;
    int sumsSize;
}NumMatrix;

NumMatrix *numMatrixCreate(int **matrix,int matrixSize,int *matrixColSize){
    NumMatrix *ret=malloc(sizeof(NumMatrix));
    ret->sums=malloc(sizeof(int *)*(matrixSize+1));
    ret->sumsSize=matrixSize+1;
    int n=matrixSize?matrixColSize[0]:0;
    
    for(int i=0;i<=matrixSize;i++)
    {
        ret->sums[i]=malloc(sizeof(int)*(n+1));
        memset(ret->sums[i],0,sizeof(int)*(n+1));
    }
    for(int i=0;i<matrixSize;i++)
    {
        for(int j=0;j<matrixColSize[i];j++) ret->sums[i+1][j+1]=ret->sums[i][j+1]+ret->sums[i+1][j]-ret->sums[i][j]+matrix[i][j];
    }
    return ret;
}

int numMatrixSumRegion(NumMatrix *obj,int r1,int c1,int r2,int c2){
    return obj->sums[r2+1][c2+1]-obj->sums[r1][c2+1]-obj->sums[r2+1][c1]+obj->sums[r1][c1];
}

void numMatrixFree(NumMatrix *obj){
    for(int i=0;i<obj->sumsSize;i++) free(obj->sums[i]);
    free(obj->sums);
}

//T5.合并k个链表
//合并两个有序链表:O(1)时间合并--原地调整链表节点的next指针
//法一:顺序合并
//时间复杂度:O(n*k^2),链表最长长度为n.
/*
struct ListNode *mergeTwoLists(struct ListNode *head1,struct ListNode *head2){
    if(head1==NULL) return head2;
    else if(head2==NULL) return head1;
    struct ListNode *dummy=(struct ListNode *)malloc(sizeof(struct ListNode)),*tmp=dummy,*p1=head1,*p2=head2;
    while(p1!=NULL&&p2!=NULL)
    {
        if(p1->val<=p2->val)
        {
            tmp->next=p1;
            p1=p1->next;
        }
        else
        {
            tmp->next=p2;
            p2=p2->next;
        }
        tmp=tmp->next;
    }
    if(p1!=NULL) tmp->next=p1;
    if(p2!=NULL) tmp->next=p2;
    return dummy->next;
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    if(listsSize==0) return NULL;
    struct ListNode *ans=NULL;
    for(int i=0;i<listsSize;i++) ans=mergeTwoLists(ans,lists[i]);
    struct ListNode *cur=ans;
    while(cur!=NULL)
    {
        printf("%d ",cur->val);
        cur=cur->next;
    }
    return ans;
}
*/


