#ifndef ISMTOOLS_H
#define ISMTOOLS_H

#define MAX_N 1001

bool ismtools(int8_t match_score, int8_t mismatch_score, int8_t gap_score, std::string A, std::string B, int dp[MAX_N][MAX_N]);

#endif /* ISMTOOLS_H */

