#pragma once

#include "Tupla.h"
#include "Puntero.h"

template <class C>
class ComparacionTupla : public Comparacion <Tupla<C, C>>
{

public:

	ComparacionTupla()
	{
		comp = Comparador<C>::Default;
	};

	ComparacionTupla(const Comparador<C> &c)
	{
		comp = c;
	};

	CompRetorno Comparar(const Tupla<C, C>&t1, const Tupla<C, C>&t2) const
	{
		if (comp.SonIguales(t1.ObtenerDato1(), t2.ObtenerDato1()) && comp.SonIguales(t1.ObtenerDato2(), t2.ObtenerDato2()))
		{
			return IGUALES;
		}
		else
		{
			return MENOR;
		}
	};

private:

	Comparador<C> comp;

};