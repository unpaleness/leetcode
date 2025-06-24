#include <cstdint>

struct ListNode {
    int32_t val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int32_t x) : val(x), next(nullptr) {}
    ListNode(int32_t x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    static ListNode* removeNthFromEnd(ListNode* head, const int32_t n) {
        if (!head) {
            return nullptr;
        }
        ListNode* prev = head;
        int32_t delay = 0;
        ListNode* it = head;
        while (it->next) {
            if (delay >= n) {
                prev = prev->next;
            }
            ++delay;
            it = it->next;
        }
        if (delay == n - 1) {
            return head->next;
        }
        if (delay < n) {
            return head;
        }
        prev->next = prev->next->next;
        return head;
    }
};