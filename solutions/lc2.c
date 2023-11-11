/**
 * 2 add-two-numbers
 * medium
 * 
 * single-linked-list
*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};
//

struct ListNode *newNode(int val) {
    struct ListNode *newNode = (struct ListNode*) malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode dummy = {.next = NULL}, *p = &dummy;

    int carry = 0;
    while (l1 || l2) {
        int v1 = l1 ? l1->val : 0;
        int v2 = l2 ? l2->val : 0;
        int sum = v1 + v2 + carry;
        carry = sum / 10;
        p->next = newNode(sum % 10);
        p = p->next;
        if (l1) {
            l1 = l1->next;
        }
        if (l2) {
            l2 = l2->next;
        }
    }
    if (carry == 1) {
        p->next = newNode(1);
        p = p->next;
    }
    return dummy.next;
}
