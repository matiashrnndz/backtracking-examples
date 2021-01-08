#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Producto.h"
#include "ComparacionTupla.h"
#include "ListaOrdArray.h"
#include "ComparacionMaterias.h"
#include "ComparacionICiudad.h"
#include "ComparacionNat.h"

class Sistema : public ISistema
{

public:

	Sistema();

	Iterador<Tupla<nat,nat>> Laberinto(Tupla<nat,nat> &inicio, Tupla<nat,nat> &fin, Matriz<nat> &laberinto) override;

	virtual Iterador<Iterador<Puntero<ICiudad>>> Viajero(Array<Puntero<ICiudad>> &ciudadesDelMapa, Matriz<nat> &mapa, Puntero<ICiudad> &ciudadPartida, Iterador<Puntero<ICiudad>> &ciudadesPasar, nat costoMax) override;
	
	virtual Array<nat> Intercalar(Array<nat> &arreglo, nat i, nat m, nat d) override;

	virtual Array<nat> Degustacion(Array<Producto> productos, nat maxDinero, nat maxCalorias, nat maxAlcohol) override;

	//PRE: relacionesCiudades representa la matriz de adyacencia. Para un par de ciudades i,j relacionCiudades[i][j] devuelve una tupla con el costo, distancia y dinero (en ese orden) necesarios para viajar desde i hasta j.
	//POS: se retorna OK y un iterador con las ciudades a recorrer en orden.
	virtual Tupla<TipoRetorno, Iterador<nat>> Viajero2(Matriz<Tupla<nat, nat, nat>> relacionesCiudades, Iterador<nat> CiudadesPasar, Iterador<nat> CiudadesNoPasar) override;

	//PRE: recibe una array con todas las acciones posibles, indicando los recursos que se necesitan para cada accion y el impacto que tiene.
	//POST: retorna OK y un array de booleanos indicando cuántas veces realizar cada acción para maximizar el impacto.
	virtual Tupla<TipoRetorno,  Array<nat>> ProteccionAnimales(Array<Accion> acciones, nat maxVeterinarios, nat maxVehiculos, nat maxDinero, nat maxVacunas, nat maxVoluntarios) override;

	//POST: Ordena el array usando la tecnica de quicksort.
	virtual Array<nat> QuickSort(Array<nat> elementos) override;

	//PRE: pasar y noPasar son iteradores de casillas validas
	//POS: OK si existe camino. Iterador de mejores camino (cada camino se representa con un Iterador de casillas o Tuplas<int, int>)
	virtual Tupla<TipoRetorno, Iterador<Iterador<Tupla<int, int>>>> CaminoCaballo(Tupla<int, int>& salida, Tupla<int, int>& destino, nat cantAPasar, nat tamTablero, Iterador<Tupla<int, int>>& pasar, Iterador<Tupla<int, int>>& noPasar) override;

	//PRE: semillas es un Array que contiene una Tupla de <costo siembra, agua necesaria, ganancia>
	//POS: se retorna OK, y un array indicando cantidad de hectáreas por especie.
	virtual Tupla<TipoRetorno, Array<nat>> OptimizarGranja(Array<Tupla<nat, nat, nat>>& semillas, nat dinero, nat tierra, nat agua) override;

	//PRE: matutino y nocturno representan un Iterador de Tupla<materia, creditos, horas>
	//POS: OK si existe solución y un iterador de Tupla<materia, es de turno matutino>
	virtual Tupla<TipoRetorno, Iterador<Tupla<Cadena, bool>>> InscribirMaterias(Iterador<Tupla<Cadena, nat, nat>> matutino, Iterador<Tupla<Cadena, nat, nat>> nocturno, nat horasM, nat horasN) override;

private:

	// EJERCICIO 1

	void LaberintoBT(Matriz<nat>& laberinto, Tupla<nat, nat>& fin, Array<int> movX, Array<int> movY,
		Puntero<ListaOrdArray<Tupla<nat, nat>>>& solucion, int& cambiosDireccionMin,
		Puntero<ListaOrdArray<Tupla<nat, nat>>> solActual, int cambiosDireccionActual, Tupla<int, int> ultimoCambio, Tupla<nat, nat> actual);

