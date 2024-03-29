/*
Problem: Given two strings, 'S' and 'T' with lengths 'M' and 'N', find the length of the 'Longest Common Subsequence'.

For a string 'str'(per se) of length K, the subsequences are the strings containing characters in the same relative order as they are present in 'str,' but not necessarily contiguous. Subsequences contain all the strings of length varying from 0 to K.

Example :
Subsequences of string "abc" are:  ""(empty string), a, b, c, ab, bc, ac, abc.

link: https://www.codingninjas.com/studio/problems/longest-common-subsequence_624879
*/

/*
memoization
*/
int f(int i, int j, string s, string t, vector<vector<int>> &dp){
	if(i < 0 || j < 0)
		return 0;
	if(dp[i][j] != -1) return dp[i][j];
	if(s[i] == t[j])
		dp[i][j] = 1 + f(i - 1, j - 1, s, t, dp);
	else
		dp[i][j] = max(f(i - 1, j, s, t, dp), f(i, j - 1, s, t, dp));
	return dp[i][j];
}

int lcs(string s, string t)
{
	vector<vector<int>> dp(s.size(), vector<int>(t.size(), -1));
	return f(s.size() - 1, t.size() - 1, s, t, dp);
}

/*
my tabulation
*/

int lcs(string s, string t)
{
	vector<vector<int>> dp(s.size(), vector<int>(t.size(), 0));
	for(int i = 0; i < s.size(); i++){
		for(int j = 0; j < t.size(); j++){
			if(s[i] == t[j]){
				dp[i][j] = 1;
				if(i > 0 && j > 0)
					dp[i][j] += dp[i - 1][j - 1];
			}
			else{
				int c1 = 0;
				int c2 = 0;
				if(i > 0)
					c1 = dp[i - 1][j];
				if(j > 0)
					c2 = dp[i][j - 1];
				dp[i][j] = max(c1, c2);
			}
		}
	}
	return s.size() > 0 && t.size()> 0 ? dp[s.size() - 1][t.size() - 1] : 0;
}

/*
striver's tabulation
approach: shift the indexes so that -1 points to 0. this will eliminate the conditions for checking the bounds
*/

int lcs(string s, string t)
{
	vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
	for(int i = 1; i <= s.size(); i++){
		for(int j = 1; j <= t.size(); j++){
			if(s[i - 1] == t[j - 1])
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[s.size()][t.size()];
}

/*
space optimization
*/
int lcs(string s, string t)
{
	vector<int> prev(t.size() + 1, 0);
	vector<int> curr(t.size() + 1, 0);
	for(int i = 1; i <= s.size(); i++){
		for(int j = 1; j <= t.size(); j++){
			if(s[i - 1] == t[j - 1])
				curr[j] = 1 + prev[j - 1];
			else
				curr[j] = max(prev[j], curr[j - 1]);
		}
		prev = curr;
	}
	return prev[t.size()];
}

/*
printing longest common subsequence
*/

#include <iostream>
#include <vector>

using namespace std;

string lcs(string s, string t)
{
	vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
	// filling up the dp matrix
	for (int i = 1; i <= s.size(); i++) {
		for (int j = 1; j <= t.size(); j++) {
			if (s[i - 1] == t[j - 1])
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	
	int lcs_size = dp[s.size()][t.size()];
	int i = s.size();
	int j = t.size();
	int k = lcs_size - 1;
	string lcs;
	lcs.resize(lcs_size);
	while (i > 0 && j > 0) {
		if (s[i - 1] == t[j - 1]) {
			lcs[k] = (s[i - 1]);
			i--;
			j--;
			k--;
		}
		else if (dp[i - 1][j] >= dp[i][j]) {
			i--;
		}
		else {
			j--;
		}
	}
	return lcs;
}

int main()
{
	string s = "bdgek";
	string t = "abcde";
	cout << s << endl << t << endl;
	cout << lcs(s, t) << endl;
}

/*
problem variation: 
You are given 2 non-empty strings 's1' and 's2' consisting of lowercase English alphabets only.
In one operation you can do either of the following on 's1':
(1) Remove a character from any position in 's1'.
(2) Add a character to any position in 's1'.
Find the minimum number of operations required to convert string 's1' into 's2'.

Link: https://www.codingninjas.com/studio/problems/can-you-make_4244510

Solution:
given string length n of s and m of t
assuming n > m then,
deletions = n - len(lcs(s,t))
insertions = m - len(lcs(s,t))
deletions + insertions = n + m - 2 len(lcs(s,t)) 
this is the required answer
*/
int canYouMake(string &s1, string &s2){
    int n = s1.size();
    int m = s2.size();
    int lcs_len = lcs(s1, s2);
    return n + m - (2 * lcs_len);
}