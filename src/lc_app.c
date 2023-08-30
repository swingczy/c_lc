#include "lc_app.h"
#include "uthash.h"

typedef struct {
    int num;
    int idx;
    UT_hash_handle hh;
} HashEle;

void hashFree(HashEle **map) {
    HashEle *el, *tmp;
    HASH_ITER(hh, *map, el, tmp) {
        HASH_DEL(*map, el);
        free(el);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int *ans = malloc(sizeof(int) * 2);
    *returnSize = 2;

    HashEle *map = NULL;
    HashEle *s;

    for (int i = 0; i < numsSize; i++) {
        int numToFind = target - nums[i];
        HASH_FIND_INT(map, &numToFind, s);
        if (!s) {
            s = malloc(sizeof(HashEle));
            s->num = nums[i];
            s->idx = i;
            HASH_ADD_INT(map, num, s);
        } else {
            ans[0] = i;
            ans[1] = s->idx;
            hashFree(&map);
            return ans;
        }
    }

    return ans;
}
