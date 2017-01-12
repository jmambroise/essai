/*#include  <bcm2835.h>
#include "GPIO.h"

//int patte = 	// patte 4 du connecteur 40 point RPi 2B
*/
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <bcm2835.h>
#include "../ClasseGpioBase/ClasseGpioBase.h"
#include "ClasseGpioOneWire.h"

using namespace std;


//int patteLED	= RPI_BPLUS_GPIO_J8_12;	// Patte n° 12 (RPI_BPLUS_GPIO_J8_12) = GPIO 18 : c'est la valeur qui est passée bcm2835_gpio_fsel()
ClasseGpioOneWire* unFil;				// Pointeur sur la classe de base

void sig_handler(int sig);
 
bool ctrl_c_pressed = false;

int main(int argc, char** argv) {
	struct sigaction sig_struct;
	sig_struct.sa_handler = sig_handler;
	sig_struct.sa_flags = 0;
	sigemptyset(&sig_struct.sa_mask);

	if (sigaction(SIGINT, &sig_struct, NULL) == -1) {
		cout << "Problème avec sigaction" << endl;
		exit(1);
	}

	printf("Pwm sur Raspberry PI 2 B\n");
	unFil = new ClasseGpioOneWire(patteLED, SORTIE, true); // Initialisation du bcm2835 dans la classe ClasseGpioOneWire et de la patte n° 12 (gpio 18) en sortie.
	if (unFil->classeInitialisee() == ERREUR) {
		cout << "Erreur dans l'initialisation de la classe gpioPatte 7 (ClasseGpioOneWire). Sortie de l'application....." << endl;
		return ERREUR;
	}
	unFil->clignotte();

    cout << "Sortie de l'application....." << endl;
	return OK;
}

void sig_handler(int sig) {
	write(0, "\n-> Ctrl-C (^C)  a été pressé dans le gestionnaire de signaux.\n", 64);
	ctrl_c_pressed = true;
	if(ctrl_c_pressed) {
		cout  << endl << "Ctrl-C (^C) a été pressé." << endl;
		cout << "Déallocation des pattes utilisée. " << flush;
 		cout << "Déallocation des objets GPIO." << endl;
 		if (unFil)
			delete unFil;
		unFil = 0;
	}
	cout << "Sortie de l'application....." << endl;
}