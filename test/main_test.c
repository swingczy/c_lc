#include "../src/lc_app.h"

int main() {
    printf("TEST RUNNING.\n");
    //////////////////////////

    char *s = timeToStr(0, 0);
    printf("s:%s\n", s); // "0:00"

    int a = countOneBits(5);
    assert(a == 2);

    /////////////////////////////
    printf("TEST SUCCEEDED.\n");
    return 0;
}
