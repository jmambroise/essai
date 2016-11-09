/*#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

//int patte = 	// patte 4 du connecteur 40 point RPi 2B
*/
#include <signal.h>
#include <stdio.h>
//#include <wiringPi.h>
#include  <bcm2835.h>
#include "ClasseGpioBase.h"

ClasseGpioBase::ClasseGpioBase(int patte = 0, int direction = ENTREE, bool initialiseBcm2835 = false) {
// SORTIE/ENTREE sont dans ClasseGpioBase.h, OUTPUT est dans wiringPi.h, BCM2835_GPIO_FSEL_INPT / BCM2835_GPIO_FSEL_OUTP dans bcm2835.h
//	avec bcm2835.h, la patte a pour vateur réelle le n° GPIO mais pas la patte réelle : Patte n° 7 (RPI_BPLUS_GPIO_J8_07) -> 4 (GPIO 4)
	this->m_numeroPatte = patte;
	this->m_direction = direction;
	this->m_retour = ERREUR;
	if (initialiseBcm2835) {
		if (!bcm2835_init()) {
			return;
		}
		if (this->m_numeroPatte > 0) {
			bcm2835_gpio_fsel(patte, direction);
			this->m_retour = OK;
		}
	}
}

int ClasseGpioBase::classeInitialisee(void) {
	return this->m_retour;
}

int ClasseGpioBase::lisPatte(void) {
	if (this->m_numeroPatte > 0) {
		return bcm2835_gpio_lev(this->m_numeroPatte);
	}
	return ERREUR;
}

int ClasseGpioBase::ecrisPatte(int valeur) {
	valeur &= 0x01;	// valeur doit être HAUT (1) ou BAS (0)
	if ((this->m_direction == SORTIE) || (this->m_numeroPatte > 0)) {
		bcm2835_gpio_write(this->m_numeroPatte, valeur);
		return OK;
	}
	return ERREUR;
}

void ClasseGpioBase::delais(unsigned int millis) {
	bcm2835_delay (millis);
}

void ClasseGpioBase::razPatte(void) {
	if (this->m_numeroPatte > 0)
		bcm2835_gpio_write(this->m_numeroPatte, ENTREE);
//	bcm2835_close();	// ???
	this->m_direction = ENTREE;
}



