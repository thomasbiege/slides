#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <limits.h>

int main(void)
{
	float	f;
	u_long	mant, exp, i;

//#undef FLT_ROUNDS
//#define FLT_ROUNDS 0

	printf("Float Limits:\n");
	printf("\tsizeof(float) : %4d\n", sizeof(float));
	printf("\tFLT_MANT_DIG  : %4d\n", FLT_MANT_DIG);
	printf("\tFLT_DIG       : %4d\n", FLT_DIG);
	printf("\tFLT_MIN       :    %e\n", FLT_MIN);
	printf("\tFLT_MAX       :    %e\n", FLT_MAX);
	printf("\tFLT_MIN_10_EXP: %4d\n", FLT_MIN_10_EXP);
	printf("\tFLT_MAX_10_EXP: %4d\n", FLT_MAX_10_EXP);
	printf("\tFLT_ROUNDS    : %4d\n", FLT_ROUNDS);
	printf("\n");


	// test
	f = 233.8173;
	printf("test: f = %e (0x%08x) -> mantisse = 0x%06x, exponent = 0x%02x\n", f, (long) f, ((long) f & 0xFFFFFF00) >> (32-FLT_MANT_DIG), (u_char)((long) f & 0x000000FF));

	f = pow(2,23) * pow(2,127);
	printf("test: f = %e\n", f);	


	printf("\n");

	// add_1
	f = FLT_MAX+100.0;
	printf("FLT_MAX+100      : %e\t(0x%08x)\t-> %s\n", f, (long) f, (f == FLT_MAX) ? "no overflow" : "overflow!");
	printf("\t\t\t-> mantisse = 0x%06x, exponent = 0x%02x\n", ((long) f >> (32-FLT_MANT_DIG) & 0x00FFFFFF), (long) f & 0x000000FF);

	printf("\n");

	// add_2
	printf("FLT_MAX+i        : ");
	for(i = 0; i < ULONG_MAX; i++)
	{
		f = FLT_MAX + (float) i;
		if(f != FLT_MAX)
		{
			printf("i = %ld, %e\t(0x%08x)\t-> overflow!", i, f, (long) f);
			printf("\t\t\t-> mantisse = 0x%06x, exponent = 0x%02x\n", ((long) f >> (32-FLT_MANT_DIG) & 0x00FFFFFF), (long) f & 0x000000FF);
			break;
		}
	}

	printf("\n");

	// mul
	f = 1.0000001*FLT_MAX;
	printf("FLT_MAX*1.0000001: %e\t\t(0x%08x)\t-> %s\n", f, (long) f, (f == FLT_MAX) ? "no overflow" : "overflow!");
	printf("\t\t\t-> mantisse = 0x%06x, exponent = 0x%02x\n", ((long) f >> (32-FLT_MANT_DIG) & 0x00FFFFFF), (long) f & 0x000000FF);
	
	printf("\n");


	// sub_1
	f = FLT_MIN-100.0;
	printf("FLT_MIN-100      : %e(0x%08x)\t-> %s\n", f, (long) f, (f == FLT_MIN) ? "no overflow" : "overflow!");
	printf("\t\t\t-> mantisse = 0x%06x, exponent = 0x%02x\n", ((long) f >> (32-FLT_MANT_DIG) & 0x00FFFFFF), (long) f & 0x000000FF);

	printf("\n");

	/* sub_2
	printf("FLT_MIN-i        : ");
	for(i = 0; i < ULONG_MAX; i++)
	{
		f = FLT_MIN - (float) i;
		if(f != FLT_MIN)
		{
			printf("i = %ld, %e\t(0x%08x)\t-> overflow!", i, f, (long) f);
			break;
		}
	}
	printf("\n");
	*/

	// div
	f = FLT_MIN/1.0000001;
	printf("FLT_MAX/1.0000001: %e\t(0x%08x)\t-> %s\n", f, (long) f, (f == FLT_MIN) ? "no overflow" : "overflow!");
	printf("\t\t\t-> mantisse = 0x%06x, exponent = 0x%02x\n", ((long) f >> (32-FLT_MANT_DIG) & 0x00FFFFFF), (long) f & 0x000000FF);

	printf("\n");
	return 0;
}

//EOF


