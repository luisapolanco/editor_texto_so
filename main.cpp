#include <iostream>
#include <fstream>
#include <string>
#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <crypto++/filters.h>
#include <ncurses.h>

using namespace CryptoPP;
using namespace std;

// Clave y vector de inicialización (IV) para la encriptación
CryptoPP::byte key[AES::DEFAULT_KEYLENGTH] = {
    'm', 'i', '_', 's', 'u', 'p', 'e', 'r',
    '_', 'k', 'e', 'y', '1', '2', '3', '4'
};
CryptoPP::byte iv[AES::BLOCKSIZE]  = {
    'v', 'e', 'c', 't', 'o', 'r', '_', 'd', 
    'e', '_', 'i', 'n', 'i', '1', '2', '4'
};

// Función de encriptación
string encriptar(const string& texto) {
    string cipher;
    CBC_Mode<AES>::Encryption encryptor(key, sizeof(key), iv);
    StringSource s(texto, true, new StreamTransformationFilter(encryptor, new StringSink(cipher)));
    return cipher;
}

// Función de desencriptación
string desencriptar(const string& cipher) {
    string plain;
    CBC_Mode<AES>::Decryption decryptor(key, sizeof(key), iv);
    StringSource s(cipher, true, new StreamTransformationFilter(decryptor, new StringSink(plain)));
    return plain;
}

// Función para guardar texto encriptado
void guardarEncriptado(const string& nombreArchivo, const string& texto) {
    string cipher = encriptar(texto);
    ofstream archivo(nombreArchivo, ios::binary);
    archivo.write(cipher.c_str(), cipher.size());
    archivo.close();
}

// Función para cargar texto desencriptado
string cargarDesencriptado(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    
    // Validar si el archivo existe y se pudo abrir
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'." << endl;
        return ""; // Devuelve una cadena vacía como indicador
    }

    // Mover el cursor al final del archivo para verificar el tamaño
    archivo.seekg(0, ios::end);
    size_t size = archivo.tellg();
    archivo.seekg(0, ios::beg); // Regresar al inicio del archivo

    // Verificar si el archivo está vacío
    if (size == 0) {
        cerr << "Advertencia: El archivo '" << nombreArchivo << "' está vacío." << endl;
        return ""; // Devuelve una cadena vacía
    }

    // Leer el contenido del archivo
    string cipher((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();

    // Intentar desencriptar el contenido
    try {
        return desencriptar(cipher);
    } catch (const CryptoPP::Exception& e) {
        cerr << "Error: Fallo al desencriptar el contenido. " << e.what() << endl;
        return ""; // Devuelve una cadena vacía en caso de error
    }
}

// Función para borrar todos los elementos del archivo
void limpiarArchivo(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::trunc); // Abre en modo truncado
    archivo.close();
    cout << "Archivo '" << nombreArchivo << "' limpiado exitosamente.\n";
}

// Función para crear el archivo por si se borra o se inicia por primera vez el programa
void crearArchivoSiNoExiste(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);

    if (!archivo.is_open() || archivo.peek() == ifstream::traits_type::eof()) { 
        cout << "El archivo no existe o está vacío. (presiona Enter en una línea vacía para finalizar) Escribe el contenido inicial:\n";
        string nuevoContenido, linea;
        cin.ignore();
        while (true) {
            getline(cin, linea);
            if (linea.empty()) {
                break;
            }
            nuevoContenido += linea + "\n";
        }

        guardarEncriptado(nombreArchivo, nuevoContenido);
        cout << "Archivo creado y encriptado exitosamente.\n";
    }
}

int main() {
    
    string nombreArchivo = "archivo_encriptado.txt";
    crearArchivoSiNoExiste(nombreArchivo);

    while (true) {
        cout << "\n--- Menú ---\n";
        cout << "1. Abrir archivo\n";
        cout << "2. Editar archivo\n";
        cout << "3. Limpiar archivo\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        
        int opcion;
        cin >> opcion;
        cin.ignore(); //Buffr limpio
        
        if (opcion == 1) {
            string contenido = cargarDesencriptado(nombreArchivo);
            cout << "Contenido desencriptado:\n" << contenido << endl;
        } else if (opcion == 2) {
            // Cargar el contenido existente desencriptado
            string contenidoActual = cargarDesencriptado(nombreArchivo);

            // Mostrar el contenido existente
            cout << "Contenido actual (desencriptado):\n";
            cout << contenidoActual;
            cout << "--- Escribe el nuevo contenido (presiona Enter en una línea vacía para finalizar) ---\n";

            // Permitir agregar nuevas líneas
            string nuevoContenido;
            string linea;
            while (true) {
                getline(cin, linea);
                if (linea.empty()) {
                    break;
                }
                nuevoContenido += linea + "\n";
            }

            // Al contenido existente pues se le agrega el nuevo
            contenidoActual += nuevoContenido;

            guardarEncriptado(nombreArchivo, contenidoActual);
            cout << "Archivo actualizado y encriptado.\n";
        } else if (opcion == 3) {
            limpiarArchivo(nombreArchivo);
            crearArchivoSiNoExiste(nombreArchivo);
        } else if (opcion == 4) {
            cout << "Saliendo...\n";
            break;
        } else {
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    }
    return 0;
}
