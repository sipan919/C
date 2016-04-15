#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "msort.h"
#include "common.h"


void* merge_sort_function(void* info)
{
    int* size_and_data = (int*)info;

    const int size = *size_and_data;
    ++size_and_data;

    int *const data = *((int *const*)size_and_data);

    merge_sort(data, size);
}

void merge_sort(int *const data, const int size)
{
    if (!data || size < 2)
        return;

    int mid = size / 2;

    void *info = malloc(sizeof(int*) + sizeof(int));
    memcpy(&size, info, sizeof(int));
    memcpy(&data, info + sizeof(int), sizeof(int*));

    //merge_sort(data, mid);
    pthread_t first_part_thread;
    pthread_create(&first_part_thread, NULL, merge_sort_function, info);

    merge_sort(data + mid, size - mid);

    pthread_join(first_part_thread, NULL);
    merge(data, mid, size - mid);
}

static void merge(int *const data, const int first_size, const int second_size)
{
    const int size_in_bytes = (first_size + second_size) * sizeof(int);
    int* sorted_data = (int*)malloc(size_in_bytes);
    if (!sorted_data) {
        process_error(ALLOCATING);
        return;
    }

    int first_index = 0;
    int second_index = 0;

    while (!(first_index == first_size && second_index == second_size)) {
        if (second_index == second_size ||
           (first_index != first_size && data[first_index] < data[first_size + second_index])) {
            sorted_data[first_index + second_index] = data[first_index];
            ++first_index;
        }
        else {
            sorted_data[first_index + second_index] = data[first_size + second_index];
            ++second_index;
        }
    }

    memcpy(data, sorted_data, size_in_bytes);
}

