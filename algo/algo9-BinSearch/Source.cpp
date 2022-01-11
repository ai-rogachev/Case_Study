// https://leetcode.com/problems/binary-search/

class Solution {
public:
    int search(vector<int>& nums, int target) {

        int begin = 0;
        int end = nums.size() - 1;
        while (end >= begin) {
            int center = begin + (end - begin) / 2;

            if (nums[center] == target)
                return center;
            else if (target > nums[center]) 
                begin = center + 1;
            else
                end = center - 1;
        }
        return -1; 

    }
};