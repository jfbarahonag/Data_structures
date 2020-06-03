#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Las siguientes declaraciones tienen  que manterse en ese orden
#include "datos.h"
#include "pilas.h"
#include "colas.h"

// Muestra una pila con una expresion sin destruirla
void mostrarPila(TipoPila **pila) {
	Datos info;
	TipoPila *aux;
	crearPila(&aux);
	printf("\nLos datos de la pila son :\n");
	while (!vaciaPila(*pila)) {
		info=retirarPila(pila);
		if (tipoDato(info)==1) {
			printf("\nEl valor es : %.2f",info.valor);
		}
		else {
			printf("\nEl operador es : %c",info.operador);
		}
		insertarPila(&aux,info);
	}
	while (!vaciaPila(aux)) {
		insertarPila(pila,retirarPila(&aux));
	}
}

// Muestra una cola con una expresion sin destruirla
void mostrarCola(TipoCola *lacola) {
	Datos info;
	TipoCola aux;
	crearCola(&aux);
	printf("\nLos datos de la cola son :\n");
	while (!vaciaCola(lacola)) {
		info=retirarCola(lacola);
		if (tipoDato(info)==1) {
			printf("\nEl valor es : %.2f",info.valor);
		}
		else {
			printf("\nEl operador es : %c",info.operador);
		}
		insertarCola(&aux,info);
	}
	while (!vaciaCola(&aux)) 
	   insertarCola(lacola,retirarCola(&aux));
}

/*
* Se lee el string completo ingresado por el usuario
*/
void ingresar_datos_usuario ( char *buff ) {
	printf("Ingrese expresion\n");
	scanf("%[^\n]%*c", buff);
}

/*
*
*/
char *encontrar_prox_operador ( char *buff ) {
	size_t tamano = strlen(buff);
	char *dato;
	dato = buff;
	int i = 0;
	//printf("tamaño = %ld\n", tamano);
	while (i < tamano) {
		if (*(dato+i) >= '0' && *(dato+i) <= '9') { /* si es un numero */

		} 
		else if (*(dato+i) == '\0') {
			return NULL;
		}
		else {
		 return dato+i;
		}
		i++;
	}
	
	return NULL;

}

/*
* Toma los datos leidos por el buffer y los organiza en el mismo orden que llegaron en la cola
*/
void ingresar_datos_cola ( ApTipoCola cola, char *buff ) {
	Datos info;
	char buff_temp[51];
	buff_temp[51-1] = '\0';
	char *inicio, *fin;
	inicio = buff;
	do {
		//printf("inicio = %s\n",inicio);
		fin = encontrar_prox_operador(inicio);
		if (fin != NULL) {
			strncpy(buff_temp, inicio, fin-inicio);
			info.valor = atof(buff_temp);
			info.operador = ' ';
			//printf("info.valor %f\n",info.valor);
			insertarCola(cola, info);
			info.valor = 0;
			info.operador = *fin;
			insertarCola(cola, info);
			//printf("info.operador %c\n",info.operador);
			inicio = fin+1;
		} 
		else {
			strncpy(buff_temp, inicio, (inicio-1)-buff);
			info.valor = atof(buff_temp);
			info.operador = ' ';
			insertarCola(cola, info);
			//printf("info.valor %f\n",info.valor);
			
		}
		memset(buff_temp, '\0', 51);
	} while (fin != NULL);
	
}

/*
*
*/
Datos encontrarUltimoCola ( ApTipoCola cola ) {
	Datos info, info_necesaria;
	TipoCola aux;
	crearCola(&aux);
	ApTipoCola aux_ptr;
	aux_ptr = &aux;

	while ( !vaciaCola(cola) ) {
		info = retirarCola(cola);
		if (vaciaCola(cola)) { /* revisa el siguiente */
			info_necesaria = info;
		}
		insertarCola(aux_ptr, info);
	}
	while ( !vaciaCola(aux_ptr) ) {
		insertarCola(cola, retirarCola(aux_ptr));
	}
	return info_necesaria;

}

/*
*
*/
void eliminarUltimoCola ( ApTipoCola cola ) {
	Datos info;
	TipoCola aux;
	crearCola(&aux);
	ApTipoCola aux_ptr;
	aux_ptr = &aux;

	while ( !vaciaCola(cola) ) {
		info = retirarCola(cola);
		if (!vaciaCola(cola)) { /* revisa el siguiente */
			insertarCola(aux_ptr, info);
		} 
	}
	while ( !vaciaCola(aux_ptr) ) {
		insertarCola(cola, retirarCola(aux_ptr));
	}
}

