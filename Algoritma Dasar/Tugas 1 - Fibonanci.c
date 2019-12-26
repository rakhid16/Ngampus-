#include <stdio.h>
main()
{ 	int i=2, nilai, a=0,b=1,f=0;
	printf("Masukkan jumlah perulangan bilangan fibonansi ");
	scanf("%d", &nilai);
	printf("%d %d", a, b);
	while (i<nilai)
	{
		f=a+b;
		a=b;
		b=f;
		++i;
		printf(" %d",f);
	}
}
