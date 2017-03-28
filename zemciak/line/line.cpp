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

#include "line.h"

void lineInit()
{
	DDRD |= (1 << PD6);	//Zasilanie czujków
	PORTD &= ~(1 << PD6);	//Zapal

	DDRD &= ~((1 << PD7));	//Czujniki, wyłącz pullup
	PORTD &= ~((1 << PD7));

	DDRC &= ~((1 << PC0));
	PORTC &= ~((1 << PC0));

	DDRB &= ~((1 << PB1) | (1 << PB0));
	PORTB &= ~((1 << PB1) | (1 << PB0));
}

bool lineFR()
{
	if(!(PIND & (1 << PD7)))
	{
		_delay_us(500);
		if(!(PIND & (1 << PD7)))
		{
			_delay_us(500);
			if(!(PIND & (1 << PD7)))
				return true;
		}
	}

	else return false;
}

bool lineFL()
{
	if(!(PINB & (1 << PB1)))
	{
		_delay_us(500);
		if(!(PINB & (1 << PB1)))
		{
			_delay_us(500);
			if(!(PINB & (1 << PB1)))
				return true;
		}
	}

	else return false;
}

bool lineBR()
{
	if(!(PINC & (1 << PC0)))
	{
		_delay_us(500);
		if(!(PINC & (1 << PC0)))
		{
			_delay_us(500);
			if(!(PINC & (1 << PC0)))
				return true;
		}
	}

	else return false;
}

bool lineBL()
{
	if(!(PINB & (1 << PB0)))
	{
		_delay_us(500);
		if(!(PINB & (1 << PB0)))
		{
			_delay_us(500);
			if(!(PINB & (1 << PB0)))
				return true;
		}
	}

	else return false;
}
