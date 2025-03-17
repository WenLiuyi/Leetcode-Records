//
//  main.c
//  Recurrence
//
//  Created by 文柳懿 on 2023/9/5.
//

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

//回溯问题
//T1(Leetcode17).电话号码的字母组合
//维护一个字符串,表示已有字母排列(初始为空).每次将一位数字的对应字母,插到已有排列之后
char phoneMap[11][5] = {"\0", "\0", "abc\0", "def\0", "ghi\0", "jkl\0", "mno\0", "pqrs\0", "tuv\0", "wxyz\0"};

char **combinations;        //答案数组
int combinations_size;

char *combination;          //当前组合
int combination_size;

int digits_size;

void backtrack(int index,char *digits){
    if(index==digits_size)      //当前组合已经构建完成，加入combinations中
    {
        char* tmp = malloc(sizeof(char) * (combination_size + 1));
        memcpy(tmp,combination,sizeof(char)*(combination_size + 1));
        combinations[combinations_size++]=tmp;
        //注意:(1)combinations[i]为字符型指针,因此只能重新构造指针tmp,使其指向tmp,而不能使用memcpy(这只针对申请了空间的字符型数组)
        //memcpy(combinations[combinations_size++],combination,sizeof(char) * (combination_size + 1));
        //(2)不能写为:combinations[combination_size++]=combination(combination会不断改变)
    }
    else
    {
        char *letters=phoneMap[digits[index]-'0'];      //index字符对应的所有字母
        int len=strlen(letters);
        for(int i=0;i<len;i++)
        {
            combination[combination_size++]=letters[i];
            backtrack(index+1,digits);
            combination[--combination_size]='\0';   //回退
        }
    }
}

char ** letterCombinations(char * digits, int* returnSize){
    combinations_size=combination_size=0;
    digits_size=strlen(digits);         //字符串长度
    if(digits_size==0)
    {
        *returnSize=0;
        return combinations;
    }
    
    //预估combinations长度
    int num=1;
    for(int i=0;i<digits_size;i++) num*=4;
    combinations=(char **)malloc(sizeof(char *)*num);
    combination=(char *)malloc(sizeof(char)*(digits_size+1));
    memset(combination,'\0',digits_size+1);
    
    backtrack(0,digits);
    *returnSize=combinations_size;
    return combinations;
}

//T2(Leetcode77).组合：给定n,k,返回[1,n]中所有可能k个数的组合
//时间复杂度:O(C(n,k)*k);空间复杂度:O(n+k)--递归栈空间+临时数组temp空间代价
int *temp;         //当前组合
int tmp_size;

int **ans;
int ans_size;       //答案数组

//int used[21]={0};       //used[i]记录整数i的出现情况

//*returnColumnSizes为记录每个组合长度的数组(统一值k);lowBound记录元素取值下限(为保持升序排序,避免重复出现)
void getCombination(int index,int k,int n,int lowBound){     //index为当前插入temp中的元素下标
    if(index==k)
    {
        int *cur=(int *)malloc(sizeof(int)*k);
        memcpy(cur,temp,sizeof(int)*k);
        ans[ans_size++]=cur;
    }
    else
    {
        for(int i=lowBound+1;n-i+1>=k-index;i++)    //剪枝:n-i+1>=k-index,提前排除不可能的情况
        {
            //if(used[i]) continue;     //加入lowBound后,无需使用可去除used数组的记录
            temp[tmp_size++]=i;
            //used[i]=1;
            getCombination(index+1,k,n,i);
            temp[--tmp_size]=0;     //回退
            //used[i]=0;
        }
    }
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes){
    tmp_size=ans_size=0;
    
    ans=(int **)malloc(sizeof(int *)*200001);      //num预估ans包含的组合个数,用于预先申请空间
    temp=(int *)malloc(sizeof(int)*k);
    memset(temp,0,k);
    
    getCombination(0,k,n,0);
    *returnSize=ans_size;
    (*returnColumnSizes)=(int *)malloc(sizeof(int *)*ans_size);
    for(int i=0;i<ans_size;i++) (*returnColumnSizes)[i]=k;
    
    return ans;
}

//T3(Leetcode46).全排列:不含重复数字的数组nums
//时间复杂度:O(n*n!);空间复杂度:O(n)--递归栈空间
int **res;
int res_size;

int *cur;
int cur_size;

int used[6]={0};        //used[i]记录原数组nums中,nums[i]在当前排列状态的使用情况

void getPermutations(int index,int n,int nums[]){
    if(index==n)
    {
        int *tmp=(int *)malloc(sizeof(int)*n);
        memcpy(tmp,cur,sizeof(int)*n);
        res[res_size++]=tmp;
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            if(used[i]) continue;
            cur[index]=nums[i];
            used[i]=1;
            getPermutations(index+1,n,nums);
            used[i]=0;      //回退
        }
    }
}

int **permute(int *nums,int numsSize,int *returnSize,int **returnColumnSizes){
    int total=1;
    for(int i=numsSize;i>0;i--) total*=i;   //total为res中组合的数目
    
    res_size=cur_size=0;
    res=(int **)malloc(sizeof(int *)*total);
    cur=(int *)malloc(sizeof(int)*numsSize);
    memset(cur,0,numsSize);
    
    getPermutations(0,numsSize,nums);
    *returnSize=res_size;
    *returnColumnSizes=(int *)malloc(sizeof(int)*res_size);
    for(int i=0;i<res_size;i++) (*returnColumnSizes)[i]=numsSize;
    
    return res;
}

