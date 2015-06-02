#include <stdio.h>
unsigned char arry[1024*1024*3];


unsigned char   charToIn(char arg)
{
	if(arg > 0 )
}

int main()
{
	
	int dataLen = 0;
	
	FILE * file = fopen("file", "rw");
	char data;
	if(file == NULL)
	{
		printf("file open error\n");
	}
	
	while((data = getc(file)) != EOF)
	{
		char temp;
	//	printf("%c",data);	
		if((data < '10') && (data > '0'))
		{
			temp = getc(file);
			if(temp )
			
		}				
	}

	
//	fgetc(file);
//	printf("The second and first is i %c %c", getc(file), getc(file)); 

}
