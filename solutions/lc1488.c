/**
 * 1488 medium, avoid-flood-in-the-city
 * hash, double-linked-list
*/


struct DLLNode_ { // DLL: Double Linked List
    int day;
    struct DLLNode_* prev;
    struct DLLNode_* next;
};

typedef struct DLLNode_ DLLNode;

typedef struct {
    DLLNode dummy; // to simplify the delete operation when it's head node.
    DLLNode* tail;
} List;

typedef List SunnyDays;

void listInit(List* l);
void listPushBack(List* l, int day);
DLLNode* listFindFirstGt(List* l, int day); // find first greater than @p day
void listDelete(List* l, DLLNode* pDel);
void listFree(List* l);

typedef struct {
    int lake; // lake number
    int lastRainDay; // last rainy date
    UT_hash_handle hh;
} MapEle;

typedef MapEle* RainLakes;

void mapInsert(MapEle** map, int lake, int lastRainDay);
MapEle* mapFind(MapEle* map, int key);
void mapFree(MapEle** map);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* avoidFlood(int* rains, int rainsSize, int* returnSize) {
    RainLakes rainedLakes = NULL;
    SunnyDays sunnyDays;
    listInit(&sunnyDays);

    int* ans = (int*)malloc(sizeof(int) * rainsSize);
    for (int i = 0; i < rainsSize; i++) {
        ans[i] = 1;
    }

    for (int day = 0; day < rainsSize; day++) {
        if (rains[day] == 0) { // sunny
            listPushBack(&sunnyDays, day);
        } else {
            ans[day] = -1;
            int lake = rains[day];
            MapEle* it = mapFind(rainedLakes, lake);
            if (it != NULL) {
                DLLNode* sDay = listFindFirstGt(&sunnyDays, it->lastRainDay);
                if (sDay == NULL) {
                    free(ans);
                    *returnSize = 0;
                    mapFree(&rainedLakes);
                    listFree(&sunnyDays);
                    return NULL;
                } else {
                    ans[sDay->day] = lake; // pipe the `lake' at sDay->day
                    listDelete(&sunnyDays, sDay); // rm the sunny from the list
                }
                it->lastRainDay = day; // update the rainy date
            } else {
                mapInsert(&rainedLakes, lake, day); // first time raining
            }
        }
    }

    mapFree(&rainedLakes);
    listFree(&sunnyDays);

    *returnSize = rainsSize;
    return ans;
}

void listInit(List* l) {
    l->dummy.next = NULL;
    l->dummy.prev = NULL;
    l->tail = &l->dummy;
}

void listPushBack(List* l, int day) {
    DLLNode* node = (DLLNode*)malloc(sizeof(DLLNode));
    node->day = day;
    node->next = NULL;

    node->prev = l->tail;
    l->tail->next = node;

    l->tail = node;
}

DLLNode* listFindFirstGt(List* l, int day) {
    DLLNode* p = l->dummy.next;
    while (p && p->day < day) {
        p = p->next;
    }
    return p;
}

void listDelete(List* l, DLLNode* pDel) {
    pDel->prev->next = pDel->next;
    if (pDel->next) { // isn't the last node
        pDel->next->prev = pDel->prev;
    } else { // last node, need to modify l->tail
        l->tail = pDel->prev;
    }
    free(pDel);
}

void listFree(List* l) {
    DLLNode* p = l->dummy.next;
    while (p) {
        DLLNode* next = p->next;
        free(p);
        p = next;
    }
}

void mapInsert(MapEle** map, int lake, int lastRainDay) {
    MapEle* s;
    s = (MapEle*)malloc(sizeof(MapEle));
    s->lake = lake;
    s->lastRainDay = lastRainDay;
    HASH_ADD_INT(*map, lake, s);
}

MapEle* mapFind(MapEle* map, int lake) {
    MapEle* s;
    HASH_FIND_INT(map, &lake, s);
    return s;
}

void mapFree(MapEle** map) {
    MapEle* el, * tmp;
    HASH_ITER(hh, *map, el, tmp) {
        HASH_DEL(*map, el);
        free(el);
    }
}

// int main()
// {
//     int a[] = { 1,2,0,2,3,0,1 };
//     int p = 0;
//     int* q = avoidFlood(a, 7, &p); // -1 -1 2 -1 -1 1 -1
//     for (int i = 0; i < p; i++) {
//         printf("%d\n", q[i]);
//     }
//     free(q);
//     return EXIT_SUCCESS;
// }
