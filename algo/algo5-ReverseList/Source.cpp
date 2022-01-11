
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* curNode = head;
        ListNode* prevNode = nullptr;
        while (curNode != nullptr)
        {
            auto nextNode = curNode->next;
            if (nextNode == nullptr) 
            {
                curNode->next = prevNode;
                return curNode;
            }
            
            auto tmp = nextNode->next;
            nextNode->next = curNode;   
            curNode->next = prevNode;    

            prevNode = nextNode;

            curNode = tmp;
        }
        return prevNode;
    }
};