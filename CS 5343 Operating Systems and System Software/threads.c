#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int n;
int t;
int* P;

void* eliminateMultiples(void* param) {
	int factor = *((int *) param);
	for (int i = 2 * factor; i < n; i += factor) {
		P[i] = 0;
	}
	free(param);
}

int main() {
	printf("Value of n: ");
	scanf("%d", &n);

	P = malloc(n * sizeof(*P));
	for (int i = 0; i < n; i++) {
		P[i] = 1;
	}

	printf("Number of threads: ");
	scanf("%d", &t);

	pthread_t tid[t];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for (int i = 0; i < t; i++) {
		int* factor = (int*)malloc(sizeof(int));
		*factor = i + 2;
		pthread_create(&(tid[i]), &attr, eliminateMultiples, (void*)(factor));
	}

	for (int i = t; i > 0; i--) {
		pthread_join(tid[i - 1], NULL);
	}

	for (int i = 2; i < n; i++) {
		if (P[i]) {
			printf("%d\n", i);
		}
	}

	free(P);

	return 0;
}