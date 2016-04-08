/*
 ============================================================================
 Name        : Robert H Conner II
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Matrix_RC.c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 3
#define K 2
#define N 3

int a[M] [K] = { {1,4}, {2,5}, {3,6}};
int b[K] [N] = { {8, 7, 6}, {5,4,3}};
int c[M] [N];

struct matrix_index
{
	int i, j;

};

void *matrix_thread(void *param)
{
	struct matrix_index values = *(struct matrix_index *) param;

	int i=values.i;
	int j=values.j;

	c[i][j] = (a[i][0] * b[0][j] + (a[i][1] *b[1][j]));
}

int main(int argc, char *argv[])
{
	int i,j;

		for(i=0; i<M; i++)
			for(j =0; j<M; j++)
			{
				struct matrix_index *m;
				m = (struct matrix_index* ) malloc(sizeof(struct matrix_index));
				m->i = i;
				m->j = j;

				pthread_t tid;
				pthread_attr_t attr;
				pthread_attr_init(&attr);
				pthread_create(&tid, &attr, matrix_thread, m);
				pthread_join(tid, NULL);

			}

			printf("\nResult of matrix multiplication\n");

			for(i =0; i < M; i++)
			{
				for(j=0; j<N; j++)
				{
					printf("%d\t", c[i][j]);
				}

				printf("\n");
			}

			return 0;


}
