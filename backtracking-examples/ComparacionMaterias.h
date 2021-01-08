#ifndef COMPARACIONMATERIAS_H
#define COMPARACIONMATERIAS_H

#include "Cadena.h"
#include "Comparador.h"
#include "Tupla.h"

class ComparacionMaterias : public Comparacion <Tupla<Cadena, bool>>
{

public:

	ComparacionMaterias() { };

	CompRetorno Comparar(const Tupla<Cadena, bool>& e1, const Tupla<Cadena, bool>& e2) const
	{
		if (e1.ObtenerDato1() == e2.ObtenerDato1())
		{
			return IGUALES;
		}

		return MENOR;
	}

};

#endif