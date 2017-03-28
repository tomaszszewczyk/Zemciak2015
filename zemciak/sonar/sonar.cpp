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

#include "sonar.h"

uint8_t sonarL = 0xFF;
uint8_t sonarR = 0xFF;

void sonarInit()
{
	//Inicjalizacja SONARu/SPI
	DDRB |= (1 << PB7) | (1 << PB4); //SCK, SS jako wyjście
	DDRB &= ~(1 << PB6); //MISO jako wejście
	PORTB |= (1 << PB4); //SS stan wysoki
	DDRC |= (1 << PC7);	//aktywacja jako wyjście
	PORTC |= (1 << PC7); //dezaktywacja sonaru
	SPCR |= (1 << MSTR) | (1 << SPE) | (1 << SPR1) | (1 << SPR0); //Master, odblokowany, div64

	//Przerwanie
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TIMSK |= (1 << TOIE0);
}

uint8_t sonarLeft() {return sonarL;}
uint8_t sonarRight() {return sonarR;}
uint8_t sonarMin() {return sonarL < sonarR ? sonarL : sonarR;}
uint8_t sonarMax() {return sonarL > sonarR ? sonarL : sonarR;}
uint8_t sonarAvg() {return ((sonarL + sonarR) / 2);}

ISR(TIMER0_OVF_vect)
{
	static uint8_t bufferL[SONAR_PROBES+1], bufferR[SONAR_PROBES+1];	//Bufory do obliczeń
	static uint8_t index = 0;
	uint32_t tmp;

	PORTC &= ~(1<< PC7);	//Aktywowanie nadajnika
	_delay_us(5);

	SPDR = 0;	//Pobieranie wyniku
	while(!(SPSR & (1<<SPIF)));
	bufferL[index] = SPDR;

	_delay_us(5);

	SPDR = 0;	//Pobieranie drugiego bajtu
	while(!(SPSR & (1<<SPIF)));
	bufferR[index] = SPDR;

	index++;	//Zawijanie indexu
	if(index > SONAR_PROBES) index = 0;

	tmp = 0;
	for(uint8_t i = 0; i < SONAR_PROBES; i++) tmp += (uint32_t) bufferL[i];	//Uśrednianie wyników
	sonarL = tmp/SONAR_PROBES;

	tmp = 0;
	for(uint8_t i = 0; i < SONAR_PROBES; i++) tmp += (uint32_t) bufferR[i];
	sonarR = tmp/SONAR_PROBES;

	PORTC |= (1<< PC7); //dezaktywacja nadajnika, uruchomienie kolejnego pomiaru

	/*PORTC &= ~(1<< PC7);	//Aktywowanie nadajnika
	_delay_us(5);

	SPDR = 0;	//Pobieranie wyniku
	while(!(SPSR & (1<<SPIF)));
	sonarL = SPDR;

	_delay_us(5);

	SPDR = 0;	//Pobieranie drugiego bajtu
	while(!(SPSR & (1<<SPIF)));
	sonarR = SPDR;

	PORTC |= (1<< PC7); //dezaktywacja nadajnika, uruchomienie kolejnego pomiaru*/

}
