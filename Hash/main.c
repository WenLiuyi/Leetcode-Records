//
//  main.c
//  Hash
//
//  Created by 文柳懿 on 2023/8/10.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<uthash.h>
#include<stdbool.h>

//T2.同构字符串:str1,str2中字符能否形成一一映射(双射)
//维护两个hash表:一个s->t;一个t->s
/*
struct HashTable{
    char key;
    char val;
    UT_hash_handle hh;
};

bool isIsomorphic(char * s, char * t){
    if(strlen(s)!=strlen(t)) return false;
    
    struct HashTable *s2t=NULL;
    struct HashTable *t2s=NULL;
    
    int n=strlen(s);
    for(int i=0;i<n;i++)
    {
        //在hash表中,分别寻找当前位置:s对应t中字符,t对应s中字符
        struct HashTable *tmp1,*tmp2;
        HASH_FIND(hh,s2t,&s[i],sizeof(char),tmp1);
        HASH_FIND(hh,t2s,&t[i],sizeof(char),tmp2);
        if(tmp1!=NULL)
        {
            if(tmp1->val!=t[i]) return false;
        }
        else
        {
            tmp1=(struct HashTable *)malloc(sizeof(struct HashTable));
            tmp1->key=s[i];tmp1->val=t[i];
            HASH_ADD(hh,s2t,key,sizeof(char),tmp1);
        }
        
        if(tmp2!=NULL)
        {
            if(tmp2->val!=s[i]) return false;
        }
        else
        {
            tmp2=(struct HashTable *)malloc(sizeof(struct HashTable));
            tmp2->key=t[i];tmp2->val=s[i];
            HASH_ADD(hh,t2s,key,sizeof(char),tmp2);
        }
    }
    return true;
}
 */

//T3.单词规律:字符--字符串一一对应(双射)
//时间复杂度:O(m+n)--字符串分割O(m),寻找映射O(n).
/*
typedef struct HashTable{
    int key;
    char val[301];
    UT_hash_handle hh;
};

bool wordPattern(char *pattern,char *s){
    char **strs=(char **)malloc(sizeof(char *)*300);     //二维数组储存:模式串分割后的字符串
    char *val=strtok(s," ");        //用空格分割
    strs[0]=val;
    int i=1;        //i记录s中字符串个数
    while(val!=NULL)
    {
        val=strtok(NULL," ");
        strs[i++]=val;
    }
    int n=strlen(pattern);
    if(n!=i-1) return false;
    
    struct HashTable *hash1=NULL,*hash2=NULL;
    for(int i=0;i<n;i++)
    {
        int x=pattern[i]-'a';
        struct HashTable *tmp1,*tmp2;
        HASH_FIND_INT(hash1,&x,tmp1);
        HASH_FIND_STR(hash2,strs[i],tmp2);
        
        if(tmp1!=NULL)      //pattern中当前字符,在hash1中有匹配的字符串
        {
            if(strcmp(tmp1->val,strs[i])) return false;
        }
        else
        {
            tmp1=(struct HashTable *)malloc(sizeof(struct HashTable));
            tmp1->key=x;strcpy(tmp1->val,strs[i]);
            HASH_ADD_INT(hash1,key,tmp1);
        }
        
        if(tmp2!=NULL)      //s中当前字符串,在hash2中有匹配的字符
        {
            if(tmp2->key!=x) return false;
        }
        else
        {
            tmp2=(struct HashTable *)malloc(sizeof(struct HashTable));
            tmp2->key=x;
            strcpy(tmp2->val,strs[i]);
            HASH_ADD_STR(hash2,val,tmp2);
        }
    }
    free(strs);
    return true;
}
 */

//T4.有效的字母异位词:s,t中字母出现次数是否相等
//法一:维护table,依次遍历s,t,对table中频次值进行加减
//时间复杂度:O(n);空间复杂度:O(S),S为字符集大小
/*
bool isAnagram(char *s,char *t){
    int l1=strlen(s),l2=strlen(t);
    if(l1!=l2) return false;
    
    int table[26]={0};
    for(int i=0;i<l1;i++)
    {
        table[s[i]-'a']++;
    }
    for(int i=0;i<l2;i++)
    {
        table[t[i]-'a']--;
        if(table[t[i]-'a']<0) return false;
    }
    return true;
}
 */

//法二:排序:排序后是否相等
/*
int cmp(const void *e1,const void *e2){
    return *(char *)e1-*(char *)e2;
}

bool isAnagram(char *s,char *t){
    int l1=strlen(s),l2=strlen(t);
    if(l1!=l2) return false;
    
    qsort(s,l1,sizeof(char),cmp);
    qsort(t,l2,sizeof(char),cmp);
    return strcmp(s,t)==0;
}
 */

