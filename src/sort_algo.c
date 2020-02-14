/**
 * @file sort_algo.h 
 * source file contains of difination of sort algorithm.
 *
 * @author  duruyao
 * @version 1.0  19-12-19
 * @update  [id] [yy-mm-dd] [author] [description] 
 */

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "sort_algo.h"


/*****************************************************************************/
/*                                                                           */
/* struct defination                                                         */
/*                                                                           */
/*****************************************************************************/

/*

array of Bucket type

0  ____________
  | Bucket     |                              size
  |      ______|   ____________________________/\________________________...
  |     |      |  /
  |     | size |   ________________    ________________    ________________
  |     |______|  | Entry          |  | Entry          |  | Entry          |
  |     |      |  |    ____________|  |    ____________|  |    ____________|
  |     |*head===>|   |     |      |  |   |     |      |  |   |     |      |
  |     |      |  |   |*ele |*next--->|   |*ele |*next--->|   |*ele |*next--->
  |     |      |  |   | ment|      |  |   | ment|      |  |   | ment|      |
1 |_____|______|  |___|_____|______|  |___|_____|______|  |___|_____|______|
  | Bucket     |
  |      ______|
  |     |      |
  |     | size |   ________________    ________________    ________________
  |     |______|  | Entry          |  | Entry          |  | Entry          |
  |     |      |  |    ____________|  |    ____________|  |    ____________|
  |     |*head===>|   |     |      |  |   |     |      |  |   |     |      |
  |     |      |  |   |*ele |*next--->|   |*ele |*next--->|   |*ele |*next--->
  |     |      |  |   | ment|      |  |   | ment|      |  |   | ment|      |
2 |_____|______|  |___|_____|______|  |___|_____|______|  |___|_____|______|
  | Bucket     |
  |      ______|
  |     |      |
  |     | size |   ________________    ________________    ________________
  |     |______|  | Entry          |  | Entry          |  | Entry          |
  |     |      |  |    ____________|  |    ____________|  |    ____________|
  |     |*head===>|   |     |      |  |   |     |      |  |   |     |      |
  |     |      |  |   |*ele |*next--->|   |*ele |*next--->|   |*ele |*next--->
  |     |      |  |   | ment|      |  |   | ment|      |  |   | ment|      |
3 |_____|______|  |___|_____|______|  |___|_____|______|  |___|_____|______|
  
  ... ...

*/

struct entry {
    void *element;
    struct entry *next;
};

struct bucket {
    int size;
    Entry *head;
};


/*****************************************************************************/
/*                                                                           */
/* function defination                                                       */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/* compare func                                                              */
/*****************************************************************************/

/*
 * compare function for uint8_t data type.
 *
 * @return 1 (*p1 > *p2), -1 (*p1 < *p2), 0 (*p1 = *p2)
 */

int cmp_uint8(const void *ptr1, const void *ptr2) {
    uint8_t *p1 = (uint8_t *)ptr1, *p2 = (uint8_t *)ptr2;
    return *p1 == *p2 ? 0 : (*p1 > *p2 ? 1 : -1);
}

/*
 * compare function for double floating point data type.
 *
 * @return 1 (*p1 > *p2), -1 (*p1 < *p2), 0 (*p1 = *p2)
 */

int cmp_dbl(const void *ptr1, const void *ptr2) {
    double *p1 = (double *)ptr1, *p2 = (double *)ptr2;
    return *p1 == *p2 ? 0 : (*p1 > *p2 ? 1 : -1);
}

/*
 * compare function for double floating point data type.
 *
 * @return -1 (*p1 > *p2), 1 (*p1 < *p2), 0 (*p1 = *p2)
 */

int cmp_dbl_rev(const void *ptr1, const void *ptr2) {
    double *p1 = (double *)ptr1, *p2 = (double *)ptr2;
    return *p1 == *p2 ? 0 : (*p1 > *p2 ? -1 : 1);
}

/*****************************************************************************/
/* insert sort                                                               */
/*****************************************************************************/

/*
 * insert sort function base value.
 *
 * best case   : O(n)
 * worst case  : O(n ^ 2)
 * average case: O(n ^ 2)
 */

void insert_sort(void *arr, int n, size_t s, 
                 int(*cmp)(const void *, const void *)) {
    void *temp = malloc(s);
    for (int i = 1, j = 0; i < n; i++, j = i - 1) {
        for (; j >= 0 && cmp(arr + j * s, arr + i * s) > 0; j--);
        if (++j == i) continue;
        memmove(temp, arr + i * s, s);
        memmove(arr + (j + 1) * s, arr + j * s, (i - j) * s);
        memmove(arr + j * s, temp, s);
    }
    free(temp);
}

