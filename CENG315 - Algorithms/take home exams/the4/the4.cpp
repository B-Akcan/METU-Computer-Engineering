#include <vector>
// do not add extra libraries here

int divide_land(int X, int Y, bool** possible_plots) {

    std::vector<std::vector<int>> dp(X + 1, std::vector<int>(Y + 1, 0));
    
    for (int i=1; i <= X; i++)
    {
        for (int j=1; j <= Y; j++)
            dp[i][j] = i*j;
    }

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            if (possible_plots[i][j])
                dp[i][j] = 0;
                
            for (int k = 1; k < i; k++)
                dp[i][j] = std::min(dp[i][j], dp[k][j] + dp[i - k][j]);
            for (int k = 1; k < j; k++)
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[i][j - k]);
        }
    }

    return dp[X][Y];
}