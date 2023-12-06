#include <stdio.h>
#include <stdlib.h>

void print_arr(char* arr, unsigned arr_size) {

	for (int i=0;i<arr_size;++i) {
		printf("%u ",(unsigned char)arr[i]);
	}
	printf("\n");

}

int main() {
	unsigned arr_size, arr_pos, full, shift;
	char *arr;

	if (scanf("%u", &arr_size) != 1 ||  arr_size == 0) abort();
	arr = malloc(arr_size);
	for (int i = 0; i < arr_size; ++i) {
		unsigned tmp = 0;
		scanf("%u", &tmp);
		arr[i] = tmp;
	}


	if (scanf("%u", &arr_pos) != 1) abort();
	
	if (arr_pos < arr_size*8) {
		full = arr_pos / 8;
		shift = arr_pos % 8;
		arr[full] = arr[full] ^ (1u << shift);
	}
	
	print_arr(arr, arr_size);

	free(arr);
}
