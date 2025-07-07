class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.empty()) {
            return 0;
        }
        int result = nums.size();
        for (int i = nums.size() - 1; i >= 0; --i) {
            int& n1 = nums[i];
            if (n1 == val) {
                if (i < result - 1) {
                    int& n2 = nums[result - 1];
                    const int tmp = n2;
                    n2 = n1;
                    n1 = tmp;
                }
                --result;
            }
        }
        return result;
    }
};
