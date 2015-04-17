/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 	/
+												     	+
+  Clase Polinomio										   	+
+ 													+
+  Created by n3xt0r on 18/05/2015								+
+													+
/ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Polinomio{
	private:
		float *coef;
		int grado;
		int max_grado;
	public:
		// Constructores
		Polinomio();
		Polinomio(int grado_act);
		Polinomio(const Polinomio &p);
		// Destructor
		~Polinomio();
		// Sets
		inline void setGrado(int grado) {this->grado=grado;}
		inline void setMaxGrado(int max_grado) {this->max_grado=max_grado;}
		void setCoeficiente(int i, float nuevo_coef);
		// Gets
		inline int getGrado() const {return grado;}
		inline int getMaxGrado() const {return max_grado;}
		// Print : Para imprimir el polinomio
		void print();
		Polinomio sumaPolinomios (Polinomio *&poli2);

};
Polinomio::Polinomio(){
	max_grado=5;
	grado=-1;
	// Reserva de memoria del vector de coeficientes
	coef=new float[max_grado+1];
	if (coef==0){
		cerr << "No hay memoria suficiente. Se abortará la ejecución del programa." << endl;
		exit(-1);
	}
	// Inicialización del vector de coeficientes;
	for (int i=0; i<=max_grado;i++ ){
		coef[i]=0.0;
	}

	cout << endl << "*********Debug: Llamada al constructor por defecto.*********" << endl << endl;
}
Polinomio::Polinomio(int grado_act){
	max_grado=grado_act;
	grado=grado_act;
	// Reserva de memoria del vector de coeficientes
	coef=new float[max_grado+1];
	if (coef==0){
		cerr << "No hay memoria suficiente. Se abortará la ejecución del programa." << endl;
		exit(-1);
	}
	// Inicialización del vector de coeficientes;
	for (int i=0; i<=max_grado;i++ ){
		coef[i]=0.0;
	}

	cout << endl << "*********Debug: Llamada al constructor por parametro.*********" << endl << endl;
}
Polinomio::Polinomio(const Polinomio &p){
	this->max_grado = p.max_grado;
	this->grado = p.grado;
	this->coef=new float[p.max_grado+1];
	for (int i=0; i<=this->max_grado;i++ ){
		this->coef[i]=p.coef[i];
	}
	cout << endl << "*********Debug: Llamada al constructor por copia.*********" << endl << endl;
	
}

Polinomio::~Polinomio(){
	cout << endl << "*********Debug: Llamada al destructor.*********" << endl << endl;
	delete [] coef;
}

/**
 * @brief Método de la clase Polinomio que cambia el coeficiente de un monomio.
 * @param int i Grado del monomio que voy a cambiar.
 * @param float nuevo_coef Nuevo Coeficiente que le vamos a establecer al monomio de grado i.
 * @pre El Polinomio debe estar construido (el vector de coeficientes debe estar reservado).
 * @post Se puede ver alterado el grado del Polinomio en función del estado inicial del mismo y del monomio
 *      que se esté modificando.
 */
void Polinomio::setCoeficiente(int i, float nuevo_coef){
    if (i >= 0){
        if (i <= grado){
            if(nuevo_coef != 0) //i > 0 && i <= grado && nuevo_coef != 0
                coef[i] = nuevo_coef;
            else{ // i > 0 && i <= grado && nuevo_coef == 0
                if (i != grado) //i != grado
                    coef[i] = nuevo_coef;
                else{ // i == grado
                    coef[i] = 0;
                    // Buscar en el polinomio el primer coeficiente distinto de 0
                    // porque ese será el nuevo grado de mi polinomio
                    bool encontrado = false;
                    for(int j = grado-1; (j >= 0) && (!encontrado); j--){
                        if (coef[j] != 0){
                            encontrado = true;
                            setGrado(j);
                        }
                    }
                    if (!encontrado){
                        setGrado(0);
                        cerr << "Warning: Su polinomio es p(x) = 0" << endl;
                    }
                }
            }
        }
        else{ //i > grado
            if (i <= max_grado){
                coef[i] = nuevo_coef;
                setGrado(i);
            }
            else{ // i > grado && i > max_grado
                cerr << "Debug:Se duplicará la memoria." << endl;
                // Reservo nueva memoria
                float* aux = new float[i+1];
                if (!aux){
                    cerr << "Error: El S.O. no dispone de memoria suficiente." << endl;
                    exit(-1);
                }
                // Copio los datos antiguos en la nueva memoria
                for(int j = 0; j <= grado; j++)
                    aux[j] = coef[j];
                // Borro la antigua memoria
                delete [] coef;
                // Asigno el nuevo puntero a coef
                coef = aux;
                aux = 0;
                //Ahora tranquilamente, ya tengo espacio para hacer la asignación del coeficiente
                coef[i] = nuevo_coef;
                setGrado(i);
                max_grado = i+1;
            }
        }
    
    }
    else
        cerr << "Warning: No existen monomios con grado negativo." << endl;
}

