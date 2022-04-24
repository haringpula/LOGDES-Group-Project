#include<stdio.h>
#include<windows.h>
#define CLRSCR system("cls");
/*Included: (1)Input from base 2,8,10, and 16 then convert to all 4.(2)Character representation
(ascii/ebcdic), Gray Code, Hamming code (16 bits), Binary Coded Decimal (8 4 2 1/2 4 2 1/8 4 -2 -1),
Excess 3 Code. (3) Hamming Code Error Detection/Correction (21 Bits), Binary Complement (1s,2s)
Logic Design and Digital Computer Circuit project;
made with love by: King Red Sanchez, BSCS 2-3 (Group 15)*/
int menu;
inline void foo(){CLRSCR}
int power (int base, int raise){
	int p_count,num=1;
	for (p_count=0; p_count<raise; ++p_count)
		num*=base;
	return (num);
}
void nse(int answer){
	int dec,d_count, bin, o_count=1, oct=0;
	printf("\nDecimal = %d",answer);
	printf("\nBinary = ");
	for (d_count=15; d_count>=0; d_count--){
		bin = answer >> d_count;
		if (bin&1)
			printf("1");
		else
			printf("0");		
	}
	dec=answer;
	while (dec!= 0){
		oct += (dec%8)*o_count;
		dec/=8;
		o_count*=10;
	}
	printf("\nOctal = %d", oct);
	printf("\nHexadecimal = %x", answer);
}
void numsys(){
	int choice,decimal=0,h_count=0,val,len,oct,o_count=0,b_count=0,rem;
	char hex[17];
	long long bin;
	foo();
	printf("Choose input\n(1) Decimal\n(2) Octal\n(3) Hexadecimal\n(4) Binary\n: ");
	scanf("%d",&choice);
	foo();
	switch (choice){
		case 1:{
			printf("Enter digit: ");
			scanf("%d",&decimal);
			nse(decimal);
			break;
		}
		case 2:{
			printf("Enter digit: ");
			scanf("%d",&oct);
			while (oct!=0){
				decimal+=(oct%10)*power(8,o_count);
				++o_count;
				oct/=10;
			}
			o_count=1;
			nse(decimal);
			break;
		}
		case 3:{
			printf("Enter digit: ");
			scanf("%s",hex);
			len = strlen(hex);
			len--;
			decimal=0;
			for (h_count=0; hex[h_count]!='\0'; h_count++){
				if (hex[h_count]>='0'&&hex[h_count]<='9')
					val=hex[h_count]-48;
				else if (hex[h_count]>='a'&&hex[h_count]<='f')
					val=hex[h_count]-97+10;
				else if (hex[h_count]>='A'&&hex[h_count]<='F')
					val=hex[h_count]-65+10;
				decimal+=val*power(16,len);
				len--;
			}
			nse(decimal);
			break;
		}
		case 4:{
			printf("Enter digit: ");
			scanf("%lld",&bin);
			while (bin!=0){
				rem=bin%10;
				bin/=10;
				decimal+=rem*power(2,b_count);
				++b_count;
			}
			nse(decimal);
			break;
		}
	}
	menu=0;
	return;
}
void codes(){
	int choice,bin,g_a,g_b,gray=0,g_count=0,h_count=0,d_count=0;
	int data[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char asc,ebc;
	char dec[20];
	static char tt[256]={ //ebcdic table from stackoverflow.com
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x4F,0x7F,0x7B,0x5B,0x6C,0x50,0x7D,
	0x4D,0x5D,0x5C,0x4E,0x6B,0x60,0x4B,0x61,
	0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,
	0xF8,0xF9,0x7A,0x5E,0x4C,0x7E,0x6E,0x6F,
	0x7C,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,
	0xC8,0xC9,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,
	0xD7,0xD8,0xD9,0xE2,0xE3,0xE4,0xE5,0xE6,
	0xE7,0xE8,0xE9,0x4A,0xE0,0x5A,0x5F,0x6D,
	0x79,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
	0x88,0x89,0x91,0x92,0x93,0x94,0x95,0x96,
	0x97,0x98,0x99,0xA2,0xA3,0xA4,0xA5,0xA6,
	0xA7,0xA8,0xA9,0xC0,0x6A,0xD0,0xA1,0x40,
	0xB9,0xBA,0xED,0xBF,0xBC,0xBD,0xEC,0xFA,
	0xCB,0xCC,0xCD,0xCE,0xCF,0xDA,0xDB,0xDC,
	0xDE,0xDF,0xEA,0xEB,0xBE,0xCA,0xBB,0xFE,
	0xFB,0xFD,0x7d,0xEF,0xEE,0xFC,0xB8,0xDD,
	0x77,0x78,0xAF,0x8D,0x8A,0x8B,0xAE,0xB2,
	0x8F,0x90,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0xAA,0xAB,0xAC,0xAD,0x8C,0x8E,0x80,0xB6,
	0xB3,0xB5,0xB7,0xB1,0xB0,0xB4,0x76,0xA0,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40 
	};
	foo();
	printf("(1) Character Representation (ASCII/EBCDIC)\n(2) Binary to Gray Code\n(3) 4 Bytes Hamming Code");
	printf("\n(4) Binary Coded Decimal (8 4 2 1/2 4 2 1/8 4 -2 -1)\n(5) Decimal to Excess 3 Code\n: ");
	scanf("%d",&choice);
	foo();
	switch (choice){
		case 1:{
			printf("\nEnter character: ");
			scanf(" %c",&asc);
			ebc=tt[asc];
			printf("\nCharacter entered: %c\nASCII equivalent: %c (%d)\nEBCDIC equivlent: %c (%d)",asc,asc,asc,ebc,ebc);
			break;
		}
		case 2:{
			printf("\nEnter binary digit: ");
			scanf("%d",&bin);
			printf("\nThe Gray Code of %d ",bin);
			while (bin!=0){
				g_a=bin%10;
				bin=bin/10;
				g_b=bin%10;
				if ((g_a&&!g_b)||(!g_a&&g_b))
					gray=gray+power(10,g_count);
				g_count++;
			}
			printf("is %d",gray);
			break;
		}
		case 3:{
			printf("\nEnter 16 bits of transmitted data one by one\n: ");{ scanf(" %d",&data[2]);
			printf(": ");scanf(" %d",&data[4]);
			printf(": ");scanf(" %d",&data[5]);
			printf(": ");scanf(" %d",&data[6]);
			printf(": ");scanf(" %d",&data[8]);
			printf(": ");scanf(" %d",&data[9]);
			printf(": ");scanf(" %d",&data[10]);
			printf(": ");scanf(" %d",&data[11]);
			printf(": ");scanf(" %d",&data[12]);
			printf(": ");scanf(" %d",&data[13]);
			printf(": ");scanf(" %d",&data[14]);
			printf(": ");scanf(" %d",&data[16]);
			printf(": ");scanf(" %d",&data[17]);
			printf(": ");scanf(" %d",&data[18]);
			printf(": ");scanf(" %d",&data[19]);
			printf(": ");scanf(" %d",&data[20]);}
			/*check bits*/ {
			data[0]=(data[2]+data[4]+data[6]+data[8]+data[10]+data[12]+data[14]+data[16]+data[18]+data[20])%2;
			data[1]=(data[2]+data[5]+data[6]+data[9]+data[10]+data[13]+data[14]+data[17]+data[18])%2;
			data[3]=(data[4]+data[5]+data[6]+data[11]+data[12]+data[13]+data[14]+data[19]+data[20])%2;
			data[7]=(data[8]+data[9]+data[10]+data[11]+data[12]+data[13]+data[14])%2;
			data[15]=(data[16]+data[17]+data[18]+data[19]+data[20])%2;}
			printf("\nThe message transmitted is: \n");
			for (h_count=0;h_count<21;h_count++){
				printf("%d ",data[h_count]);
			}

			break;
		}
		case 4:{
			printf("\nEnter decimal digit: ");
			scanf(" %s",dec);
			printf("\nDigit in BCD (8 4 2 1) is: ");
			while (dec[d_count]!= NULL){
				switch(dec[d_count]){
					case '0':printf("0000 ");break;
					case '1':printf("0001 ");break;
					case '2':printf("0010 ");break;
					case '3':printf("0011 ");break;
					case '4':printf("0100 ");break;
					case '5':printf("0101 ");break;
					case '6':printf("0110 ");break;
					case '7':printf("0111 ");break;
					case '8':printf("1000 ");break;
					case '9':printf("1001 ");break;
				}
				d_count++;
			}
			printf("\nDigit in BCD (2 4 2 1) is: ");
			d_count=0;
			while (dec[d_count]!= NULL){
				switch(dec[d_count]){
					case '0':printf("0000 ");break;
					case '1':printf("0001 ");break;
					case '2':printf("0010 ");break;
					case '3':printf("0011 ");break;
					case '4':printf("0100 ");break;
					case '5':printf("1011 ");break;
					case '6':printf("1100 ");break;
					case '7':printf("1101 ");break;
					case '8':printf("1110 ");break;
					case '9':printf("1111 ");break;
				}
				d_count++;
			}
			printf("\nDigit in BCD (8 4 -2 -1) is: ");
			d_count=0;
			while (dec[d_count]!= NULL){
				switch(dec[d_count]){
					case '0':printf("0000 ");break;
					case '1':printf("0111 ");break;
					case '2':printf("0110 ");break;
					case '3':printf("0101 ");break;
					case '4':printf("0100 ");break;
					case '5':printf("1011 ");break;
					case '6':printf("1010 ");break;
					case '7':printf("1001 ");break;
					case '8':printf("1000 ");break;
					case '9':printf("1111 ");break;
				}
				d_count++;
			}
			break;
		}
		case 5:{
			printf("\nEnter decimal digit: ");
			scanf(" %s",dec);
			printf("\nDigit in Excess 3 is: ");
			while (dec[d_count]!= NULL){
				switch(dec[d_count]){
					case '0':printf("0011 ");break;
					case '1':printf("0100 ");break;
					case '2':printf("0101 ");break;
					case '3':printf("0110 ");break;
					case '4':printf("0111 ");break;
					case '5':printf("1000 ");break;
					case '6':printf("1001 ");break;
					case '7':printf("1010 ");break;
					case '8':printf("1011 ");break;
					case '9':printf("1100 ");break;
				}
				d_count++;
			}
			break;
		}
	}
	menu=0;
}
void others(){
	int choice,h_count=0,biterr=0,b_count=0,carry=1;
	int data[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int rec[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char bin[16],comp1[16],comp2[16];
	foo();
	printf("(1) Hamming Code Error Detection/Correction (21 Bits)\n(2) Binary Complement (4 Bytes)\n: ");
	scanf("%d",&choice);
	foo();
	switch (choice){
		case 1:{
			printf("Enter 16 bits of transmitted data one by one\n: ");{scanf(" %d",&data[2]);
			printf(": ");scanf(" %d",&data[4]);
			printf(": ");scanf(" %d",&data[5]);
			printf(": ");scanf(" %d",&data[6]);
			printf(": ");scanf(" %d",&data[8]);
			printf(": ");scanf(" %d",&data[9]);
			printf(": ");scanf(" %d",&data[10]);
			printf(": ");scanf(" %d",&data[11]);
			printf(": ");scanf(" %d",&data[12]);
			printf(": ");scanf(" %d",&data[13]);
			printf(": ");scanf(" %d",&data[14]);
			printf(": ");scanf(" %d",&data[16]);
			printf(": ");scanf(" %d",&data[17]);
			printf(": ");scanf(" %d",&data[18]);
			printf(": ");scanf(" %d",&data[19]);
			printf(": ");scanf(" %d",&data[20]);}
			/*check bits*/ {
			data[0]=(data[2]+data[4]+data[6]+data[8]+data[10]+data[12]+data[14]+data[16]+data[18]+data[20])%2;
			data[1]=(data[2]+data[5]+data[6]+data[9]+data[10]+data[13]+data[14]+data[17]+data[18])%2;
			data[3]=(data[4]+data[5]+data[6]+data[11]+data[12]+data[13]+data[14]+data[19]+data[20])%2;
			data[7]=(data[8]+data[9]+data[10]+data[11]+data[12]+data[13]+data[14])%2;
			data[15]=(data[16]+data[17]+data[18]+data[19]+data[20])%2;}
			printf("\nThe message transmitted is: \n");
			for (h_count=0;h_count<21;h_count++){
				printf("%d ",data[h_count]);
			}
			Sleep(3000);
			printf("\nEnter 21 bits of received data one by one\n: ");{scanf(" %d",&rec[0]);
			printf(": ");scanf(" %d",&rec[1]);
			printf(": ");scanf(" %d",&rec[2]);
			printf(": ");scanf(" %d",&rec[3]);
			printf(": ");scanf(" %d",&rec[4]);
			printf(": ");scanf(" %d",&rec[5]);
			printf(": ");scanf(" %d",&rec[6]);
			printf(": ");scanf(" %d",&rec[7]);
			printf(": ");scanf(" %d",&rec[8]);
			printf(": ");scanf(" %d",&rec[9]);
			printf(": ");scanf(" %d",&rec[10]);
			printf(": ");scanf(" %d",&rec[11]);
			printf(": ");scanf(" %d",&rec[12]);
			printf(": ");scanf(" %d",&rec[13]);
			printf(": ");scanf(" %d",&rec[14]);
			printf(": ");scanf(" %d",&rec[15]);
			printf(": ");scanf(" %d",&rec[16]);
			printf(": ");scanf(" %d",&rec[17]);
			printf(": ");scanf(" %d",&rec[18]);
			printf(": ");scanf(" %d",&rec[19]);
			printf(": ");scanf(" %d",&rec[20]);}
			/*check bits*/ {
			if ((rec[0]+rec[2]+rec[4]+rec[6]+rec[8]+rec[10]+rec[12]+rec[14]+rec[16]+rec[18]+rec[20])%2==1)
				biterr=biterr+1;
			if ((rec[1]+rec[2]+rec[5]+rec[6]+rec[9]+rec[10]+rec[13]+rec[14]+rec[17]+rec[18])%2==1)
				biterr=biterr+2;
			if ((rec[3]+rec[4]+rec[5]+rec[6]+rec[11]+rec[12]+rec[13]+rec[14]+rec[19]+rec[20])%2==1)
				biterr=biterr+4;
			if ((rec[7]+rec[8]+rec[9]+rec[10]+rec[11]+rec[12]+rec[13]+rec[14])%2==1)
				biterr=biterr+8;
			if ((rec[15]+rec[16]+rec[17]+rec[18]+rec[19]+rec[20])%2==1)
				biterr=biterr+16;}
			printf("\nThe message received is: \n");
			for (h_count=0;h_count<21;h_count++){
				printf("%d ",rec[h_count]);
			}
			if (biterr==0){
				printf("\nThere are no errors");
			}
			else{
				printf("\nError detected at %d",biterr);
				if (rec[biterr-1]==0)
					rec[biterr-1]=1;
				else if (rec[biterr-1]==1)
					rec[biterr-1]=0;
				printf("\nThe correct message is: \n");
				for (h_count=0;h_count<21;h_count++){
					printf("%d ",rec[h_count]);
				}
			}
			break;
		}
		case 2:{
			printf("\nEnter 16 bits of Binary data: ");
			scanf("%s",bin);
			for (b_count=0; b_count<16; b_count++){
				if (bin[b_count]=='1')
					comp1[b_count]='0';
				else if (bin[b_count]=='0')
					comp1[b_count]='1';
			}
			comp1[16]='\n';
			for (b_count=15; b_count>=0; --b_count){
				if (comp1[b_count]=='1'&&carry==1){
					comp2[b_count]='0';
				}
				else if (comp1[b_count]=='0'&&carry==1){
					comp2[b_count]='1';
					carry=0;
				}
				else{
					comp2[b_count]=comp1[b_count];
				}
			}
			comp2[16]='\n';
			printf("\nOriginal Binary: %s\nOnes Complement: ",bin);
			for (b_count=0; b_count<16; b_count++){
				printf("%c",comp1[b_count]);
			}
			printf("\nTwos Complement:\n");
			for (b_count=0; b_count<16; b_count++){
				printf("%c",comp2[b_count]);
			}
			break;
		}
	}
	menu=0;
}
int main(){
	int choice,i;
	printf("  ________________________\n");
	printf(" / \\                       \\.\n");
	printf("|   |         My           |.\n");
	printf(" \\_ |     Logic Design     |.\n");
	printf("    |         and          |.\n");
	printf("    |   Digital Computer   |.\n");
	printf("    |       Circuit        |.\n");
	printf("    |       Midterm        |.\n");
	printf("    |       Project        |.\n");
	printf("    |   ___________________|__\n");
	printf("    |  / by: King Red Sanchez /.\n");
	printf("    \\_/______________________/. \n");
	Sleep(3000);
	foo();
	printf("Choose from the choices below\n(1) Number System\n(2) Codes\n(3) Others\n(4) Exit\n: ");
	scanf("%d",&menu);
	while (menu!=4){
		switch (menu){
			case 0:{
				Sleep(5000);
				printf("\nDo you want to try again(1=yes/0=no): ");
				scanf("%d",&choice);
				if (choice==1){
					foo();
					printf("Choose from the choices below\n(1) Number System\n(2) Codes\n(3) Others\n(4) Exit\n: ");
					scanf("%d",&menu);
					foo();
				}
				else if (choice==0){
					menu=4;
				}
				break;
			}
			case 1: numsys();
			break;
			case 2: codes();
			break;
			case 3: others();
			break;
			default:{
				printf("\nTry again: ");
				scanf("%d",&menu);
				break;
			}
		}
	}
	foo();{
	printf("Thank you for using!\n");
	printf("   *1�g�#�$��1�,Q        \n");
	printf("  ��������������         \n");
	printf(" #/�������������g        \n");
	printf(" 1�����?�����������\\      \n");
	printf(" /@ $@@,0��1�|7$e$,      \n");
	printf("       4j7�4!            \n");
	printf("|  @    #7Y*   @   \\     \n");
	printf("4�    #�4��9      4      \n");
	printf("$�9g e@��!4��$-  #e      \n");
	printf("|�����#|   |e����$e      \n");
	printf(" Yeg��\\,   $9���e�4      \n");
	printf(" gp@l��,��Y@��M7 7       \n");
	printf(" , ��@1����9���4Q        \n");
	printf("    \"�  /Q�-��7,0$      \n");
	printf(" !     ��                \n");
	printf(" \\�\\�         �440       \n");
	printf(" 1�\\�    *�0    �        \n");
	printf("  1�9���# �*�   �        \n");
	printf("    e������  ����        \n");
	printf("Closing now");
	for (i=0; i<10; i++){
		Sleep(500);
		printf(".");
	}
	}
	foo();{
	printf("Thank you for using!\n");
	printf("   *1�g�#�$��1�,Q        \n");
	printf("  ��������������         \n");
	printf(" #/�������������g        \n");
	printf(" 1�����?�����������\\      \n");
	printf(" /@ $@@,0��1�|7$e$,      \n");
	printf("       4j7�4!            \n");
	printf("|       #7Y*       \\     \n");
	printf("4�    #�4��9      4      \n");
	printf("$�9g e@��!4��$-  #e      \n");
	printf("|�����#|   |e����$e      \n");
	printf(" Yeg��\\,   $9���e�4      \n");
	printf(" gp@l��,��Y@��M7 7       \n");
	printf(" , ��@1����9���4Q        \n");
	printf("    \"�  /Q�-��7,0$      \n");
	printf(" !     ��                \n");
	printf(" \\�\\�         �440       \n");
	printf(" 1�\\�    *�0    �        \n");
	printf("  1�9���# �*�   �        \n");
	printf("    e������  ����        \n");}
	printf("Closing now");
	for (i=0; i<3; i++){
		Sleep(500);
	}
	return 0;
}
