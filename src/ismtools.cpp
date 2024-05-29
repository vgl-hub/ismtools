#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include "ismtools.h"

#define DPRINTC(C) printf(#C " = %c\n", (C))
#define DPRINTS(S) printf(#S " = %s\n", (S))
#define DPRINTD(D) printf(#D " = %d\n", (D))
#define DPRINTLLD(LLD) printf(#LLD " = %lld\n", (LLD))
#define DPRINTLF(LF) printf(#LF " = %.5lf\n", (LF))

using namespace std;
typedef long long lld;
typedef unsigned long long llu;

/*
 Needleman-Wunsch algorithm for determining the optimal alignment between two strings
 assuming a given score for hits, gaps and mismatches.
 Complexity: O(n * m) time, O(n * m) memory
*/

inline int needleman_wunsch(uint32_t n, uint32_t m, int dp[MAX_N][MAX_N], int8_t match_score, int8_t mismatch_score, int8_t gap_score, std::string A, std::string B) {
    for (uint32_t i=0;i<=n;i++) dp[i][0] = dp[0][i] = i * gap_score;
    for (uint32_t i=1;i<=n;i++)
    {
        for (uint32_t j=1;j<=m;j++)
        {
            int S = (A[i-1] == B[j-1] && (A[i-1] == 'T' || A[i-1] == 'C')) ? match_score : mismatch_score;
            dp[i][j] = max(dp[i-1][j-1] + S, max(dp[i-1][j] + gap_score, dp[i][j-1] + gap_score));
        }
    }
    return dp[n][m];
}

inline pair<std::string, std::string> get_optimal_alignment(uint32_t n, uint32_t m, int dp[MAX_N][MAX_N], int8_t match_score, int8_t mismatch_score, std::string A, std::string B)
{
    std::string retA, retB;
    stack<char> SA, SB;
    int ii = n, jj = m;
    while (ii != 0 || jj != 0)
    {
        if (ii == 0)
        {
            SA.push('-');
            SB.push(B[jj-1]);
            jj--;
        }
        else if (jj == 0)
        {
            SA.push(A[ii-1]);
            SB.push('-');
            ii--;
        }
        else
        {
            int S = (A[ii-1] == B[jj-1] && (A[ii-1] == 'T' || A[ii-1] == 'C')) ? match_score : mismatch_score;
            if (dp[ii][jj] == dp[ii-1][jj-1] + S)
            {
                SA.push(A[ii-1]);
                SB.push(B[jj-1]);
                ii--; jj--;
            }
            else if (dp[ii-1][jj] > dp[ii][jj-1])
            {
                SA.push(A[ii-1]);
                SB.push('-');
                ii--;
            }
            else
            {
                SA.push('-');
                SB.push(B[jj-1]);
                jj--;
            }
        }
    }
    while (!SA.empty())
    {
        retA += SA.top();
        retB += SB.top();
        SA.pop();
        SB.pop();
    }
    return make_pair(retA, retB);
}

bool ismtools(int8_t match_score, int8_t mismatch_score, int8_t gap_score, std::string A, std::string B, int dp[MAX_N][MAX_N]) {
    uint32_t n = A.size(), m = B.size();
    printf("%d\n",needleman_wunsch(n, m, dp, match_score, mismatch_score, gap_score, A, B));
    pair<std::string, std::string> alignment = get_optimal_alignment(n, m, dp, match_score, mismatch_score, A, B);
    printf("%s\n%s\n", alignment.first.c_str(), alignment.second.c_str());
    return true;
}
