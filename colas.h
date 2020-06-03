// Datos que se almacenan en la pila donde si el operador es ' ',
//lo almacenado es un valor, sino el *,+,-,/ almacenado en operador
// Se comentan para no hacer conflicto cuando se usan pilas.
/*
typedef struct {
  	float valor;
	char operador;	
}Datos;
*/

typedef struct lista {
   Datos info;
   struct lista *sgte, *ante;	
}TipoNodo, *ApTipoNodo;

typedef struct {
	TipoNodo *cabeza,*cola;
}TipoCola, *ApTipoCola;

void mostrarCola(TipoCola lacola) {
	ApTipoNodo p;
	p=lacola.cabeza;
	printf("\nLa informacion de la cola es : \n");
	while (p!=NULL) {
		printf("\t%.2f, %c",p->info.valor, p->info.operador);
		p=p->ante;
	}
}

bool vaciaCola(ApTipoCola lacola) {
	return lacola->cabeza==NULL && lacola->cola==NULL;
}

void crearCola(ApTipoCola lacola) {
	lacola->cabeza=lacola->cola=NULL;
}

void insertarCola(ApTipoCola lacola, Datos info) {
	ApTipoNodo p;
	p=(ApTipoNodo) malloc(sizeof(TipoNodo));
	if (p==NULL) {
		printf("\nNo ha memoria");
		return ;
	}
	p->info=info;
	p->ante=NULL;
	if (vaciaCola(lacola)) {
		p->sgte=NULL;
		lacola->cabeza=lacola->cola=p;
	}
	else {
		p->sgte=lacola->cola;
		lacola->cola->ante=p;
		lacola->cola=p;
	}
}

Datos consultarCola(ApTipoCola lacola) {
	Datos info;
	info.operador=' '; info.valor=0;
	if (vaciaCola(lacola)) {
		printf("\nCola Vacia");
		return info;
	}
	else {
		info=lacola->cabeza->info;
		return info;
	}
}

Datos retirarCola(ApTipoCola lacola) {
	Datos info;
	info.operador=' ';
	info.valor=0;
	ApTipoNodo p;
	if (vaciaCola(lacola)) {
		printf("\nCola Vacia");
		return info;
	}
	else {
		p=lacola->cabeza;
		info= p->info;
		if (p->ante==NULL) {
			lacola->cabeza=lacola->cola=NULL;
			free(p); 
		}
		else {
			p->ante->sgte=NULL;
			lacola->cabeza=p->ante;
			free(p); 
		}
		return info;	
	}
}