//T4(Leetcode39).组合总和:无重复元素整数数组candidates,目标整数target--找出candidates中数字和为target的不同组合
//所给数据使得:组合数少于150个
int **lists;
int list_size;

int *tmp;
int tmp_size;

int global_candidatesSize;
int global_target;

void getCandidates(int index,int *candidates,int curSum,int **returnColumnSizes,int lowerBound){
    if(curSum==global_target)      //记录合法结果
    {
        int *cur=(int *)malloc(sizeof(int)*tmp_size);
        memcpy(cur,tmp,sizeof(int)*tmp_size);
        lists[list_size]=cur;
        (*returnColumnSizes)[list_size++]=tmp_size;
    }
    else if(lowerBound>=global_candidatesSize) return;
    else
    {
        int flag=0;
        for(int i=lowerBound;i<global_candidatesSize;i++)
        {
            if(curSum+candidates[i]>global_target) continue;
            flag=1;
            tmp[tmp_size++]=candidates[i];
            curSum+=candidates[i];
            getCandidates(index+1,candidates,curSum,returnColumnSizes,i);
            tmp_size--;     //回退
            curSum-=candidates[i];
        }
        if(flag==0) return;         //剪枝(时间复杂度上是否有用?)
    }
}

int **combinationSum(int *candidates,int candidatesSize,int target,int *returnSize,int **returnColumnSizes){
    list_size=tmp_size=0;
    lists=(int **)malloc(sizeof(int *)*1001);
    tmp=(int *)malloc(sizeof(int)*40);
    global_candidatesSize=candidatesSize;global_target=target;
    memset(tmp,0,40);
    *returnColumnSizes=(int *)malloc(sizeof(int)*1001);
    memset(*returnColumnSizes,0,1001);
    
    getCandidates(0,candidates,0,returnColumnSizes,0);
    *returnSize=list_size;
    
    return lists;
}

//T5(Leetcode22).括号生成
char **parentheses;          //所有括号组合的集合
int parentheses_size;

char *bracket;
int bracket_size;           //当前括号组合

void getBracket(int n,int left,int right){         //left,right为当前已有左/右括号数量
    if(left==right&&left==n)        //记录合法结果
    {
        parentheses[parentheses_size]=(char *)malloc(sizeof(char)*bracket_size);
        memcpy(parentheses[parentheses_size++],bracket,sizeof(char)*bracket_size);
        //parentheses[i]中为字符型指针，未申请空间，因此不能写作:
        //memcpy(parentheses[parentheses_size++],bracket,sizeof(char)*bracket_size);
        return;
    }
    //1.不超过n的前提下，加入左括号
    if(left>=right&&left<n)
    {
        bracket[bracket_size++]='(';
        getBracket(n,left+1,right);
        bracket_size--;
    }
    //2.加入右括号
    if(left>right)
    {
        bracket[bracket_size++]=')';
        getBracket(n,left,right+1);
        bracket_size--;
    }
}

char ** generateParenthesis(int n, int* returnSize){
    parentheses_size=bracket_size=0;
    parentheses=(char **)malloc(sizeof(char *)*10001);        //预估集合中最大组合数
    bracket=(char *)malloc(sizeof(char *)*(2*n+1));
    memset(bracket,'\0',2*n+1);
    
    getBracket(n,0,0);
    *returnSize=parentheses_size;
    return parentheses;
}

//T6(Leetcode79).单词搜索
//时间复杂度:宽松上界O(MN*3^L)--每次调用findWord时,最多进入3个分支(除了第一次可进入4个分支)
//空间复杂度:O(MN)(visited),栈深度最大为O(min(L,MN)).
bool findWord(char **board,char *word,int index,int len,int row,int col,int m,int n,int **visited){
    if(index==len) return true;
    if(row>0)   //上有字母
    {
        if(board[row-1][col]==word[index]&&!visited[row-1][col])
        {
            visited[row-1][col]=1;
            if(findWord(board,word,index+1,len,row-1,col,m,n,visited)) return true;
            visited[row-1][col]=0;
        }
    }
    if(row<m-1)     //下有字母
    {
        if(board[row+1][col]==word[index]&&!visited[row+1][col])
        {
            visited[row+1][col]=1;
            if(findWord(board,word,index+1,len,row+1,col,m,n,visited)) return true;
            visited[row+1][col]=0;
        }
    }
    if(col>0)   //左有字母
    {
        if(board[row][col-1]==word[index]&&!visited[row][col-1])
        {
            visited[row][col-1]=1;
            if(findWord(board,word,index+1,len,row,col-1,m,n,visited)) return true;
            visited[row][col-1]=0;
        }
    }
    if(col<n-1)
    {
        if(board[row][col+1]==word[index]&&!visited[row][col+1])
        {
            visited[row][col+1]=1;
            if(findWord(board,word,index+1,len,row,col+1,m,n,visited)) return true;
            visited[row][col+1]=0;
        }
    }
    return false;
}
bool exist(char** board, int boardSize, int* boardColSize, char * word){
    int m=boardSize,n=boardColSize[0],len=strlen(word);     //m,n为board的行数,列数
    int **visited=(int **)malloc(sizeof(int *)*boardSize);
    for(int i=0;i<boardSize;i++)
    {
        visited[i]=(int *)malloc(sizeof(int)*boardColSize[0]);
        memset(visited[i],0,sizeof(int)*boardColSize[0]);
    }
    
    if(len>m*n) return false;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(board[i][j]==word[0])
            {
                visited[i][j]=1;
                if(findWord(board,word,1,len,i,j,m,n,visited)) return true;
                visited[i][j]=0;
            }
        }
    }
    return false;
}
