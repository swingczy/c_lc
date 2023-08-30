#include <stdio.h>
#include <assert.h>
#include "uthash.h"
#include "../src/lc_app.h"

int main() {
    printf("TEST RUNNING.\n");

    int a[] = {2,7,11,15};
    int p = 0;
    int *pp = twoSum(a, 4, 9, &p);

    printf("CTEST1: %d\n", pp[0]);
    printf("CTEST2: %d\n", pp[1]);

    free(pp);

    return 0;
}
