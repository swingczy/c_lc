#include "lc_app.h"

int main(int, char**){
    int a[] = {1,2,3,1};
    int b = rob(a, 4);
    assert(b == 4);

    return 0;
}
