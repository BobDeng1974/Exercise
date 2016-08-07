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
    ListNode* rotateRight(ListNode* head, int k) {
        if(k==0 || head==NULL) return head;
        
        int length=1;
        ListNode *temp;
        //length++;
        for(temp=head;temp->next!=NULL;temp=temp->next)
            length++;
        
        if(k==length) return head;
        else if(k>length) k=k%length;
        if(k==0) return head;
        
        temp=head;
        for(int i=1;i<length-k;i++)
            temp=temp->next;
        ListNode *newhead=temp->next;
        temp->next=NULL;
        temp=newhead;
        
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=head;
        
        return newhead;
/*           
        ListNode *newnext=temp->next;
        temp->next=head;
        
        while(newnext!=NULL) {
            temp->next=newnext;
            temp=newnext;
            newnext=newnext->next;
        }
*/
    }
};
