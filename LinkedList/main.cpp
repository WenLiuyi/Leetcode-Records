//
//  main.cpp
//  LinkedList
//
//  Created by 文柳懿 on 2025/3/5.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// 1. T203.移除链表元素:给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
// 法一：直接操作原链表：分头节点、非头节点两种情况
class Solution_1_1 {
public:
    ListNode* removeElements(ListNode* head, int val) {
        while(head!=nullptr && head->val==val){     // 1. 删除头节点
            ListNode *tmp=head;
            head=head->next;    // 新的头节点
            delete tmp;
        }
        ListNode *cur=head;     // 2. 删除非头节点:判断cur的下一个节点（因为删除头节点时，需要该节点的前驱节点）
        while(cur!=nullptr && cur->next!=nullptr){
            if(cur->next->val==val){
                ListNode *tmp=cur->next;
                cur->next=cur->next->next;
                delete tmp;
            }else{
                cur=cur->next;
            }
        }
        return head;
    }
};

// 法二：使用虚拟头节点操作
class Solution_1_2 {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *dummy=new ListNode(0);
        dummy->next=head;
        ListNode *cur=dummy;
        while(cur!=nullptr && cur->next!=nullptr){
            if(cur->next->val==val){
                ListNode *tmp=cur->next;
                cur->next=cur->next->next;
                delete tmp;
            }else{
                cur=cur->next;
            }
        }
        head=dummy->next;
        delete dummy;
        return head;
    }
};

// 法三：递归
// 空间复杂度：O(n)
class Solution_1_3 {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(head==nullptr) return head;  // 终止条件：链表为空
        if(head->val==val){
            ListNode *newHead=removeElements(head->next,val);
            delete head;
            return newHead;
        }else{
            head->next=removeElements(head->next,val);
            return head;
        }
    }
};

// 2. T237.删除链表中的节点：给你一个需要删除的节点 node 。你将 无法访问 第一个节点  head。
/*链表中每个节点的值都是 唯一 的
 需要删除的节点 node 是 链表中的节点 ，且 不是末尾节点*/
class Solution_2 {
public:
    void deleteNode(ListNode* node) {
        *node=*(node->next);        // 对节点浅拷贝：直接将下一个节点，移至当前节点
    }
};

// 3. T707.设计链表
/*你可以选择使用单链表或者双链表，设计并实现自己的链表。
 单链表中的节点应该具备两个属性：val 和 next 。val 是当前节点的值，next 是指向下一个节点的指针/引用。
 如果是双向链表，则还需要属性 prev 以指示链表中的上一个节点。假设链表中的所有节点下标从 0 开始。*/

// 1. 单向链表实现：设置虚拟头节点dummy
/*时间复杂度: 涉及 index 的相关操作为 O(index), 其余为 O(1)
 空间复杂度: O(n)*/
class MyLinkedList {
public:
    struct LinkedNode{  // 单链表节点
        int val;
        LinkedNode *next;
        LinkedNode(int val):val(val),next(nullptr){}
    };
    LinkedNode *dummy;
    int size;
    
    MyLinkedList() {    // 初始化
        dummy=new LinkedNode(0);    // 虚拟头节点
        size=0;
    }
    int get(int index) {    // 获取链表中下标为 index 的节点的值。如果下标无效，则返回 -1
        if(index>size-1) return -1;
        LinkedNode *cur=dummy->next;
        for(int i=0;i<index;i++){
            cur=cur->next;
        }
        return cur->val;
    }
    void addAtHead(int val) {   // 将一个值为 val 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点
        LinkedNode *newNode=new LinkedNode(val);
        newNode->next=dummy->next;
        dummy->next=newNode;
        size++;
    }
    void addAtTail(int val) {   // 将一个值为 val 的节点追加到链表中作为链表的最后一个元素
        LinkedNode *newNode=new LinkedNode(val);
        LinkedNode *cur=dummy;
        while(cur->next!=nullptr){      // 遍历链表至尾节点
            cur=cur->next;
        }
        cur->next=newNode;
        size++;
    }
    void addAtIndex(int index, int val) {
        /*将一个值为 val 的节点插入到链表中下标为 index 的节点之前。如果 index 等于链表的长度，那么该节点会被追加到链表的末尾。如果 index 比长度更大，该节点将 不会插入 到链表中。*/
        if(index<0 || index>size) return;
        LinkedNode *newNode=new LinkedNode(val);
        LinkedNode *cur=dummy;
        for(int i=0;i<index;i++){
            cur=cur->next;
        }
        newNode->next=cur->next;
        cur->next=newNode;
        size++;
    }
    void deleteAtIndex(int index) {     // 如果下标有效，则删除链表中下标为 index 的节点
        if(index<0 || index>=size) return;
        LinkedNode *cur=dummy;
        for(int i=0;i<index;i++){
            cur=cur->next;
        }
        LinkedNode *tmp=cur->next;
        cur->next=cur->next->next;
        delete tmp;
        tmp=nullptr;    // //被delete后的指针tmp的值（地址）并非就是NULL，而是随机值。也就是被delete后，
                        //如果不再加上一句tmp=nullptr,tmp会成为乱指的野指针
        size--;
    }
};

