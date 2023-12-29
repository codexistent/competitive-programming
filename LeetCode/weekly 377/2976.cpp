class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        long long frcost[26][26];
        for(int i = 0; i < 26; i++) for(int j = 0; j < 26; j++) frcost[i][j] = INT_MAX;
        for(int i = 0; i < 26; i++) frcost[i][i] = 0;
        int N = original.size();
        for(int i = 0; i < N; i++) frcost[original[i] - 'a'][changed[i] - 'a'] = min(frcost[original[i] - 'a'][changed[i] - 'a'], (long long)cost[i]);
                                
        for(int k = 0; k < 26; k++){ 
            for(int i = 0; i < 26; i++){
                for(int j = 0; j < 26; j++){
                    frcost[i][j] = min(frcost[i][j], frcost[i][k] + frcost[k][j]);
                }
            }
        }
                                                                                                               
        long long r = 0;
        for(int i = 0; i < source.length(); i++){
            r += frcost[source[i] - 'a'][target[i] - 'a'];
            if(frcost[source[i] - 'a'][target[i] - 'a'] == INT_MAX) return -1;
        }
        return r;
    }
};
