# AyED_TP_Anual 

Repositorio destinado al desarrollo, resolución y entrega del Trabajo Práctico Anual de la materia **Algoritmos y Estructuras de Datos**, dictado por la docente **Roxana Leituz** en la **Universidad Tecnológica Nacional - Facultad Regional Buenos Aires (UTN.BA)**.

## 👥 Integrantes
* **Vinazza Antonio**
* **Burgos Victoria**


---

## 🎯 Descripción del Proyecto
El objetivo del TP consiste en el desarrollo de una Inteligencia Artificial rebajada orientada a la recopilación científica. El sistema se compone de dos programas principales interactuando a través de archivos binarios/texto en C++:

1. **Programa de Recopilación de Datos:** Encargado de la persistencia y escritura de archivos completos según los requerimientos solicitados por el servidor.
2. **Programa de Consultas:** Un sistema interactivo que procesa la información disponible en los archivos generados para responder a consultas científicas específicas utilizando un menú estructurado.

---

## 📊 Categorías de Datos Implementadas

1. **Clima:** Control de IDs únicos, fechas, vectores térmicos (mínima, persistente, máxima), descripción de condiciones climáticas y milímetros de agua caída.
2. **Movimientos Sísmicos:** Registro secuencial por ID de la fecha (D/M/A), localización geográfica por país, coordenadas (latitud/longitud) y magnitud registrada.
3. **Datos Físicos de Caballos:** Administración del identificador del caballo, velocidad máxima, peso, tamaño de herradura e información cronológica del último evento hípico.
4. **Jockeys:** Informacion sobre los jockey de los caballos.

---

## ⚙️ Conceptos de Algoritmos Aplicados
Para cumplir con las restricciones de la cátedra de no utilizar bibliotecas externas a lo aprendido en clase, se implementaron de forma nativa las siguientes técnicas lógicas:
* **Estructuras de Datos Dinámicas:** Listas enlazadas simples/dobles para la carga de datos catastróficos.
* **Algoritmos de Ordenamiento y Búsqueda:** Búsqueda binaria para optimizar accesos y búsqueda directa.
* **Procesamiento de Archivos:** Lectura y escritura secuencial de flujos de datos.
* **Lógica Avanzada de Flujos:** Implementación de Apareo de archivos y algoritmos basados en Corte de Control.
* **Modularización:** Sobrecarga de funciones para diversificar comportamientos según los tipos de datos procesados.

---

## 📂 Estructura del Repositorio
* `/RecopilacionDeDatos.cpp` -> Código fuente del módulo de carga y almacenamiento de datos científicos.
* `/[Nombre_Consultas].cpp` -> Código fuente del sistema de menús y procesamiento de consultas analíticas.
* `/Archivos_Anexos/` -> Carpeta con los archivos `.dat` o `.txt` generados para las pruebas funcionales.
* `/Documentacion/` -> Manual de usuario, detalles metodológicos de resolución y capturas de pantalla de ejecución.
