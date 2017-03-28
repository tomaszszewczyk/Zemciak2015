/***
 *
 *
 *    ZZZZZZZZZZZZZZZZZZZ                                                                  iiii                    kkkkkkkk
 *    Z:::::::::::::::::Z                                                                 i::::i                   k::::::k
 *    Z:::::::::::::::::Z                                                                  iiii                    k::::::k
 *    Z:::ZZZZZZZZ:::::Z                                                                                           k::::::k
 *    ZZZZZ     Z:::::Z      eeeeeeeeeeee       mmmmmmm    mmmmmmm       cccccccccccccccciiiiiii   aaaaaaaaaaaaa    k:::::k    kkkkkkk
 *            Z:::::Z      ee::::::::::::ee   mm:::::::m  m:::::::mm   cc:::::::::::::::ci:::::i   a::::::::::::a   k:::::k   k:::::k
 *           Z:::::Z      e::::::eeeee:::::eem::::::::::mm::::::::::m c:::::::::::::::::c i::::i   aaaaaaaaa:::::a  k:::::k  k:::::k
 *          Z:::::Z      e::::::e     e:::::em::::::::::::::::::::::mc:::::::cccccc:::::c i::::i            a::::a  k:::::k k:::::k
 *         Z:::::Z       e:::::::eeeee::::::em:::::mmm::::::mmm:::::mc::::::c     ccccccc i::::i     aaaaaaa:::::a  k::::::k:::::k
 *        Z:::::Z        e:::::::::::::::::e m::::m   m::::m   m::::mc:::::c              i::::i   aa::::::::::::a  k:::::::::::k
 *       Z:::::Z         e::::::eeeeeeeeeee  m::::m   m::::m   m::::mc:::::c              i::::i  a::::aaaa::::::a  k:::::::::::k
 *    ZZZ:::::Z     ZZZZZe:::::::e           m::::m   m::::m   m::::mc::::::c     ccccccc i::::i a::::a    a:::::a  k::::::k:::::k
 *    Z::::::ZZZZZZZZ:::Ze::::::::e          m::::m   m::::m   m::::mc:::::::cccccc:::::ci::::::ia::::a    a:::::a k::::::k k:::::k
 *    Z:::::::::::::::::Z e::::::::eeeeeeee  m::::m   m::::m   m::::m c:::::::::::::::::ci::::::ia:::::aaaa::::::a k::::::k  k:::::k
 *    Z:::::::::::::::::Z  ee:::::::::::::e  m::::m   m::::m   m::::m  cc:::::::::::::::ci::::::i a::::::::::aa:::ak::::::k   k:::::k
 *    ZZZZZZZZZZZZZZZZZZZ    eeeeeeeeeeeeee  mmmmmm   mmmmmm   mmmmmm    cccccccccccccccciiiiiiii  aaaaaaaaaa  aaaakkkkkkkk    kkkkkkk
 *
 *		Ola Druciak & Patrycja Zemankiewicz & Grzegorz Dobroń & Tomasz Szewczyk
 *		II LO Świdnica
 *		Diversity 2015, Kraków
 */

#include "engine.h"

void setEngine(int8_t left, int8_t right)
{
	int8_t swap; // Było odwrotnie, a nie chce mi się przepisywać funkcji

	swap = left;
	left = right;
	right = swap;

	if(left >= 0)
	{
		PORTC |= (1 << PC2);	//Kierunek
		PORTC &= ~(1 << PC4);

		if(left == 0) OCR1A = 0;	//PWM
		else OCR1A = (left*2) + 1;
	}

	if(left < 0)
	{
		PORTC &= ~(1 << PC2);
		PORTC |= (1 << PC4);

		OCR1A = (left*(-2)) + 1;
	}

	if(right >= 0)
	{
		PORTC |= (1 << PC6);
		PORTC &= ~(1 << PC5);

		if(right == 0) OCR1B = 0;
		else OCR1B = (right*2) +1;
	}

	if(right < 0)
	{
		PORTC &= ~(1 << PC6);
		PORTC |= (1 << PC5);

		OCR1B = (right*(-2)) + 1;
	}
}

void engineInit()
{
	DDRC |= (1 << PC6) | (1 << PC5) | (1 << PC4) | (1 << PC2);		//Piny sterujące, wyjście, niski
	PORTC &= ~((1 << PC6) | (1 << PC5) | (1 << PC4) | (1 << PC2));

	DDRD |= (1 << PD5) | (1 << PD4);	//Piny PWM, wyjście, niski
	PORTD &= ~((1 << PD5) | (1 << PD4));

    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);	//Korekcja fazy 8-bit, div64
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

	OCR1A = 0;
	OCR1B = 0;
}
