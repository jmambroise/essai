/*#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

//int patte = 	// patte 4 du connecteur 40 point RPi 2B
*/
#include <signal.h>
#include <stdio.h>
#include <wiringPi.h>
#include  <bcm2835.h>
#include "ClasseGpioBase.h"

ClasseGpioBase::ClasseGpioBase(int patte, int direction = SORTIE) {	// SORTIE/ENTREE sont dans ClasseGpioBase.h, OUTPUT est dans wiringPi.h
	this->m_numeroPatte = patte;
	this->m_direction = direction;
	wiringPiSetup();
	pinMode(m_numeroPatte, direction);
}

int ClasseGpioBase::clignote(void) {
	if (m_direction == ENTREE) {
		return 1;	// Raté, la patte n'est pas en sortie
	}
	int i;
	for (i = 0; i < 20; i++) {
		digitalWrite(m_numeroPatte, HAUT);	// On
		delay(1000);						// mS
		digitalWrite(m_numeroPatte, BAS);	// Off
		delay(1000);
	}
	return 0;
}