// 4. T206.反转链表:给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
// 法一：反转指针的指向
// 时间复杂度：O(n)；空间复杂度：O(1)
class Solution_4_1 {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *cur=head,*pre=nullptr;
        while(cur!=nullptr){
            ListNode *tmp=cur->next;    // 记录原本的下一个节点（否则反转指针走向后，找不到）
            cur->next=pre;
            pre=cur;cur=tmp;
        }
        return pre;
    }
};
// 递归：反转第二个节点往后的链表（从后往前反转）
// 空间复杂度：O(n)
class Solution_4_2 {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return head;
        ListNode *last=reverseList(head->next);
        head->next->next=head;
        head->next=nullptr;
        
        return last;
    }
};

// 5. T92.反转链表II:给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
// 法一：穿针引线
// 1. 先反转[left,right]区域；
// 2. 再处理left-1和right+1处的指针指向
class Solution_5_1 {
public:
    void reverseLinkedList(ListNode *head){
        ListNode *cur=head,*pre=nullptr;
        while(cur!=nullptr){
            ListNode *tmp=cur->next;    // 记录原本的下一个节点（否则反转指针走向后，找不到）
            cur->next=pre;
            pre=cur;cur=tmp;
        }
    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *dummy=new ListNode(0);
        dummy->next=head;
        
        ListNode *pre=dummy;
        for(int i=0;i<left-1;i++){  // pre来到left-1位置的节点
            pre=pre->next;
        }
        ListNode *rightNode=pre;
        for(int i=0;i<right-left+1;i++){    // rightNode来到right位置的节点
            rightNode=rightNode->next;
        }
        ListNode *leftNode=pre->next,*succ=rightNode->next;
        
        // 反转前切断连接
        pre->next=nullptr;rightNode->next=nullptr;
        // 反转[left,right]区间的链表
        reverseLinkedList(leftNode);
        
        // 重新接回原来的链表
        pre->next=rightNode;
        leftNode->next=succ;
        
        return dummy->next;
    }
};

// 法二：一次遍历「穿针引线」反转链表
// 优化思路：在需要反转的区间里，每遍历到一个节点，让这个新节点来到反转部分的起始位置。
class Solution_5_2 {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *dummy=new ListNode(0);
        dummy->next=head;
        
        ListNode *pre=dummy;
        for(int i=0;i<left-1;i++){  // 1. pre来到left-1位置
            pre=pre->next;
        }
        ListNode *cur=pre->next;    // cur为当前遍历到的节点，它的下一个节点需要插入反转部分的起始位置
        for(int i=left;i<right;i++){   // i为cur当前所在位置
            ListNode *tmp=cur->next;    // 当前节点cur与下一个节点tmp之间断开
            cur->next=tmp->next;
            tmp->next=pre->next;
            pre->next=tmp;
        }
        return dummy->next;
    }
};

// 6. 两两交换链表中的节点:给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
class Solution_6 {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head==nullptr||head->next==nullptr) return head;
        ListNode *dummy=new ListNode(0);
        dummy->next=head;
        
        ListNode *cur=dummy;    // 当前遍历的的节点：这里作为前驱节点
        while(cur->next!=nullptr && cur->next->next!=nullptr){
            ListNode *leftNode=cur->next,*rightNode=cur->next->next;
            leftNode->next=rightNode->next;
            rightNode->next=leftNode;
            cur->next=rightNode;
            
            cur=cur->next->next;
        }
        ListNode *res=dummy->next;
        delete dummy;
        return res;
    }
};

