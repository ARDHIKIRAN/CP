/*************************Graph Representation*************************************/

/* 
       1.Adjaceny matrix (V * E)
       2.Adjaceny list (V + E)
    
    indegree -> nnumber of incoming edges
    outdegree -> number of outgoing edges
    Degree -> indegree + outdegree
     
    1.Centre of Graph -> the node which have indegree/outdegree is (N- 1)
    
    2.Minimum Degree of a Connected Trio in a Graph  
      Degree = umber of edges where one endpoint is in the trio, and the other is not
        Observations : 
                1.(u,v,w) -> if these are making Trio , then degree will be (degree[u] + degree[v] + degree[w] - 6) 

                2.how we will confirm (u , v , w) is trio ? 
                        u -> (v,w)
                        v -> (u,w)
                        w -> (u,v)
                    then we should use adjacency matrix to confirm this.
                         If adj[u][v] == 1 and adj[u][w] == 1 and adj[v][w] == 1 then (u,v,w) is a trio.


*/


/*************************BFS*************************************/

/* 
    Problem 1.Snake and Ladder Problem
        Observation : 
            1. we need to find the shortest path from 1 to (n * n) , as each jump contribute 1 -> we can use BFS
            2.we have dice -> choice = {1,2,3,4,5,6}
            3.we have to jump array which will have the jump from i to jump[i] using ladder or snake

        q.push(1);
        dist[1] = 0;
        while(!q.empty()){
            auto node = q.front();
            q.pop();

            if(node == n * n) return dist[node];

            for(int dice = 1;dice <= 6 ; ++dice){
                int next = node + dice;
                if(next > (n * n)) continue;
                if(jump[next] != -1){
                    next = jump[next];
                }
                if(dist[next] == -1){
                    dist[next] = 1 + dist[node]};
                    q.push(next);
                }   
        }
        return -1; // cannot reach to destination 

       
        Problem 2.Message Route : you need to find the shortest path from 1 to n 

        queue<int> q;
    q.push(1);
    vis[1] = 1;
    dist[1] = 0;
    par[0] = -1;
    
    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(auto nbr:adj[node]){
            if(vis[nbr] == 0){
                q.push(nbr);
                dist[nbr] = 1 + dist[node];
                vis[nbr] = 1;
                par[nbr] = node; 
            }
        }
    }
    
    if(dist[n] == INT_MAX){
        cout << "IMPOSSIBLE" << endl;
    }else{
        vector<int> ans;
        cout << dist[n] + 1 << endl;
        int temp = n;
        while(temp != 1){
            ans.push_back(temp);
            temp = par[temp];
        }
        ans.push_back(1);
        
        for(int i = ans.size() - 1 ; i>= 0 ;i--){
            cout << ans[i] << " ";
        }
    }


    Problem 3 : word ladder 
        Observation : 
            1. we need to find the shortest path from beginWord to endWord , as each jump contribute 1 -> we can use BFS
            2. we have to change the word to another word in the list
            3. we can change only one character at a time
        

        int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<pair<string,int>> q;
        q.push({beginWord , 0});
        unordered_map<string,int> mp;
        for(auto word : wordList){
            mp[word]++;
        }
        int k = beginWord.size();

        while(!q.empty()){
            auto [word,jump] = q.front();
            q.pop();

            if(word == endWord){
                return jump + 1;
            }

             for(int i = 0 ; i < k ; ++i){
                for(char ch = 'a' ; ch <= 'z' ; ch++){
                    if(word[i] == ch) continue;
                    string temp = word;
                    temp[i] = ch;
                    if(mp.count(temp) > 0 && mp[temp] > 0){
                        q.push({temp, jump + 1});
                        mp[temp]--;
                    }
                }
             }
        }
        return 0;
    }


    Problem 4: Valid BFS ? 
    
    Questions : 
        1. we have to check whether the given traversal is valid BFS or not ?
        2. if the given traversal is valid BFS then print "YES" otherwise print "NO"
        3. 1 based indexing is used
        4. we have to check the given traversal is valid BFS for the tree or not ?
        5. N <= 2 * 10^5
    To check if a BFS traversal is valid, we need to ensure that:
    Sorting adjacency lists ensures : The nodes in each level are visited in the same order as ans expects.

    Code : 
       #include<bits/stdc++.h>
       using namespace std;
       const int N = 200007;
       int relorder[N];
       bool cmp(int a,int b){
	       return relorder[a]<relorder[b];
       }
    int main(){
      int n;
      cin >> n;
      vector<int> adj[n+1];
      for(int i = 0 ; i < n - 1 ; ++i){
          int u,v;
          cin >> u >> v;
          adj[u].push_back(v);
          adj[v].push_back(u);
      }
      vector<int> ans(n);
      for(int i = 0 ; i < n ; i++){
         cin >> ans[i];
      }
      for(int i=0;i<n;i++){
	    relorder[ans[i]]=i;
	 }	
	 for(int i=1;i<=n;i++){
	 	sort(adj[i].begin(),adj[i].end(),cmp);
	 }
     vector<int> vis(n + 1,0);
     vector<int> val;
     queue<int> q;
     q.push(1);
     vis[1] = 1;
     while(!q.empty()){
         auto node = q.front();
         q.pop();
         val.push_back(node);
         for(auto nbr:adj[node]){
             if(!vis[nbr]){
                 q.push(nbr);
                 vis[nbr] = 1;
             }
         }
     }
     for(int i = 0 ; i < val.size() ; ++i){
         if(ans[i] != val[i]){
             cout << "NO";
             return 0;
         }
     }
     cout << "YES\n";
   }
*/



