#include <stdio.h>
#include <stdlib.h>
char CCards[4][4], pilih;
int nilai, P,D,t=0;

FMskNl()
{
	if (nilai==1) CCards[0][0]='@';
	if (nilai==2) CCards[0][1]='#';
	if (nilai==3) CCards[0][2]='*';
	if (nilai==4) CCards[0][3]='^';
	if (nilai==5) CCards[1][0]='#';
	if (nilai==6) CCards[1][1]='+';
	if (nilai==7) CCards[1][2]='^';
	if (nilai==8) CCards[1][3]='*';	
	if (nilai==9) CCards[2][0]='$';
	if (nilai==10) CCards[2][1]='@';
	if (nilai==11) CCards[2][2]='%';
	if (nilai==12) CCards[2][3]='&';
	if (nilai==13) CCards[3][0]='%';
	if (nilai==14) CCards[3][1]='+';
	if (nilai==15) CCards[3][2]='$';
	if (nilai==16) CCards[3][3]='&';
}

main()
{
    CCards[0][0]='X';
    CCards[0][1]='X';
    CCards[0][2]='X';
    CCards[0][3]='X';
    CCards[1][0]='X';
    CCards[1][1]='X';
    CCards[1][2]='X';
    CCards[1][3]='X';
    CCards[2][0]='X';
    CCards[2][1]='X';
    CCards[2][2]='X';
    CCards[2][3]='X';
    CCards[3][0]='X';
    CCards[3][1]='X';
    CCards[3][2]='X';
    CCards[3][3]='X';

	printf("Halo pemain!\nDi sini terdapat 16 kartu tertutup dengan simbol X, Di mana dibalik setiap kartu tertutup terdapat karakter unik\nJumlah karakter unik tersebut adalah 8. Untuk memenangkan permainan sederhana ini, pemain ditantang untuk menyamakan\ndua kartu yang memiliki karakter unik yang sama. Setiap pemain hanya diberi kesempatan menebak sebanyak 15 kali\nJika pemain telah menebak 15 kali namun seluruh kartu belum terbuka maka pemain akan dinyatakan kalah\nSiap bemain (Y/N)");
	scanf("%c", &pilih);
	if (pilih=='y' || pilih=='Y')
		system("cls");
	else goto w;
	
	//z:
	while(t<16) 
	{
		printf(" Kondisi kartu\n");
		for( P=0;P<=3;P++)
			{
			for( D=0;D<=3;D++)
			{
				printf("  %c",CCards[P][D]);
			}
			printf("\n");
			}
		
		printf("\n Setiap angka melambangkan letak kartu");
		printf("\n  1  2  3  4\n  5  6  7  8\n  9 10 11 12\n 13 14 15 16\n");
	
		printf("\n Kartu pertama yang ingin dibuka : ");
		scanf("%d", &nilai);
		FMskNl();

		printf(" Kartu kedua yang ingin dibuka : ");
		scanf ("%d", &nilai);
		FMskNl();

		printf ("\n Kartu yang terbuka\n");
		for( P=0;P<=3;P++)
		{
			for( D=0;D<=3;D++)
			{
				printf("  %c",CCards[P][D]);
			}
			printf("\n");
		}
		
		if (CCards[0][0]!='X' && CCards[0][1]!='X' && CCards[0][2]!='X' && CCards[0][3]!='X' && CCards[1][0]!='X' && CCards[1][1]!='X' && CCards[1][2]!='X' && CCards[1][3]!='X' && CCards[2][0]!='X' && CCards[2][1]!='X' && CCards[2][2]!='X' && CCards[2][3]!='X' && CCards[3][0]!='X' && CCards[3][1]!='X' && CCards[3][2]!='X' && CCards[3][3]!='X')
		{
			printf("\nSelamat! Anda telah menyelesaikan permainan ini :)"); exit(0);
		}
		else
		{
    		if (CCards[0][0]=='X' && CCards[2][1]=='@' || CCards[0][0]=='@' && CCards[2][1]=='X') { CCards[0][0]='X';CCards[2][1]='X'; }
    		if (CCards[0][1]=='X' && CCards[1][0]=='#' || CCards[0][1]=='#' && CCards[1][0]=='X') { CCards[0][1]='X';CCards[1][0]='X'; }
    		if (CCards[0][3]=='X' && CCards[1][2]=='^' || CCards[1][2]=='X' && CCards[0][3]=='^') { CCards[1][2]='X';CCards[0][3]='X'; }
    		if (CCards[3][3]=='X' && CCards[2][3]=='&' || CCards[3][3]=='&' && CCards[2][3]=='X') { CCards[3][3]='X';CCards[2][3]='X'; }
    		if (CCards[1][3]=='X' && CCards[0][2]=='*' || CCards[1][3]=='*' && CCards[0][2]=='X') { CCards[1][3]='X';CCards[0][2]='X'; }
    		if (CCards[1][1]=='X' && CCards[3][1]=='+' || CCards[1][1]=='+' && CCards[3][1]=='X') { CCards[1][1]='X';CCards[3][1]='X'; }
    		if (CCards[3][0]=='X' && CCards[2][2]=='%' || CCards[3][0]=='%' && CCards[2][2]=='X') { CCards[3][0]='X';CCards[2][2]='X'; }
    		if (CCards[2][0]=='X' && CCards[3][2]=='$' || CCards[2][0]=='$' && CCards[3][2]=='X') { CCards[2][0]='X';CCards[3][2]='X'; }

			Sleep(1000);
    		system("cls");
		} t++; //goto z; 
	}
	
	printf("Aduh kesempatan anda telah berakhir :("); exit(0);
	w : printf("Anda memilih untuk tidak bermain"); exit(0);
}
