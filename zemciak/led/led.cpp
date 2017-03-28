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

#include "led.h"

void ledInit()
{
	//Inicjalizacja LEDów
	LED_FR_DDR |= (1 << LED_FR);
	LED_FL_DDR |= (1 << LED_FL);
	LED_BR_DDR |= (1 << LED_BR);
	LED_BL_DDR |= (1 << LED_BL);
}

void ledFR(bool onoff) {if(onoff == true) LED_FR_PORT |= (1 << LED_FR); else LED_FR_PORT &= ~(1 << LED_FR);}
void ledFL(bool onoff) {if(onoff == true) LED_FL_PORT |= (1 << LED_FL); else LED_FL_PORT &= ~(1 << LED_FL);}
void ledBR(bool onoff) {if(onoff == true) LED_BR_PORT |= (1 << LED_BR); else LED_BR_PORT &= ~(1 << LED_BR);}
void ledBL(bool onoff) {if(onoff == true) LED_BL_PORT |= (1 << LED_BL); else LED_BL_PORT &= ~(1 << LED_BL);}
