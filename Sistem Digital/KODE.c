#include <stdio.h>
int p,q,a,HasilAkhir,sisa, pilih;

IfHasilAkhir()
{	
	if (HasilAkhir==0)	printf("abcdef "); 
	if (HasilAkhir==1)	printf("bc ");
	if (HasilAkhir==2)	printf("abdeg ");
	if (HasilAkhir==3)	printf("abcdg ");
	if (HasilAkhir==4)	printf("bcfg ");
	if (HasilAkhir==5)	printf("acdfg ");
	if (HasilAkhir==6)	printf("acdefg ");
	if (HasilAkhir==7)	printf("abc ");
	if (HasilAkhir==8)	printf("abcdefg ");
	if (HasilAkhir==9)	printf("abcdfg ");
}

IfMinus()
{
	if (sisa >-10 && sisa <0)
	{
		sisa=sisa*-1;
		printf("g ");
		HasilAkhir=sisa;
		IfHasilAkhir();
	}
		if (sisa >-100 && sisa <=- 10)
		{
			sisa=sisa*-1;
			printf("g ");
			HasilAkhir=sisa/10;
			IfHasilAkhir();
			HasilAkhir=sisa%10;		
			IfHasilAkhir();
		}
			if (sisa >-1000 && sisa <=- 100)
			{
				sisa=sisa*-1;
				printf("g ");
				HasilAkhir=sisa/100;
				IfHasilAkhir();
				HasilAkhir=sisa%100;
				HasilAkhir=HasilAkhir/10;
				IfHasilAkhir();
				HasilAkhir=sisa%10;		
				IfHasilAkhir();
			}
			if(sisa >-10000 && sisa <=- 1000)				{ sisa=sisa*-1; printf("g "); IfSisa6(); }		
			if(sisa >-100000 && sisa <=- 10000)				{ sisa=sisa*-1; printf("g "); IfSisa5(); }
			if(sisa >-1000000 && sisa <=- 100000)			{ sisa=sisa*-1; printf("g "); IfSisa4(); }
			if(sisa >-10000000 && sisa <=- 1000000)			{ sisa=sisa*-1; printf("g "); IfSisa3(); }
			if(sisa >-100000000 && sisa <=- 10000000)		{ sisa=sisa*-1; printf("g "); IfSisa2(); }
			if(sisa >-1000000000 && sisa <=- 100000000)		{ sisa=sisa*-1; printf("g "); IfSisa1(); }
			if(sisa >-10000000000 && sisa <=- 100000000)	{ sisa=sisa*-1; printf("g "); IfSisa();  }
}

IfSisa()
{	int n=100000000;
	HasilAkhir=sisa/1000000000;
	IfHasilAkhir();
	HasilAkhir=sisa%1000000000;
	while (n!=0)
	{
	HasilAkhir=HasilAkhir/n;
	IfHasilAkhir();
	HasilAkhir=sisa%n;
	n=n/10;
	}
}

IfSisa1()
{
	int n=10000000;
	HasilAkhir=sisa/100000000;
	IfHasilAkhir();
	HasilAkhir=sisa%100000000;
	while (n!=0)
	{
	HasilAkhir=HasilAkhir/n;
	IfHasilAkhir();
	HasilAkhir=sisa%n;
	n=n/10;
	}
}

IfSisa2()
{
	int n=1000000;
	HasilAkhir=sisa/10000000;
	IfHasilAkhir();
	HasilAkhir=sisa%10000000;
	while (n!=0)
	{
	HasilAkhir=HasilAkhir/n;
	IfHasilAkhir();
	HasilAkhir=sisa%n;
	n=n/10;
	}	
}

IfSisa3()
{
	int n=100000;
	HasilAkhir=sisa/1000000;
	IfHasilAkhir();
	HasilAkhir=sisa%1000000;
	while (n!=0)
	{
	HasilAkhir=HasilAkhir/n;
	IfHasilAkhir();
	HasilAkhir=sisa%n;
	n=n/10;
	}
}

IfSisa4()
{
	int n=10000;
	HasilAkhir=sisa/100000;
	IfHasilAkhir();
	HasilAkhir=sisa%100000;
	while (n!=0)
	{
	HasilAkhir=HasilAkhir/n;
	IfHasilAkhir();
	HasilAkhir=sisa%n;
	n=n/10;
	}
}

