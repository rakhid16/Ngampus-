#include <stdio.h>
int i;
main()
{
	printf("Masukkan nilai : ");
	scanf("%d", &i);
	while (i>=1)
	{
		printf("%d\n", i);
		i--;
	}
	printf("MELUNCUR!");
}
