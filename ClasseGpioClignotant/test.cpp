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
#include "ClasseGpioClignotant.h"

using namespace std;


int patteLED	= RPI_BPLUS_GPIO_J8_07;	// Patte n° 7 (RPI_BPLUS_GPIO_J8_07) = GPIO 4 : c'est la valeur qui est passée bcm2835_gpio_fsel()
//int patteBouton	= RPI_BPLUS_GPIO_J8_13;	// Patte n° 13 (RPI_BPLUS_GPIO_J8_13) = GPIO 27
ClasseGpioClignotant* gpioPatte7;				// Pointeur sur la classe de base

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

	printf("Clignotant sur Raspberry PI 2 B\n");
	gpioPatte7 = new ClasseGpioClignotant(patteLED, SORTIE, true); // Initialisation du bcm2835 dans la classe ClasseGpioClignotant et de la patte n° 7 (gpio 4) en sortie.
	if (gpioPatte7->classeInitialisee() == ERREUR) {
		cout << "Erreur dans l'initialisation de la classe gpioPatte 7 (ClasseGpioClignotant). Sortie de l'application....." << endl;
		return ERREUR;
	}
	gpioPatte7->clignote();

    cout << "Sortie de l'application....." << endl;
	return OK;
}

void sig_handler(int sig) {
	write(0, "\n-> Ctrl-C (^C)  a été pressé dans le gestionnaire de signaux.\n", 70);
	ctrl_c_pressed = true;
	if(ctrl_c_pressed) {
		cout  << endl << "Ctrl-C (^C) a été pressé." << endl;
		cout << "Déallocation des pattes utilisée" << endl;
 		cout << "Déallocation des objets GPIO." << endl;
 		if (gpioPatte7)
			delete gpioPatte7;
		gpioPatte7 = 0;
	}
	cout << "Sortie de l'application....." << endl;
}