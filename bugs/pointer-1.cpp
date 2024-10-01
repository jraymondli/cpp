// This code has one pointer use bug.
// Please find it out.
// Specifically, here is the error message
// AddressSanitizer: heap-use-after-free on address 0x51500000617c at pc 0x5654d4ea336a bp 0x7fff07bb0af0 sp 0x7fff07bb0ae8

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

class Solution {
    unordered_map<int, vector<int>> keys;
    unordered_set<int> visited;
    queue<int> dq;

public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int nRooms = rooms.size();
        for (int i =0; i < nRooms; i++) {
            keys[i] = rooms[i];
        }
        dq.push(0);
        while (dq.size() > 0 ) {
            auto& curr_rm = dq.front();
            visited.insert(curr_rm);
            dq.pop();
            for (auto& nxt : keys[curr_rm]) {
                if (visited.find(nxt) == visited.end()) dq.push(nxt);
            }
        }
        return visited.size() == nRooms;
    }
};

// ANSWER
// line 24
/*
The heap-use-after-free error in your C++ code might be caused by the line auto& curr_rm = dq.front();. This line uses a reference to an element in the queue (dq), and the problem is that you're modifying the queue (via dq.pop()) while still holding a reference to an element that has been removed.

When you call dq.pop(), it invalidates the reference to dq.front(). After pop, accessing curr_rm would result in undefined behavior, which can cause the AddressSanitizer error you're seeing.

*/


