/*
Problem:
You are given an infinite supply of coins of each of denominations D = {D0, D1, D2, D3, ...... Dn-1}. You need to figure out the total number of ways W, in which you can make a change for value V using coins of denominations from D. Print 0, if a change isn't possible.

Link: https://www.codingninjas.com/studio/problems/ways-to-make-coin-change_630471
*/

/*
recursion
*/
long f(int i , int v, int *deno){
    int *d = deno + i;
    if(v == 0)
        return 1;
    if(i < 0)
        return 0;
    long ans = 0;
    if (v >= *d) {
        ans += f(i, v - *d, deno);
    }
    ans += f(i - 1, v, deno);
    return ans;
}

/*
tabulation
*/

long countWaysToMakeChange(int *denominations, int n, int value)
{
    vector<vector<long>> dp(n, vector<long>(value + 1, 0));
    for(int i = 0; i < n; i++)
        dp[i][0] = 1;
    for(int v = 1; v <= value; v++)
        dp[0][v] = v % *denominations == 0 ? 1 : 0;
    for(int i = 1; i < n; i++){
        for(int v = 1; v <= value; v++){
            int *d = denominations + i;
            // not take
            dp[i][v] += dp[i - 1][v];
            // take
            if(v >= *d)
                dp[i][v] += dp[i][v - *d];
        }
    }
    return dp[n - 1][value];
}