#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int count;
} ElementCount;

int compare(const void *a, const void *b) {
    return ((ElementCount*)b)->count - ((ElementCount*)a)->count;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    ElementCount* counts = (ElementCount*)malloc(numsSize * sizeof(ElementCount));
    int* result = (int*)malloc(k * sizeof(int));
    
    int numUnique = 0;
    for (int i = 0; i < numsSize; i++) {
        int found = 0;
        for (int j = 0; j < numUnique; j++) {
            if (counts[j].key == nums[i]) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            counts[numUnique].key = nums[i];
            counts[numUnique].count = 1;
            numUnique++;
        }
    }
    
    qsort(counts, numUnique, sizeof(ElementCount), compare);
    
    for (int i = 0; i < k; i++) {
        result[i] = counts[i].key;
    }
    
    *returnSize = k;
    free(counts);
    return result;
}

int main() {
    int nums[] = {1, 1, 1, 2, 2, 1};
    int k = 2;
    int returnSize;
    int* result = topKFrequent(nums, 6, k, &returnSize);

    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i]);
        if (i < returnSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(result);
    return 0;
}
