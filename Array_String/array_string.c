//
//  main.c
//  Array_String
//
//  Created by 文柳懿 on 2023/7/17.
//

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "uthash.h"
#include<stdbool.h>
#include<time.h>

//Leetcode数组/字符串
//T1(Leetcode26).删除有序数组中的重复项
//双指针法：时间复杂度O(n),空间复杂度O(1).
/*
int removeDuplicates(int *nums,int numsSize){
    int left=0,cnt=numsSize;
    for(int right=0;right<numsSize;right++)
    {
        if(right==0||(right>0&&nums[right]!=nums[right-1])) nums[left++]=nums[right];
        else cnt--;
    }
    return cnt;
}
*/

//变式.(Leetcode80).删除有序数组中的重复项II:超过两次的只出现两次
int removeDuplicates(int *nums,int numsSize){
    int left=0,cnt=numsSize;
    for(int right=0;right<numsSize;right++)
    {
        if(right>1&&nums[right]==nums[left-2]) cnt--;   //注意：不能写为nums[right]=nums[right-1]=nums[right-2],有可能right-2处元素已被left指针改变
        else nums[left++]=nums[right];
    }
    return cnt;
}

//T2(Leetcode169).多数元素：寻找数组中，出现次数大于floor(n/2)的元素(假设数组总存在多数元素)
//法一：排序--时间复杂度O(n*logn),空间复杂度O(logn)(库自带排序算法,栈空间)
/*
int cmp(const void *e1,const void *e2){
    int *a=(int *)e1,*b=(int *)e2;
    return *a-*b;
}
int majorityElement(int *nums,int numsSize){
    qsort(nums,numsSize,sizeof(int),cmp);
    return nums[numsSize/2];
}
*/

//法二：哈希表：统计每个元素出现次数
//时间复杂度:O(n);空间复杂度:O(n)(最多n-[n/2]个元素)
/*
struct hashTable{
    int key;
    int val;
    UT_hash_handle hh;
};
struct hashTable *hashtable;

struct hashTable *insert(int ikey,int ival){
    struct hashTable *tmp=malloc(sizeof(struct hashTable));
    tmp->key=ikey;tmp->val=ival;
    HASH_ADD_INT(hashtable,key,tmp);
    return tmp;
}

struct hashTable *find(int ikey){
    struct hashTable *tmp;
    HASH_FIND_INT(hashtable,&ikey,tmp);
    if(tmp==NULL) tmp=insert(ikey,1);
    else tmp->val++;
    return tmp;
}

int majorityElement(int *nums,int numsSize){
    hashtable=NULL;
    int maxCnt=0,ans;
    for(int i=0;i<numsSize;i++)
    {
        struct hashTable *it=find(nums[i]);     //统计词频
        if(it->val>maxCnt)
        {
            maxCnt=it->val;
            ans=it->key;
        }
    }
    return ans;
}
*/

//法三：随机化
//时间复杂度:理论上最坏情况O(inf).当众数恰好占据数组一半时,在第i次找到概率为i/2^i,期望复杂度为O(n).

//法四：分治:求出数组左右部分的众数，选出正确的众数
//时间复杂度:O(n*logn);空间复杂度:O(logn)递归深度
/*
int count(int *nums,int key,int low,int high){
    int cnt=0;
    for(int i=low;i<=high;i++)
    {
        if(nums[i]==key) cnt++;
    }
    return cnt;
}
int majorityElement_rec(int *nums,int low,int high){
    if(low==high) return nums[low];
    int mid=(low+high)/2;
    int left_major=majorityElement_rec(nums,low,mid),left_cnt=count(nums,left_major,low,high);
    int right_major=majorityElement_rec(nums,mid+1,high),right_cnt=count(nums,right_major,low,high);
    if(left_cnt>right_cnt) return left_major;
    else return right_major;
}

int majorityElement(int *nums,int numsSize){
    return majorityElement_rec(nums,0,numsSize-1);
}
*/

