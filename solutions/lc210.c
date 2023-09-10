typedef struct {
    int node;
    int *children;
    int maxLen;
    int len;
    UT_hash_handle hh;
} HashEle;

HashEle* newHashNode(int node, int child, int initLen) {
    HashEle *s = malloc(sizeof(HashEle));
    s->node = node;
    s->children = malloc(sizeof(int) * initLen);
    s->children[0] = child;
    s->len = 1;
    return s;
}

void appendHashNode(HashEle *key, int child) {
    if (key->len == key->maxLen) {
        printf("HashEle Expanded Vector, key:%d.\n", key->node);

        int *newChildren = malloc(sizeof(int) * (key->maxLen * 2));
        key->maxLen *= 2;
        memcpy(newChildren, key->children, sizeof(int) * key->len);
        free(key->children);
        key->children = newChildren;
    }

    key->children[key->len] = child;
    key->len++;
}

void freeHashTbl(HashEle **map) {
    HashEle *el, *tmp;
    HASH_ITER(hh, *map, el, tmp) {
        HASH_DEL(*map, el);
        free(el->children);
        free(el);
    }
}

typedef struct {
    int *d;
    int cap;
    int front;
    int rear;
} Queue;

void qIn(Queue *q, int n) {
    q->d[q->rear] = n;
    q->rear = (q->rear + 1) % q->cap;
}

int qSize(Queue *q) {
    return (q->rear - q->front + q->cap) % q->cap;
}

// peek front and pop
int qOffer(Queue *q) {
    int ret = q->d[q->front];
    q->front = (q->front + 1) % q->cap;
    return ret;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize){
    // directed graph
    HashEle *graphs = NULL;
    // indegrees, init by 0
    int *indegrees = malloc(sizeof(int) * numCourses);
    memset(indegrees, 0, sizeof(int) * numCourses);

    for (int i = 0; i < prerequisitesSize; i++) {
        int from = prerequisites[i][1];
        int to = prerequisites[i][0];

        indegrees[to]++;

        HashEle *s;
        HASH_FIND_INT(graphs, &from, s);
        if (!s) {
            s = newHashNode(from, to, numCourses);
            HASH_ADD_INT(graphs, node, s);
        } else {
            appendHashNode(s, to);
        }
    }

    // answer
    int *ans_d = malloc(sizeof(int) * numCourses);
    int ans_p = 0;

    // queue
    Queue q = {
        .d = malloc(sizeof(int) * (numCourses + 1)),
        .cap = numCourses + 1,
        .front = 0,
        .rear = 0,
    };

    // inqueue, indegree eq 0
    for (int j = 0; j < numCourses; j++) {
        if (indegrees[j] == 0) {
            qIn(&q, j);
        }
    }

    while (qSize(&q) != 0) {
        int n = qOffer(&q);

        ans_d[ans_p] = n;
        ans_p++;

        // find all children, decrease indegree by 1
        HashEle *s1;
        HASH_FIND_INT(graphs, &n, s1);
        if (s1) {
            for (int k = 0; k < s1->len; k++) {
                int v = s1->children[k];
                indegrees[v]--;
                if (indegrees[v] == 0) {
                    qIn(&q, v);
                }
            }
        }
    }

    freeHashTbl(&graphs);
    free(indegrees);
    free(q.d);

    if (ans_p == numCourses) {
        *returnSize = ans_p;
        return ans_d;
    } else {
        *returnSize = 0;
        free(ans_d);
        return NULL;
    }
}
