/*#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

//int patte = 	// patte 4 du connecteur 40 point RPi 2B
*/
#include <signal.h>
#include <stdio.h>
#include <iostream>
#//#include <wiringPi.h>
#include  <bcm2835.h>
#include "../ClasseGpioBase/ClasseGpioBase.h"
#include "ClasseGpioClignotant.h"

ClasseGpioClignotant::ClasseGpioClignotant(int patte, int direction = SORTIE, bool initialiseBcm2835 = true) : ClasseGpioBase(patte, direction, false) {
// SORTIE/ENTREE sont dans ClasseGpioClignotant.h, OUTPUT est dans wiringPi.h, BCM2835_GPIO_FSEL_INPT / BCM2835_GPIO_FSEL_OUTP dans bcm2835.h
// avec bcm2835.h, la patte a pour vateur réelle le n° GPIO mais pas la patte réelle : Patte n° 7 (RPI_BPLUS_GPIO_J8_07) -> 4 (GPIO 4)
// initialiseBcm2835 accompli l'initialisation du bcm2835 seulement dans la classe extérieure.
//	this->m_numeroPatte, this->m_direction  et this->m_retour sont initialisé dans la classe de base
	if (initialiseBcm2835) {
		if (!bcm2835_init()) {
			return;
		}
		bcm2835_gpio_fsel(patte, direction);
		this->m_retour = OK;
	}
}

int ClasseGpioClignotant::clignote(void) {
	if (m_direction == ENTREE) {
		return ERREUR;	// Raté, la patte n'est pas en sortie
	}
	int i, valeur;
	for (i = 0; i < 20; i++) {
		ecrisPatte(HAUT);
		valeur = lisPatte();
		std::cout << i << " : " << valeur << std::flush;
		delais(1000);
	
		ecrisPatte(BAS);
		valeur = lisPatte();
		std::cout << " -> " << valeur << std::endl;
		delais(1000);
    }
 	return OK;
}


ClasseGpioClignotant::~ClasseGpioClignotant(void) {
	bcm2835_gpio_write(this->m_numeroPatte, BAS);
	bcm2835_close();
}