//法五：Boyer-Moore投票算法：维护candidate和其count;相等时,count+1,不相等时,count-1,count=0时，更换candidate
int majorityElement(int *nums,int numsSize){
    int count=0,candidate=nums[0];
    for(int i=0;i<numsSize;i++)
    {
        if(nums[i]==candidate) count++;
        else if(count==0) {candidate=nums[i];count=1;}
        else count--;
    }
    return candidate;
}

//T3(Leetcode189).轮转数组：数组中元素向右轮转k个位置
//普通解法：使用额外数组，存放轮转后数组，最后拷贝
//时间复杂度:O(n);空间复杂度:O(n).
/*
void rotate(int *nums,int numsSize,int k){
    int *ret=(int *)malloc(sizeof(int)*numsSize);
    for(int i=0;i<numsSize;i++) ret[(i+k)%numsSize]=nums[i];
    for(int i=0;i<numsSize;i++) nums[i]=ret[i];
}
*/

//法二：环状替换
//从位置0开始，每次走过k个位置，回到位置0时，走过a圈，共遍历b个元素.有:a*n=b*k.
//时间复杂度:O(n);空间复杂度:O(1)--常数
/*
int gcd(int a,int b){
    return b!=0?gcd(b,a%b):a;
}
void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}
void rotate(int *nums,int numsSize,int k){
    for(int i=0;i<gcd(k,numsSize);i++)
    {
        int tmp=nums[i],pos=(i+k)%numsSize;
        for(;pos!=i;pos=(pos+k)%numsSize) swap(&tmp,nums+pos);
        swap(&tmp,nums+pos);
        
    }
}
*/

//法三：数组翻转
//结果：数组末尾k(mod n)个元素移至头部.分区域进行翻转
//时间复杂度:O(n);空间复杂度:O(1).
void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}
void reverse(int *nums,int start,int end){
    while(start<end)
    {
        swap(&nums[start],&nums[end]);
        start++;end--;
    }
}
void rotate(int *nums,int numsSize,int k){
    reverse(nums,0,numsSize-1);
    k=k%numsSize;
    reverse(nums,0,k-1);
    reverse(nums,k,numsSize-1);
}

//T4.买卖股票的最佳时机I(买入一次)
//当前买入点后，在持续上升至最高点时卖出
//时间复杂度:O(n);空间复杂度:O(1).
/*
int maxProfit(int *prices,int pricesSize){
    int max=0,in=0,i=1;
    for(;i<pricesSize;i++)
    {
        if(prices[i]<prices[in]) in=i;          //记录历史最低点
        else if(max<prices[i]-prices[in]) max=prices[i]-prices[in];
    }
    return max;
}
 */

//T5.买卖股票的最佳时机II(可买进卖出多次,任何时候只能持有一股)
//法一：贪心算法:寻找不相交区间的等式最大化sigma(a[ri]-a[li]).--选择贡献大于0的区间
//时间复杂度:O(n);空间复杂度:O(1).
/*
int maxProfit(int *prices,int pricesSize){
    int sum=0;
    for(int i=1;i<pricesSize;i++)
    {
        if(prices[i]>prices[i-1]) sum+=prices[i]-prices[i-1];
    }
    return sum;
}
*/

//法二：动态规划
//定义:dp[i][0],dp[i][1]分别为:第i天交易后，手中持有/没有股票的最大累积净利润(包括此时持有股票的成本)
//时间复杂度:O(n);空间复杂度:O(n).
/*
int max(int a,int b){
    return a>b?a:b;
}
int maxProfit(int *prices,int pricesSize){
    int dp[pricesSize][2];
    dp[0][0]=0,dp[0][1]=-prices[0];
    for(int i=1;i<pricesSize;i++)
    {
        dp[i][0]=max(dp[i-1][0],dp[i-1][1]+prices[i]);
        dp[i][1]=max(dp[i-1][1],dp[i-1][0]-prices[i]);
    }
    return dp[pricesSize-1][0];
}
*/

