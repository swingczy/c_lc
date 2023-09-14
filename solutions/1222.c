/**
 * 1222 queens-that-can-attack-the-king
 * medium
 * 
 * hash
*/

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point p;
    UT_hash_handle hh;
} HashEle;

HashEle *setFromVec(int **matrix, int matrixSize) {
    HashEle *set = NULL;
    HashEle *s;
    for (int i = 0; i < matrixSize; i++) {
        Point p = {.x = matrix[i][0], .y = matrix[i][1]};
        HASH_FIND(hh, set, &p, sizeof(Point), s);
        if (!s) {
            s = malloc(sizeof(HashEle));
            s->p = p;
            HASH_ADD(hh, set, p, sizeof(Point), s);
        }
    }
    return set;
}

bool setContains(HashEle *set, int x, int y) {
    Point p = {.x = x, .y = y};
    HashEle *s;
    HASH_FIND(hh, set, &p, sizeof(p), s);
    return s != NULL;
}

void setFree(HashEle **set) {
    HashEle *el, *tmp;
    HASH_ITER(hh, *set, el, tmp) {
        HASH_DEL(*set, el);
        free(el);
    }
}

#define VALID_POS(x, y) ((x) >= 0 && (x) <= 7 && (y) >= 0 && (y) <= 7)

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** queensAttacktheKing(int** queens, int queensSize, int* queensColSize, int* king, int kingSize, int* returnSize, int** returnColumnSizes){
    const int directions[8][2] = {
        {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1},
    };

    HashEle *set = setFromVec(queens, queensSize);

    int **ans = malloc(sizeof(int*) * queensSize);
    int p = 0;
    *returnColumnSizes = malloc(sizeof(int) * queensSize);

    for (int dir = 0; dir < 8; dir++) {
        const int xstep = directions[dir][0], ystep = directions[dir][1];
        int x = king[0] + xstep, y = king[1] + ystep;
        while (VALID_POS(x, y)) {
            if (setContains(set, x, y)) {
                ans[p] = malloc(sizeof(int) * 2);
                ans[p][0] = x;
                ans[p][1] = y;
                (*returnColumnSizes)[p] = 2;
                p++;
                break;
            }
            x += xstep;
            y += ystep;
        }
    }

    setFree(&set);

    *returnSize = p;
    return ans;
}
