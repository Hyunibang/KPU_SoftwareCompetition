#include        <stdio.h>

#define N       12

int
main(void)
{
        static int a[] = {80,41,35,90,40,20,25,95,10,50,60,70};
        int min, s, t, i, j;

        printf("input data:  ");
        for(i=0; i<N; i++)
                printf("%d ", a[i]);
        printf("\n");
        for(i=1; i<N-1;i++) {
                min = a[i]; s = i;
                for(j=i+1;j<N-1;j++) {
                        if(a[j] < min) {
                                min = a[j];
                                s = j;
                        }
                }
                t = a[i];
                a[i] = a[s];
                a[s] = t;
        }

        printf("sorted data: ");
        for(i=0; i<N; i++)
                printf("%d ", a[i]);

        printf("\n");
}
