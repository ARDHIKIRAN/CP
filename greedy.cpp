
/*
     Given an array of water levels, find the maximum amount of water that can be trapped between any two levels of the array. 
     Optimal Solution : 
          take two pointer left , right and move the pointer which will make the water area maximum that current area 
           
          Area  = min(h[left],h[right]) * (right - left)
          -> so it is optimal to move the pointer which will increase the minimum height 
            move the pointer which is minimum in both the heights pointing to left and right 


        Time Complexity : O(n)
        Space Complexity : O(1)
       
        while(i<j){
            int ht = min(height[i],height[j]);
            int wd = j-i;
            water = max(water,ht*wd);
            
            if(height[i] < height[j]) i++;
            else j--;
        }
 */


 /*
     Given an string s and p  
        Operations : 
            1. '?' -> single character matched 
            2.'*' -> empty or any sequence of characters matched
    
    return true if the string s matches the pattern p

     Dp solution : 
        dp[i][j] -> true if s[0...i] matches p[0...j]
        dp[i][j] = dp[i-1][j-1] if s[i] == p[j] || p[j] == '?'
        dp[i][j] = dp[i-1][j] || dp[i][j-1] if p[j] == '*'
        
        Time Complexity : O(n*m)
        Space Complexity : O(n*m)

     Optimal solution (Greedy Solution) :

           1. if charaacter macthed  or '? -> then we can move the pointer of both the string 

           2.if '*' -> 
                then we will store the pos of '*' in p and corresponding index of s
            
             3.if not macthed , then we can backtrack the pointer of s to the last '*' and move the pointer of p to the next of '*' 
            
             4.if we can't backtrack then return false


        Time Complexity : O(n + m)
        Space Complexity : O(1)
*/


/*
      
   Jump Game II (min jumps to reach to the end) each value on the array is the maximum jump that can be made from that index
    
    DP solution : 
        TC : O(N * max(arr[i]))
        SC : O(N)

    Greedy Solution : 

        initialize , we at pos = 0 ,jumps = 0 , l = 0 , r = 0

        Range wise traversal 
           1.we will find the farthest jump we can do from the current range  and increase the jump by 1 
           2.till we hit the the tange , where n-1 idnex is there 
            
           jump = 0 
           l = 0 
           r = 0 
           while(r < size - 1){  
                int farthest = 0;
                for(int k = l;k<=r;k++){
                     farthest = max(farthest,k + arr[k]);
                }
                l = r + 1;
                r = farthest;
                jump++;
           }
        // jump is the final answer -> as it is guranteed that we can reach to the end

        TC : O(N)
        SC : O(1)
*/


/*
    Jump Game : 
     Given an array of intergers , where each value represent the maximum jump that can be made from that index.
     you need to find the whether you can reach to the end of the array or not ? 

     DP solution : 
        TC : O(N * max(arr[i]))
        SC : O(N)

    greedy Solution : 
        1.we will maintain the maxIndex that can be reached from the current index.
        2.if any current index is greater than the maxIndex -> which you cannot reach that index by someone.-> return false 
        3.else return true
        
        int maxIndex = 0;
        for(int i = 0 ; i < nums.size() ; ++i){
            if(i > maxIndex) return false;
            maxIndex = max(maxIndex, i + nums[i]);
        }
        return true;
*/



/*
    Best Time to Buy and Sell Stock II
    get the max. profit by buy and sell the stocks multiple times
    after buying one stock , you need to sell it before buying another stock


    Greedy Solution : 
        1.buy at local minima and sell it local maxima 
       
        Trick : 
            to get the differncece local maxima and local minima  = sum of all the difference of the adjaceny elements (cond : arr[j] >= arr[j-1]) 

        int profit = 0;
        for(int i = 1 ; i < prices.size() ; ++i){
            if(prices[i] > prices[i-1]) {
                profit += prices[i] - prices[i-1];
            }
        }

        TC : O(N)
        SC : O(1)
*/