//T6.买卖股票的最佳时机III(最多可完成两笔交易，不可同时持有多股)
//注意：不等于寻找最大、第二大利润的单次操作(可能存在覆盖)
//动态规划:5种状态:未操作；一次买入操作--buy1；一次买入卖出操作--sell1；一笔交易后，第二次买入操作--buy2；两笔交易完成--sell2.
/*
int max(int a,int b){
    return a>b?a:b;
}
int maxProfit(int *prices,int pricesSize){
    //buy1,sell1,buy2,sell2记录第i天结束后,处于4种状态下的累积净利润
    int buy1=-prices[0],sell1=0;
    int buy2=-prices[0],sell2=0;
    for(int i=1;i<pricesSize;i++)
    {
        buy1=max(buy1,0-prices[i]);         //未操作/买入第一笔
        sell1=max(sell1,buy1+prices[i]);
        buy2=max(buy2,sell1-prices[i]);
        sell2=max(sell2,buy2+prices[i]);
    }
    return sell2;       //(允许当天买入当天卖出)若最优解为一笔交易,sell1会归入sell2
}
*/

//T7.买卖股票的最佳时机IV(最多可完成k笔交易，不可同时持有多股)
//buy[i][j]为第i天结束恰好完成j笔交易，且当前持有一支股票,此时的最大利润.
//最终答案为sell[n-1][0..k];初始化buy[0][0..k],sell[0][0..k].
int min(int a,int b){
    return a<b?a:b;
}
int max(int a,int b){
    return a>b?a:b;
}
int maxProfit(int k,int *prices,int pricesSize){
    if(pricesSize==0) return 0;
    k=min(k,pricesSize/2);       //n天最多进行[n/2]笔交易
    int buy[pricesSize][k+1],sell[pricesSize][k+1];
    memset(buy,0,sizeof(buy));memset(sell,0,sizeof(sell));
    
    for(int j=0;j<=k;j++)
    {
        buy[0][j]=-prices[0];sell[0][j]=0;
    }
    
    for(int i=1;i<pricesSize;i++)
    {
        buy[i][0]=max(buy[i-1][0],sell[i-1][0]-prices[i]);
        for(int j=1;j<=k;j++)
        {
            buy[i][j]=max(buy[i-1][j],sell[i-1][j]-prices[i]);
            sell[i][j]=max(sell[i-1][j],buy[i-1][j-1]+prices[i]);
        }
    }
    int res=0;
    for(int j=0;j<=k;j++) res=max(res,sell[pricesSize-1][j]);
    return res;
}

//T8(Leetcode55).跳跃游戏
//我的解法:时间复杂度:O(n);空间复杂度O(n).
//空间优化：维护最远可达位置的变量--O(1).
bool canJump(int* nums, int numsSize){
    int visited[numsSize];
    memset(visited,0,sizeof(visited));
    for(int i=0;i<numsSize;i++)
    {
        for(int j=1;j<=nums[i]&&i+j<numsSize;j++) visited[i+j]=1;
        if(visited[i]==0&&i!=0) return false;
    }
    return true;
}

//T9变式(Leetcode45).跳跃游戏II--返回到达终点的最小次数
//法一：反向查找出发位置(贪心寻找:可以到达当前位置的最小位置)
//时间复杂度:O(n^2);空间复杂度:O(1).
/*
int jump(int *nums,int numsSize){
    int pos=numsSize-1,steps=0;
    while(pos>0)
    {
        for(int i=0;i<pos;i++)
        {
            if(i+nums[i]>=pos) {pos=i;steps++;}     //寻找可以到达pos的最小位置
        }
    }
    return steps;
}
*/

//法二：正向查找：从起点出发，考虑下一步位置时，选择能使两步后位置最远的下一步位置
//时间复杂度:O(n);空间复杂度:O(1).
int jump(int *nums,int numsSize){
    int steps=0,cur=0;
    while(cur<numsSize-1)
    {
        int maxPos=0,next;
        for(int i=1;i<=nums[cur]&&cur+i<numsSize;i++)   //cur+i<numsSize:避免超出数组范围
        {
            if(cur+i>=numsSize-1) return ++steps;       //cur+i+nums[cur+i]已超出范围，不纳入比较，直接一步完成
            if(cur+i+nums[cur+i]>maxPos)
            {
                maxPos=cur+i+nums[cur+i];
                next=cur+i;
            }
        }
        cur=next;steps++;
    }
    return steps;
}

