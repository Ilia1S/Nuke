#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define SIZE 20 // количество имеющихся целей (строк в файле)

uint8_t targetsCoords[SIZE][2]; // объявляем массив, в который будут передаваться данные координат из файла

uint8_t addInfo (char *fileName) // функция для заполнения массива данными координат
{
	FILE *fp;
	fp=fopen(fileName, "r");
	if (fp==NULL)
	{
		printf("Error occured while opening the file\n"); // проверка на ошибку открытия
		fclose(fp);
		return 0;
	}
	else
	{
		for (uint8_t i=0;i<SIZE;i++)
			fscanf(fp,"%hhu,%hhu",&targetsCoords[i][0],&targetsCoords[i][1]); // заполнение массива данными из файла
		fclose(fp);
		return 1;
	}
}
void calculation (uint8_t r)
{
	int8_t i,k,max=0; // k - кол-во пораженных целей в данной точке, max - наибольшее кол-во пораженных целей на карте
	int8_t x,y;
	uint8_t optimalPointX, optimalPointY;
	for (x=0;x<100;x++)
	{
		for (y=0;y<100;y++)
		{
			k=0;
			for (i=0;i<SIZE;i++)
			{
				if ((x+r)>=targetsCoords[i][0] && targetsCoords[i][0]>=(x-r) && (y+r)>=targetsCoords[i][1] && targetsCoords[i][1]>=(y-r)) // последовательно перебираем каждую точку от 0 до 99 по осям X и Y, 
					k++;																												  // отсчитываем от неё радиус поражения в разные стороны и считаем, сколько точек из файла с координатами попадает в данную зону
				if (k>max)																												 
				{																														  
					optimalPointX = x;																									  // запоминаем координаты точки с наибольшим кол-вом пораженных целей
					optimalPointY = y;
					max=k;																												  // если кол-во пораженных точек превышает наибольшее, то записываем это значение в переменную max
				}
			}
		}
	}
	printf("Optimal target X:%hhu Y:%hhu\nNumber of targets - %hhu",optimalPointX,optimalPointY,max);									  // вывод результатов. Возможная неточность данной методики в том, что областью поражения является квадрат со стороной равно 2r, а не круг с радиусом r
}

int main(int argc, char **argv)
{
	uint8_t r,er; // r - радиус поражения er - проверка ошибки открытия файла
	char *fileName = 0;
	if (argc!=3)
		printf ("Enter all the parameters as: nuke.exe <filename.txt> [damage radius]\n");
	else
	{
		fileName=argv[1];
		r = atoi(argv[2]);
		er = addInfo(fileName);
		if (er==1)
			calculation (r);
	}
	return 0;
}

