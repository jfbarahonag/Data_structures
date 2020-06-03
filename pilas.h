/* Implementación de las funciones de la Pila con listas encadenadas
simples, bajo las siguientes operaciones:
-create : Crea una pila vacía 
-isempty : Determina si una pila esta vacia (sin elementos)
-push : Almacena un valor en la pila
-pop :  Retira un valor de la pila
-top : Consulta el valor que hay en la cima o tope de la pila
*/
#include <stdio.h>

typedef struct datos{
	Datos info;
	struct datos *sgte;
} TipoPila, *ApTipoPila;


// Crea una pila vacia
void crearPila(ApTipoPila *pila) {
	*pila=NULL;
}


// Determina si una pila esta vacia
bool vaciaPila(ApTipoPila pila) {
	if (pila==NULL)
	   return true;
	else
	   return false;
}


// Almacena un valor en una pila
void insertarPila(ApTipoPila *pila, Datos info){
	TipoPila *p;
	p=(ApTipoPila)malloc(sizeof(TipoPila));
	p->info=info;
	p->sgte=*pila;
	*pila=p;
}


// Retira un valor de la pila
Datos retirarPila(ApTipoPila *pila) {
	TipoPila *p;
	Datos info;
	info.valor=-1;
	if (!vaciaPila(*pila)) {
		p=*pila;
		info=p->info;
		*pila=p->sgte;
		free(p);
	}
	return info;
}


// Consulta el tipo de elemento que hay en la pila sin retirarlo
// Regresa 0 y ' ' en los campos valor y operador si está vacía
Datos consultarPila(ApTipoPila pila) {
	Datos info;
	info.valor=0;
	info.operador=' ';
	if (!vaciaPila(pila))
		info=pila->info;
	return info;
}


