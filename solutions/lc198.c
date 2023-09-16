/**
 * 198 medium, house-robber
 * dp
 * @see lc213.c
*/

int rob(int* nums, int numsSize){
    // dp0: max money when NOT stealing current house
    int dp0 = 0;
    // dp1: max money when stealing current house
    int dp1 = nums[0];

    for (int i = 1; i < numsSize; i++) {
        int dp0new = fmax(dp0, dp1);
        int dp1new = dp0 + nums[i];
        dp0 = dp0new;
        dp1 = dp1new;
    }
    return fmax(dp0, dp1);
}