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
    int getCount(ListNode* head) {
        int count = 0;
        auto& curr = head;
        while (curr != nullptr) {
            count += 1;
            curr = curr->next;
        }
        return count;
    }
public:
    ListNode* deleteMiddle(ListNode* head) {
        auto nNodes = getCount(head);

        if (nNodes < 2) return nullptr; 

        auto prev = head;
        auto curr = head->next;
        int idx = 1;
        while (curr != nullptr) {
            if (idx == int(nNodes/2)) {
                prev->next = curr->next;
                return head;
            }
            prev = curr;
            curr = curr->next;
            idx += 1;
        }
        return nullptr;
    }
};
