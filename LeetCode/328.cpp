/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head==NULL || head->next==NULL) return head;
        ListNode* oddhead,*odd,*evenhead,*even;
        oddhead=odd=head;
        evenhead=even=head->next;

        while(even->next!=NULL && even->next->next!=NULL) {
            odd->next=even->next;
            odd=odd->next;
            even->next=odd->next;
            even=even->next;
        }
        
        if(even->next!=NULL) {
            odd->next=even->next;
            odd=odd->next;
        }
        
        odd->next=evenhead;
        even->next=NULL;
        
        return oddhead;
    }
};