//T10(Leetcode274).H指数:寻找数组中最大的h,满足:大于等于h的数,出现次数大于等于h次
//法一：排序
//时间复杂度:排序O(n*logn),遍历O(n);空间复杂度:O(logn)(排序栈空间)
/*
int cmp(const void *e1,const void *e2){
    return *(int *)e1-*(int *)e2;
}
int hIndex(int* citations, int citationsSize){
    qsort(citations,citationsSize,sizeof(int),cmp);     //升序排列
    int i;
    for(i=0;i<citationsSize;i++)
    {
        if(citations[i]>=citationsSize-i) return citationsSize-i;   //引用次数依次减少,找到符合要求的最大h
    }
    return 0;
}
*/

//法二：计数排序：counter[i]记录引用次数为i的论文篇数
//时间复杂度:O(n);空间复杂度:O(n).
/*
int hIndex(int *citations,int citationsSize){
    int n=citationsSize;
    int counter[n+1];       //counter[n]为所有饮用次数>=n的论文篇数
    memset(counter,0,sizeof(counter));
    for(int i=0;i<n;i++)
    {
        if(citations[i]>=n) counter[n]+=1;
        else counter[citations[i]]+=1;
    }
    //对引用次数倒序遍历，寻找达到的论文总数节点(论文总数不超过n,因此将引用次数>=n统一合并至counter[n])
    int tot=0;
    for(int i=n;i>=0;i--)
    {
        tot+=counter[i];
        if(tot>=i) return i;
    }
    return 0;
}
 */

//法三：二分搜索(对论文总数)
//时间复杂度:O(n*logn)--logn次二分搜索,每次搜索遍历数组一遍;空间复杂度:O(1).
int hIndex(int *citations,int citationsSize){
    int left=0,right=citationsSize,mid=0,cnt=0;
    while(left<right)
    {
        mid=(left+right+1)>>1;
        cnt=0;
        for(int i=0;i<citationsSize;i++)        //遍历一遍,统计引用次数达到mid的论文篇数
        {
            if(citations[i]>=mid) cnt++;
        }
        if(cnt>=mid) left=mid;
        else right=mid-1;
    }
    return left;
}

//T11(Leetcode380).O(1)时间插入/删除/获取随机元素
//变长数组:O(1)时间获取;哈希表:O(1)时间插入/删除
#define MAX_NUM_SIZE 10001
typedef struct{         //hash表中:key为待插入值,val为对应数组中下标
    int key;
    int val;
    UT_hash_handle hh;
}HashItem;

//hash表obj中，寻找是否存在val:存在返回true,不存在返回false
bool findHash(HashItem **obj,int key){       //注意！传入二重指针参数
    HashItem *pEntry=NULL;
    HASH_FIND_INT(*obj,&key,pEntry);
    if(pEntry!=NULL) return true;
    else return false;
}

//hash表obj中，返回key对应值
int getHash(HashItem **obj,int key){
    HashItem *pEntry=NULL;
    HASH_FIND_INT(*obj,&key,pEntry);
    if(pEntry==NULL) return -1;
    return pEntry->val;
}

//hash表obj中,插入键值对key-val
void insertHash(HashItem **obj,int key,int val){
    HashItem *pEntry=NULL;
    HASH_FIND_INT(*obj,&key,pEntry);
    if(pEntry!=NULL) pEntry->val=val;
    else
    {
        pEntry=(HashItem *)malloc(sizeof(HashItem));
        pEntry->key=key;
        pEntry->val=val;
        HASH_ADD_INT(*obj,key,pEntry);
    }
}

//hash表obj中,删除键值对key-val
void removeHash(HashItem **obj,int key){
    HashItem *pEntry=NULL;
    HASH_FIND_INT(*obj,&key,pEntry);
    if(pEntry!=NULL)
    {
        HASH_DEL(*obj,pEntry);
        free(pEntry);
    }
}

void freeHash(HashItem **obj){
    HashItem *cur,*tmp;
    HASH_ITER(hh,*obj,cur,tmp)
    {
        HASH_DEL(*obj,cur);
        free(cur);
    }
}

