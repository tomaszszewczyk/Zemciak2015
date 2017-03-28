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

#include "zemciak.h"

int8_t engineLeft[ENGINE];
int8_t engineRight[ENGINE];
uint16_t timing[ENGINE];
uint8_t index = 0;
uint8_t end = 0;

int main()
{
	ledInit();
	sonarInit();
	engineInit();
	lineInit();
	switchInit();
	loopInit();
	debugInit();
	adcInit();
	sei();

	bool strona = false;
	uint8_t proba = 0;
	uint16_t ataktime = 0;
	uint16_t szukanietime = 0;

	while(1)
	{
		//--------------------------------------------------------------------------
		//Moduł atak

		ataktime = 0;

		while(sonarMin() < 200)
		{
			if(ataktime <= ATAK)
			{
				if(sonarLeft() < sonarRight()) {ledFL(true); ledFR(false);}
				else {ledFR(true); ledFL(false);}

				if(sonarLeft() > sonarRight() - 10 && sonarRight() > sonarLeft() - 10)
					setEngine(127, 127);
				else if(sonarLeft() > sonarRight())
					setEngine(127, 0);
				else
					setEngine(0, 127);

				if(sonarLeft() < sonarRight()) strona = false;
				else strona = true;

				if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
					goto linia;

				ataktime++;
			}
			else
			{
				ataktime = 0;
			}
		}

		//--------------------------------------------------------------------------
		//Moduł szukanie

		szukanietime = 0;

		while(sonarMin() > 200)
		{
			if(szukanietime < SZUKANIE)
			{
				if(sonarLeft() < sonarRight()) {ledFL(true); ledFR(false);}
				else {ledFR(true); ledFL(false);}

				if(strona == false)
					setEngine(-127, 127);
				else
					setEngine(127, -127);

				if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true )
					goto linia;

				_delay_ms(1);
				szukanietime++;
			}
			else
			{
				setEngine(127, 127);
				if(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true )
					goto linia;
			}
		}

		linia:
		//--------------------------------------------------------------------------
		//Moduł linia
		while(lineFR() == true || lineFL()  == true || lineBR()  == true || lineBL() == true)
		{
			if(lineFR() == true)
			{
				setEngine(-127,-110);
				_delay_ms(250);
				strona = false;
			}
			if(lineFL() == true)
			{
				setEngine(-110,-127);
				_delay_ms(250);
				strona = true;
			}

			if(lineBR() == true)
			{
				setEngine(110,127);
				_delay_ms(250);
				strona = false;
			}
			if(lineBL() == true)
			{
				setEngine(127,110);
				_delay_ms(250);
				strona = true;
			}


			if(sonarAvg() < 200)
			{
				proba++;
				if(proba > PROBA)
				{
					if(strona == false)
						setEngine(-127, 127);
					else
						setEngine(127, -127);
					_delay_ms(500);
					proba = 0;
				}
			}
		}
	}
}

void loopInit()
{
	ASSR &= ~(1 << AS2);
	TCCR2 |= (1 << WGM21) | (1 << CS22) | (1 << CS21) | (1 << CS20);	//CTC, div1024
	OCR2 = 150; //T=10ms
	TIMSK |= (1 << OCIE2);
}

ISR(TIMER2_COMP_vect)
{
	char nadawanie[100];

	sprintf(nadawanie, "%3d %3d %3d\n", adcBattery(), adcEngineLeft(), adcEngineRight());
	send(nadawanie);
}

void switchInit()
{
	DDRD &= ~(1 << PD3);
	PORTD |= (1 << PD3);
}

bool getSwitch()
{
	if(PIND & (1 << PD3))
	{
		_delay_ms(10);
		if(PIND & (1 << PD3))
			return false;
	}
	else return true;
	return true;
}
