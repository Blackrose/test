#include <stdio.h>
typedef struct {
	int a;
	char b;
	int c;
}data_t;

data_t testdata;
int main(int argc, char *argv[])
{
	data_t* p = &testdata;	
	void* pvoid = &testdata;
	printf("The len of data_t %d  \n", sizeof(data_t));
	printf("The p is  0x%d \n", p);
	printf("The p + 1 is 0x%d \n", p + 1);

	printf("The pvoid is  0x%d \n", pvoid);
	printf("The pvoid + 1 is 0x%d \n", pvoid + 1);

	
}