/*************************DFS*************************************/

/*
    
    Problem 1 : Krys and rooms 
        -> If You can visit all the rooms or not ? -> do dfs on 0 -> if all rooms are visited -> then return true , else return false


    Problem 2 : Max Area of Island
        -> you have to find the maximum area of island
        -> do dfs on each cell and find the maximum area of island

    Code : 

        int dx[4] = {0,0,1,-1};
        int dy[4] = {1,-1,0,0};
        int dfs(int i,int j,vector<vector<int>> &vis , vector<vector<int>>& grid ,int row, int col ){
            vis[i][j] = 1;
        
            int ans = 1;
            for(int ind = 0 ; ind < 4 ; ind++){
                int x = i + dx[ind];
                int y = j + dy[ind];
                if(x >= 0 && x < row && y >= 0 && y < col && grid[x][y] == 1 && vis[x][y] == 0){
                     ans += dfs(x,y,vis,grid,row,col);
                }
            }
            return ans;
        }
        int maxAreaOfIsland(vector<vector<int>>& grid) {
            int row = grid.size();
            int col = grid[0].size();
            vector<vector<int>> vis(row,vector<int>(col,0));
            int ans = 0;
            for(int i = 0 ; i < row ; ++i){
                for(int j = 0; j < col ; ++j){
                    if(grid[i][j] == 1 && vis[i][j] == 0){
                         ans = max(ans , dfs(i , j , vis , grid , row, col) );
                    }
                }
            }
            return ans;
        }
*/


/*********************Cycle Detection************/

/*
    Course Schedule : 
        you have to find whether the given graph is DAG or not ?
        if it is DAG then return true , otherwise return false

    Observation : 
        1. if the graph is DAG then there will be no cycle in the graph
        2. if the graph is not DAG then there will be cycle in the graph

    Code : 
    bool dfs(int node,vector<int> &visited,vector<int> adj[]){
       visited[node] = 2;

       for(auto nbr:adj[node]){
            if(visited[nbr] == 2){
                return true;
            }
            else if(visited[nbr] == 0){
                if(dfs(nbr , visited, adj)){
                  return true;
                }
            }
       }
       visited[node] = 1;
       return false;
   }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];

        for(auto edge : prerequisites){
            adj[edge[0]].push_back(edge[1]);
        }

        vector<int> visited(numCourses , 0);
        for(int i = 0 ; i < numCourses ; ++i){
            if(visited[i] == 0){
                if(dfs(i , visited , adj)){
                    return false;
                }
            }
        }
        return true;
    }

*/


