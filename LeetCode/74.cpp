class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
	int n = 1;
	int flag = 0;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++,n++) {
			if (matrix[i][j] == target) {
				flag = 1;
				break;
			}
			if (flag == 1) break;
		}
	}

    if(flag==1) return true;
    else return false;
    }
};