typedef struct{
    int *nums;
    int numsSize;   //变长数组
    HashItem *indices;  //hash表
}RandomizedSet;

//创建集合
RandomizedSet* randomizedSetCreate() {
    srand((unsigned)time(NULL));
    RandomizedSet* obj=(RandomizedSet*)malloc(sizeof(RandomizedSet));
    obj->nums=(int *)malloc(sizeof(int)*MAX_NUM_SIZE);
    obj->numsSize=0;
    obj->indices=NULL;
    return obj;
}

//插入：存在val返回false;不存在val返回true
bool randomizedSetInsert(RandomizedSet* obj, int val){
    if(findHash(&obj->indices,val)) return false;
        //注意！obj->indices结构体指针类型(HashItem*型),作为函数参数,应传入其地址(参数定义为双重指针类型)
    //不存在,val插入变长数组和hash表中
    obj->nums[obj->numsSize++]=val;
    insertHash(&obj->indices,val,obj->numsSize-1);
    return true;
}

//删除：存在val返回true;不存在val返回false
bool randomizedSetRemove(RandomizedSet* obj, int val) {
    if(!findHash(&obj->indices,val)) return false;
    //找到变长数组中val对应下标index，用于删除(用数组最后一个元素覆盖,调整hash表)
    int index=getHash(&obj->indices,val);
    obj->nums[index]=obj->nums[obj->numsSize-1];
    obj->numsSize--;
    insertHash(&obj->indices,obj->nums[index],index);
    removeHash(&obj->indices,val);
    return true;
}

//随机获取
int randomizedSetGetRandom(RandomizedSet* obj) {
    int randomIndex=rand()%obj->numsSize;
    return obj->nums[randomIndex];
}

void randomizedSetFree(RandomizedSet* obj) {
    freeHash(&obj->indices);
    free(obj->nums);
    free(obj);
}

//T12(Leetcode 238).除自身以外数组的乘积
//要求:不使用除法,且在O(n)时间复杂度内完成
//法一：指定元素左右乘积相乘--维护L,R两个数组，分别记录从左、右两个方向累乘至当前位置的乘积
//时间复杂度:O(n);空间复杂度:O(n).
/*
int *productExceptSelf(int *nums,int numsSize,int *returnSize){
    int *ret=(int *)malloc(sizeof(int)*numsSize);
    *returnSize=numsSize;
    int LeftMulti[numsSize], RightMulti[numsSize],product=1;
    for(int i=0;i<numsSize;i++)
    {
        LeftMulti[i]=product;
        product*=nums[i];
    }
    product=1;
    for(int i=numsSize-1;i>=0;i--)
    {
        RightMulti[i]=product;
        product*=nums[i];
    }
    //左右乘积
    for(int i=0;i<numsSize;i++) ret[i]=LeftMulti[i]*RightMulti[i];
    return ret;
}
*/

//法二:空间优化:复杂度O(1)--直接使用结果数组ret储存L结果，再从右开始遍历，更新ret
/*
int *productExceptSelf(int *nums,int numsSize,int *returnSize){
    int *ret=(int *)malloc(sizeof(int)*numsSize);
    *returnSize=numsSize;
    ret[0]=1;
    for(int i=1;i<numsSize;i++) ret[i]=ret[i-1]*nums[i-1];      //ret储存L结果
    int R=1;
    for(int i=numsSize-1;i>=0;i--)
    {
        ret[i]=ret[i]*R;
        R*=nums[i];
    }
    return ret;
}
*/

//T13(Leetcode134).加油站:
//思想：单次遍历,求出以每个加油站为起点,所能到达的最远加油站
//性质:设起点为x时,最远到达y.则从x,y中任一z出发,不能到达超过y的地方
//解法：从0开始遍历
int canCompleteCircuit(int* gas,int gasSize,int* cost,int costSize){
    int cur=gas[0],start=0,i=0;
    while(start<gasSize)
    {
        if(cur<cost[i%gasSize])
        {
            start=i+1;
            if(i+1>=gasSize) break;
            cur=gas[i+1];
        }
        else cur=cur-cost[i%gasSize]+gas[(i+1)%gasSize];
        if((i-start)%gasSize==0&&i!=start) return start;
        i++;
    }
    return -1;
}

