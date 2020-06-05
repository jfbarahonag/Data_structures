#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Las siguientes declaraciones tienen  que manterse en ese orden
#include "datos.h"
#include "pilas.h"
#include "colas.h"

/*
* Solucion al parcial 2, Estructuras de datos
*
* Juan Felipe Barahona Gonzalez
* Mateo Alvarez Vasquez
* 
* Inicialmente la expresion se almacena en una cola (cada operador
* o valor ocupa un solo nodo) posteriormente se recorre la cola 
* buscando la operacion segun un orden de prioridad asignado, en 
* este caso, primero se realizan multiplicaciones y/o divisiones cuyos
* resultados se guardan en la misma cola, para despues operar la 
* expresion resultante ahora ya evaluando sumas y/o restas. Finalmente 
* se devuelve el resultado como un flotante.
*/

/*
* Muestra una pila con una expresion sin destruirla
*
* @param **pila
* @return void
*/
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

/*
* Muestra una cola con una expresion sin destruirla
*
* @param cola
* @return void
*/
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
*
* @param *buff
* @return void
*/
void ingresar_datos_usuario ( char *buff ) {
	printf("Ingrese expresion\n");
	scanf("%[^\n]%*c", buff);
}

/*
* Encuentra un operador, como parametro recibe un apuntador al buffer y 
* retorna un apuntador al buffer desde el operador encontrado.
*
* @param *buff
* @return dato[i] || @return NULL
*/
char *encontrar_prox_operador ( char *buff ) {
	size_t tamano = strlen(buff);
	char *dato;
	dato = buff;
	int i = 0;
	//printf("tamaño = %ld\n", tamano);
	while (i < tamano) {
        if (*(dato+i) >= '0' && *(dato+i) <= '9') { // Si es un numero 

        }
        else if (*(dato+i) == '\0') {    // Cuando termina el string
            return NULL;
        }
       	else if ( *(dato+i) =='*' ||*(dato+i) =='/' ||*(dato+i) =='+' ||*(dato+i) =='-' ){     //Si es un operador
         	return dato+i;
        }
        else {
            printf("Operador invalido, el codigo se cerrara\n");
            exit(-1);
            return NULL;
        }
        i++; // Se mueve a la siguiente posici�n del buffer
    }
	
	return NULL;

}


/*
* Toma los datos leidos por el buffer y los organiza en el mismo orden 
* que llegaron en la cola.
* Como parametro de entrada recibe la cola en que seran guardados los 
* datos y el buffer del cual provienen. La funcion  opera con dos apuntadores
* los cuales apuntaran a diferentes posiciones del buffer segun el contenido 
* de este (Valor u operador) para lo cual se utilizara otra funcion llamada 
* "encontrar_prox_operador" se iran insertando los datos que se encuentren 
* dentro del rango obtenido al restar las dos posiciones de cada apuntador.
*
* @param cola
* @param *buff
* @return void
*/
void ingresar_datos_cola ( ApTipoCola cola, char *buff ) {
	Datos info;
	char buff_temp[51];
	buff_temp[51-1] = '\0';									//Se le asigna NULL al ultimo espacio del buffer
	char *inicio, *fin;										//inicio apunta al primer espacio del buffer
	inicio = buff;
	do {
		//printf("inicio = %s\n",inicio);
		fin = encontrar_prox_operador(inicio);   
		if (fin != NULL) {									// Si fin apunta a un signo (operador) 
			strncpy(buff_temp, inicio, fin-inicio);			// copia en buff_temp los elementos que interesan (lo que se encuentra antes del operador).        
			info.valor = atof(buff_temp);					//convierte de string a float y lo guarda en info.valor  
			info.operador = ' ';
			//printf("info.valor %f\n",info.valor);
			insertarCola(cola, info);						// inserta en la cola la informaci�n
			info.valor = 0;
			info.operador = *fin;							// El operador ser� el primer elemento de fin
			insertarCola(cola, info);
			//printf("info.operador %c\n",info.operador);
			inicio = fin+1;									// Actualiza el apuntador, apunta a la posici�n siguiente del signo encontrado
			
		} 
		else {												// Ya es el ultimo digito
			strncpy(buff_temp, inicio, (inicio-1)-buff);	// Copia en buffer temporal el d�gito despu�s del �ltimo operador
			info.valor = atof(buff_temp);
			info.operador = ' ';
			insertarCola(cola, info);
			//printf("info.valor %f\n",info.valor);
			
		}
		memset(buff_temp, '\0', 51);						//llena el buffer temporal de NULL, evita que se sobreescriba
	} while (fin != NULL);
	
}

