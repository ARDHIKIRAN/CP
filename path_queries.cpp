
// Problem Link : https://codeforces.com/contest/1213/problem/G

// Topic : DSU + sorting + trees

#include<bits/stdc++.h>
using namespace std;
#define int long long int 
vector<int> par , sz;
int cnt;
void init(int n){
    par.resize(n);
    iota(par.begin() , par.end() , 0);
    sz.resize(n , 1);
}
int find(int node){
    if(par[node] == node) return node;
    return par[node] = find(par[node]);
}
void Union(int x,int y){
    x = find(x);
    y = find(y);
    if(x == y){
        return;
    }
    if(sz[x] < sz[y]) swap(x , y);
    par[y] = x;
    cnt -= (sz[y] * (sz[y] - 1))/2;
    cnt -= (sz[x] * (sz[x] - 1))/2;
    sz[x] += sz[y];
    cnt += (sz[x] * (sz[x] - 1))/2;
    // cout << "ki " << cnt << endl;
}
int32_t main(){
    int n , x , y , wt , q;
    cin >> n >> q;
    init(n + 1);
    vector<vector<int>> edges;
    for(int i = 0 ; i < n - 1 ; ++i){
        cin >> x >> y >> wt;
        edges.push_back({wt , x, y});
    }
    vector<pair<int,int>> queries(q);
    
    for(int i = 0 ; i < q ; ++i){
        cin >> queries[i].first;
        queries[i].second = i;
    }
    
    
    sort(edges.begin() , edges.end());
    sort(queries.begin() , queries.end());
    
    vector<int> ans(q , 0);
    cnt = 0;
    int i = 0;
    for(auto query : queries){
        int val = query.first;
        
        while(i < n-1 && edges[i][0] <= val){
            Union(edges[i][1] , edges[i][2]);
            // cout << "kiran" << endl;
            ++i;
        }
        ans[query.second] = cnt;
    }
    
    for(auto it:ans){
      cout << it << " ";
    }
    
    
    
}
