// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

/*
My test
8 9 0 1 3 4 5 6 7 

3 4 5 6 7 8 9 0 1

6 7 8 9 0 1 3 4 5
*/

class Solution {
public:
    int findMin(vector<int>& nums) {

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
        return nums[center];

    }
};