// 7. T19.删除链表的倒数第N个节点:给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
// 要一次扫描：设置快、慢指针，快指针领先慢指针n个节点；快指针指向尾节点时，慢指针恰好指向待删除节点的前驱节点
class Solution_7 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy=new ListNode(0);
        dummy->next=head;
        ListNode *slow=dummy,*fast=dummy;
        
        while(n--&&fast->next!=nullptr){
            fast=fast->next;
        }
        while(fast->next!=nullptr){
            fast=fast->next;slow=slow->next;
        }
        slow->next=slow->next->next;
        
        return dummy->next;
    }
};

// 8. T141.环形链表:给你一个链表的头节点 head ，判断链表中是否有环。
// 法一：运用哈希表登记
// 时间复杂度：O(n)；空间复杂度：O(n)，将每个节点插入哈希表一次
class Solution_8_1 {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode *>seen;
        while(head!=nullptr){
            if(seen.count(head)) return true;
            seen.insert(head);
            head=head->next;
        }
        return false;
    }
};

// 法二：Floyd 判圈算法：
/*定义两个指针，一快一慢。慢指针每次只移动一步，而快指针每次移动两步。
 初始时，慢指针在位置 head，而快指针在位置 head.next。
 这样一来，如果在移动的过程中，快指针反过来追上慢指针，就说明该链表为环形链表；否则快指针将到达链表尾部，该链表不为环形链表。*/
/* 时间复杂度：
 1. 当链表中不存在环时，快指针将先于慢指针到达链表尾部，链表中每个节点至多被访问两次；
 2. 当链表中存在环时，每一轮移动后，快慢指针的距离将减小一。而初始距离为环的长度，因此至多移动 N 轮。
 空间复杂度：O(1)
 */
class Solution_8_2 {
public:
    bool hasCycle(ListNode *head) {
        if(head==nullptr||head->next==nullptr) return false;
        ListNode *slow=head,*fast=head->next;
        while(slow!=fast){
            if(fast==nullptr||fast->next==nullptr) return false;
            slow=slow->next;
            fast=fast->next->next;
        }
        return true;
    }
};

// 9. T142.环形链表II
/*给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
 不允许修改 链表。*/

/* 假设从头结点到环形入口节点的节点数为x; 环形入口节点到fast指针与slow指针相遇节点数为y; 从相遇节点再到环形入口节点数为z.
 有：x+n(y+z)+y=2(x+y)，即：x=n(y+z)-y=(n-1)(y+z)+z.
 从头节点/相遇节点出发，到环形入口节点的距离相同。
 */
/*时间复杂度:O(n);
    快慢指针相遇前，指针走的次数小于链表长度，快慢指针相遇后，两个index指针走的次数也小于链表长度，总体为走的次数小于 2n
 空间复杂度: O(1).
 */
class Solution_9{
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow=head,*fast=head;
        while(fast!=nullptr&&fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            
            if(slow==fast){     // 快慢指针相遇
                ListNode *node1=head,*node2=fast;
                while(node1!=node2){
                    node1=node1->next;
                    node2=node2->next;
                }
                return node1;
            }
        }
        return nullptr;
    }
};

// 10. T2.两数相加
/*给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 请你将两个数相加，并以相同形式返回一个表示和的链表。
 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。*/
// 思路：两个指针分别遍历两个链表，将当前节点相加，若有进位，到下一个节点时+1
class Solution_10 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1==nullptr&&l2==nullptr) return nullptr;
        else if(l1==nullptr) return l2;
        else if(l2==nullptr) return l1;
        ListNode *head=nullptr,*pre=nullptr;
        int carry=0;  // 记录进位
        
        while(l1!=nullptr&&l2!=nullptr){
            ListNode *newNode=new ListNode((l1->val+l2->val+carry)%10);
            carry=(l1->val+l2->val+carry)/10;
            if(head==nullptr){
                head=newNode;pre=newNode;
            }
            else{
                pre->next=newNode;pre=newNode;
            }
            l1=l1->next;l2=l2->next;
        }
        while(l1!=nullptr){
            ListNode *newNode=new ListNode((l1->val+carry)%10);
            carry=(l1->val+carry)/10;
            if(head==nullptr){
                head=newNode;pre=newNode;
            }
            else{
                pre->next=newNode;pre=newNode;
            }
            l1=l1->next;
        }
        while(l2!=nullptr){
            ListNode *newNode=new ListNode((l2->val+carry)%10);
            carry=(l2->val+carry)/10;
            if(head==nullptr){
                head=newNode;pre=newNode;
            }
            else{
                pre->next=newNode;pre=newNode;
            }
            l2=l2->next;
        }
        // 注意！如果遍历完成后，carry=1，新增一个节点
        if(carry){
            ListNode *newNode=new ListNode(carry);
            pre->next=newNode;
        }
        return head;
    }
};