//T14(Leetcode13).罗马数字转整数
int romanToInt(char *s){
    int ans=0,len=strlen(s);
    for(int i=0;i<len-1;i++)        //排除最后一个字母
    {
        if(s[i]=='V') ans+=5;
        else if(s[i]=='L') ans+=50;
        else if(s[i]=='D') ans+=500;
        else if(s[i]=='M') ans+=1000;
        
        else if(s[i]=='I')
        {
            if(s[i+1]=='V'||s[i+1]=='X') ans-=1;
            else ans+=1;
        }
        else if(s[i]=='X')
        {
            if(s[i+1]=='L'||s[i+1]=='C') ans-=10;
            else ans+=10;
        }
        else if(s[i]=='C')
        {
            if(s[i+1]=='D'||s[i+1]=='M') ans-=100;
            else ans+=100;
        }
    }
    
    switch(s[len-1]){
        case 'I':ans+=1;break;
        case 'V':ans+=5;break;
        case 'X':ans+=10;break;
        case 'L':ans+=50;break;
        case 'C':ans+=100;break;
        case 'D':ans+=500;break;
        case 'M':ans+=1000;break;
    }
    return ans;
}

//T15(Leetcode12).整数转罗马数字
//数据范围:1<=num<=3999,最长数:3888,15位
//整数转罗马数字规则：用不超过num的最大value值依次表示(类比于10进制规则)
//时间复杂度:O(1)--values长度固定,每个字符出现次数不超过3(所表示的数范围有限)
/*
const int values[]={1000,900,500,400,100,90,50,40,10,9,5,4,1};
const char *symbols[]={"M","CM","D","CD","C","XC","L","XL","X","IX","V","I"};
char *intToRoman(int num){
    char str[16]={0};
    for(int i=0;i<13;i++)
    {
        while(num>=values[i])
        {
            strcpy(str+strlen(str),symbols[i]);
            num-=values[i];
        }
        if(num==0) break;
    }
    return str;
}
 */

//另解:十进制转化
const char* thousands[] = {"", "M", "MM", "MMM"};
const char* hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
const char* tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
const char* ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

char* intToRoman(int num) {
    char* roman = malloc(sizeof(char) * 16);
    roman[0] = '\0';
    strcpy(roman + strlen(roman), thousands[num / 1000]);
    strcpy(roman + strlen(roman), hundreds[num % 1000 / 100]);
    strcpy(roman + strlen(roman), tens[num % 100 / 10]);
    strcpy(roman + strlen(roman), ones[num % 10]);
    return roman;
}

//T16(Leetcode58).最后一个单词长度
int lengthOfLastWord(char *s){
    int len=strlen(s),wordLen=0,flag=0;
    for(int i=len-1;i>=0;i--)
    {
        if(!isalpha(s[i])&&flag==1) return wordLen;
        else if(isalpha(s[i])) {flag=1;wordLen++;}
    }
    return wordLen;
}

//T17(Leetcode14).最长公共前缀
//法一：横向扫描：依次遍历每个字符串，更新最长公共前缀
//时间复杂度：O(m*n),m为字符串平均长度,n为数量;空间复杂度:O(1).
/*
char *longestCommonPrefix(char **strs,int strsSize){
    int strNum=strlen(strs);
    if(strNum==0) return "";
    
    char *prefix=(char *)malloc(sizeof(char)*201);
    strcpy(prefix,strs[0]);
    int len=strlen(prefix);
    for(int i=1;i<strsSize;i++)
    {
        if(len==0) return "";
        int len2=strlen(strs[i]),j=0;
        while(j<len&&j<len2)
        {
            if(prefix[j]!=strs[i][j]) break;
            j++;
        }
        len=j;
    }
    for(int i=len;i<201;i++) prefix[i]='\0';
    return prefix;
}
 */

