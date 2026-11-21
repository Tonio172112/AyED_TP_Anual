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
    int id;
    Fecha fecha;
    int temperaturas[3];
    char descripcion[256+1];
    int mmAguaCaida;
};

struct MovSismicos{
    int id;
    Fecha fechaReg;
    char paisReg[56+1];
    double latitud;
    double longitud;
    float magnitud;
};

struct Caballo{
    int id; 
    int idJockey; 
    char nombre[100+1];
    int idCaballo; 
    float velocidadMaxima; 
    float peso;
    float tamanoHerradura;
    FechaHora ultimaCarrera;
};

struct NodoCaballo{
    Caballo info;
    NodoCaballo* sgte;
};

struct Jockey{
    int id;
    char nombreApellido[100+1];
    int DNI; 
    int edad;
    NodoCaballo* listaCaballos;
};

void leerArchivo(FILE* f, Clima info);
void leerArchivo(FILE* f, MovSismicos info);
void leerArchivo(FILE* f, Caballo info);
void leerArchivo(FILE* f, Jockey info);
void mostrarDatos(const char* nombreArchivo, Clima info);
void mostrarDatos(const char* nombreArchivo, MovSismicos info);
void mostrarDatos(const char* nombreArchivo, Caballo info);
void mostrarJockeysConCaballos(const char* archivoJockeys, const char* archivoCaballos);

int main(){
    cout << "=== LECTURA DE ARCHIVOS ===" << endl;
    Clima c;
    MovSismicos s;
    Caballo cab;
    
    mostrarDatos("../Archivos/clima.dat", c);
    mostrarDatos("../Archivos/sismos.dat", s);
    mostrarDatos("../Archivos/caballos.dat", cab);
    mostrarJockeysConCaballos("../Archivos/jockeys.dat", "../Archivos/caballos.dat");
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
    cout << "\n--- Caballos (General) ---\n";
    while(fread(&info, sizeof(Caballo), 1, f) == 1) {
        cout << "ID Caballo: " << info.id << " | ID Jockey Vinculado: " << info.idJockey << endl;
        cout << "Nombre: " << info.nombre << endl;
        cout << "ID Matricula Caballo: " << info.idCaballo << endl;
        cout << "Velocidad Maxima: " << info.velocidadMaxima << " Km/h" << endl;
        cout << "Peso: " << info.peso << endl;
        cout << "Tamano herradura: " << info.tamanoHerradura << endl;
        
        int h= info.ultimaCarrera.tiempo.hora;
        int min= info.ultimaCarrera.tiempo.minuto;
        int seg= info.ultimaCarrera.tiempo.segundo;
        const char* ampm= (h>=12) ? "PM":"AM";
        int hora12= h % 12;
        if(hora12==0)hora12=12;
        cout << "Ultima carrera: "
        <<info.ultimaCarrera.fecha.dia<< "/"
        <<info.ultimaCarrera.fecha.mes<< "/"
        <<info.ultimaCarrera.fecha.anio<< " "
        <<hora12<< ":"
        <<(min<10 ? "0":"")<<min<< ":"
        <<(seg<10 ? "0":"")<<seg<< " "
        <<ampm<<"GMT -3"<< endl;
        cout << "-----------------------------------" << endl;
    }
}


void mostrarJockeysConCaballos(const char* archivoJockeys, const char* archivoCaballos) {
    FILE* fJ = fopen(archivoJockeys, "rb");
    if(fJ == NULL) {
        cout << "El archivo de jockeys todavia no existe o no hay datos cargados." << endl;
        return;
    }

    Jockey j;
    cout << "\n--- JOCKEYS Y SUS CABALLOS ASIGNADOS ---" << endl;
    while(fread(&j, sizeof(Jockey), 1, fJ) == 1) {
        cout << "ID Jockey: " << j.id << endl;
        cout << "Nombre y Apellido: " << j.nombreApellido << endl;
        cout << "DNI: " << j.DNI << endl;
        cout << "Edad: " << j.edad << endl;
        cout << " Caballos asignados:" << endl;

        // Abrimos el archivo de caballos para buscar los que pertenecen a este jockey
        FILE* fC = fopen(archivoCaballos, "rb");
        bool tieneCaballos = false;
        if(fC != NULL) {
            Caballo c;
            while(fread(&c, sizeof(Caballo), 1, fC) == 1) {
                if(c.idJockey == j.id) {
                    tieneCaballos = true;
                    cout << "   - ID Caballo: " << c.id << " | Nombre: " << c.nombre 
                         << " (Vel. Max: " << c.velocidadMaxima << " Km/h)" << endl;
                }
            }
            fclose(fC);
        }
        if(!tieneCaballos) {
            cout << "   (Sin caballos asignados)" << endl;
        }
        cout << "-----------------------------------" << endl;
    }
    fclose(fJ);
}

void mostrarDatos(const char* nombreArchivo, Clima info) {
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL) { cout << "Archivo no encontrado: " << nombreArchivo << endl; return; }
    leerArchivo(f, info);
    fclose(f);
}

void mostrarDatos(const char* nombreArchivo, MovSismicos info) {
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL) { cout << "Archivo no encontrado: " << nombreArchivo << endl; return; }
    leerArchivo(f, info);
    fclose(f);
}

void mostrarDatos(const char* nombreArchivo, Caballo info) {
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL) { cout << "Archivo no encontrado: " << nombreArchivo << endl; return; }
    leerArchivo(f, info);
    fclose(f);
}