/**
 * 213, medium, house-robber-ii
 * dp
 * @see lc198.c
*/

static int robRange(int *nums, int numsSize, int start, int end) {
    if (start > end) {
        return 0;
    }

    int dp0 = 0;
    int dp1 = nums[start];
    for (int i = start + 1; i <= end; i++) {
        int dp0_1 = fmax(dp0, dp1);
        int dp1_1 = dp0 + nums[i];
        dp0 = dp0_1;
        dp1 = dp1_1;
    }

    return fmax(dp0, dp1);
}

int rob(int* nums, int numsSize){
    if (numsSize == 1) {
        return nums[0];
    }
    return fmax(robRange(nums, numsSize, 0, numsSize - 2), robRange(nums, numsSize, 1, numsSize - 1));
}