//T5.字母异位词分组
//互为异位词的字符串字母相同,对所有字符串内部重排列(作为hash表的键)
//时间复杂度:O(n*klogk),遍历n个字符串,每个字符串O(k*logk)排序,O(1)时间更新hash表
//空间复杂度:O(n*k).
typedef struct{
    char *key;
    char **vals;
    int cnt;        //该组中字母异位词个数
    UT_hash_handle hh;
}HashTable;

int cmp(const void *e1,const void *e2){
    return *(char *)e1-*(char *)e2;
}

//returnSize为组数,returnColumnSizes为每组中字母异位词的个数
char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    HashTable *ans=NULL;
    *returnSize=0;
    
    for(int i=0;i<strsSize;i++)
    {
        char *sortStr=(char *)malloc(sizeof(char)*(strlen(strs[i])+1));
        strcpy(sortStr,strs[i]);
        qsort(sortStr,strlen(sortStr),sizeof(char),cmp);
        HashTable *tmp;
        HASH_FIND_STR(ans,sortStr,tmp);
        
        if(tmp==NULL)
        {
            (*returnSize)++;
            tmp=(HashTable *)malloc(sizeof(HashTable));
            tmp->key=sortStr;
            tmp->cnt=1;
            tmp->vals=(char **)malloc(sizeof(char *)*strsSize);     //该组中,最多strsSize个字符串
            tmp->vals[0]=strs[i];
            HASH_ADD_STR(ans,key,tmp);
        }
        else tmp->vals[tmp->cnt++]=strs[i];
    }
    
    char ***res=(char ***)malloc(sizeof(char **)*(*returnSize));
    *returnColumnSizes=(int*)malloc(sizeof(int)*(*returnSize));
    HashTable *tmp=NULL,*s=NULL;
    int cur=0;
    HASH_ITER(hh,ans,s,tmp)
    {
        char **group=(char **)malloc(sizeof(char *)*s->cnt);
        for(int i=0;i<s->cnt;i++) group[i]=s->vals[i];
        (*returnColumnSizes)[cur]=s->cnt;
        res[cur++]=group;
        HASH_DEL(ans,s);
    }
    return res;
}

/*
int main(){
    char *strs[6]={"eat","tea","tan","ate","nat","bat"};
    int Size;
    int *cols=(int *)malloc(sizeof(int)*30);
    char ***ans=groupAnagrams(strs,6,&Size,&cols);
    printf("size=%d\n",Size);
    for(int i=0;i<Size;i++)
    {
        printf("colSize=%d\n",cols[i]);
        for(int j=0;j<cols[i];j++) printf("%s ",ans[i][j]);
        printf("\n");
    }
    
    return 0;
}
*/

//T7.存在重复元素II:判断是否存在nums[i]==nums[j],且abs(i-j)<=k.
//法一:hash表--记录每个元素的最大下标
//时间复杂度:O(n);空间复杂度:O(n).
struct HashTable{
    int key;        //元素
    int val;        //最大下标
    UT_hash_handle hh;
};

struct HashTable *hashFindItem(struct HashTable **obj,int key){
    struct HashTable *pEntry=NULL;
    HASH_FIND_INT(*obj,&key,pEntry);
    return pEntry;
}

void hashAddItem(struct HashTable **obj,int key,int val){
    struct HashTable *pEntry=(struct HashTable *)malloc(sizeof(struct HashTable));
    pEntry->key=key;
    pEntry->val=val;
    HASH_ADD_INT(*obj,key,pEntry);
}

void hashFreeAll(struct HashTable **obj){
    struct HashTable *curr,*tmp;
    HASH_ITER(hh,*obj,curr,tmp)
    {
        HASH_DEL(*obj,curr);
        free(curr);
    }
}

/*
bool containsNearbyDuplicate(int* nums, int numsSize, int k){
    struct HashTable *dict=NULL;
    for(int i=0;i<numsSize;i++)
    {
        struct HashTable *pEntry=hashFindItem(&dict,nums[i]);
        if(pEntry!=NULL)
        {
            if(i-pEntry->val<=k)
            {
                hashFreeAll(&dict);
                return true;
            }
        }
        hashAddItem(&dict,nums[i],i);
    }
    hashFreeAll(&dict);
    return false;
}
*/

//法二：滑动窗口:数组中每个长度不超过k+1的窗口
//时间复杂度:O(n);空间复杂度:O(k).
void hashEraseItem(struct HashTable **obj,int key){
    struct HashTable *p=NULL;
    HASH_FIND_INT(*obj,&key,p);
    if(p!=NULL)
    {
        HASH_DEL(*obj,p);
        free(p);
    }
}
bool containsNearbyDuplicate(int* nums, int numsSize, int k){
    struct HashTable *cnt=NULL;     //记录元素出现次数
    for(int i=0;i<numsSize;i++)
    {
        if(i>k) hashEraseItem(&cnt,nums[i-k-1]);       //移除
        struct HashTable *p=hashFindItem(&cnt,nums[i]);
        if(p!=NULL) return true;
        hashAddItem(&cnt,nums[i],1);
    }
    hashFreeAll(&cnt);
    return false;
}


