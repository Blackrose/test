#include <stdio.h>
unsigned char arry[1024*1024*3];
int dataLen = 0;

char charToIn(char arg, unsigned char* result)
{
    char res = 1;
	if((arg >= '0') && (arg <= '9') )
	{
        *result =  arg - '0';
	}
	else if((arg >= 'A')  && (arg <= 'F'))
	{
	    *result = arg - 'A' + 10; 

	}
	else if((arg >= 'a') && (arg <= 'f'))
	{
	    *result = arg - 'a' + 10;

	}
	else 
	{
	    res = 0;
	}
	return res;
	
}

int main(int argc, char *argv[])
{
	
	if(argc != 2)
	{
	    printf("please input the filename\n");
	    return -1;
	}
	FILE * file = fopen(argv[1], "rw");
	FILE * fileOutTxt = fopen("fileOutTxt", "w");
	FILE * fileOutBin = fopen("fileOutBin", "w");
	char data;
	if(file == NULL)
	{
		printf("file open error\n");
		return -1;
	}
	
	while((data = getc(file)) != EOF)
	{
	    char dataH = 0;
	    char dataL = 0;
		char temp = 0;
		if(charToIn(data, &dataH))
		{
		    if((temp = getc(file)) != EOF)
		    {
		        if(charToIn(temp, &dataL))
		        {
		            arry[dataLen ++ ] = (dataH << 4) + (dataL);
		            //printf("%d", arry[dataLen]);
		        }
		    }
		    else
		    {
		        break;
		    }
    	}
	
	}
	int i;
	int j;
	printf("\n");
	for(i = 0; i < dataLen; i++)
	{
        fprintf(fileOutTxt,"%02X ", arry[i]);
        if(((i + 1)% 17))
        {
        
        }
        else
        {
            fprintf(fileOutTxt,"\n");
        }
        
	}
	printf("datalen %d\n", dataLen);
	for(i = 0; i < dataLen;)
	{
	    if((arry[i] == 0x4e) && (arry[i + 1] == 0x00) && (arry[i + 2] == 0x30))
	    {
	        if((i+3 + 30) < dataLen)
	        {
	            fwrite(&arry[i + 3], sizeof(arry[0]), 0x30, fileOutBin);
	            i = i + 51;
	        }
	        else
	        {
	            printf("=---The Fram len is not enough\n");
	            break;
	        }
	    }
	    else
	    {
	        printf("----------> error the fram is error\n");
	        break;
	    }
	    
	}
	
//	fgetc(file);
//	printf("The second and first is i %c %c", getc(file), getc(file)); 

}
