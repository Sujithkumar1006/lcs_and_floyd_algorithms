#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        printf("Usage: ./lcs <string1> <string2>\n");
        return 0;
    }

    int str1_length = strlen(argv[1]);
    int str2_length = strlen(argv[2]);
    int matrix[str1_length + 1][str2_length + 1];

    for (int str1_index_1 = 0; str1_index_1 <= str1_length; str1_index_1++)
        matrix[str1_index_1][0] = 0;
    for (int str2_index = 0; str2_index <= str2_length; str2_index++)
        matrix[0][str2_index] = 0;

    for (int str1_index = 1; str1_index <= str1_length; str1_index++)
    {
        for (int str2_index = 1; str2_index <= str2_length; str2_index++)
        {

            if (argv[1][str1_index - 1] == argv[2][str2_index - 1])
            {
                matrix[str1_index][str2_index] = matrix[str1_index - 1][str2_index - 1] + 1;
            }
            else if (matrix[str1_index - 1][str2_index] >= matrix[str1_index][str2_index - 1])
            {
                matrix[str1_index][str2_index] = matrix[str1_index - 1][str2_index];
            }
            else
            {
                matrix[str1_index][str2_index] = matrix[str1_index][str2_index - 1];
            }
        }
    }
    printf("Length of LCS: %d\n", matrix[str1_length][str2_length]);

    int index = matrix[str1_length][str2_length];
    char lcs[index];
    lcs[index] = '\0';

    int temp_s1_len = str1_length, temp_s2_len = str2_length;
    while (temp_s1_len > 0 && temp_s2_len > 0)
    {

        if (argv[1][temp_s1_len - 1] == argv[2][temp_s2_len - 1])
        {
            lcs[index - 1] = argv[1][temp_s1_len - 1];
            temp_s1_len--;
            temp_s2_len--;
            index--;
        }
        else if (matrix[temp_s1_len - 1][temp_s2_len] > matrix[temp_s1_len][temp_s2_len - 1])
            temp_s1_len--;
        else
            temp_s2_len--;
    }
    printf("LCS: %s\n",lcs);
    return 0;
}