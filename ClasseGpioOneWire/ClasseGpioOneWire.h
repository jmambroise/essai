/*
Déclarations pour la classe GPIO
*/

#ifndef	__CLASSE_GPIO_SPI_H__
#define	__CLASSE_GPIO_SPI_H__

#include "../ClasseGpioBase/ClasseGpioBase.h"

class ClasseGpioOneWire : public ClasseGpioBase {
public:
	ClasseGpioOneWire(bool);
	~ClasseGpioOneWire();

	// Gestion du bus SPI
	// - P1-19 (MOSI)
	// - P1-21 (MISO) 
	// - P1-23 (CLK) 
	// - P1-24 (CE0) 
	// - P1-26 (CE1)
	// arguments	  ordreBit, mode,   diviseur,  selectionCS, polarité
	void initialiseOneWire(uint8_t, uint8_t, uint16_t, uint8_t, uint8_t);
	void fermeOneWire(void);
};




#endif