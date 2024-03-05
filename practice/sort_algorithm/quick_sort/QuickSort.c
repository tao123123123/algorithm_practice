#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int (*CompareFunction)(const void*, const void*);

void swap(void* a, void* b, size_t size) {
    void* temp = malloc(size);
    if (!temp) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

int partition(void* arr, int low, int high, size_t size, CompareFunction compare) {
    void* pivot = (char*)arr + low * size;
    int i = low + 1;
    int j = high;

    while (true) {
        while (i <= j && compare((char*)arr + i * size, pivot) <= 0) {
            i++;
        }
        while (i <= j && compare((char*)arr + j * size, pivot) >= 0) {
            j--;
        }
        if (i <= j) {
            swap((char*)arr + i * size, (char*)arr + j * size, size);
        } else {
            break;
        }
    }

    swap((char*)arr + low * size, (char*)arr + j * size, size);
    return j;
}

void quickSortHelper(void* arr, int low, int high, size_t size, CompareFunction compare) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, size, compare);
        quickSortHelper(arr, low, pivotIndex - 1, size, compare);
        quickSortHelper(arr, pivotIndex + 1, high, size, compare);
    }
}

void quickSort(void* arr, int size, size_t elementSize, CompareFunction compare) {
    quickSortHelper(arr, 0, size - 1, elementSize, compare);
}

void* selectKthSmallest(void* arr, int size, int k, size_t elementSize, CompareFunction compare) {
    if (k < 0 || k >= size) {
        fprintf(stderr, "Selected element out of bounds\n");
        exit(EXIT_FAILURE);
    }

    int low = 0, high = size - 1;

    while (high > low) {
        int pivotIndex = partition(arr, low, high, elementSize, compare);

        if (pivotIndex > k) {
            high = pivotIndex - 1;
        } else if (pivotIndex < k) {
            low = pivotIndex + 1;
        } else {
            return (char*)arr + pivotIndex * elementSize;
        }
    }

    return (char*)arr + low * elementSize;
}