// 11. T21.合并两个有序链表:将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
// l1 和 l2 均按 非递减顺序 排列
class Solution_11 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1==nullptr&&list2==nullptr) return nullptr;
        else if(list1==nullptr) return list2;
        else if(list2==nullptr) return list1;
        ListNode *head=nullptr,*cur1=list1,*cur2=list2,*pre=nullptr;
        
        while(cur1!=nullptr && cur2!=nullptr){
            if(cur1->val<=cur2->val){
                if(head==nullptr) {
                    head=cur1;
                    cur1=cur1->next;
                    head->next=nullptr;
                    pre=head;
                }
                else{
                    pre->next=cur1;
                    cur1=cur1->next;
                    pre->next->next=nullptr;    // 断开节点之后的连接
                    pre=pre->next;
                }
            }else{
                if(head==nullptr){
                    head=cur2;
                    cur2=cur2->next;
                    head->next=nullptr;
                    pre=head;
                }
                else{
                    pre->next=cur2;
                    cur2=cur2->next;
                    pre->next->next=nullptr;    // 断开节点之后的连接
                    pre=pre->next;
                }
            }
        }
        if(cur1!=nullptr) pre->next=cur1;
        if(cur2!=nullptr) pre->next=cur2;
        
        return head;
    }
};

// 12. T138.随机链表的复制
/*给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。
 构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。
 例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。
 返回复制链表的头节点。

 用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：
 val：一个表示 Node.val 的整数。
 random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
 你的代码 只 接受原链表的头节点 head 作为传入参数。*/
class Node{
public:
    int val;
    Node *next,*random;
    Node (int _val){
        val=_val;
        next=nullptr;random=nullptr;
    }
};
// 法一：回溯+哈希表
// 哈希表记录：每一个节点对应新节点的创建情况
// 时间复杂度：O(n)，对于每个节点，我们至多访问其「后继节点」和「随机指针指向的节点」各一次，均摊每个点至多被访问两次。
// 空间复杂度：O(n)，哈希表空间开销
class Solution_12_1 {
public:
    unordered_map<Node *,Node *>map;
    Node* copyRandomList(Node* head) {
        if(head==nullptr) return nullptr;
        
        if(!map.count(head)){
            Node *newHead=new Node(head->val);  // 创建新节点
            map[head]=newHead;
            newHead->next=copyRandomList(head->next);
            newHead->random=copyRandomList(head->random);
        }
        return map[head];
    }
};
// 法二：省去哈希表的开销空间：
// 对于链表 A→B→C，我们可以将其拆分为 A→A′→B→B′→C→C′
class Solution_12_2 {
public:
    unordered_map<Node *,Node *>map;
    Node* copyRandomList(Node* head) {
        if(head==nullptr) return nullptr;
        // 1. 为每个节点创建新节点，并插在原节点的下一个位置
        for(Node *cur=head;cur!=nullptr;cur=cur->next->next){
            Node *newNode=new Node(cur->val);
            newNode->next=cur->next;
            cur->next=newNode;
        }
        // 2. 设置新节点的random指针
        for(Node *cur=head;cur!=nullptr;cur=cur->next->next){
            Node *newNode=cur->next;
            if(cur->random==nullptr) newNode->random=nullptr;
            else newNode->random=cur->random->next;
        }
        // 3. 将新节点从原链表中摘除，重新设置next指针
        Node *newHead=head->next;
        for(Node *cur=head;cur!=nullptr;cur=cur->next){
            Node *newNode=cur->next;
            cur->next=cur->next->next;
            if(newNode->next!=nullptr) newNode->next=newNode->next->next;
            else newNode->next=nullptr;
        }
        return newHead;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