/*
static char *super[] = {"\xe2\x81\xb0", "\xc2\xb9", "\xc2\xb2",
    "\xc2\xb3", "\xe2\x81\xb4", "\xe2\x81\xb5", "\xe2\x81\xb6",
    "\xe2\x81\xb7", "\xe2\x81\xb8", "\xe2\x81\xb9"};
static char *sub[] = {"\xe2\x82\x80", "\xe2\x82\x81", "\xe2\x82\x82",
    "\xe2\x82\x83", "\xe2\x82\x84", "\xe2\x82\x85", "\xe2\x82\x86",
    "\xe2\x82\x87", "\xe2\x82\x88", "\xe2\x82\x89"};

  //  printf (super[i]);
*/
void Polinomio::print(){
	int i;
	cout << "Grado Actual: " << this->getGrado() << endl;
	cout << "Grado Máximo: " << max_grado << endl;
	cout << "Dirección de memoria: " << coef << endl;
	if(grado!=-1){
		cout << "\n\tp(x)= " ;
		cout << coef[grado] << "x^" << grado;
		for (i=grado-1; i>=0; i--){
			if (i==0 && coef[i]!=0)
				cout << " + " << coef[i];
			else
				if (i==1&&coef[i]!=0)
					cout << " + " << coef[i] << "x";
			else 
				if (coef[i]!=0)
					cout << " + " << coef[i] << "x^" << i;
		}
		cout << endl;
	}
	else{
		cout << "\n\tEl Polinomio no tiene valores. Es un polinomio vacío." << endl;
	}
}

Polinomio Polinomio::sumaPolinomios(Polinomio *&poli2){
	int grado_act;
	bool yosoymayor=false;

	if (grado > poli2->grado) {
		grado_act = grado;
		yosoymayor = true;
	}
	else {
		grado_act = poli2->grado;
	}
	Polinomio poli3 (grado_act);
	if (yosoymayor = true) {
		for (int i = 0; i<=poli2->grado; i++) {
			poli3.coef[i]=poli2->coef[i];
		}
	}
	else {
		for (int i = 0; i<=grado; i++) {
			poli3.coef[i]=coef[i];
		}
	}
	if (yosoymayor = true) {
		for (int i = 0; i<=grado; i++) {
			poli3.coef[i]=poli3.coef[i]+coef[i]; 
		}
	}
	else {
		for (int i = 0; i<=grado; i++) {
			poli3.coef[i]=poli3.coef[i]+poli2->coef[i]; 

		}
	}	
	return poli3;
}


int main(){
	system("clear");
	Polinomio *p1;
	p1 = new Polinomio();
	p1->setCoeficiente(0,5);
	p1->setCoeficiente(2,1);
	p1->setCoeficiente(3,2);
	p1->setCoeficiente(4,6);
	p1->setCoeficiente(5,12);
	Polinomio *p2;
	p2 = new Polinomio(4);
	p2->setCoeficiente(2,4);
	p2->setCoeficiente(4,6);
	p2->setCoeficiente(0,3);
	p2->setCoeficiente(1,12);
	Polinomio *p3;
	p3 = new Polinomio(p1->sumaPolinomios(p2));
	p1->print();
	cout << " + " << endl;
	p2->print();
	cout << " = " << endl;	
	p3->print();
	




}


