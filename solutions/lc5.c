/**
 * 5 longest-palindromic-substring
 * medium
 * 
 * string
*/

int expand(char* s, const int len, int left, int right) {
    int step = 0;
    while( left >= 0 && right < len && s[left] == s[right] ){
        step++;
        left--;
        right++;
    }
    return step;
}

char * longestPalindrome(char * s) {
    const int sLen = strlen(s);
    if (sLen < 2) {
        return s;
    }

	int maxSubStrLen = 0;
    int maxSubStrIdx = 0;

    for (int i = 0; i < sLen; i++) {
        int oddStep = expand(s, sLen, i, i);
        int evenStep = expand(s, sLen, i, i + 1);
        int oddLen = 2 * oddStep - 1;
        int evenLen = 2 * evenStep;
        if (oddLen > evenLen) {
            if (oddLen > maxSubStrLen) {
                maxSubStrLen = oddLen;
                maxSubStrIdx = i - oddStep + 1;
            }
        } else {
            if (evenLen > maxSubStrLen) {
                maxSubStrLen = evenLen;
                maxSubStrIdx = i - evenStep + 1;
            }
        }

    }
    s[maxSubStrIdx + maxSubStrLen] = 0;
    return s + maxSubStrIdx;
}
