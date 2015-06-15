 /*    Keil project example for HD44780 LCD driver
 *
 *    @author     Tilen Majerle
 *    @email        tilen@majerle.eu
 *    @website    http://stm32f4-discovery.com
 *    @ide        Keil uVision 5
 */

#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"
#include "tm_stm32f4_hcsr04.h"
#include "string.h"

//#include "stdio.h"
#include "math.h"

enum pozycja{
	Czujnik_Lewy,
	Czujnik_Prawy,
};

void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}
int poww(int x, unsigned int y)
{
  if (y == 0) return 1;
  if (y == 1) return x;
  int a = y / 2;
  int xa = poww(x, a);
  if (a + a == y) // y even
    return xa * xa;
  else
    return xa * xa * x;
}

void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * poww(afterpoint,10);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}


int opcja=0;

void strzaleczki(int n,enum pozycja gdzie){
	int l=0;

	if(n < 1)
		l=8;
	if(n >= 1 && n < 3)
		l=7;
	if(n >= 3 && n < 5)
		l=6;
	if(n >= 5 && n < 7)
		l=5;
	if(n >= 7 && n < 9)
		l=4;
	if(n >= 9 && n < 11)
		l=3;
	if(n >= 11 && n < 13)
		l=2;
	if(n >= 13 && n< 15)
		l=1;
	if(n >= 15)
		l=0;



	int i=0;
	switch(gdzie){
	case Czujnik_Lewy:
		for(i=0; i<l;i++){
			TM_HD44780_Puts(i,1,">");
			//TM_HD44780_Puts(15-i,1,"<");
		}
		for(i=l; i<8;i++){
			TM_HD44780_Puts(i,1," ");
			//TM_HD44780_Puts(15-i,1," ");
		}
		break;
	case Czujnik_Prawy:
		for(i=0; i<l;i++){
			//TM_HD44780_Puts(i,1,">");
			TM_HD44780_Puts(15-i,1,"<");
		}
		for(i=l; i<8;i++){
			//TM_HD44780_Puts(i,1," ");
			TM_HD44780_Puts(15-i,1," ");
		}
		break;
	}


}
TM_HCSR04_t HCSR2;
TM_HCSR04_t HCSR1;
void initButton() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure) ;
}
int main(void) {
	initButton();
    SystemInit();

    //Initialize LCD 20 cols x 4 rows
    TM_HD44780_Init(16, 2);
    TM_HD44780_Clear();



    //TM_GPIO_Init(GPIOA,GPIO_PIN_0, GPIO_Mode_IN, GPIO_OType_PP,GPIO_PuPd_DOWN, GPIO_Speed_50MHz);
    TM_HD44780_Puts(5,0,"WITAM!");
    Delayms(700);
    TM_HD44780_Clear();

    int czekaj = 700;


	    float n = 0;
	    int i =0;
	TM_HCSR04_Init(&HCSR2,GPIOC,GPIO_PIN_14,GPIOC,GPIO_PIN_15);
	TM_HCSR04_Init(&HCSR1,GPIOA,GPIO_PIN_14,GPIOA,GPIO_PIN_15);

	while (1) {
////////////////////////////////////////////////////////////////  PIERWSZA OPCJA
    	opcja = 1;
    	TM_HD44780_Puts(0,0, "1. Zmierz odleglosc.");
    	while(czekaj){
    		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
    		    			distance(10,1);
    		    	}
    		czekaj--;
    		Delayms(1);
    	}
    	GPIO_ReadOutputDataBit(GPIOA,GPIO_PIN_0);
    	TM_HD44780_Clear();

//////////////////////////////////////////////////		DRUGA OPCJA
    	czekaj = 700;
    	opcja = 2;
    	TM_HD44780_Puts(0,0, "2. Zlicz.");
    	while(czekaj){
    		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
    		    			counter(150);
    		    	}
    	    czekaj--;
    	    Delayms(1);
    	}
    	GPIO_ReadOutputDataBit(GPIOA,GPIO_PIN_0);
    	czekaj = 700;
    	TM_HD44780_Clear();
//////////////////////////////////////////////////     TRZECIA OPCJA
    	czekaj = 700;
    	opcja = 3;
    	TM_HD44780_Puts(0,0, "3. Policz kubature.");
    	while(czekaj){
    		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
    					kubatura();
    		    	}
    	    czekaj--;
    	    Delayms(1);
    	}
    	GPIO_ReadOutputDataBit(GPIOA,GPIO_PIN_0);
    	czekaj = 700;
    	TM_HD44780_Clear();
	}
}

