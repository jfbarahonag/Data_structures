// Datos que se almacenan en la pila donde si el operador es ' ',
//lo almacenado es un valor, sino el *,+,-,/ almacenado en operador
typedef struct {
  	float valor;
	char operador;	
}Datos;

// Retorna el tipo de dato, donde 1 es un valor y 2 es un operador
int tipoDato(Datos dato) {
	if (dato.operador==' ')
	  return 1;
	else
	  return 2;
}