/*
*
*/
void eliminar_multip_div ( ApTipoCola cola ) {
	Datos num1, num2, op;
	TipoCola aux;
	ApTipoCola aux_ptr;
	crearCola(&aux);
	aux_ptr = &aux;
	num1 = retirarCola(cola);
	op = retirarCola(cola);

	

	if ( op.operador == '*' ) {
		num2 = retirarCola(cola);
		num2.valor *= num1.valor; 
		insertarCola(aux_ptr, num2);
	} 
	else if ( op.operador == '/' ) {
		num2 = retirarCola(cola);
		if (num2.valor == 0) {
			printf("ERROR DIV 0\n");
			return;
		}
		num1.valor /= num2.valor;
		insertarCola(aux_ptr, num1);
	} 
	else if ( op.operador == '+' || op.operador == '-' ) { 
		insertarCola(aux_ptr, num1);
		insertarCola(aux_ptr, op);
	}


	while (!vaciaCola(cola)) {
		if ( tipoDato(consultarCola(cola)) == 1 ) { // si es valor significa que el anterior era suma/resta
			num1 = retirarCola(cola);
			if (vaciaCola(cola)) {
				insertarCola(aux_ptr, num1);
			}
			else {
				op = retirarCola(cola);
				if ( op.operador == '*' ) {
					num2 = retirarCola(cola);
					num2.valor *= num1.valor; 
					insertarCola(aux_ptr, num2);
				} 
				else if ( op.operador == '/' ) {
					num2 = retirarCola(cola);
					if (num2.valor == 0) {
						printf("ERROR DIV 0\n");
						return;
					}
					num1.valor /= num2.valor;
					insertarCola(aux_ptr, num1);
				} 
				else if ( op.operador == '+' || op.operador == '-' ) { 
					insertarCola(aux_ptr, num1);
					insertarCola(aux_ptr, op);
			}
			}
			
		}
		else { // es un operador significa que el anterior era multip/division
			
			op = retirarCola(cola);
			
			if ( op.operador == '*' ) {
				num2 = encontrarUltimoCola(aux_ptr);
				num1 = retirarCola(cola);
				num2.valor *= num1.valor;
				eliminarUltimoCola(aux_ptr);
				insertarCola(aux_ptr, num2);
			} 
			else if ( op.operador == '/' ) {
				num2 = encontrarUltimoCola(aux_ptr);
				num1 = retirarCola(cola);
				if (num1.valor == 0) {
					printf("ERROR DIV 0\n");
					return;
				}
				num2.valor /= num1.valor;
				eliminarUltimoCola(aux_ptr);
				insertarCola(aux_ptr, num2);
			} 
			else if ( op.operador == '+' || op.operador == '-' ) { 
				num1 = retirarCola(cola);
				insertarCola(aux_ptr, op);
				insertarCola(aux_ptr, num1);
			}
		}
	}
	//printf("\nllegue\n");
	//mostrarCola(aux_ptr);
	while ( !vaciaCola(aux_ptr) ) {
		insertarCola(cola, retirarCola(aux_ptr));
	}
}

/*
*
*/
float operar_restantes ( ApTipoCola cola ) {

	Datos num1, num2, op, resultado;
	TipoCola aux;
	crearCola(&aux);
	ApTipoCola aux_ptr;
	aux_ptr = &aux;

	num1 = retirarCola(cola);

	if( vaciaCola(cola) ) {
		resultado = num1;
		return resultado.valor;
	}

	op = retirarCola(cola);
	num2 = retirarCola(cola);

	if (op.operador == '+') {
		num1.valor += num2.valor;
		insertarCola(aux_ptr, num1);
	}
	else if (op.operador == '-') {
		num1.valor -= num2.valor;
		insertarCola(aux_ptr, num1);
	}
	else { /* ERROR */
		while(1);
	}

	while ( !vaciaCola(cola) ) {
		op = retirarCola(cola);
		if ( op.operador == '+' ) {
			num1 = retirarCola(aux_ptr);
			num2 = retirarCola(cola);
			num1.valor += num2.valor;
			insertarCola(aux_ptr, num1);
		}
		else if ( op.operador == '-' ) {
			num1 = retirarCola(aux_ptr);
			num2 = retirarCola(cola);
			num1.valor -= num2.valor;
			insertarCola(aux_ptr, num1);
		}
	}
	resultado = retirarCola(aux_ptr);
	return resultado.valor;
}

/*
*
*/
float realizar_operacion_ingresada ( ApTipoCola cola ) {
	eliminar_multip_div ( cola );
	return operar_restantes ( cola );
}

/*
*
*/
void invertirColaRec ( ApTipoCola cola ) {
	Datos info;
	if(!vaciaCola(cola)) {
		info = retirarCola(cola);
		invertirColaRec(cola);
		insertarCola(cola, info);
	}
}

/*
*
*/
void imprimirColaRec ( ApTipoCola cola ) {
	Datos info;
	if(!vaciaCola(cola)) {
		info = retirarCola(cola);
		if ( tipoDato(info) == 1 ) { /* es un valor */
			printf("El valor es:\t%0.2f\n", info.valor);
		}
		else {
			printf("El operador es:\t%c\n", info.operador);
		}
		imprimirColaRec(cola);
		insertarCola(cola, info);	
	}
}

/*
*
*/
void mostrarColaRec ( ApTipoCola cola ) {
	printf("\n La cola esta asi :\n\n");
	imprimirColaRec(cola);
	invertirColaRec(cola);
	printf("\n Fin cola\n\n");
}

int main(void){
	TipoPila *pila;
	TipoCola cola;
	Datos info;
	ApTipoCola cola_ptr;
	float resultado;
	char buff[51];

	cola_ptr = &cola;
	crearCola(&cola);
	
	memset(buff, '\0', 51);
	ingresar_datos_usuario(buff);
	ingresar_datos_cola (cola_ptr, buff);
	mostrarColaRec(cola_ptr);
	resultado = realizar_operacion_ingresada(cola_ptr);
	printf("resultado final = %0.2f\n", resultado);
	
}
