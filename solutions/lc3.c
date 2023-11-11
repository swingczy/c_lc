/**
 * 3 longest-substring-without-repeating-characters
 * medium
 * 
 * sliding window
 * set
*/

typedef struct {
    int num;
    UT_hash_handle hh;
} HashEle;

HashEle* SetGet(HashEle** set, int key) {
    HashEle *s;
    HASH_FIND_INT(*set, &key, s);
    return s;
}

void SetAdd(HashEle** set, int key) {
    HashEle* s = SetGet(set, key);
    if (s) {
        return;
    }
    s = (HashEle*) malloc(sizeof(HashEle));
    s->num = key;
    HASH_ADD_INT(*set, num, s);
}

void SetRm(HashEle** set, HashEle* s) {
    HASH_DEL(*set, s);
    free(s);
}

int lengthOfLongestSubstring(char * s){
	int sLen = strlen(s);
    if (sLen < 2) {
        return sLen;
    }

    HashEle* set = NULL;

    int maxSize = 0;

    int right = -1;
    for (int left = 0; left < sLen; left++) {
        if (left > 0) {
            HashEle* p = SetGet(&set, s[left - 1]);
            SetRm(&set, p);
        }
        while (right + 1 < sLen && !SetGet(&set, s[right + 1])) {
            right++;
            SetAdd(&set, s[right]);
        }
        maxSize = fmax(maxSize, right - left + 1);
    }

    HashEle *el, *tmp;
    HASH_ITER(hh, set, el, tmp) {
        HASH_DEL(set, el);
        free(el);
    }

    return maxSize;
}
