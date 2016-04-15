#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msort.h"
#include "common.h"


enum Boolean read_data(const char *const file_name, int **const data, int *const size)
{
    FILE* input_file = fopen(file_name, "r");
    if (!input_file)
        return process_error(INVALIDFILE);

    char num[10];
    fscanf(input_file, "%s", num);
    *size = atoi(num);

    if (*size < 0 || *size > MAX_SIZE)
        return process_error(INVALIDSIZE);

    *data = (int*)malloc(*size * sizeof(int));
    
    int offset = strlen(num) + 1;
    fseek(input_file, offset, SEEK_SET);

    int index = 0;
    while(index < *size) {
        memset(num, 0, sizeof(num));
        fscanf(input_file, "%s", num);
        offset += strlen(num) + 1;
        fseek(input_file, offset, SEEK_SET);
        (*data)[index] = atoi(num);
        ++index;
    }

    fclose(input_file);

    return TRUE;
}

enum Boolean write_data(const char *const file_name, const int *const data, const int size)
{
    FILE* output_file = fopen(file_name, "w");
    if (!output_file)
        return process_error(INVALIDFILE);

    int index = 0;
    while (index < size) {
        fprintf(output_file, "%d\n", data[index++]);
    }

    return TRUE;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        return process_error(INVALIDARGUMENTS);

    int* data = NULL;
    int size = 0;

    if (!read_data(argv[1], &data, &size))
        return process_error(READING);

    //printf("read successfully\n");

    merge_sort(data, size);
    //printf("sorted successfully\n");

    if (!write_data(argv[2], data, size))
        return process_error(WRITING);
    
    //printf("wrote successfully\n");

    return 0;
}

