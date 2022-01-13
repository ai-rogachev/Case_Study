// https://leetcode.com/problems/search-in-rotated-sorted-array/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        int shift = getShift(nums);
        
        int begin = 0;
        int end = nums.size() - 1;

        while (end >= begin) {
            int center = begin + (end - begin) / 2;
            int shiftCnt = (center + shift) % nums.size();

            if (nums[shiftCnt] == target)
                return shiftCnt;
            else if (target > nums[shiftCnt]) 
                begin = center + 1;
            else
                end = center - 1;
        }
        return -1; 
    }

    int getShift(const vector<int>& nums)
    {
        int begin = 0;
        int end = nums.size() - 1;
        int center = 0;
        while (begin <= end) 
        {
            center = begin + (end - begin) / 2;
            
            if (nums[center] >= nums[end])
                begin = center + 1;
            else
                end = center;
        }
        return center;
    }
};