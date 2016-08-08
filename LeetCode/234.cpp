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
    bool isPalindrome(ListNode* head) {
        if(head==NULL) return true;
        
        ListNode *temp=head;
        int length=1;
        for(;temp->next!=NULL;temp=temp->next)
            length++;
        
        int middle;    
        if(length==1) return true;
        if(length%2==0) middle=length/2;
        else middle=(length-1)/2;
        
        stack<int> st;
        temp=head;
        for(int i=1;i<=middle;temp=temp->next,i++)
            st.push(temp->val);
        
        queue<int> que;
        if(length%2!=0)
            temp=temp->next;
        for(int i=1;i<=middle;i++,temp=temp->next)
            que.push(temp->val);
            
        for(int i=1;i<=middle;i++)  {
            if(que.front()!=st.top())
                return false;
            que.pop();
            st.pop();
        }

        return true;

/*
        temp=head;
        for(int i=1;i<=length-middle;i++,temp=temp->next)   ;
        
        ListNode *temp2=head;
        long long sum1=0,sum2=0;
        for(int i=1;i<=middle;i++,temp=temp->next,temp2=temp2->next) {
            sum1+=temp->val;
            sum2+=temp2->val;
        }
        
        if(sum1==sum2) return true;
        else return false;
*/
    }
};
