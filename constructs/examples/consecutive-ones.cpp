#include <utility>
#include <vector>
#include <algorithm>

class Solution {
    vector<pair<int, int>> getSegments(vector<int>& nums) {
        vector<pair<int, int>> segs;
        bool wait_start = true;
        int s_start = 0, s_end;
        for (int i = 0; i < size(nums); i++) {
            if (wait_start && nums[i] == 1) {
                s_start = i;
                wait_start = false;
            }
            if (! wait_start && nums[i] == 0) {
                s_end = i;
                segs.push_back(make_pair(s_start, s_end));
                wait_start = true;
            }
        }
        if (!wait_start) {
            segs.push_back(make_pair(s_start, size(nums)));
        }
        return segs;
    }
public:
    int longestOnes(vector<int>& nums, int k) {
        const auto& segs = getSegments(nums);

        int nSegs = size(segs);
        int nNums = size(nums);
        int maxOnes = min(nNums, k);

       
        for (int i = 0; i < nSegs; i++) {
            int kRemaining = k;
            bool breakInMiddle = false;
            for (int j=i+1; j < nSegs; j++) {
                if ((segs[j].first - segs[j-1].second) <= kRemaining) {
                    kRemaining -= (segs[j].first - segs[j-1].second);
                    continue;
                }
                maxOnes = max(maxOnes, segs[j-1].second - segs[i].first + kRemaining);
                breakInMiddle = true;
                break;
            }
            if (!breakInMiddle) {
                int border = nNums - segs[nSegs-1].second;
                if (i == 0) border += segs[0].first;
                else border += (segs[i].first - segs[i-1].second);
                maxOnes = max(maxOnes, segs[nSegs-1].second - segs[i].first + min(border, kRemaining));
            }
        }
        return maxOnes;
    }
};
