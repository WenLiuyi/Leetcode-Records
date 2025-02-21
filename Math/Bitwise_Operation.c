//
//  main.c
//  biteWise_Operation
//
//  Created by 文柳懿 on 2023/9/10.
//

#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//T1(Leetcode67).二进制求和:二进制字符串,返回二进制形式的和
//法一：模拟相加和进位
//时间复杂度:O(n),假设n=max{|a|,|b|}.
//空间复杂度:用了两个数组sum,ans(ans由sum反转而成)
/*
char * addBinary(char * a, char * b){
    char sum[10005]={0};
    int m=strlen(a),n=strlen(b);
    int i=m-1,j=n-1,now=0,carry=0;
    while(i>=0&&j>=0)
    {
        sum[now++]=(a[i]-'0'+b[j]-'0'+carry)%2+'0';
        carry=(a[i]-'0'+b[j]-'0'+carry)/2;
        i--;j--;
    }
    while(i>=0)
    {
        sum[now++]=(a[i]-'0'+carry)%2+'0';
        carry=(a[i]-'0'+carry)/2;
        i--;
    }
    while(j>=0)
    {
        sum[now++]=(b[j]-'0'+carry)%2+'0';
        carry=(b[j]-'0'+carry)/2;
        j--;
    }
    if(carry) sum[now++]='1';
    //printf("now=%d ",now);
    char *ans=(char *)malloc(sizeof(char)*(now+1));
    memset(ans,'\0',sizeof(char)*(now+1));
    for(int i=0;i<now;i++) ans[i]=sum[now-1-i];
    
    return ans;
}
*/

//法一变式:先reverse
/*
#define max(a,b) a>b?a:b
void reverse(char *s){
    int len=strlen(s);
    for(int i=0;i<len/2;i++)
    {
        char t=s[i];
        s[i]=s[len-1-i],s[len-1-i]=t;
    }
}

char *addBinary(char *a,char *b){
    reverse(a);reverse(b);      //翻转字符串,从低位到高位
    int len1=strlen(a),len2=strlen(b),n=max(len1,len2),carry=0,len=0;
    char *ans=(char *)malloc(sizeof(char)*(n+2));   //答案最多n+1位，字符串结尾加1位
    
    for(int i=0;i<n;i++)
    {
        carry+=i<len1?(a[i]=='1'):0;
        carry+=i<len2?(b[i]=='1'):0;
        ans[len++]=carry%2+'0';
        carry/=2;
    }
    if(carry) ans[len++]='1';
    ans[len]='\0';
    reverse(ans);
    
    return ans;
}
*/

//法三:位运算:(python3编写较方便)
//把 aaa 和 bbb 转换成整型数字 xxx 和 yyy，在接下来的过程中，xxx 保存结果，yyy 保存进位。
//当进位不为 000 时:
//计算当前 xxx 和 yyy 的无进位相加结果：answer = x ^ y
//计算当前 xxx 和 yyy 的进位：carry = (x & y) << 1
//完成本次循环，更新 x = answer，y = carry
//返回 xxx 的二进制形式


//T2.颠倒二进制位(32位无符号整数)
//注：Java中只定义了有符号整数.对n的右移应采用逻辑右移

//法一：逐位颠倒
//思路：从低位向高位枚举n的二进制位，倒序添加至翻转结果rev中
//时间复杂度:O(logn);空间复杂度:O(1).
/*
uint32_t reverseBits(uint32_t n){
    uint32_t rev=0;
    for(int i=0;i<32&&n>0;i++)
    {
        rev|=(n&1)<<(31-i);         //n&1取n的末位;rev|=将翻转后的当前位数字,融入rev中
        n>>=1;
    }
    return rev;
}
*/

//法二：位运算分治
//思路：二进制串均分为左右两部分,对每部分执行翻转,将左半部分拼在右半部分之后
//从底向上构建
//时间复杂度:O1();空间复杂度:O(1).

const uint32_t M1=0x55555555;   //01010101010101010101010101010101
const uint32_t M2=0x33333333;   //00110011001100110011001100110011
const uint32_t M4=0x0f0f0f0f;   //00001111000011110000111100001111
const uint32_t M8=0x00ff00ff;   //00000000111111110000000011111111

uint32_t reverseBits(uint32_t n){
    n=n>>1&M1 | (n&M1)<<1;      //奇偶位翻转
    n=n>>2&M2 | (n&M2)<<2;      //每两位一组,奇数/偶数组交换
    n=n>>4&M3 | (n&M3)<<4;
    n=n>>8&M4 | (n&M4)<<8;
    
    return n>>16 | n<<16;
}

//T3.位1的个数:返回无符号整数,二进制表达式中'1'的个数
//法一：逐位检查
//时间复杂度:O(k),k是int型的二进制位数,k<=32空间复杂度:O(1).
/*
int hammingWeight(uint32_t n){
    int cnt=0;
    for(int i=0;i<32&&n>0;i++)
    {
        cnt+=n&1;
        n>>=1;
    }
    return cnt;
}
*/

//法二:位运算优化
//n&(n-1):运算结果为:将n的二进制位中最低位1变为0.
//每次运算使得n中最低位1被翻转,因此运算次数即为:n的二进制位中1的个数
//时间复杂度:O(logn).
int hammingWeight(uint32_t n){
    int cnt=0;
    while(n)
    {
        n&=(n-1);
        cnt++;
    }
    return cnt;
}

//T4.只出现一次的数字:找出非空数组nums中,只出现一次的数字(其余数字均出现2次)
//不考虑时间/空间复杂度限制时,多种解决思路:
//集合储存数字;哈希表储存数字和次数--额外O(n)空间

//异或运算:a^0=a;a^a=0;满足交换律/结合律
//(a1^a1)^...^(am^am)^a[m+1]--出现2次归0，最后留下出现1次的
//空间复杂度:O(1)
/*
int singleNumber(int *nums,int numsSize){
    int ans=0;
    for(int i=0;i<numsSize;i++) ans^=nums[i];
    return ans;
}
*/

//T5(Leetcode137).只出现一次的数字II：num中,1个数字出现1次,其余数字出现3次

//法一：
//考虑答案的第i个二进制位(i从0开始编号):
//对于数组中非答案的元素，其和为3的倍数.
//推论:答案中第i个二进制位,是数组中所有元素第i个二进制位之和,除以3的余数.
//时间复杂度:O(n*logC)--n为数组长度,C为数据范围;空间复杂度:O(1).
int singleNumber(int *nums,int numsSize){
    int ans=0;
    for(int i=0;i<32;i++)
    {
        int total=0;
        for(int j=0;j<numsSize;j++) total+=(nums[j]>>i)&1;      //取nums[j]的第i个二进制位
        if(total%3) ans|=(1u<<i);
    }
    return ans;
}

//T6.数字范围按位与:返回left~right间,所有数字按位与的结果
//直观方案:遍历每一个数
//转化:给定两个整数，寻找其二进制串的公共前缀

//法一：位移
//两个数字逐位右移,直至数字相等,找到公共前缀;公共前缀左移,右端补满0.
//时间复杂度:O(logn);空间复杂度:O(1).
/*
int rangeBitwiseAnd(int left,int right){
    int shift=0;
    while(left<right)
    {
        left>>=1;
        right>>=1;
        shift++;
    }
    return left<<shift;
}
*/

//法二:Brian Kernighan 算法
//时间复杂度:O(logn)--和位移有相同的渐近复杂度，但该算法跳过了数字间的所有0位，需要的迭代次数更少
int rangeBitwiseAnd(int left,int right){
    while(left<right) right&=(right-1);        //抹去最右侧的1
    return right;
}
