#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

//7 Вариант. Увеличить яркость вертикальными полосами по 64 пикселя.
int main()
{
	int sumtimec = 0;
	int sumtimes = 0;
	int sumtimev = 0;
	time_t start;
	for (int i = 0; i < 100; i++)
	{
		//Начало замера
		start = clock();

		//Блок c++. Считывание и запись заголовка
		FILE* in, * out;
		unsigned __int8* buffer;
		unsigned __int32 wight, height;

		fopen_s(&in, "test.bmp", "rb");
		buffer = (unsigned __int8*)malloc(54);
		fread(buffer, 1, 54, in);

		for (int i = 0; i <= 3; i++)
		{
			wight = buffer[21 - i] | wight << 8;
			height = buffer[25 - i] | height << 8;
		}

		if (i == 0)
		{
			cout << wight << "x" << height << endl;
		}
		

		fopen_s(&out, "test2_cpp.bmp", "wb");
		fwrite(buffer, 1, 54, out);

		free(buffer);

		//Блок c++. Считывание, модификация и запись цвета

		buffer = (unsigned __int8*)malloc(wight * height * 4);

		fread(buffer, 1, wight * height * 4, in);
		fclose(in);

		for (int i = 0; i < wight; i += 128)
		{
			for (int j = 0; j < height; j++)
			{
				for (int k = i; k < (i + 64); k++)
				{
					buffer[wight * 3 * j + k * 3 + 0] = 255;
					buffer[wight * 3 * j + k * 3 + 1] = 255;
					buffer[wight * 3 * j + k * 3 + 2] = 255;
				}
			}
		}

		fwrite(buffer, 1, wight * height * 4, out);
		fclose(out);

		free(buffer);

		//Конц замера
		sumtimec += clock() - start;

		//Начало замера
		start = clock();

		//Блок ассемблера. Скаляр. Считывание и запись заголовка

		in = NULL;
		out = NULL;
		buffer = NULL;
		wight = 0;
		height = 0;

		fopen_s(&in, "test.bmp", "rb");
		buffer = (unsigned __int8*)malloc(54);
		fread(buffer, 1, 54, in);

		//Получим высоту и ширину
		__asm
		{
			mov esi, buffer;			//Указатель на массив

			mov ecx, 3;					//Начинаем извлекать высоту и ширину
			mov ebx, 18;
			mov eax, [esi + ebx];
			mov wight, eax;
			mov eax, [esi + ebx + 4];
			mov height, eax;
		}

		fopen_s(&out, "test2_scal.bmp", "wb");
		fwrite(buffer, 1, 54, out);

		free(buffer);

		//Блок ассемблера. Скаляр. Считывание, модификация и запись цвета
		buffer = (unsigned __int8*)malloc(wight * height * 4);

		fread(buffer, 1, wight * height * 4, in);
		fclose(in);

		__asm
		{
			//Получаем адресс из буфера
			mov esi, buffer;

			//Делаем счётчик для 1 цикла
			mov ecx, wight;

		l1:
			//Убираем счётчик в стек
			push ecx;

			//Делаем новый счётчик для 2 цикла
			mov ecx, height;

		l2:
			//Подготавливаем часть индекса, который используется в 3 цикле (wight*3*j)
			mov eax, 3;
			mul wight;
			mov ebx, height;
			sub ebx, ecx;
			mul ebx;
			mov ebx, eax;

			//Подготавливаем остальную часть индекса(+i*3). Тк там используется значения из 1 цикла, делаем махинации с стеком
			mov eax, ecx;	//Сохраняем текущее значение счётчика
			pop ecx;		//Достаём значения счётчика с прошлого цикла
			push eax;		//Тк нам понадобится eax, сохраняем значения текущего счётчика в стеке

			mov eax, wight;
			sub eax, ecx;
			mov edx, 3;
			mul edx;
			add ebx, eax;
			mov eax, 0;

			//Возвращаем значения счётчика 1 цикла в стек и достаём значения текущего
			pop eax;
			push ecx;
			mov ecx, eax;
			mov eax, 0;

			push ecx;
			mov ecx, 192;

		l3:
			//Освещаем пиксель
			mov[esi + ebx], 255;
			inc ebx;

			//Циклы
			loop l3;

			pop ecx;		//Забираем счётчик 2 цикла из стека
			loop l2;

			pop ecx;		//Забираем счётчик 3 цикла из стека
			sub ecx, 127;	//Смещаемся не на 1 пиксель, а на 64*2-1, тк взаимодействие с 64 нужными было в 3 цикле
			cmp ecx, 0;		//Если наше смещение привело к отрицательному(или равному нулую) ecx - выходим из 1 цикла
			jle ex;
			loop l1;
		ex:
		}

		fwrite(buffer, 1, wight * height * 4, out);
		fclose(out);

		free(buffer);

		//Конц замера
		sumtimes += clock() - start;

		//Начало замера
		start = clock();

		//Блок ассемблера. Вектор. Считывание и запись заголовка

		in = NULL;
		out = NULL;
		buffer = NULL;
		wight = 0;
		height = 0;

		fopen_s(&in, "test.bmp", "rb");
		buffer = (unsigned __int8*)malloc(54);
		fread(buffer, 1, 54, in);

		//Получим высоту и ширину
		__asm
		{
			mov esi, buffer;			//Указатель на массив

			mov ecx, 3;					//Начинаем извлекать высоту и ширину
			mov ebx, 18;
			mov eax, [esi + ebx];
			mov wight, eax;
			mov eax, [esi + ebx + 4];
			mov height, eax;
		}

		fopen_s(&out, "test2_vect.bmp", "wb");
		fwrite(buffer, 1, 54, out);

		free(buffer);

		//Блок ассемблера. Вектор. Считывание, модификация и запись цвета
		buffer = (unsigned __int8*)malloc(wight * height * 4);

		fread(buffer, 1, wight * height * 4, in);
		fclose(in);

		__asm
		{
			//Получаем адресс из буфера
			mov esi, buffer;

			//Делаем счётчик для 1 цикла
			mov ecx, wight;

		l11:
			//Убираем счётчик в стек
			push ecx;

			//Делаем новый счётчик для 2 цикла
			mov ecx, height;

		l12:
			//Подготавливаем часть индекса, который используется в 3 цикле (wight*3*j)
			mov eax, 3;
			mul wight;
			mov ebx, height;
			sub ebx, ecx;
			mul ebx;
			mov ebx, eax;

			//Подготавливаем остальную часть индекса(+i*3). Тк там используется значения из 1 цикла, делаем махинации с стеком
			mov eax, ecx;	//Сохраняем текущее значение счётчика
			pop ecx;		//Достаём значения счётчика с прошлого цикла
			push eax;		//Тк нам понадобится eax, сохраняем значения текущего счётчика в стеке

			mov eax, wight;
			sub eax, ecx;
			mov edx, 3;
			mul edx;
			add ebx, eax;
			mov eax, 0;

			//Возвращаем значения счётчика 1 цикла в стек и достаём значения текущего
			pop eax;
			push ecx;
			mov ecx, eax;
			mov eax, 0;

			push ecx;
			mov ecx, 48;

		l13:
			//Освещаем пиксель
			movd mm0, [esi + ebx];
			mov eax, 0xFFFFFFFF;
			movd mm1, eax;
			paddusb mm0, mm1;
			movd[esi + ebx], mm0;
			add ebx, 4;

			//Циклы
			loop l13;

			pop ecx;		//Забираем счётчик 2 цикла из стека
			loop l12;

			pop ecx;		//Забираем счётчик 3 цикла из стека
			sub ecx, 127;	//Смещаемся не на 1 пиксель, а на 64*2-1, тк взаимодействие с 64 нужными было в 3 цикле
			cmp ecx, 0;		//Если наше смещение привело к отрицательному(или равному нулую) ecx - выходим из 1 цикла
			jle ex1;
			loop l11;
		ex1:
		}

		fwrite(buffer, 1, wight * height * 4, out);
		fclose(out);

		free(buffer);

		//Конц замера
		sumtimev += clock() - start;

		cout << "\nEnd of iteration: " << i;
	}

	cout << "\nAverage code time in C++: " << sumtimec / 100 << "\nAverage code time in assembler via scalar: " << sumtimes / 100 << "\nAverage assembly code time via mmx: " << sumtimev / 100 << endl;

	system("pause");
	return 0;
}
