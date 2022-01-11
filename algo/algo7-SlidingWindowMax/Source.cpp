// https://leetcode.com/problems/sliding-window-maximum/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        std::vector<int> answer;        
        std::deque<int> max;

        for (int i=0; i<nums.size(); ++i) 
        {
            // index max elem in window [i, i + k]
            if (max.size() > 0 && max.front() <= i-k)
                max.pop_front();
            // pop elems which less than next
            while (max.size()>0 && nums[i]>=nums[max.back()])
                max.pop_back();
            // save index next elem
            max.push_back(i);
            if (i >= k-1)
                answer.push_back(nums[max.front()]);
        }
        return answer;
    }
};