/*
* Retorna el ultimo valor de una cola
*
* @param cola 
* @return info_necesaria
*/
Datos encontrarUltimoCola ( ApTipoCola cola ) {
	Datos info, info_necesaria;
	TipoCola aux;
	crearCola(&aux);
	ApTipoCola aux_ptr;
	aux_ptr = &aux;

	while ( !vaciaCola(cola) ) {
		info = retirarCola(cola);
		if (vaciaCola(cola)) {		// revisa el siguiente 
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
* Elimina el ultimo valor de una cola.
*
* @param cola
* @return void
*/
void eliminarUltimoCola ( ApTipoCola cola ) {
	Datos info;
	TipoCola aux;
	crearCola(&aux);
	ApTipoCola aux_ptr;
	aux_ptr = &aux;

	while ( !vaciaCola(cola) ) {
		info = retirarCola(cola);
		if (!vaciaCola(cola)) {                                  // revisa el siguiente 
			insertarCola(aux_ptr, info);
		} 
	}
	while ( !vaciaCola(aux_ptr) ) {
		insertarCola(cola, retirarCola(aux_ptr));
	}
}

/*
* La funcion recibe como parametro una cola en la que se encuentra la 
* expresion original y la modifica entregando en la misma cola una nueva
* expresion equivalente la cual solo incluye sumas y restas, es decir, la 
* funcion solo opera divisiones y multiplicaciones.
* Si en la expresion solo hay multiplicaciones y/o divisiones devuelve 
* el resultado en la misma cola
*
* @param cola
* @return void
*/
void eliminar_multip_div ( ApTipoCola cola ) {
	Datos num1, num2, op;
	TipoCola aux;
	ApTipoCola aux_ptr;
	crearCola(&aux);
	aux_ptr = &aux;
	num1 = retirarCola(cola);                                 // Se extrae el primer digito recibido
	op = retirarCola(cola);                                   // Se extrae el primer operador recibido

	//Se mira a que operador corresponde
	//Si el operador es * extrae el siguiente valor de la cola para posteriormente ser operado y guardado en la cola auxiliar

	if ( op.operador == '*' ) {                               
	   	num2 = retirarCola(cola);                             
		num2.valor *= num1.valor;                             
		insertarCola(aux_ptr, num2);                          
	} 
	//Si el operador es / extrae el siguiente valor de la cola para posteriormente ser operado y guardado en la cola auxiliar
	else if ( op.operador == '/' ) {
		num2 = retirarCola(cola);
		if (num2.valor == 0) {
			printf("ERROR DIV 0, el codigo se cerrara\n");
			exit(-1);
			return;
		}
		num1.valor /= num2.valor;
		insertarCola(aux_ptr, num1);
	} 
	//Si el operador es + extrae el operador y el siguiente valor y los guarda en la cola
	else if ( op.operador == '+' || op.operador == '-' ) { 
		insertarCola(aux_ptr, num1);
		insertarCola(aux_ptr, op);
	}


	while (!vaciaCola(cola)) {
		if ( tipoDato(consultarCola(cola)) == 1 ) {              // si es valor significa que el anterior era suma/resta
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
						printf("ERROR DIV 0, el codigo se cerrara\n");
						exit(-1);
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
		else { // es un operador significa que el anterior era multip/division, se analiza cual de los dos es
			
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
					printf("ERROR DIV 0, el codigo se cerrara\n");
					exit(-1);
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
	while ( !vaciaCola(aux_ptr) ) {  //Se hace una migraci�n de datos de la cola auxiliar a la original
		insertarCola(cola, retirarCola(aux_ptr));
	}
}

/*
* Recibe como parametro una cola cuyo contenido es una expresion 
* que solo contiene sumas y/o restas o solo el resultado si las 
* operaciones son solo multiplicaciones y/o divisiones ,retorna 
* el resultado como un valor flotante y destruye la cola original.
*
* @param cola
* @return resultado.valor
*/
float operar_restantes ( ApTipoCola cola ) {

	Datos num1, num2, op, resultado;
	TipoCola aux;
	crearCola(&aux);
	ApTipoCola aux_ptr;
	aux_ptr = &aux;

	num1 = retirarCola(cola);		//retira el ultimo de la cola	 
	if( vaciaCola(cola) ) {			// Si es el unico u ultimo numero de la cola ese sera el resultado                   
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
		exit(-1);
	}
	// El siguiente dato de la cola ser� un operador
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
* La funcion recibe como parametro una cola, realiza el desarrollo de 
* la expresion segun una prioridad que se asigno para el desarrollo del 
* programa (primero divisiones y multiplicaciones) despues procede a 
* realizar la expresion resultante para finalmente retornar el resultado 
* final.
*
* @param cola
* @return operar_restantes
*/
float realizar_operacion_ingresada ( ApTipoCola cola ) {
	eliminar_multip_div ( cola );
	return operar_restantes ( cola );
}

/*
* Como parametro recibe una cola y realiza la inversion recursiva de esta.
*
* @param cola
* @return void
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
* Imprime los valores de la cola recursivamente y la invierte.
*
* @param cola
* @return void
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
* La funcion recibe como parametro una cola y la muestra de manera recursiva.
* Primero se muestra la cola inviertiendola, luego se invierte de nuevo.
*
* @param cola
* @return void
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
	
	memset(buff, '\0', 51); //llena el buffer de Nulls
	ingresar_datos_usuario(buff); 
	ingresar_datos_cola (cola_ptr, buff);
	mostrarColaRec(cola_ptr);
	resultado = realizar_operacion_ingresada(cola_ptr);
	printf("resultado final = %0.2f\n", resultado);

	return NULL;
	
}
