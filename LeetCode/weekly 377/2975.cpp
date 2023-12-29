class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        unordered_set<int> seen;
        sort(begin(hFences), end(hFences));
        sort(begin(vFences), end(vFences));
        
        hFences.push_back(m);
        for(int r = 0; r < hFences.size(); r++) seen.insert(hFences[r] - 1);
        for(int l = 0; l < hFences.size(); l++) for(int r = l + 1; r < hFences.size(); r++) seen.insert(hFences[r] - hFences[l]);
        
        
        long long MAX = -1;
        vFences.push_back(n);
        for(int r = 0; r < vFences.size(); r++) if(seen.find((long long)vFences[r] - 1) != seen.end()) MAX = max(MAX, (long long)vFences[r] - 1);
        for(int l = 0; l < vFences.size(); l++) for(int r = l + 1; r < vFences.size(); r++) if(seen.find((long long)vFences[r] - (long long)vFences[l]) != seen.end()) MAX = max(MAX, (long long)vFences[r] - (long long)vFences[l]);
        
        if(MAX == -1) return -1;
        else return ((long long) MAX * MAX) % 1000000007;
    }
};
