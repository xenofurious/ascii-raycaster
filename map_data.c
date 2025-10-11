#include <stdlib.h>
#include <stdio.h>

#include "map_data.h"

map_object** malloc_map(int rows, int cols) {
    map_object** arr;
    arr = (map_object**)malloc(rows * sizeof(map_object*)); 
    for (int i = 0; i < rows; i++)
        arr[i] = (map_object*)malloc(cols * sizeof(map_object));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = empty; 
        }
    }
    return arr;
}

struct file_parse_return init_map(char *filename) {
    FILE *fp = fopen(filename, "r");
    
    // first pass reads the header file. this is of the form "int row, int col"
    int rows, cols;
    fscanf(fp, "%d%d", &rows, &cols);
    printf("\nno of rows: %d, no of cols = %d\n\n", rows, cols);
    
    map_object **map_ptr = malloc_map(rows, cols);

    // second pass reads the rest of the map data and then writes it to the malloc'ed array
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            fscanf(fp, "%d", &map_ptr[i][j]);
        }
    }

    fclose(fp);
    return (struct file_parse_return) {map_ptr, rows, cols};
}

void deinit_map(map_object** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]); 
    }
    free(arr); 
}
