#include <stdio.h>

void count_system(unsigned x, unsigned y) {
	unsigned k, i = 0;
	unsigned result[32] = {0};
	while(x != 0) {
		k = x % y;
		x = x / y;
		result[i] = k;
		i++;
	}

	for(int j=i-1; j>=0; j--) {
		printf("%u", result[j]);
	}
	printf("\n");

}

int main() {
	unsigned x, y;
	scanf("%u%u", &x, &y);
	count_system(x, y);
}