/*
 * insert sort function base pointer.
 *
 * best case   : O(n)
 * worst case  : O(n ^ 2)
 * average case: O(n ^ 2)
 */

void insert_sort_p(void **arr, int n, 
                   int(*cmp)(const void *, const void *)) {
    void *value = NULL;
    for (int i = 1, j = 0; i < n; i++, j = i - 1) {
        value = arr[i];
        for (; j >= 0 && cmp(arr[j], value) > 0; j--) 
            arr[j + 1] = arr[j];
        arr[j + 1] = value;
   }
}

/*****************************************************************************/
/* select sort                                                               */
/*****************************************************************************/

/*
 * select sort function base pointer.
 *
 * best case   : O(n ^ 2)
 * worst case  : O(n ^ 2)
 * average case: O(n ^ 2)
 */

void select_sort(void *arr, int n, size_t s,
                 int(*cmp)(const void *, const void *)) {
    void *temp = malloc(s);
    int max_pos;
    for (int i = n - 1; i >= 1; i--) {
        max_pos = 0;    
        for (int j = 1; j <= i; j++) {
            if (cmp(arr + j, arr + max_pos) > 0)
                max_pos = j;
        }
        SWAP_MEM(arr + i, arr + max_pos, temp, s);
    }
    free(temp);
}

/*
 * select sort function base pointer.
 *
 * best case   : O(n ^ 2)
 * worst case  : O(n ^ 2)
 * average case: O(n ^ 2)
 */

void select_sort_p(void **arr, int n,
                   int(*cmp)(const void *, const void *)) {
    int max_pos;
    for (int i = n - 1; i >= 1; i--) {
        max_pos = 0;    
        for (int j = 1; j <= i; j++) {
            if (cmp(arr[j], arr[max_pos]) > 0)
                max_pos = j;
        }
        SWAP_PTR(arr[i], arr[max_pos]);
    }
}

/*****************************************************************************/
/* heap sort                                                                 */
/*****************************************************************************/

/*
 * keep attribute of heap base pointer.
 *
 * the heap is big top heap (default).
 */

void heapify_p(void **arr, int begin, int end,
               int(*cmp)(const void *, const void *)) {
    int left  = 2 * begin + 1;
    int right = 2 * begin + 2;
    int max_idx = begin;
    if (left  < end && cmp(arr[left],  arr[max_idx]) > 0)
        max_idx = left;
    if (right < end && cmp(arr[right], arr[max_idx]) > 0)
        max_idx = right;
    if (begin != max_idx) {
        SWAP_PTR(arr[begin], arr[max_idx]);
        heapify_p(arr, max_idx, end, cmp);
    }
}

/*
 * build a heap base pointer by using one-dimension array. 
 * 
 * @param k is the max number of elements in heap.
 */

void heap_build_p(void **arr, int k,
                  int(*cmp)(const void *, const void *)) {
    for (int i = k / 2 - 1; i >= 0; i--)
        heapify_p(arr, i, k, cmp);
}

/*
 * get top element of heap.
 *
 * @return the element which is the top of heap.
 */

void *heap_top_p(void **arr) {
    return arr[0];
}

/*
 * insert a new element into a heap.
 *
 * @param n is the current number of elements in heap.
 * @param k is the max number of elements in heap.
 */

void heap_insert_p(void **arr, void *new, int n, int k,
                   int(*cmp)(const void *, const void *)) {
    if (n + 1 > k) return;
    arr[n] = new;
    int p_idx = (n - 1) / 2, c_idx = n;
    while (p_idx >= 0 && cmp(arr[c_idx], arr[p_idx]) > 0) {
        SWAP_PTR(arr[p_idx], arr[c_idx]);
        c_idx = p_idx;
        p_idx = (c_idx - 1) / 2;
    }
}

/*
 * replace the top of heap and keep the nature of heap.
 *
 */

void heap_repl_p(void **arr, void *new, int n,
                 int(*cmp)(const void *, const void *)) {
    arr[0] = new;
    heapify_p(arr, 0, n, cmp);
}

/*
 * delete top of heap and keep the nature of heap.
 *
 * @param n is the number of elements in old heap.
 *
 * @return the element which is the top of heap.
 */

void *heap_del_p(void **arr, int n,
                 int(*cmp)(const void *, const void *)) {
    void *ret = arr[0];
    SWAP_PTR(arr[0], arr[n - 1]);
    heapify_p(arr, 0, n - 1, cmp);
    memset(arr + (n - 1), 0, sizeof(void *));
    return ret;
}

