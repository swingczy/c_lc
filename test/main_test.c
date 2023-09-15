#include "../src/lc_app.h"

int main() {
    printf("TEST RUNNING.\n");
    //////////////////////////


    int a[] = {1,2,3,1};
    int b = rob(a, 4);
    assert(b == 4);


    /////////////////////////////
    printf("TEST SUCCEEDED.\n");
    return 0;
}
