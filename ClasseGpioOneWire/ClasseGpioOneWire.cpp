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
#include  <bcm2835.h>
#include "ClasseGpioOneWire.h"

ClasseGpioOneWire::ClasseGpioOneWire(bool initialiseBcm2835 = true) : ClasseGpioBase() {
// SORTIE/ENTREE sont dans ClasseGpioBase.h, OUTPUT est dans wiringPi.h, BCM2835_GPIO_FSEL_INPT / BCM2835_GPIO_FSEL_OUTP dans bcm2835.h
// initialiseBcm2835 accompli l'initialisation du bcm2835 seulement dans la classe extérieure.
//	this->m_numeroPatte, this->m_direction  et this->m_retour sont initialisé dans la classe de base
	if (initialiseBcm2835) {
		if (!bcm2835_init()) {
			this->m_retour = ERREUR;
			return;
		}
		this->m_retour = OK;
	}
}

ClasseGpioOneWire::~ClasseGpioOneWire(void) {
	razPatte();
	std::cout << std::endl << "Destruction de la classe ClasseGpioOneWire." << std::endl;
}

// OneWire
// ordre des bits, mode (0-3), diviseur (x-y), selection (BCM2835_SPI_CS0, CS1), polarité (HAUT/BAS)
void ClasseGpioOneWire::initialiseOneWire(uint8_t ordreBit, uint8_t mode, uint16_t diviseur, uint8_t selectionCS, uint8_t polarité) {
}

void ClasseGpioOneWire::fermeOneWire(void) {
}


