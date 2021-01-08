#ifndef LISTAORDARRAY_CPP
#define LISTAORDARRAY_CPP

#include "ListaOrdArray.h"

template <class T>
ListaOrdArray<T>::ListaOrdArray(const Comparador<T> &c) 
{
	elementos = Array<T>(0);
	largo = 0;
	comp = c;
}

template <class T>
ListaOrdArray<T>::~ListaOrdArray()
{
	elementos = NULL;
	largo = 0;
	comp = NULL;
}

template <class T>
void ListaOrdArray<T>::InsertarOrdenado(const T& e)
{
	largo++;

	if (largo > elementos.ObtenerLargo())
	{
		Array<T> mayor(largo);
		mayor.Copiar(elementos, mayor);
		elementos = mayor;
	}

	nat posAInsertar = 0;

	while ((posAInsertar < largo - 1) && comp.EsMenor(elementos[posAInsertar], e))
	{
		posAInsertar++;
	}

	if (posAInsertar != largo - 1)
	{
		elementos.Copiar(elementos, posAInsertar, largo - posAInsertar - 1, elementos, posAInsertar + 1);
	}

	elementos[posAInsertar] = e;
}

template <class T>
const T& ListaOrdArray<T>::Cabeza() const
{
	return elementos[0];
}

template<class T>
void ListaOrdArray<T>::EliminarPrimero()
{
	Array<T> nueva = Array<T>(elementos.Largo - 1);

	for (nat i = 1; i < elementos.Largo; i++)
	{
		nueva[i - 1] = elementos[i];
	}

	elementos = nueva;

	largo--;
};

template <class T>
void ListaOrdArray<T>::Eliminar(const T& e) 
{
	if (Pertenece(e))
	{
		Array<T> nueva = Array<T>(elementos.Largo - 1);
		nat posAInsertar = 0;

		for (nat i = 0; i < elementos.Largo; i++)
		{
			if (!comp.SonIguales(elementos[i], e))
			{
				nueva[posAInsertar] = elementos[i];
				posAInsertar++;
			}
		}

		elementos = nueva;

		largo--;
	}
}

template<class T>
void ListaOrdArray<T>::EliminarUltimo()
{
	if (!EstaVacia())
	{
		largo--;

		Array<T> nuevo = Array<T>(largo);

		for (nat i = 0; i < largo; i++)
		{
			nuevo[i] = elementos[i];
		}

		elementos = nuevo;
	}
};

template <class T>
nat ListaOrdArray<T>::Largo() const 
{
	return largo;
}

template <class T>
const T& ListaOrdArray<T>::Obtener(const nat n) const 
{
	if (n < largo)
	{
		return elementos[n];
	}
	else
	{
		return *(new T());
	}
}

template <class T>
bool ListaOrdArray<T>::Pertenece(const T& e) const 
{
	for (nat i = 0; i < elementos.Largo; i++)
	{
		if (comp.SonIguales(elementos[i], e))
		{
			return true;
		}
	}

	return false;
}

template <class T>
bool ListaOrdArray<T>::EstaVacia() const
{
	return (largo == 0);
}

template <class T>
Puntero<ListaOrd<T>> ListaOrdArray<T>::Clon() const
{
	Puntero<ListaOrdArray<T>> nueva = new ListaOrdArray<T>(comp);

	nueva->elementos = Array<T>(elementos.ObtenerLargo());
	elementos.Copiar(elementos, nueva->elementos);
	nueva->largo = largo;

	return nueva;
}

template <class T>
Iterador<T> ListaOrdArray<T>::ObtenerIterador() const
{
	return elementos.ObtenerIterador();
}

#endif