/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root==NULL)
            return 0;
        if(root->left==NULL && root->right==NULL)
            return 1;
        else if(root->left==NULL)
            return minDepth(root->right)+1;
        else if(root->right==NULL)
            return minDepth(root->left)+1;

        //int left = minDepth(root->left);
        //int right = minDepth(root->right);
        //if(left==1&&right==0 || left==0&&right==1) return 2;
        else 
        return minDepth(root->left)<=minDepth(root->right) ? minDepth(root->left)+1:minDepth(root->right)+1;
    }
};
