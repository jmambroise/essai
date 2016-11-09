/*
Déclarations pour la classe GPIO
*/

#ifndef	__CLASSE_GPIO_CLIGNOTTANT_H__
#define	__CLASSE_GPIO_CLIGNOTTANT_H__

#include "../ClasseGpioBase/ClasseGpioBase.h"

class ClasseGpioClignotant : public ClasseGpioBase {
public:
	ClasseGpioClignotant(int patte, int direction, bool initialiseBcm2835);
	~ClasseGpioClignotant();
	int clignote(void);
};




#endif