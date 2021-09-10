# include <stdio.h>

void merge_arrays(const int* arr, int n, int k, int* output)
{
    int index[n];

    for (int i = 0; i < n; i++)
        index[i] = i * k;

    int min, m;
    for (int i = 0; i < n * k; i++)
    {
        min = 98765;

        for (int j = 0; j < n; j++)
            if (arr[index[j]] < min && index[j] < (j + 1) * k)
            {
                min = arr[index[j]];
                m = j;
            }

        output[i] = min;
        index[m]++;
    }
}