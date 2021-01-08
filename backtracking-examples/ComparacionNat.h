#ifndef COMPARACIONNAT_H
#define COMPARACIONNAT_H

#include "Comparador.h"

class ComparacionNat : public Comparacion<unsigned int> {

public:

	ComparacionNat() {};

	CompRetorno Comparar(const unsigned int& e1, const unsigned int& e2) const
	{
		if (e1 == e2)
		{
			return IGUALES;
		}
		else
		{
			return MENOR;
		}
	}
};

#endif