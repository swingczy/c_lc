#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "uthash.h"
#include "lc_app.h"

int main(int, char**){
    int a[] = {2,7,11,15};
    int p = 0;
    int *pp = twoSum(a, 4, 9, &p);
    printf("Hello, c_lc! {%d,%d}.\n", pp[0], pp[1]);
    free(pp);
    return 0;
}