//法二：纵向比较:依次比较所有字符串上第n个字符
//时间复杂度：O(m*n);空间复杂度:O(1).
/*
char *longestCommonPrefix(char **strs,int strsSize){
    if(strsSize==0) return "";              //注意！考虑strs[0]的存在性
    int i=0,firstLen=strlen(strs[0]),flag=0;
    
    for(i=0;i<firstLen;i++)     //依次每个字符
    {
        char ch=strs[0][i];
        for(int j=1;j<strsSize;j++)     //依次每个字符串相同位置
        {
            if(i>=strlen(strs[j])) {flag=1;break;}
            else if(ch!=strs[j][i]) {flag=1;break;}
        }
        if(flag) break;
    }
    char *prefix=(char *)malloc(sizeof(char)*201);
    strncpy(prefix,strs[0],i);
    for(int j=i;j<201;j++) prefix[j]='\0';          //必须置0,否则报错
    return prefix;
}
*/

//法三：分治：分为两部分，分别求最长公共前缀
//时间复杂度:T(n)=2*T(n/2)+O(m),得:O(m*n);空间复杂度:O(m*logn),logn为递归调用层数
#define min(a,b) a<b?a:b
char *compare(char *str1,char *str2){
    int minLen=min(strlen(str1),strlen(str2)),i=0;
    char *prefix=(char *)malloc(sizeof(char)*(minLen+1));
    for(;i<minLen;i++)
    {
        if(str1[i]!=str2[i]) break;
    }
    strncpy(prefix,str1,i);
    for(int j=i;j<minLen+1;j++) prefix[j]='\0';
    return prefix;
}

char *longestCommonPrefixBetween(char **strs,int left,int right){
    if(left==right) return strs[left];
    int mid=(left+right)/2;
    return compare(longestCommonPrefixBetween(strs,left,mid),longestCommonPrefixBetween(strs,mid+1,right));
        //分别求左右两部分的最长公共前缀,再合并
}

char *longestCommonPrefix(char **strs,int strsSize){
    if(strsSize==0) return "";
    return longestCommonPrefixBetween(strs,0,strsSize-1);
}

/*
int main(){
    char *strs[]={"flower","flow","flight"};
    char *strs2[]={"dog","racecar","car"};
    printf("%s\n",longestCommonPrefix(strs,3));
    printf("%s",longestCommonPrefix(strs2,3));
    return 0;
}
*/

//T18.(Leetcode151).反转字符串中的单词顺序(单词内部字符保持不变)
//注意：移除字符串前/后空格，单词间多余空格
//时间复杂度:O(n);空间复杂度:O(1).
void reversePart(char *s,int start,int end){
    while(start<end)
    {
        char tmp=s[start];
        s[start]=s[end];
        s[end]=tmp;
        start++;end--;
    }
}

char *reverseWords(char *s){
    //遍历一遍,移除多余空格空格--快慢指针
    int len=strlen(s),fast=0,slow=0;
    while(s[fast]==' ') fast++;         //1.移除前端空格
    while(fast<len-1)               //2.移除单词间空格
    {
        if(s[fast]==' '&&s[fast+1]==' ') fast++;
        else s[slow++]=s[fast++];
    }
    if(s[fast]==' ') s[slow]='\0';      //此时fast=len-1
    else {s[slow++]=s[fast];s[slow]='\0';}
    
    //反转整个字符串
    reversePart(s,0,slow-1);
    
    //反转每一个单词
    for(int i=0;i<slow;i++)
    {
        int j=i;
        while(j<slow&&s[j]!=' ') j++;
        reversePart(s,i,j-1);
        i=j;
    }
    return s;
}

//T19.N字形变换
//法一:二维矩阵模拟(行列根据numRows定制)
//注:二维矩阵不写成1000x1000,太多空间浪费
//超时写法:
/*
char *convert(char *s,int numRows){
    int len=strlen(s),row=0,col=0,rev=0;
    char matrix[1000][1000]={0};
    char *ans=(char *)malloc(sizeof(char)*(len+1));
    for(int i=0;i<len;i++)
    {
        matrix[row][col]=s[i];
        if(row==numRows-1) rev=1;
        else if(row==0&&col!=0) rev=0;
        if(rev==0) row++;
        else {row--;col++;}
    }
    int cur=0;
    for(int i=0;i<1000;i++)
    {
        for(int j=0;j<1000;j++)
        {
            if(matrix[i][j]!='\0') ans[cur++]=matrix[i][j];
        }
    }
    ans[len]='\0';return ans;
    //如果定义char ans[len+1],会提醒:Address of stack memory associated with local variable 'ans' returned
    //应定义为:char *ans=(char *)malloc(sizeof(char)*(len+1));
}
 */

