#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long encode(char *s)
{
    long a, b, c, x;
    a = s[0];
    b = s[1];
    c = s[2];
    x = ((((a * 69) + c) * 137) + b) * 39;
    x = x % 54321;
    return x;
}

int main()
{
    char s[4];
    long x, y;
    int i, j, k;

    printf("Enter the code: ");
    scanf("%ld", &x);

    s[3] = '\0';

#pragma omp parallel num_threads(16) private(i, j, k, y)
    {
#pragma omp for collapse(3)
        for (i = 0; i < 26; i++)
        {
            for (j = 0; j < 26; j++)
            {
                for (k = 0; k < 26; k++)
                {
                    s[0] = i + 'a';
                    s[1] = j + 'a';
                    s[2] = k + 'a';
                    y = encode(s);
                    if (x == y)
                    {
                        printf("The letters for code %ld are %s\n", y, s);
#pragma omp cancel for
                    }
                }
            }
        }
    }

    return 0;
}