IfSisa5()
{
	int n=1000;
	HasilAkhir=sisa/10000;
	IfHasilAkhir();
	HasilAkhir=sisa%10000;
	while (n!=0)
	{
	HasilAkhir=HasilAkhir/n;
	IfHasilAkhir();
	HasilAkhir=sisa%n;
	n=n/10;
	}
}

IfSisa6()
{
	HasilAkhir=sisa/1000;
	IfHasilAkhir();
	HasilAkhir=sisa%1000;
	HasilAkhir=HasilAkhir/100;
	IfHasilAkhir();
	HasilAkhir=sisa%100;
	HasilAkhir=HasilAkhir/10;
	IfHasilAkhir();;
	HasilAkhir=sisa%10;
	IfHasilAkhir();
}

IfFinal()
{
	if (sisa <10)
	{
		HasilAkhir=sisa;
		IfHasilAkhir();
	}
		if (sisa >= 10 && sisa < 100)
		{
			HasilAkhir=sisa/10;
			IfHasilAkhir();
			HasilAkhir=sisa%10;		
			IfHasilAkhir();
		}
			if (sisa >=100 && sisa<1000)
			{
				HasilAkhir=sisa/100;
				IfHasilAkhir();
				HasilAkhir=sisa%100;
				HasilAkhir=HasilAkhir/10;
				IfHasilAkhir();
				HasilAkhir=sisa%10;		
				IfHasilAkhir();
			}
			if(sisa >=1000 && 		sisa<10000)			{IfSisa6();}		
			if(sisa >=10000 && 		sisa<100000)		{IfSisa5();}
			if(sisa >=100000 && 	sisa<1000000)		{IfSisa4();}
			if(sisa >=1000000 && 	sisa<10000000)		{IfSisa3();}
			if(sisa >=10000000 && 	sisa<100000000)		{IfSisa2();}
			if(sisa >=100000000 && 	sisa<1000000000)	{IfSisa1();}
			if(sisa >=1000000000)						{IfSisa();}
}

main() //PROGRAM UTAMA
{
do{ z:
	printf("\t\tPROGRAM KALKULATOR BCD DECODER");
	printf("\n================================================================================");
	printf("\n\t\tPembimbing : Faisal Mutaqqin, S.Kom., M.T\n");
	printf("\t\tDibuat oleh: \n\t-M Idham Fachrurrozi [17081010044] -R Rakhman Wahid [17081010068]");
	printf("\n================================================================================");
	printf("\nPilih Operasi Bilangan: \n1.Penjumlahan\n2.Pengurangan\n3.Perkalian\n4.Pembagian\n5.Exit\n\nPilihan : ");
	scanf("%d",&pilih);
	switch(pilih)
		{
			case 1 : printf("\nAngka pertama : ");	scanf("%d", &p);	printf("Angka kedua : ");	scanf("%d", &q); sisa=p+q; break;
			case 2 : printf("\nAngka pertama : ");	scanf("%d", &p);	printf("Angka kedua : ");	scanf("%d", &q); sisa=p-q; break;
			case 3 : printf("\nAngka pertama : ");	scanf("%d", &p);	printf("Angka kedua : ");	scanf("%d", &q); sisa=p*q; break;
			case 4 : printf("\nAngka pertama : ");	scanf("%d", &p);	printf("Angka kedua : ");	scanf("%d", &q); sisa=p/q; break;
			case 5 : printf("\nTerimakasih telah menggunakan program ini :)"); exit(0); break;
			default: printf("\nOPERASI TIDAK DITEMUKAN, PILIH LAGI!\n"); goto z; break;
		}
	printf("Hasil operasi : %d\n", sisa);
	
	a=sisa;
	sisa=p;
	printf("\nAngka Pertama Setelah diubah menjadi kode\t: ");
	IfFinal();	IfMinus();
	
	sisa=q;
	printf("\nAngka Kedua Setelah Diubah menjadi kode\t\t: ");
	IfFinal();	IfMinus();
	
	sisa=a;
	printf("\nSetelah diubah menjadi kode\t\t\t: ");
	IfFinal();	IfMinus();
	printf("\n\n");
	
	}while (pilih!=5);
}
