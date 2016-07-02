class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //int nab= count(nums.begin(), nums.end(), nums[0]);
        int num;
        if (nums.size() % 2 == 0)    num = 0;
        else num = 1;
        vector<int> number(nums);
        vector<int>::iterator iter = unique(nums.begin(), nums.end());
        nums.erase(iter, nums.end());

        int  k = 0, n;
        iter = number.begin();
        //vector<int>::iterator it=nums.begin();
        while (iter != number.end())
        {
            n = count(number.begin() + k, number.end(), number[k]);
            if (n >= 2) {
                nums.insert(nums.begin() + num, number[k]);
                num++;
            }
            num++;
            k+=n;
            iter += n;
        }

        return nums.size();
    }
};