/*
    Gas Station 
    given an gas and cost at each station , to go to next station you need cost[i] gas to move to (i + 1)th station
    you have gas[i] gas at ith station 
    you need to find the starting station from where you can complete the circle.
    initially you have 0 gas in your car.
    
    

    Greedy Solution : -> YOU SHOULD KNOW THIS SOLUTION BEFOREHAND

           totalgas < totalcost -> return -1 
           else{
                it is guarantee that there is a unique solution exists.


                we will see each one as polential answer and go move ahead  , if not possible then we will eleminate the that start station  
                and make the next station as the start station(by by eliminating the wrong station we will get the start station)


                int currGas = 0;
                int startIndex = 0;
                int totalGas = 0 , totalCost = 0;
                for(int i = 0 ; i < gas.size() ; ++i){
                    currGas += (gas[i] - cost[i]);
                    totalGas += gas[i];
                    totalCost += cost[i];

                    if(currGas < 0){
                         currGas = 0;
                         startIndex = i + 1;
                    }
                }
                if(totalGas < totalCost) return -1;
                return startIndex;

                TC: O(N)
                SC : O(1)
        }

*/



/*
     Candy 
     given an array of ratings of the students , you need to distribute the candies to the students such that 
     1. each student should get atleast one candy
     2. if a student has higher rating than his neighbour then he should get more candies than his neighbour
    
     Greedy Solution : 
        1.we will traverse the array one by one  
           1.1.if curr and prev rating is same , then we will give candy to the current student as 1 
           1.2. (as increasing th rating from the current students)
                ex :           [1,3,4,5,7,8,9,3...]
                disribution : [1,2,3,4,5,6,7,1...]
            1.3.same for decreasing also 
                ex : [6,4,2,1,8,...]
                distribution : [5,3,2,1,2,...]
        
        2.Subtract overlap at the peak 

        increasing ......peak ......decreasing 
        ex : [1,2,3,4,57,5,3,2,1]
        distrubution -> [1,2,3,4,5,1,2,3,4]  -> but  in our second while loop ans += (...5,4,3,2,1) -> we are couting 5 extra to avoid peak element (double count)
             so we will subtract the peak element from the count
        
        int i = 1 , size = ratings.size();
        int ans = size;
        while(i < size){
            if(ratings[i] == ratings[i-1]){
                i++;
                continue;
            }
            int v = 0 , m = 0;
            while(i < size && ratings[i] > ratings[i-1]){
                i++;
                v++;
                ans += v;
            }
            while(i < size && ratings[i] < ratings[i-1]){
                i++;
                m++;
                ans += m;
            }
            ans -= min(v,m);
        }
        return ans;
*/ 


/*
    find the largest number , formed by the given array of numbers 
        ex : [3,30,34,5,9] -> 9534330


    Greedy Solution : 
        sort the numbers using the comparator function 
           where decision is based on num1 + num2 > num2 + num1
        

        bool cmp(int num1,int num2){
            string s1 = to_string(num1);
            string s2 = to_string(num2);
            return s1 + s2 > s2 + s1;
        }
        TC : O(NlogN)
        SC : O(N)
*/


/*
    Remove Duplicate Letters
        Given a string s, remove duplicate letters so that every letter appears once and only once. 
        You must make sure your result is the smallest in lexicographical order among all possible results.

    
    Greedy Solution + monotonic stack : 
        1.we will build the ans by traversing the string
        2.if the current characters is greater than previous characters -> then it is valid move
        3.if curr ch > prev ch -> then we need to check :
            3.1.can we remove it from the ans , if that character is present in later part of the string.
            3.2.if yes , then we will pop the element from the ans and mark it as not present
            3.3.push the current character to the ans


        vector<int> last(26,-1);
        vector<int> vis(26,0);
        for(int i = 0 ; i < s.size() ; ++i){
            last[s[i] - 'a'] = i;
        }
        string ans = "";
        for(int i = 0 ; i < s.size() ; ++i){
            char ch = s[i];
            if(vis[ch - 'a'] == 1) continue;
            while(!ans.empty() && ans.back() > ch && last[ans.back() - 'a'] > i){
                vis[ans.back() - 'a'] = 0;
                 ans.pop_back();
            }
            ans += ch;
            vis[ch - 'a'] = 1;
        }
        return ans;


        TC: O(N)
        SC : O(2 * 26) -> CONSTANT SPACE

*/






