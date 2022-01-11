// https://leetcode.com/problems/single-number/
// The trick is: A^B^A=B

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (const int& num : nums) {
            result ^= num;
        }
        return result;
    }
};