void kubatura(){
	float n=0,n2=0,n3=0;
	char res[20];
	int czekaj=1000;
	int i=0;
	int czy=0;
	TM_HD44780_Clear();
	TM_HD44780_Puts(0,0,"Kubatura.");
	Delayms(500);

	TM_HD44780_Cmd();
	TM_HD44780_Puts(0,0,"Przyloz i wcisnij:");
	Delayms(700);

	TM_HD44780_Clear();
	TM_HD44780_Puts(0,0,"X=");

	while(!czy){
		for(i=0,n=0;i<10;i++){
			n += TM_HCSR04_Read(&HCSR2);
			Delayms(2);
			}
		n = (n/10);

		ftoa(n,res,0);
		TM_HD44780_Puts(2,0,res);

		//TM_HD44780_Puts(14,1,"G");
		while(czekaj){

			//TM_HD44780_Puts(14,1,"C");
		    		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
		    			czy= 1;
		    			break;
		    		    	}
		    	    czekaj--;
		    	    Delayms(1);
		    	}
		czekaj=1000;
	}

	czy=0;
	czekaj=1000;

	TM_HD44780_Puts(5,0,"Y=");
	while(!czy){
		for(i=0,n2=0;i<10;i++){
			n2 += TM_HCSR04_Read(&HCSR2);
			Delayms(10);
			}
		n2 = (n2/10);

		ftoa(n2,res,0);
		TM_HD44780_Puts(7,0,res);

		while(czekaj){

			//TM_HD44780_Puts(14,1,"C");
		    		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
		    			czy= 1;
		    			break;
		    		    	}
		    	    czekaj--;
		    	    Delayms(1);
		    	}
		czekaj=1000;

	}
	czy=0;
	czekaj=1000;

	ftoa((n*n2)/10000,res,2);
	TM_HD44780_Puts(10,0,"P=");
	TM_HD44780_Puts(12,0,res);

	TM_HD44780_Puts(0,1,"Z=");
	while(!czy){
		for(i=0,n3=0;i<10;i++){
			n3 += TM_HCSR04_Read(&HCSR2);
			Delayms(10);
			}
		n3 = (n3/10);

		ftoa(n3,res,0);
		TM_HD44780_Puts(2,1,res);


		while(czekaj){

			//TM_HD44780_Puts(14,1,"C");
		    		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
		    			czy= 1;
		    			break;
		    		    	}
		    	    czekaj--;
		    	    Delayms(1);
		    	}
		czekaj=1000;

	}
	czy=0;
	czekaj=1000;

	ftoa((n*n2*n3)/1000000,res,2);
	TM_HD44780_Puts(7,1,"V=");
	TM_HD44780_Puts(9,1,res);

	Delayms(200);
	while(1){
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
			return;
		 }
	}

}
void counter(int distance){
	TM_HD44780_Clear();
	float n=0;
    TM_HD44780_Puts(5,0,"counter!");
    Delayms(500);
    int licznik=0;
    float npoprzednie = distance;
    int i=0;
    char res[20];
    TM_HD44780_Clear();

	for(i=0,n=0;i<10;i++){
		n += TM_HCSR04_Read(&HCSR2);
		Delayms(2);
   	}
    n=n/10;

	TM_HD44780_Puts(0,0,"Licznik:");
	TM_HD44780_Puts(0,1,"0");

    if(!(n>distance))
    	distance = n;

    while(1){

    	for(i=0,n=0;i<20;i++){
    		n += TM_HCSR04_Read(&HCSR2);
    		Delayms(2);
       	}
    	n = n/20;


    	if (!(n>distance)) {
    		/*if(abs(n-npoprzednie) > 10){
    			licznik++;
    			ftoa(licznik,res,0);
    			//npoprzednie= n;
    			TM_HD44780_Puts(0,0,"Licznik:");
    			TM_HD44780_Puts(0,1,(res));
    		}*/
    		if(abs(n - npoprzednie) > 10){
				licznik++;
				npoprzednie = n;
				ftoa(licznik, res, 0);
				TM_HD44780_Puts(0,0,"Licznik:");
				TM_HD44780_Puts(0,1,res);
    		}
    		else{}
		}
    	else{
    		//if(!(abs(n - npoprzednie) < 5))
    			//npoprzednie = distance;
    		 npoprzednie = distance;
    	}
    	Delayms(80);

    }



}
void distance(int samples, int precision)
{
	enum pozycja poz = Czujnik_Lewy;
	enum pozycja poz2 = Czujnik_Prawy;
	float n = 0, n2=0,i=0;

	char res[20], res2[20];
	while(1){
	for(i=0,n=0,n2=0;i<samples;i++){
		n += TM_HCSR04_Read(&HCSR2);
		Delayms(30);
		n2 += TM_HCSR04_Read(&HCSR1);
		Delayms(30);
	}

	n = n/samples;
	n2 = n2/samples;

	ftoa(n2, res2, precision);
	ftoa(n, res, precision);

	TM_HD44780_Clear();
	TM_HD44780_Puts(2,0,res);
	TM_HD44780_Puts(10,0,res2);

	strzaleczki((int)(n/10),poz);
	strzaleczki((int)(n2/10),poz2);
	Delayms(200);
	}
}
