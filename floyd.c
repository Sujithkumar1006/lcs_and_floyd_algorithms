#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This method is to print the shortes path from each vertices
void print_path(int outer_index, int inner_index, int size, int pred[size][size], FILE *output_file)
{
    if (outer_index == inner_index)
    {
        fprintf(output_file, "V%d ", outer_index + 1);
        printf("V%d ", outer_index + 1);
        return; // Terminate recursion
    }

    int next_index = pred[outer_index][inner_index];

    if (next_index != 0)
    {
        print_path(outer_index, next_index - 1, size, pred, output_file);
        print_path(next_index - 1, inner_index, size, pred, output_file);
    }
    else
    {
        fprintf(output_file, "V%d ", inner_index + 1);
        printf("V%d ", inner_index + 1);
    }
}

// Method to Print PMatrix
void print_pmatrix(int p_size, int dist_pointer[p_size][p_size], int problem_number, FILE *output_file)
{
    printf("Problem%d: n = %d\n", problem_number, p_size);
    fprintf(output_file, "Problem%d: n = %d\n", problem_number, p_size);
    printf("Pmatrix: \n");
    fprintf(output_file, "Pmatrix: \n");
    // Print the shortest path lengths along with their corresponding vertices
    for (int row = 0; row < p_size; row++)
    {
        for (int column = 0; column < p_size; column++)
        {
            printf("%d ", dist_pointer[row][column]);
            fprintf(output_file, "%d  ", dist_pointer[row][column]);
        }
        printf("\n");
        fprintf(output_file, "\n");
    }
    printf("\n");
    fprintf(output_file, "\n");
}

// Method to free 2d Array
void free_heap(int **two_d_ptr, int size)
{
    for (int index = 0; index < size; index++)
    {
        free(two_d_ptr[index]);
    }
    free(two_d_ptr);
}

void compute_distance(int problem_number, int size, int **graph, FILE *output_file)
{
    int dist_pointer[size][size];
    memset(dist_pointer, 0, sizeof(dist_pointer));
    int dist[size][size];
    for (int index = 0; index < size; index++)
    {
        memcpy(dist[index], graph[index], size * sizeof(int));
    }
    for (int vertices_index = 0; vertices_index < size; vertices_index++)
    {
        for (int outer_index = 0; outer_index < size; outer_index++)
        {
            for (int inner_index = 0; inner_index < size; inner_index++)
            {
                if (dist[outer_index][inner_index] > (dist[outer_index][vertices_index] + dist[vertices_index][inner_index]))
                {
                    dist[outer_index][inner_index] = dist[outer_index][vertices_index] + dist[vertices_index][inner_index];
                    dist_pointer[outer_index][inner_index] = vertices_index + 1;
                }
            }
        }
    }
    print_pmatrix(size, dist_pointer, problem_number, output_file);

    for (int outer_index = 0; outer_index < size; outer_index++)
    {
        fprintf(output_file, "V%d-Vj:shortest path and length\n", outer_index + 1);
        for (int inner_index = 0; inner_index < size; inner_index++)
        {
            fprintf(output_file, "V%d ", outer_index + 1);
            printf("V%d ", outer_index + 1);
            print_path(outer_index, inner_index, size, dist_pointer, output_file);
            fprintf(output_file, ": %d\n", dist[outer_index][inner_index]);
            printf(": %d\n", dist[outer_index][inner_index]);
        }
        fprintf(output_file, "\n");
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        printf("Usage: ./floyd <input-graph-file>\n");
        return 0;
    }
    FILE *file, *output_file;
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    output_file = fopen("output.txt", "w");
    while (!feof(file))
    {
        int problem_number, size;
        char line[500];
        if (fgets(line, sizeof(line), file) == NULL)
        {
            break;
        }
        if (strstr(line, "Problem") && strstr(line, "Amatrix"))
        {
            if (sscanf(line, "Problem%d Amatrix: n = %d", &problem_number, &size) != 2)
            {
                printf("Error parsing line\n");
                fclose(file);
                fclose(output_file);
                return 1;
            }
        }
        else if (strstr(line, "Problem"))
        {
            if (sscanf(line, "Problem%d: n = %d", &problem_number, &size) != 2)
            {
                printf("Error parsing line\n");
                fclose(file);
                fclose(output_file);
                return 1;
            }
        }
        else
        {
            printf("Invalid line format\n");
            fclose(file);
            fclose(output_file);
            return 1;
        }
        printf("Current problem number is %d and size is %d\n", problem_number, size);
        int **graph = (int **)malloc(size * sizeof(int *));
        if (graph == NULL)
        {

            printf("Memory allocation failed\n");
            return 1;
        }
        for (int outer_index = 0; outer_index < size; outer_index++)
        {
            graph[outer_index] = (int *)malloc(size * sizeof(int));
            if (graph[outer_index] == NULL)
            {
                printf("Memory allocation failed\n");
                break;
                return 1;
            }
            for (int inner_index = 0; inner_index < size; inner_index++)
            {
                fscanf(file, "%d", &graph[outer_index][inner_index]);
            }
        }
        compute_distance(problem_number, size, graph, output_file);
        fscanf(file, " ");
        free_heap(graph, size);
    }
    fclose(file);
    fclose(output_file);
    return 0;
}