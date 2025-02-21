// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.

// Press Opt+Enter with your caret at the highlighted text to see how
// IntelliJ IDEA suggests fixing it.

// Press Ctrl+R or click the green arrow button in the gutter to run the code.
// Press Ctrl+D to start debugging your code. We have set one breakpoint
// for you, but you can always add more by pressing Cmd+F8.

//Hash表
//T1(Leetcode383).赎金信:str1能不能由str2中字符构成
/*
class Solution{
    public boolean canConstruct(String ransomNote, String magazine)
    {
        if(ransomNote.length()>magazine.length()) return false;
        int[] cnt=new int[26];      //统计26个字符的词频
        for(char c:magazine.toCharArray()) cnt[c-'a']++;
        for(char c:ransomNote.toCharArray())
        {
            cnt[c-'a']--;       //字符仅能使用一次
            if(cnt[c-'a']<0) return false;
        }
        return true;
    }
}
 */

//T2.同构字符串:str1,str2中字符能否形成一一映射
//维护两个hash表:一个s->t;一个t->s
/*
class Solution{
    public boolean isIsomorphic(String s, String t)
    {
        if(s.length()!=t.length()) return false;
        Map<Character,Character>s2t=new HashMap<Character,Character>();
        Map<Character,Character>t2s=new HashMap<Character,Character>();
        int n=s.length();
        for(int i=0;i<n;i++)
        {
            char x=s.charAt(i),y=t.charAt(i);
            if((s2t.containsKey(x)&&s2t.get(x)!=y)||(t2s.containsKey(y)&&t2s.get(y)!=x)) return false;
            s2t.put(x,y);
            t2s.put(y,x);
        }
        return true;
    }
}
 */

//T4.有效的字母异位词:s,t中字母出现次数是否相等
//拓展:Unicode--每个字符,唯一的二进制编码
/*
class Solution{
    public boolean isAnagram(String s,String t)
    {
        if(s.length()!=t.length()) return false;
        Map<Character,Integer>table=new HashMap<Character,Integer>();
        for(int i=0;i<s.length();i++)
        {
            char ch=s.charAt(i);
            table.put(ch,table.getOrDefault(ch,0)+1);
        }
        for(int i=0;i<t.length();i++)
        {
            char ch=t.charAt(i);
            table.put(ch,table.getOrDefault(ch,0)-1);
            if(table.get(ch)<0) return false;
        }
        return true;
    }
}
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
//T5.字母异位词分组
//互为异位词的字符串字母相同,对所有字符串内部重排列(作为hash表的键)
/*
class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>>map=new HashMap<String,List<String>>();
        for(String str:strs)
        {
            char[] array=str.toCharArray();
            Arrays.sort(array);
            String key=new String(array);
            List<String> list=map.getOrDefault(key,new ArrayList<String>());
            list.add(str);
            map.put(key,list);
        }
        return new ArrayList<List<String>>(map.values());
    }
}
 */

//T6.快乐数判断:每个位置上数字的平方和,是否最终得到1
//4位及以上数字,每计算一次,数位丢失,最终降至3位或以下;3位数的数字,一步后,不会超过243
//两种可能:回到1;进入循环
//法一：hash集合检测循环
//时间复杂度:计算n的下一个数字O(logn)--n的位数由logn决定.总:O(243*3+logn+loglogn+...)=O(logn).
//空间复杂度:O(logn)--放入hash集合中的数字
/*
class Solution{
    private int getNext(int n)      //计算下一个数字
    {
        int sum=0;
        while(n>0)
        {
            int d=n%10;
            sum+=d*d;
            n/=10;
        }
        return sum;
    }

    public boolean isHappy(int n)
    {
        Set<Integer>seen=new HashSet<>();       //集合set(类型HashSet)记录:当前数字n是否出现过
        while(n!=1&&!seen.contains(n))
        {
            seen.add(n);
            n=getNext(n);
        }
        return n==1;
    }
}
 */

//法二：快慢指针法
//时间复杂度:O(logn);空间复杂度:O(1),指针只需常数空间
/*
class Solution{
    public int getNext(int n)
    {
        int sum=0;
        while(n>0)
        {
            int d=n%10;
            n/=10;
            sum+=d*d;
        }
        return sum;
    }

    public boolean isHappy(int n)
    {
        int slow=n,fast=getNext(n);
        while(fast!=1&&slow!=fast)
        {
            slow=getNext(slow);
            fast=getNext(getNext(fast));
        }
        return fast==1;
    }
}
 */

