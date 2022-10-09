#include <stdio.h> //sad as
#include <stdlib.h>

void funk(int byte, unsigned char *data) 
{
	unsigned char b;
	for(int i=byte-1; i>=0; i--)
		for(int j=7; j>=0; j--)
			{ 
				b=(data[i]>>j)%2;//побитовый сдвиг и делим на 2(остаточно)
				printf("%u",b);
					if(j==0) 
						printf(" ");
			}
	}

int main() 
{
	
	system("clear");
	int int1=255, int2=-256; 
	float float1=376.32,float2=-376.36; 
	double double1=23.54,double2=-12.56; 
	char char0=-45;
	short int shortint1= 421, shortint2=-253;
	unsigned int unint=123312312;
	unsigned char unchar='t'; 
    unsigned short unshort = 32;
	unsigned char *pb;
	 
	//Целое число (4 байта)
	printf("\nЦелое число(%ld байта):", sizeof(int));
	pb=(unsigned char *)&int1;//приводим к указателю на тип данных
	printf("\n%d\n",int1);	
	funk(sizeof(int), pb);// вызов функции для перевода числа
	pb=(unsigned char *)&int2;
	printf("\n%d\n",int2);
	funk(sizeof(int), pb);
	 
	//Число с плавующей точкой (4 байта)
	printf("\n\nЧисло  с плавующей точкой(%ld байта):", sizeof(float));
	pb=(unsigned char *)&float1;
	printf("\n%f\n",float1);	
	funk(sizeof(float), pb);
	pb=(unsigned char *)&float2;
	printf("\n%f\n",float2);
	funk(sizeof(float), pb);
	 
	//Число с плавующей точкой двойной точностью (8 байт)
	printf("\n\nЧисло  с плавующей точкой двойной точности (8 байта):");
	pb=(unsigned char *)&double1;
	printf("\n%f\n",double1);
	funk(sizeof(double), pb);
	pb=(unsigned char *)&double2;
	printf("\n%f\n",double2);
	funk(sizeof(double), pb);
	 
	//Краткое целое число (2 байта)
	printf("\n\nКраткое целое число (2 байта):");
	pb=(unsigned char *)&shortint1;
	printf("\n%d\n",shortint1);
	funk(sizeof(short int), pb);
	pb=(unsigned char *)&shortint2;
	printf("\n%d\n",shortint2);
	funk(sizeof(short int),pb);
	printf("\n");
	 
	//символ (2 байта)
	printf("\n\nСимвол (2 байтa):");
	//printf("%ld",sizeof(char));
	pb=(unsigned char *)&char0;
	printf("\n%d\n",char0);
	funk(sizeof(char),pb);
	 
	//безнаковое целое число 4 байта
	printf("\n\nБезнаковае целое (4 байтa):");
	pb=(unsigned char *)&unint;
	printf("\n%d\n",unint);
	funk(sizeof(unsigned int),pb); 
	 
	//Строка (1 байт)
	printf("\n\nСтрока (1 байтa):\n");
	pb=(unsigned char *)&unchar;
	printf("%d\n",unchar);
	funk(sizeof(unsigned char),pb);
	printf("\n");
	 
    // бесзнаковое число (2 байта)  
    printf("\n\n  Бесзнаковое число (2 байта)\n");  
    pb=(unsigned char *)&unshort;  
    printf("%d\n", unshort); 
    funk(sizeof(unsigned short), pb); 
    printf("\n");

	return 0;
}
