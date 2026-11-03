#include <iostream>
// Programa para recopilacion arcihvos
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

int main(){
	
	
	
	return 0;
}
