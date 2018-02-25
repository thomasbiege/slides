#include <stdio.h>
#include <sys/types.h>

long longGetValueFromUser(void);
void voidCheckValue(u_int val);

int main(void)
{
	char Buffer[1024];
	short shortUserSize;
	short shortBufferSize = sizeof(Buffer);

	shortUserSize = longGetValueFromUser();

	printf("short value = %ld\n", shortUserSize);

	if(shortUserSize > shortBufferSize)
	{
		fprintf(stderr, "Buffer too small!\n");
		exit(-1);
	}

	voidCheckValue(shortBufferSize);

	exit(0);
}

long longGetValueFromUser(void)
{
	long val;

	printf("gimmie cookies: ");
	scanf("%ld", &val);

	printf("long value = %ld\n", val);

	return(val);
}

void voidCheckValue(size_t val)
{
	printf("size_t value = %ld\n", val);
}
