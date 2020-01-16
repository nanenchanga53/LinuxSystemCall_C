#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

int main () 
{ 
	char *ptr;
	ptr = (char *) malloc(10);
	char *ptr_dest;
        ptr_dest = (char *) malloc(sizeof(char) * 10);

	ptr[0] = '1';
        ptr[1] = '2';
        *(ptr+2) = '3';
        *(ptr+3) = '4';
        ptr[4] = '5';
        ptr[5] = '6';
        ptr[6] = '7';
        ptr[7] = '8';
        ptr[8] = '9';
        ptr[9] = '\0';

	printf("ptr = 0x%08x / 0x%08x\n", &ptr, &ptr[0]);

	printf("#1 ori = %s (%d)\n\n\n", ptr, strlen(ptr));

	printf("mem addr = 0x%08x / 0x%08x\n", &ptr, &ptr[0]);
	printf("rtn= 0x%08x\n", memset(ptr+5,'-',2));
	printf("#2 set = %s (%d)\n\n\n", ptr, strlen(ptr));

	memmove(ptr_dest, ptr, 10);

	printf("mem addr = 0x%08x / 0x%08x\n", &ptr_dest, &ptr_dest[0]);
	printf("#5 mov = %s (%d)\n\n", ptr_dest, strlen(ptr_dest));

	printf("#6 ori = %s (%d)\n\n\n", ptr, strlen(ptr));

	memcpy( ptr + 1, ptr, 10); // 오류는 발생하지 않지만 반드시 구분해서 사용

	printf("mem addr = 0x%08x / 0x%08x\n", &ptr, &ptr[0]);
	printf("#3 cpy = %s (%d)\n\n\n", ptr, strlen(ptr));

	printf("#4 ori = %s (%d)\n\n\n", ptr, strlen(ptr));

	return 0; 
}