/*
 * heap sort function base pointer.
 *
 * best case   : O(n * log n)
 * worst case  : O(n * log n)
 * average case: O(n * log n)
 */

void heap_sort_p(void **arr, int n,
                 int(*cmp)(const void *, const void *)) {
    heap_build_p(arr, n, cmp);
    for (int i = n - 1; i > 0; i--) {
        SWAP_PTR(arr[i], arr[0]);
        heapify_p(arr, 0, i, cmp);
    }
}

/*
 * select the k-th smallest or largest element of set by using heap.
 *
 * @param max_n is the number of elements of input set.
 * @param k is the size of the heap.
 * @param cmp is 'cmp()' (select the k-th smallest), is 'cmp_rev()' (
 * select the k-th largest).
 * 
 * time complexity : O(n * log k)
 * space complexity: O(k)
 */

void *heap_top_k_p(void **set, int max_n, int k,
                   int(*cmp)(const void *, const void *)) {
    if (k > max_n || k < 1)
        return NULL;
    int n = 0;
    void *k_ptr = NULL;
    void **arr  = NULL;
    arr = (void **)malloc(sizeof(void *) * (k + 1));
    if (arr == NULL) {
        fprintf(stderr, "ERROR allocating memory.\n");
        return NULL;
    }
    for (int i = 0; i < max_n; i++) {
        if (n >= k && cmp(set[i], heap_top_p(arr)) < 0)
            heap_repl_p(arr, set[i], n, cmp);
        else if (n < k)
            heap_push_p(arr, set[i], n++, k, cmp);
    }
    for (int i = k - 1; i > 0; i--) {
        SWAP_PTR(arr[i], arr[0]);
        heapify_p(arr, 0, i, cmp);
    }
    k_ptr = arr[k - 1];
    free(arr);
    return k_ptr;
}

/*****************************************************************************/
/* quick sort                                                                */
/*****************************************************************************/

/*
 * select the best pivot index from array base pointer.
 *
 * select param 'left' as the best index (number of elements < 3).
 * using three-medium-value method to select index (number of element >= 3).
 */

int three_med_val_p(void **arr, int left, int right,
                    int(*cmp)(const void *, const void *)) {
    if (right - left + 1 < 3)
        return left;
    else {
        int idx[3];
        srand((unsigned)time(NULL));
        for (int i = 0; i < 3; i++)
            idx[i] = rand() % (right - left + 1) + left;
        if (cmp(arr[idx[0]], arr[idx[1]]) * cmp(arr[idx[0]], arr[idx[2]]) <= 0)
            return idx[0];
        if (cmp(arr[idx[1]], arr[idx[0]]) * cmp(arr[idx[1]], arr[idx[2]]) <= 0)
            return idx[1];
        else
            return idx[2];
    }
}

/*
 * quick sort function base pointer.
 *
 * best case   : < O(n * log n)
 * worst case  :   O(n ^ 2)
 * average case:   O(n * log n)
 */

void quick_sort_p(void **arr, int begin, int end,
                  int(*cmp)(const void *, const void *)) {
    if (end - begin > 1) {
        // int pivot = three_med_val_p(arr, begin, end - 1, cmp);
        int pivot = BFPRT_p_idx_p(arr, begin, end, cmp);
        int low   = begin;
        int high  = end - 1;
        SWAP_PTR(arr[begin], arr[pivot]);
        pivot = begin;
        while (low < high) {
            while(low < high && cmp(arr[high], arr[pivot]) >= 0) high--;
            while(low < high && cmp(arr[low], arr[pivot]) <= 0) low++;
            SWAP_PTR(arr[low], arr[high]);
        }
        SWAP_PTR(arr[low], arr[pivot]);
        quick_sort_p(arr, begin, low, cmp);
        quick_sort_p(arr, low + 1, end, cmp);
    }
}

/*****************************************************************************/
/* bucket sort                                                               */
/*****************************************************************************/

/*
 * computing the most suitable number of buckets.
 *
 * the spetific algorithm depends on attribute input data set.
 *
 * @param n is number of item of input data set.
 */

int num_bucket_p(int n) {
    if (n < 2 * 512) return 26 * 26;
    if (n < 2 * 65536) return 26 * 26 * 26;
    return 26 * 26 * 26 * 26;
}

/*
 * computing the most suitable index of buckets array for the element.
 *
 * the spetific hash algorithm depends on specific input data set.
 * the following hash func is suit for a specific set, that contains of 
 * double floating point type data and their scope is [256, 25536].
 * 
 * @param k is number of buckets.
 */