/*
    
    Pronlem :  Is Graph Bipartite?
        Observation : 
            1. if the graph is bipartite then there will be no cycle of odd length
            2. if the graph is not bipartite then there will be cycle of odd length

        Code : 
           bool dfs(int node,int par , int col , vector<int> &color , vector<int> adj[]){
       color[node] = col;

       for(auto nbr:adj[node]){
          if(color[nbr] == 0){
               if(dfs(nbr , node, 3-col , color , adj)){
                  return true;
               }
          }else if( nbr != par && color[nbr] == color[node]){
               return true;
          }
       }
       return false;
   }
    bool isBipartite(vector<vector<int>>& graph) {
        int numVertex = graph.size();
        vector<int> adj[numVertex];

        for(int i = 0 ; i < numVertex ; ++i){
            for(auto edge : graph[i]){
                adj[i].push_back(edge);
            }
        }

        vector<int> color(numVertex , 0);
        for(int i = 0 ; i < numVertex ; ++i){
            if(color[i] == 0){
                if(dfs(i ,-1 , 1 , color , adj)){
                    return false;
                }
            }
        }
        return true;
    }

*/

/*
    Problem : Detect Cycles in 2D Grid 

     Same as cycle detction in adjacency matric graph
     Code : 

    int dx[4] = {0 , 0 , 1 , -1};
    int dy[4] = {1 , -1 , 0 , 0};
    bool dfs(int i,int j,int par_i,int par_j,vector<vector<int>> &vis,vector<vector<char>> &grid){
       vis[i][j] = 1;
       int n = grid.size();
       int m = grid[0].size();

       for(int dir = 0 ; dir < 4 ; dir++){
          int x = i + dx[dir];
          int y = j + dy[dir];

        if(x >= 0 && x < n && y>=0 && y < m && vis[x][y] == 0 && grid[x][y] == grid[i][j]){
              if(dfs(x,y,i,j ,vis , grid)){
                  return true;
          }
          }else if( x >= 0 && x < n && y>=0 && y < m && !(x == par_i && y == par_j) && vis[x][y] == 1 && grid[x][y] == grid[i][j] ){
               return true;
          }
       }
       return false;
    }
    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis( n , vector<int>( m , 0 ));
        for(int i = 0 ; i < n ; ++i){
            for(int j = 0 ; j < m ; ++j){
                if(vis[i][j] == 0){
                    if(dfs(i , j , -1 ,-1 ,vis , grid)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
*/


/*
    Problem :  Shortest Cycle in a Graph 
       Observation : 
           1.Build an adjacency list from the input edge list.
           2.For every unvisited node, run a BFS:
               *Track distances from the source.
               *(If during traversal you revisit a node that’s not your direct parent, update the cycle length.
           3.Track the minimum cycle length over all BFS runs.
           4.Return -1 if no cycles were found.


        Code : 
            int bfs(int node,vector<int> &vis,vector<int> adj[]){
        vector<int> dist(vis.size() , -1);
        queue<pair<int,int>> q;
        q.push({node,-1});
        dist[node] = 0;
        int ans = INT_MAX;
        while(!q.empty()){
            auto node = q.front();
            q.pop();
            for(auto nbr:adj[node.first]){
                if(dist[nbr] == -1){
                    q.push( {nbr,node.first} );
                    dist[nbr] = 1 + dist[node.first];
                }else if(nbr != node.second){
                    ans = min(ans , dist[nbr] + dist[node.first] + 1);
                }
            }
        }
        return ans;
    }
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<int> adj[n];
        for(auto edge : edges){
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        vector<int> vis( n , 0);
        int ans = INT_MAX;
        for(int i = 0 ; i < n ; i++){
            ans = min(ans , bfs( i , vis, adj));
        }
        if(ans == INT_MAX) return -1;
        return ans;
    }   
*/


