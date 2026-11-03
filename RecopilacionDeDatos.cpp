#include <iostream>
// Programa para recopilacion archivos
using namespace std;

// Hacemos un struct para almacenar la fecha para el struct de sismos
struct Fecha{
	int dia;
	int mes;
	int anio;
};

struct Tiempo{
	int hora;
	int minuto;
	int segundo;
};

struct FechaHora{
	Fecha fecha;
	Tiempo tiempo;
};

struct Clima{
	int id; // (unico)
	int dia; // (unico)
	int temperaturas[3];
	char descripcion[256+1];
	int mmAguaCaida;
};

struct NodoClima{
	Clima info;
	NodoClima* sgte;
};

struct MovSismicos{
	int id; // (unico)
	Fecha fechaReg;
	char paisReg [56+1];
	double latitud;
	double longitud;
	float magnitud;
};

struct NodoMovSismicos{
	MovSismicos info;
	NodoMovSismicos* sgte;
};

struct Caballo{
	int idDato; // (unico)
	char nombre[100+1];
	int idCaballo; // (unico)
	float velocidadMaxima; // (Km/h)
	float peso;
	float tamanoHerradura;
	FechaHora ultimaCarrera;
};

struct NodoCaballo{
	Caballo info;
	NodoCaballo* sgte;
};

struct Jockey{
	int idDato;
	char nombreApellido[100+1];
	int DNI; // (unico)
	int edad;
	NodoCaballo* listaCaballos;
};

struct NodoJockey{
	Jockey info;
	NodoJockey* sgte;
};
void guardarDato(FILE* f, Clima info);
void guardarDato(FILE* f, MovSismicos info);
void guardarDato(FILE* f, Caballo info);
void guardarDato(FILE* f, Jockey info);
void guardarLista(FILE* f, Clima* lista, int cantidad);
void guardarLista(FILE* f, MovSismicos* lista, int cantidad);
void guardarLista(FILE* f, Caballo* lista, int cantidad);
void guardarLista(FILE* f, Jockey* lista, int cantidad);
void llenarConDatos(Clima * lista);
int main(){
	
	llenarConDatos(listaClima);
	
	return 0;
}


//Guarda el dato en el archivo 
void guardarDato(FILE* f, Clima info) {
    fwrite(&info, sizeof(Clima), 1, f);
}

// Sobrecarga 
void guardarDato(FILE* f, MovSismicos info) {
    fwrite(&info, sizeof(MovSismicos), 1, f);
}

// Sobrecarga 
void guardarDato(FILE* f, Caballo info) {
    fwrite(&info, sizeof(Caballo), 1, f);
}
// Sobrecarga
void guardarDato(FILE* f, Jockey info) {
	fwrite(&info, sizeof(Jockey), 1, f);
}

// Guarda la lista
void guardarLista(FILE* f, Clima* lista, int cantidad) {
    clima * auxLista= lista;
	while(auxLista != NULL) {
        guardarDato(f, auxLista->info);
		auxLista = auxLista->sgte; 
    }
}

void guardarLista(FILE* f, MovSismicos* lista, int cantidad) {
	MovSismicos * auxLista= lista;
	while(auxLista != NULL) {
		guardarDato(f, auxLista->info);
		auxLista = auxLista->sgte; 
	}
}

void guardarLista(FILE* f, Caballo* lista, int cantidad) {
	Caballo * auxLista= lista;
	while(auxLista != NULL) {
		guardarDato(f, auxLista->info);
		auxLista = auxLista->sgte; 
	}
}

void guardarLista(FILE* f, Jockey* lista, int cantidad) {
	Jockey * auxLista= lista;
	while(auxLista != NULL) {
		guardarDato(f, auxLista->info);
		auxLista = auxLista->sgte; 
	}
}

void llenarConDatos(Clima * lista){
	boolean escape=false;
	while(escape==false){
		Clima nuevo;
		cout << "Ingrese el ID del clima: ";
		cin >> nuevo.id;
		cout << "Ingrese el dia del clima: ";
		cin >> nuevo.dia;
		cout << "Ingrese las temperaturas (3 valores): ";
		for(int i=0; i<3; i++){
			cin >> nuevo.temperaturas[i];
		}
		cout << "Ingrese la descripcion del clima: ";
		cin.ignore();
		cin.getline(nuevo.descripcion, 256);
		cout << "Ingrese los mm de agua caida: ";
		cin >> nuevo.mmAguaCaida;

		NodoClima* nuevoNodo = new NodoClima;
		nuevoNodo->info = nuevo;
		nuevoNodo->sgte = lista;
		lista = nuevoNodo;

		cout << "Desea ingresar otro dato? (1 para si, 0 para no): ";
		cin >> escape;
	}
}