//时间复杂度:O(r*n),遍历矩阵,矩阵列数约为n/2;空间复杂度:O(r*n).
/*
char *convert(char *s,int numRows){
    int n=strlen(s),r=numRows;
    if(r==1||r>=n) return s;
    
    int t=2*r-2;        //每个周期字符数
    int c=(n+t-1)/t*(r-1);  //列数(n/t向上取整写作:(n+t-1)/t).
    //创建二维矩阵
    char **mat=(char **)malloc(sizeof(char *)*r);
    for(int i=0;i<r;i++)
    {
        mat[i]=(char *)malloc(sizeof(char)*c);
        memset(mat[i],0,sizeof(char)*c);
    }
    int row=0,col=0;
    for(int i=0;i<n;i++)
    {
        mat[row][col]=s[i];     //一个周期内，0~(r-2)向下移动,(r-1)~(2r-3)向右上移动
        if(i%t<r-1) row++;
        else {row--;col++;}
    }
    
    int cur=0;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            if(mat[i][j]) s[cur++]=mat[i][j];
        }
    }
    free(mat);      //释放空间
    return s;
}
*/

//优化:压缩矩阵空间(无空白,直接将新元素添至行末即可).
//时间复杂度:O(n);空间复杂度:O(n).
/*
char *convert(char *s,int numRows){
    int n=strlen(s),r=numRows;
    if(r==1||r>=n) return s;
    
    char **mat=(char **)malloc(sizeof(char *)*r);
    //创建二维矩阵
    for(int i=0;i<r;i++)
    {
        mat[i]=(char *)malloc(sizeof(char)*(n+1));
        memset(mat[i],0,sizeof(char)*(n+1));
    }
    int *colSize=(int *)malloc(sizeof(int)*r);      //记录每行元素个数
    memset(colSize,0,sizeof(int)*r);
    
    int row=0;
    for(int i=0;i<n;i++)
    {
        mat[row][colSize[row]++]=s[i];      //元素补在行尾,colSize值更新
        i%(2*r-2)<r-1?row++:row--;
    }
    
    int cur=0;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<colSize[i];j++) s[cur++]=mat[i][j];
        free(mat[i]);
    }
    free(colSize);
    free(mat);
    return s;
}
 */

//法三:直接构造,判断s中字符变换后的位置
//一个周期:t=2*r-2
//时间复杂度:O(n);空间复杂度O(1)(返回值ans不算在内)
char *convert(char *s,int numRows){
    int n=strlen(s),r=numRows;
    if(r==1||r>=n) return s;
    
    int t=2*r-2;
    char *ans=(char *)malloc(sizeof(char)*(n+1));
    
    //答案逐个填入ans
    int cur=0;
    for(int i=0;i<r;i++)        //第i行
    {
        for(int j=0;j+i<n;j+=t)     //j为每个周期的起始下标,j+i为当前下标
        {
            ans[cur++]=s[j+i];      //（该行）当前周期第一个字符
            if(0<i&&i<r-1&&(j+t-i)<n) ans[cur++]=s[j+t-i];      //当前周期第二个字符(第一/最后一行只有一个字符)
        }
    }
    ans[cur]='\0';      //一定要赋值！
    return ans;
}

//T20.找出字符串中第一个匹配项的下标(即实现strstr())
//法一：暴力匹配:haystack中找出needle
int strStr(char *haystack,char *needle){
    int len1=strlen(haystack),len2=strlen(needle),flag=0;
    if(len1==0||len2==0) return -1;
    for(int i=0;i+len2<=len1;i++)
    {
        flag=0;
        for(int j=0;j<len2;j++)
        {
            if(haystack[i+j]!=needle[j]) {flag=1;break;}
        }
        if(flag==0) return i;
    }
    return -1;
}

//kmp算法.
