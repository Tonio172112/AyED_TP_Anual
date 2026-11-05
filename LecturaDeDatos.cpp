#include <iostream>
// Programa para lectura de archivos
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
    Fecha fecha; // (unico)
    int temperaturas[3];
    char descripcion[256+1];
    int mmAguaCaida;
};

struct MovSismicos{
    int id; // (unico)
    Fecha fechaReg;
    char paisReg [56+1];
    double latitud;
    double longitud;
    float magnitud;
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

struct Jockey{
    int idDato;
    char nombreApellido[100+1];
    int DNI; // (unico)
    int edad;
};

void leerArchivo(FILE* f, Clima info);
void leerArchivo(FILE* f, MovSismicos info);
void leerArchivo(FILE* f, Caballo info);
void leerArchivo(FILE* f, Jockey info);
void mostrarDatos(const char* nombreArchivo, Clima info);
void mostrarDatos(const char* nombreArchivo, MovSismicos info);
void mostrarDatos(const char* nombreArchivo, Caballo info);
void mostrarDatos(const char* nombreArchivo, Jockey info);

int main(){

    Clima c;
    Caballo cab;
    mostrarDatos("../Archivos/clima.dat", c);
    mostrarDatos("../Archivos/caballos.dat", cab);
    
    return 0;
}


//Lee y muestra el dato
void leerArchivo(FILE* f, Clima info) {
    cout << "\n--- Clima ---\n";
    while(fread(&info, sizeof(Clima), 1, f) == 1) {
        cout << "ID Clima: " << info.id << endl;
        cout << "Fecha: " << info.fecha.dia << "/" << info.fecha.mes << "/" << info.fecha.anio << endl;
        cout << "Temperaturas: " << info.temperaturas[0] << ", " << info.temperaturas[1] << ", " << info.temperaturas[2] << endl;
        cout << "Descripcion: " << info.descripcion << endl;
        cout << "Agua caída: " << info.mmAguaCaida << " mm" << endl;
        cout << "-----------------------------------" << endl;
    }
}

// Sobrecarga 
void leerArchivo(FILE* f, MovSismicos info) {
    cout << "\n--- Movimientos Sismicos ---\n";
    while(fread(&info, sizeof(MovSismicos), 1, f) == 1) {
        cout << "ID Sismico: " << info.id << endl;
        cout << "Fecha: " << info.fechaReg.dia << "/" << info.fechaReg.mes << "/" << info.fechaReg.anio << endl;
        cout << "Pais: " << info.paisReg << endl;
        cout << "Latitud: " << info.latitud << " | Longitud: " << info.longitud << endl;
        cout << "Magnitud: " << info.magnitud << endl;
        cout << "-----------------------------------" << endl;
    }
}

// Sobrecarga 
void leerArchivo(FILE* f, Caballo info) {
    cout << "\n--- Caballos ---\n";
    while(fread(&info, sizeof(Caballo), 1, f) == 1) {
        cout << "ID Dato Caballo: " << info.idDato << endl;
        cout << "Nombre: " << info.nombre << endl;
        cout << "ID Caballo: " << info.idCaballo << endl;
        cout << "Velocidad Maxima: " << info.velocidadMaxima << " Km/h" << endl;
        cout << "Peso: " << info.peso << endl;
        cout << "Tamano herradura: " << info.tamanoHerradura << endl;
        cout << "Ultima carrera: " << info.ultimaCarrera.fecha.dia << "/" << info.ultimaCarrera.fecha.mes << "/" << info.ultimaCarrera.fecha.anio << endl;
        cout << "-----------------------------------" << endl;
    }
}

// Sobrecarga
void leerArchivo(FILE* f, Jockey info) {
    cout << "\n--- Jockeys ---\n";
    while(fread(&info, sizeof(Jockey), 1, f) == 1) {
        cout << "ID Dato Jockey: " << info.idDato << endl;
        cout << "Nombre y Apellido: " << info.nombreApellido << endl;
        cout << "DNI: " << info.DNI << endl;
        cout << "Edad: " << info.edad << endl;
        cout << "-----------------------------------" << endl;
    }
}

void mostrarDatos(const char* nombreArchivo, Clima info) {
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL) {
        cout << "El archivo todavia no existe o no hay datos cargados." << endl;
        return;
    }
    leerArchivo(f, info);
    fclose(f);
}

void mostrarDatos(const char* nombreArchivo, MovSismicos info) {
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL) {
        cout << "El archivo todavia no existe o no hay datos cargados." << endl;
        return;
    }
    leerArchivo(f, info);
    fclose(f);
}

void mostrarDatos(const char* nombreArchivo, Caballo info) {
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL) {
        cout << "El archivo todavia no existe o no hay datos cargados." << endl;
        return;
    }
    leerArchivo(f, info);
    fclose(f);
}

void mostrarDatos(const char* nombreArchivo, Jockey info) {
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL) {
        cout << "El archivo todavia no existe o no hay datos cargados." << endl;
        return;
    }
    leerArchivo(f, info);
    fclose(f);
}