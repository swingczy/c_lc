/**
 * 4 median-of-two-sorted-arrays
 * hard
 * 
 * recursion
*/

void merge(int *merged, int *tail, int *nums1, int *p1, int nums1Size, int *nums2, int *p2, int nums2Size) {
    if (nums2Size - *p2 == 0) {
        memcpy(merged + *tail, nums1 + *p1, sizeof(int) * (nums1Size - *p1));
        *tail += nums1Size - *p1;
        return;
    } else if (nums1Size - * p1 == 0) {
        memcpy(merged + *tail, nums2 + *p2, sizeof(int) * (nums2Size - *p2));
        *tail += nums2Size - *p2;
        return;
    } else {
        int h1 = nums1[*p1];
        int h2 = nums2[*p2];
        if (h1 < h2) {
            merged[(*tail)++] = h1;
            (*p1)++;
        } else {
            merged[(*tail)++] = h2;
            (*p2)++;
        }
        merge(merged, tail, nums1, p1, nums1Size, nums2, p2, nums2Size);
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int *merged = malloc(sizeof(int) * (nums1Size + nums2Size));
    int tail = 0; // tail of merged

    int p1 = 0; // head of nums1
    int p2 = 0; // head of nums2
    merge(merged, &tail, nums1, &p1, nums1Size, nums2, &p2, nums2Size);

    if (tail % 2 == 0) {
        double x = (double)(merged[tail / 2 - 1] + merged[tail / 2]) / 2;
        free(merged);
        return x;
    } else {
        double x = (double)(merged[tail / 2]);
        free(merged);
        return x;
    }
}
