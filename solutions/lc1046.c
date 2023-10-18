/**
 * 1046, easy, last-stone-weight/submissions
 * heap
*/

#define ABS(x) ((x) > 0 ? (x) : -(x))


// max heap
struct HeapStruct {
    int* elements;
    int size;
    // int capacity; // can be omitted if there's no need to know if it's full
};

struct HeapStruct;
typedef struct HeapStruct* PriorityQueue;

#define QUEUE_MAX_ELE 1001 // sentinel

PriorityQueue heapInit(int max_elements);
void heapDestory(PriorityQueue h);
void heapInsert(PriorityQueue h, int x);
int heapDeleteMax(PriorityQueue h);

void heapPercolateDown(PriorityQueue h, int i);
PriorityQueue heapBuild(int* nums, int numsSize);

int lastStoneWeight(int* stones, int stonesSize) {
    PriorityQueue h = heapBuild(stones, stonesSize);

    while (h->size >= 1) {
        if (h->size == 1) {
            int ans = heapDeleteMax(h);
            heapDestory(h);
            return ans;
        } else {
            int s1 = heapDeleteMax(h);
            int s2 = heapDeleteMax(h);
            if (s1 != s2) {
                heapInsert(h, ABS(s1 - s2));
            }
        }
    }

    heapDestory(h);
    return 0;
}

PriorityQueue
heapInit(int max_elements)
{
    PriorityQueue h;
    h = malloc(sizeof(struct HeapStruct));
    assert(h != NULL);

    h->elements = malloc(sizeof(int) * (max_elements + 1));
    assert(h->elements != NULL);
    h->size = 0;
    h->elements[0] = QUEUE_MAX_ELE;

    return h;
}

void
heapDestory(PriorityQueue h)
{
    free(h->elements);
    free(h);
}

void
heapInsert(PriorityQueue h, int x)
{
    int i;
    for (i = ++h->size; h->elements[i / 2] < x; i /= 2) {
        h->elements[i] = h->elements[i / 2];
    }
    h->elements[i] = x;
}

int
heapDeleteMax(PriorityQueue h)
{
    int topEle = h->elements[1];
    int lastEle = h->elements[h->size--];

    int i, child;
    for (i = 1; i * 2 <= h->size; i = child) {
        child = i * 2;
        if (child < h->size && h->elements[child + 1] > h->elements[child]) {
            child++;
        }
        // percolate down one level
        if (lastEle < h->elements[child]) {
            h->elements[i] = h->elements[child];
        } else {
            break;
        }
    }

    h->elements[i] = lastEle;

    return topEle;
}

void
heapPercolateDown(PriorityQueue h, int i)
{
    assert(i > 0);
    assert(i <= h->size);

    int ele = h->elements[i];
    int child;
    for (; i * 2 <= h->size; i = child) {
        child = i * 2;
        // find bigger child
        if (child < h->size && h->elements[child] < h->elements[child + 1]) {
            child++;
        }
        if (ele < h->elements[child]) {
            h->elements[i] = h->elements[child];
        } else {
            break;
        }
    }

    h->elements[i] = ele;
}

PriorityQueue
heapBuild(int* nums, int numsSize)
{
    PriorityQueue h = heapInit(numsSize);
    h->size = numsSize;
    for (int i = 0; i < numsSize; i++) {
        h->elements[i + 1] = nums[i];
    }

    for (int j = numsSize / 2; j > 0; j--) {
        heapPercolateDown(h, j);
    }

    return h;
}
