#include <stdio.h>
#include <stdlib.h>

void print_bp(int value) {
	int min, max;
	min = max = -1;

	if(value == 0) {
		printf("-1\n");
		return;
	}

	for(unsigned x = 0; x < sizeof(int)*8; ++x) {
		if ((value >> x) & 1) {
			if (min == -1) min = x;	
			max = x;
		}
	}
	printf("%d %d\n", max, min);
}

int main() {
	int in_value;
	if (scanf("%d", &in_value) != 1) {
		abort();
	}
	print_bp(in_value);
}