int hash_idx_p(void *ele, int k) {
    double min = 256, max = 65536;
    return (int)(k * (*(double *)ele - min) / (max - min));
}

/*
 * extract buckets function contains of the following steps:
 *
 * 1. insert sort in inside of every bucket.
 * 2. move data from every bucket to input set.
 * 3. release memory allocated from linked list of every inside of bucket.
 *
 * @param n is number of item of input set, k is number of buckets.
 */

void ext_bucket_p(void **arr, Bucket *buckets, int n, 
                  int k, int(*cmp)(const void *, const void *)) {
    int low, pos = 0;               /* index of input data set */
    Entry *pe = NULL;               /* point to a entry        */
    Entry *pt = NULL;               /* point to temp entry     */
    for (int i = 0; i < k; i++) {
        pe = buckets[i].head;
        if (pe == NULL) continue;
        low = pos;
        arr[pos++] = pe->element;
        pt = pe;
        pe = pe->next;
        free(pt);
        for (int j; pe != NULL;) {
            j = pos - 1;
            while (j >= low && cmp(arr[j], pe->element) > 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = pe->element;
            pos++;
            pt = pe;
            pe = pe->next;
            free(pt);
        }
        buckets[i].size = 0;
    }
}

/*
 * bucket sort function base pointer.
 *
 * the algorithm is suitable for some specific data sets, such as a set, 
 * which contains of double floating point type data and their scope known,
 * it is [256, 25536].
 *
 * bucket sort need more extra memory but less time.
 *
 * time complexity : O(n)
 * space complexity: O(k)
 */

void bucket_sort_p(void **arr, int n, 
                   int(*num_bucket)(int),
                   int(*hash)(void *, int), 
                   int(*cmp)(const void *, const void *)) {
    Bucket *buckets = NULL;
    Entry *e = NULL;
    int idx  = 0;
    int k    = num_bucket(n);

    /* allocate memory for k buckets */
    buckets = (Bucket *)malloc(k * sizeof(Bucket));
    if (buckets == NULL) {
        fprintf(stderr, "ERROE allocating memory\n");
        return;
    }
    
    /* build k buckets with linked list depends on input data set */
    for (int i = 0; i < n; i++) {
        idx = hash(arr[i], k);
        e = (Entry *)malloc(1 * sizeof(Entry));
        e->element = arr[i];
        if (buckets[idx].head == NULL) {
            buckets[idx].head = e;
            buckets[idx].size = 1;
        }
        else {
            e->next = buckets[idx].head;
            buckets[idx].head = e;
            buckets[idx].size++;
        }
    }
    
    /* sort, reset input data set and release memory of linked list */
    ext_bucket_p(arr, buckets, n, k, cmp);

    /* release memory for k buckets */
    free(buckets);
}

/*****************************************************************************/
/* merge sort                                                                */
/*****************************************************************************/

/*  
 * merge sort internal recursive function.
 *
 * @param pointer 'copy' point to an allocated memory, which should be released
 * by caller.
 */

void m_sort_p(void **copy, void **result,
              int begin, int end,
              int(*cmp)(const void *, const void *)) {
    if (end - begin <= 1)
        return;
    int med = (begin + end) / 2;
    m_sort_p(result, copy, begin, med, cmp);
    m_sort_p(result, copy, med, end, cmp);
    for (int idx = begin, i = begin, j = med; idx < end;) {
        if (j >= end || (i < med && cmp(copy[i], copy[j]) <= 0))
            result[idx++] = copy[i++];
        else
            result[idx++] = copy[j++];
    }
}

/*
 * merge sort function base pointers.
 *
 * time complexity : O(n * log n)
 * space complexity: O(n)
 */

void merge_sort_p(void **arr, int n,
                  int(*cmp)(const void *, const void *)) {
    void **copy = NULL;
    copy = (void **)malloc(sizeof(void *) * n);
    if (copy == NULL) {
        fprintf(stderr, "ERROE allocating memory\n");
        return;
    }
    memmove(copy, arr, sizeof(void *) * n);
    m_sort_p(copy, arr, 0, n, cmp);
    free(copy);
}

/*****************************************************************************/
/* shell sort                                                                */
/*****************************************************************************/

/*  
 * generate a gap array for shell sort.
 *
 * @param pointer 'gap' point to an address of gap array, which will be
 * allocated memory in function and should be released by caller.
 */

int gen_gap_p(int **gap, int n){
    int k = 0, gap_val = 1;
    for (int j = 0, i; gap_val <= n / 2;) {
        *gap = realloc(*gap, sizeof(int) * (k + 1));
        if (*gap == NULL) return -1;
        (*gap)[k++] = gap_val;
        int i = ++j / 2;
        if (j % 2 == 0)
            gap_val = 9 * pow(4, i) - 9 * pow(2, i) + 1;
        else
            gap_val = pow(2, i + 2) * (pow(2, i + 2) - 3) + 1;
    }
    return k; 
}

/*
 * shell sort function base pointers.
 *
 * best case   :   O(n * log n)
 * worst case  :   O(n * (log ^ 2 (n)))
 * average case:   O(n) ~ O(n ^ 2)
 */

void shell_sort_p(void **arr, int n,
                  int(*cmp)(const void *, const void *)) {

    int k = 0, *gap = NULL;
    k = gen_gap_p(&gap, n);
    if (k < 0) {
        fprintf(stderr, "ERROE allocating memory\n");
        return;
    }
    for (int t = k - 1; t >= 0; t--) {
        int inc = gap[t];
        for (int i = inc, j; i < n; i++) {
            void *temp = arr[i];
            for (j = i - inc; j >= 0 && cmp(arr[j], temp) > 0; j -= inc)
                arr[j + inc] = arr[j];
            arr[j + inc] = temp;
        }
    }
    free(gap);
}

/*****************************************************************************/
/* bubble sort                                                               */
/*****************************************************************************/

/*
 * bubble sort function base pointers.
 *
 * best case   :   O(n)
 * worst case  :   O(n ^ 2)
 * average case:   O(n ^ 2)
 */

void bubble_sort_p(void **arr, int n,
                   int(*cmp)(const void *, const void *)) {
    int flag = 1;
    for (int i = 0; flag && i < n - 1; i++) {
        flag = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (cmp(arr[j], arr[j + 1]) > 0) {
                SWAP_PTR(arr[j], arr[j + 1]);
                flag = 1;
            }
        }
    }
}