/*************************DAG******************************/


/*
     Problem : All Paths From Source to Target
       Observarion : 
           1.Backtracking , as it is DAG graph so there will be no cycle
           2. if we reach to the destination then push the path into the result vector
*/


/*
    Problem : Course Schedule II

    Observation : Topological sort ordering (cycle should not be there)
    Code : 
         bool  dfs(int node,vector<int> &vis,vector<int> adj[] , vector<int> & order){
        vis[node] = 2;

        for(auto nbr:adj[node]){
            if(vis[nbr] == 0){
                if ( dfs(nbr , vis , adj, order) ) {
                    return true;
                }
            }else if(vis[nbr] == 2){
                return true;
            }
        }
         vis[node] = 1;
        order.push_back(node);
        return false;
   }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> order;
        vector<int> vis(numCourses , 0);
        vector<int> adj[numCourses];
        for(auto edge : prerequisites){
            adj[edge[1]].push_back(edge[0]);
        }

        for(int i = 0 ; i < numCourses ; ++i){
            if(vis[i] == 0){
                bool ok = dfs(i , vis , adj, order);
                if(ok) return {};
             }
        }
        reverse(order.begin() , order.end());
        return order;
    }
*/


/*
      Problem :  Largest Color Value in a Directed Graph
         Observation : 
                1. if cycle is there then return -1 (should be DAG)

                2.for each node , we will have an array of size 26  -> which will store the maximum color value from the node to the leaf node

                cnt[cur][i] = cnt[nbr][i] + (i == color[cur] - 'a'); -> over all character we will find the max same value node from curr to leaf node 

                3. if the graph is DAG then return the maximum color value from the source to the destination

                Code : 
                    bool dfs(int node,string &colors , vector<int> &vis,vector<int> adj[] , vector<vector<int>> &cnt){
        vis[node] = 2;
        for(auto nbr:adj[node]){
            if(vis[nbr] == 2){
                return true;
            }
            else if(vis[nbr] == 0){
                if(dfs(nbr , colors ,  vis , adj , cnt)){
                    return true;
                }
            }
            for(int i = 0 ; i < 26 ; i++){
                cnt[node][i] = max(cnt[node][i] , cnt[nbr][i]);
            }
        }
        cnt[node][colors[node] - 'a']++;
        vis[node] = 1;
        return false;
    }
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int size = colors.size();
        vector<int> adj[size];

        for(auto edge : edges){
            adj[edge[0]].push_back(edge[1]);
        }

        vector<int> vis(size , 0);
        vector<vector<int>> cnt(size , vector<int>(26,0));
        
        for(int i = 0 ; i < size ; ++i){
            if(vis[i] == 0){
                if(dfs(i , colors , vis , adj , cnt)){
                    return -1;
                }
            }
        }
        int ans = 0;
        for(int i = 0 ; i < size ; i++){
             for(int j = 0 ; j < 26 ; j++){
                     ans = max(ans , cnt[i][j]);
                }
        }
        return ans;
    }
*/


/*
    Problem : Game Routes 
       A game has n levels, connected by m teleporters, and your task is to get from level 1 to level n. 
       The game has been designed so that there are no directed cycles in the underlying graph. In how many 
       ways can you complete the game?
    
    Observation : 
        1. if the graph is DAG then return the number of ways from source to destination
        2. if the graph is not DAG then return 0

    //state     
    dp[node] = no of ways from source to n 
    //transaction 
    dp[node] += dp[nbr] for all nbr of node


    Code : 
       int dfs(int node,vector<int> &dp,vector<int> adj[]){
     if(node == n) {
        return 1;
     }
     if(dp[node] != -1){
       return dp[node];
     }
    
    int ways = 0;
    for(auto nbr : adj[node]){
       ways += dfs(nbr ,dp, adj);
       ways %= mod;
    }
      return dp[node] = ways % mod;
    }

   ans is dfs(1, dp, adj);
*/
