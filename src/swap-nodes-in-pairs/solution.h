/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* it = head;
        ListNode* prev = nullptr;
        ListNode* result = it && it->next ? it->next : it;
        while (it) {
            if (it->next) {
                if (prev) {
                    prev->next = it->next;
                }
                ListNode* nextNext = it->next->next;
                it->next->next = it;
                it->next = nextNext;
            }
            prev = it;
            it = it->next;
        }
        return result;
    }
};
