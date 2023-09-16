#include "lc_app.h"

// returned char* is malloced in function
char* timeToStr(int hour, int minute) {
    char *s = malloc(sizeof(char) * 6);
    int p = 0;

    p += snprintf(s, sizeof(char) * 6, "%d:%02d", hour, minute);
    s[p] = '\0';
    return s;
}

// count the amount of 1 in `x`
int countOneBits(int x) {
    int cnt = 0;
    while (x != 0) {
        cnt++;
        x &= x - 1;
    }
    return cnt;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** readBinaryWatch(int turnedOn, int* returnSize){
    char **ans = malloc(sizeof(char*) * (24 * 60));
    int p = 0;

    for (int i = 0; i < 12 * 60; i++) {
        int hour = i / 60;
        int min = i % 60;
        if (countOneBits(hour) + countOneBits(min) == turnedOn) {
            ans[p++] = timeToStr(hour, min);
        }
    }
    *returnSize = p;
    return ans;
}