//T8.
/*
class Solution{
    public int longestConsecutive(int[] nums) {
        Set<Integer>num_set=new HashSet<Integer>();
        for(int num:nums) num_set.add(num);     //录入所有数
        int longestStreak=0;
        for(int num:num_set)
        {
            if(!num_set.contains(num-1))
            {
                int curNum=num;
                int curStreak=1;
                while(num_set.contains(curNum+1))
                {
                    curNum+=1;
                    curStreak+=1;
                }
                longestStreak=Math.max(longestStreak,curStreak);
            }
        }
        return longestStreak;
    }
}
 */

//T9.建立四叉树:
//法一:递归处理grid:是叶节点，构造返回；非叶节点，分为四个部分
//时间复杂度:T(n)=4*T(n/2)+O(n^2);空间复杂度:O(logn)--递归栈空间
/*
class Node{
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;

    public Node() {
        this.val = false;
        this.isLeaf = false;
        this.topLeft = null;
        this.topRight = null;
        this.bottomLeft = null;
        this.bottomRight = null;
    }
    public Node(boolean val, boolean isLeaf) {
        this.val = val;
        this.isLeaf = isLeaf;
        this.topLeft = null;
        this.topRight = null;
        this.bottomLeft = null;
        this.bottomRight = null;
    }
    public Node(boolean val, boolean isLeaf, Node topLeft, Node topRight, Node bottomLeft, Node bottomRight) {
        this.val = val;
        this.isLeaf = isLeaf;
        this.topLeft = topLeft;
        this.topRight = topRight;
        this.bottomLeft = bottomLeft;
        this.bottomRight = bottomRight;
    }
};

class Solution{
    public Node construct(int [][] grid){
        return dfs(grid,0,0,grid.length,grid.length);
    }
    public Node dfs(int [][] grid,int r0,int c0,int r1,int c1){
        boolean same=true;
        for(int i=r0;i<r1;i++)
        {
            for(int j=c0;j<c1;j++)
            {
                if(grid[i][j]!=grid[r0][c0]) {same=false;break;}
                if(!same) break;
            }
        }
        if(same) return new Node(grid[r0][c0]==1,true);

        Node ret=new Node(true,false,
                dfs(grid,r0,c0,(r0+r1)/2,(c0+c1)/2),
                dfs(grid,r0,(c0+c1)/2,(r0+r1)/2,c1),
                dfs(grid,(r0+r1)/2,c0,r1,(c0+c1)/2),
                dfs(grid,(r0+r1)/2,(c0+c1)/2,r1,c1));
        return ret;
    };
}
 */

//T10.合并k个有序链表
//分治思路：k个链表合并为k/2个链表,再合并.
//时间复杂度:第一轮合并k/2组链表,每组时间为O(2n)...总时间为:O(nk*logk).
//空间复杂度:O(logk).
public class ListNode{
     int val;
     ListNode next;
     ListNode() {}
     ListNode(int val) { this.val = val; }
     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 }
 /*
class Solution{
    public ListNode mergeKLists(ListNode[] lists){
        return merge(lists,0,lists.length-1);
    }
    public ListNode merge(ListNode[] lists,int l,int r){
        if(l==r) return lists[l];
        if(l>r) return null;
        int mid=(l+r)>>1;
        return mergeTwoLists(merge(lists,l,mid),merge(lists,mid+1,r));
    }
    public ListNode mergeTwoLists(ListNode a,ListNode b){
        if(a==null||b==null) return a!=null?a:b;
        ListNode head=new ListNode(0);
        ListNode tail=head,p1=a,p2=b;
        while(p1!=null&&p2!=null)
        {
            if(p1.val<=p2.val)
            {
                tail.next=p1;
                p1=p1.next;
            }
            else
            {
                tail.next=p2;
                p2=p2.next;
            }
            tailtail.next;
        }
        tail.next=(p1!=null)?p1:p2;
        return head.next;
    }
}
  */

//法三：优先队列:维护每个链表中,未被合并的元素中最前面一个
//时间复杂度:O(nk*logk),优先队列元素最多k个,插入/删除时间为O(logk),最多kn个点.
//空间复杂度:O(k).
class Solution{
    class Status implements Comparable<Status>{
        int val;
        ListNode ptr;
        Status(int val,ListNode ptr){
            this.val=val;
            this.ptr=ptr;
        }
        public int compareTo(Status status2) {
            return this.val-status2.val;
        }
    }

    PriorityQueue<Status>queue=new PriorityQueue<Status>();
    public ListNode mergeKLists(ListNode[] lists){
        for(ListNode node:lists)
        {
            if(node!=null) queue.offer(new Status(node.val,node));
        }
        ListNode head=new ListNode(0);
        ListNode tail=head;
        while(!queue.isEmpty())
        {
            Status f=queue.poll();
            tail.next=f.ptr;
            tail=tail.next;
            if(f.ptr.next!=null) queue.offer(new Status(f.ptr.next.val,f.ptr.next));
        }
        return head.next;
    }
}