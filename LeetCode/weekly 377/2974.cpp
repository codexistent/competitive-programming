class Solution {
public:
    vector<int> numberGame(vector<int>& nums) {
        int N = nums.size();
        sort(begin(nums), end(nums));
                
        for(int i = 0; i <= N / 2 - 1; i++){
            int a = nums[2*i];
            nums[2*i] = nums[2*i + 1];
            nums[2*i + 1] = a;
        }
        
        return nums;
    }
};