int compareIntAscending(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int compareDoubleAscending(const void* a, const void* b) {
    return (*(double*)a - *(double*)b) > 0 ? 1 : (*(double*)a - *(double*)b) < 0 ? -1 : 0;
}

int compareCharAscending(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

int compareStringAscending(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

bool isSorted(void* arr, int size, size_t elementSize, CompareFunction compare) {
    for (int i = 1; i < size; i++) {
        if (compare((char*)arr + i * elementSize, (char*)arr + (i - 1) * elementSize) < 0) {
            return false;
        }
    }
    return true;
}

void printArray(void* arr, int size, size_t elementSize, CompareFunction compare) {
    for (int i = 0; i < size; i++) {
        if (compare == compareIntAscending) {
            printf("%d ", *(int*)((char*)arr + i * elementSize));
        } else if (compare == compareDoubleAscending) {
            printf("%lf ", *(double*)((char*)arr + i * elementSize));
        } else if (compare == compareCharAscending) {
            printf("%c ", *(char*)((char*)arr + i * elementSize));
        } else if (compare == compareStringAscending) {
            printf("%s ", *(char**)((char*)arr + i * elementSize));
        }
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <data_type: int, double, char, or string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error: Could not open the file.\n");
        return EXIT_FAILURE;
    }

    int dataType;
    if (strcmp(argv[2], "int") == 0) {
        dataType = 0;
    } else if (strcmp(argv[2], "double") == 0) {
        dataType = 1;
    } else if (strcmp(argv[2], "char") == 0) {
        dataType = 2;
    } else if (strcmp(argv[2], "string") == 0) {
        dataType = 3;
    } else {
        fprintf(stderr, "Error: Unsupported data type. Please use 'int', 'double', 'char', or 'string'.\n");
        return EXIT_FAILURE;
    }

    // Count the number of elements in the file
    int size = 0;
    if (dataType == 0) {
        int value;
        while (fscanf(inputFile, "%d", &value) == 1) {
            size++;
        }
    } else if (dataType == 1) {
        double value;
        while (fscanf(inputFile, "%lf", &value) == 1) {
            size++;
        }
    } else if (dataType == 2) {
        char value;
        while (fscanf(inputFile, " %c", &value) == 1) {
            size++;
        }
    } else if (dataType == 3) {
        char buffer[256]; // Assuming a reasonable maximum length for strings
        while (fscanf(inputFile, "%255s", buffer) == 1) {
            size++;
        }
    }

    // Close and reopen the file to reset the file pointer
    fclose(inputFile);
    inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        fprintf(stderr, "Error: Could not open the file.\n");
        return EXIT_FAILURE;
    }

    // Read elements from the file into an array
    void* arr;
    if (dataType == 0) {
        arr = malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            fscanf(inputFile, "%d", (int*)((char*)arr + i * sizeof(int)));
        }
    } else if (dataType == 1) {
        arr = malloc(size * sizeof(double));
        for (int i = 0; i < size; i++) {
            fscanf(inputFile, "%lf", (double*)((char*)arr + i * sizeof(double)));
        }
    } else if (dataType == 2) {
        arr = malloc(size * sizeof(char));
        for (int i = 0; i < size; i++) {
            fscanf(inputFile, " %c", (char*)((char*)arr + i * sizeof(char)));
        }
    } else if (dataType == 3) {
        arr = malloc(size * sizeof(char*));
        for (int i = 0; i < size; i++) {
            char buffer[256]; // Assuming a reasonable maximum length for strings
            fscanf(inputFile, "%255s", buffer);
            ((char**)arr)[i] = strdup(buffer);
        }
    }

    fclose(inputFile);
    // Print the array
    printf("Original Array: ");
    if (dataType == 0) {
    	printArray(arr, size, sizeof(int), compareIntAscending); 
    } else if (dataType == 1) {
    	printArray(arr, size, sizeof(double), compareDoubleAscending);
    } else if (dataType == 2) {
    	printArray(arr, size, sizeof(char), compareCharAscending);
    } else if (dataType == 3) {
    printArray(arr, size, sizeof(char*), compareStringAscending);
}

    
    // Sort the array
    if (dataType == 0) {
        quickSort(arr, size, sizeof(int), compareIntAscending);
    } else if (dataType == 1) {
        quickSort(arr, size, sizeof(double), compareDoubleAscending);
    } else if (dataType == 2) {
        quickSort(arr, size, sizeof(char), compareCharAscending);
    } else if (dataType == 3) {
        quickSort(arr, size, sizeof(char*), compareStringAscending);
    }

    // Display the sorted array
    printf("Sorted Array: ");
    if (dataType == 0) {
        printArray(arr, size, sizeof(int), compareIntAscending);
    } else if (dataType == 1) {
        printArray(arr, size, sizeof(double), compareDoubleAscending);
    } else if (dataType == 2) {
        printArray(arr, size, sizeof(char), compareCharAscending);
    } else if (dataType == 3) {
        printArray(arr, size, sizeof(char*), compareStringAscending);
    }

    // Display results again using select
    printf("\n");
    for (int i = 0; i < size; i++) {
        void* ith;
        if (dataType == 0) {
            ith = selectKthSmallest(arr, size, i, sizeof(int), compareIntAscending);
            printf("Selected element at index %d: %d\n", i, *(int*)ith);
        } else if (dataType == 1) {
            ith = selectKthSmallest(arr, size, i, sizeof(double), compareDoubleAscending);
            printf("Selected element at index %d: %lf\n", i, *(double*)ith);
        } else if (dataType == 2) {
            ith = selectKthSmallest(arr, size, i, sizeof(char), compareCharAscending);
            printf("Selected element at index %d: %c\n", i, *(char*)ith);
        } else if (dataType == 3) {
            ith = selectKthSmallest(arr, size, i, sizeof(char*), compareStringAscending);
            printf("Selected element at index %d: %s\n", i, *(char**)ith);
        }
    }

    // Free allocated memory
    if (dataType == 3) {
        for (int i = 0; i < size; i++) {
            free(((char**)arr)[i]);
        }
    }
    free(arr);

    return EXIT_SUCCESS;
}