/*****************************************************************************/
/* BFPRT                                                                     */
/*****************************************************************************/

/*
 * select pivot that is median of median.
 *
 * 1. partition set into multiple groups, every group has 5 elements.
 * 2. select medians of every group, make them form a new set.
 * 3. 1. ~ 2. ~ 1. ~ 2. ~
 *
 * @return index of pivot.
 */

int BFPRT_p_idx_p(void **arr, int begin, int end,
                  int(*cmp)(const void *, const void *)) {
    if (end - begin < 5) {
        insert_sort_p(arr, end - begin, cmp);
        return begin + ((end - begin + 1) >> 1) - 1;
    }
    int left_idx = begin;
    for (int i = begin, med_idx; i + 4 < end; i += 5) {
        insert_sort_p(arr + i, 5, cmp);
        med_idx = i + ((5 + 1) >> 1) - 1;
        SWAP_PTR(arr[left_idx], arr[med_idx]);
        left_idx++;
    }
    return BFPRT_k_idx_p(arr, begin, left_idx, 
                         (left_idx - begin + 1) >> 1, cmp);
}

/*
 * partition elements depending on pivot index;
 *
 * some keys less than pivot key and their indexes less than pivot index.
 * other keys more than pivot key and their indexes more than pivot index.
 *
 * @return index of pivot key after partitioning.
 */

int partition_p(void **arr, int begin,
                int end, int pivot_idx,
                int(*cmp)(const void *, const void *)) {
    int left_idx = begin;
    SWAP_PTR(arr[pivot_idx], arr[end - 1]);
    for (int i = begin; i < end - 1; i++) {
        if (cmp(arr[i], arr[end - 1]) < 0) {
            SWAP_PTR(arr[i], arr[left_idx]);
            left_idx++;
        }
    }
    SWAP_PTR(arr[left_idx], arr[end - 1]);
    return left_idx;
}

/*
 * select index of the k-th smallest element using BFPRT algorithm.
 *
 * worst case  : O(n)
 */

int BFPRT_k_idx_p(void **arr, int begin,
                  int end, int k,
                  int(*cmp)(const void *, const void *)) {
    if (end - begin < 2) return begin;
    int pivot_idx = BFPRT_p_idx_p(arr, begin, end, cmp);
    int ptn_idx = partition_p(arr, begin, end, pivot_idx, cmp);
    int num = ptn_idx - begin + 1;
    if (k == num) 
        return ptn_idx;
    else if (k < num)
        return BFPRT_k_idx_p(arr, begin, ptn_idx, k, cmp);
    else
        return BFPRT_k_idx_p(arr, ptn_idx + 1, end, k - num, cmp);
}

