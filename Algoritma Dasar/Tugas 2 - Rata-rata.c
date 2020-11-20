#include <stdio.h>
int x, i=0, a, jumlah=0;
float rerata;
main()
{  
	printf("Masukkan banyaknya nilai : ");
	scanf("%d", &a);
	if (a==0)
	{
		printf("Tidak ada nilai yang dimasukkan");
	}	
	else
	{
		while(i!=a)
		{
			i=i+1;
			printf("Masukkan nilai : ");
			scanf("%d", &x);
			jumlah=jumlah+x;
		}
		rerata = jumlah/(float)a;
		printf("Nilai rata-ratanya adalah = %0.2f", rerata);
	}
}
