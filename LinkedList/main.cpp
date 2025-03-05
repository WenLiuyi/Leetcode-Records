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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