	Matriz<nat> ClonarMatriz(const Matriz<nat>& mat);

	bool CoordenadaValida(int x, int y, Matriz<nat> laberinto);

	// EJERCICIO 2

	void ViajeroBT(Array<Puntero<ICiudad>>& ciudadesDelMapa, Matriz<nat>& mapa, Puntero<ICiudad>& ciudadPartida, Iterador<Puntero<ICiudad>>& ciudadesPasar,
		Puntero<ListaOrdArray<Iterador<Puntero<ICiudad>>>>& soluciones, int& mejorCosto, int& menorCantCiudades,
		Puntero<ListaOrdArray<Puntero<ICiudad>>> caminoActual, int costoActual, int cantidadCiudades, Puntero<ICiudad> ciudadActual);

	bool PasaPorTodos(Iterador<Puntero<ICiudad>> &ciudadesPasar, Puntero<ListaOrdArray<Puntero<ICiudad>>>& caminoActual);

	nat ObtenerPosCiudad(Array<Puntero<ICiudad>> &ciudadesDelMapa, Puntero<ICiudad> ciudadActual);

	// EJERCICIO 4

	void DegustacionBT(Array<Producto>& productos, nat actual,
		Array<nat>& solucion, nat& preferenciaMax, nat& dineroMax, nat& caloriasMax, nat& alcoholMax,
		Array<nat> solucionActual, nat preferenciaActual, nat dineroActual, nat caloriasActual, nat alcoholActual);

	// EJERCICIO 6

	void Sistema::ProteccionAnimalesBT(Array<Accion>& acciones, nat actual,
		Array<nat>& solucion, nat& veterinariosMax, nat& vehiculosMax, nat& dineroMax, nat& vacunasMax, nat& voluntariosMax, nat& impactoMax,
		Array<nat> solucionActual, nat veterinariosActual, nat vehiculosActual, nat dineroActual, nat vacunasActual, nat voluntariosActual, nat impactoActual);

	// EJERCICIO 7

	void QuickSortDC(Array<nat> elementos, nat inicio, nat fin);

	nat ReOrdenar(Array<nat> elementos, nat inicio, nat fin);

	// EJERCICIO 8

	void CaminoCaballoBT(Tupla<int, int> actual, Tupla<int, int> anterior, Matriz<nat>& tablero, Array<int>& movX, Array<int>& movY,
		Puntero<ListaOrdArray<Iterador<Tupla<int, int>>>>& soluciones, nat& cantAPasar, nat& cantMovimientosMin,
		Puntero<ListaOrdArray<Tupla<int, int>>> solActual, nat cantAPasarActual, nat cantMovimientosActual);

	Matriz<nat> InitMatrizCaminoCaballo(nat tamTablero, Tupla<int, int>& salida, Tupla<int, int>& destino, Iterador<Tupla<int, int>>& pasar, Iterador<Tupla<int, int>>& noPasar);

	Array<int> InitMovXCaballo();

	Array<int> InitMovYCaballo();

	bool PerteneceAlTablero(int x, int y, int largo);

	Matriz<nat> ClonarTablero(Matriz<nat> tablero);

	// EJERCICIO 9

	void OptimizarGranjaBT(Array<Tupla<nat, nat, nat>>& semillas,
		nat& dinero, nat& tierra, nat& agua, nat& gananciaMax, Array<nat>& solucion,
		nat dineroActual, nat tierraActual, nat aguaActual, nat gananciaActual, Array<nat> solucionActual, nat actual);

	// EJERCICIO 10

	void InscribirMateriasBT(Puntero<ListaOrdArray<Tupla<Cadena, nat, nat>>> matutino, Puntero<ListaOrdArray<Tupla<Cadena, nat, nat>>> nocturno,
		Puntero<ListaOrdArray<Tupla<Cadena, bool>>>& solucion, nat maxHorasM, nat maxHorasN, nat& maxCreditos,
		Puntero<ListaOrdArray<Tupla<Cadena, bool>>>& actualSolucion, nat actualHorasM, nat actualHorasN, nat actualCreditos);
};

#endif
