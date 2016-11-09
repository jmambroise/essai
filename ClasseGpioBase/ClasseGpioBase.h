/*
Déclarations pour la classe GPIO
*/

#ifndef	__CLASSE_GPIO_BASE_H__
#define	__CLASSE_GPIO_BASE_H__

// Constantes compatibles wiringPi.h et bcm2835.h
#define ENTREE	0x00
#define SORTIE	0x01
#define BAS		0x00
#define HAUT	0x01
#define ERREUR	0x00
#define OK		0x01
#define GPIO_FONCTION_ALT0 0x04   /*!< Alternate function 0 0b100 */
#define GPIO_FONCTION_ALT1 0x05   /*!< Alternate function 1 0b101 */
#define GPIO_FONCTION_ALT2 0x06   /*!< Alternate function 2 0b110, */
#define GPIO_FONCTION_ALT3 0x07   /*!< Alternate function 3 0b111 */
#define GPIO_FONCTION_ALT4 0x03   /*!< Alternate function 4 0b011 */
#define GPIO_FONCTION_ALT5 0x02   /*!< Alternate function 5 0b010 */
#define GPIO_FONCTION_MASK 0x07   /*!< Function select bits mask 0b111 */

class ClasseGpioBase {
public:
	// patte désigne le GPIO corespondant à la patte voulue, voir bcm2835 ligne 664 etc..., par exemple RPI_BPLUS_GPIO_J8_03 (patte 3) =  2 (GPIO 2)...
	//direction est ENTREE ou SORTIE.
	ClasseGpioBase(int patte, int direction, bool initialiseBcm2835);
	// retourne OK si l'initialisation a réussi, ERREUR sinon.
	int classeInitialisee(void);
	int lisPatte(void);
	int ecrisPatte(int valeur);
	void delais(unsigned int millis);
	void razPatte(void);
	
protected:
	int m_numeroPatte;
	int m_direction;
	int m_retour;
};




#endif