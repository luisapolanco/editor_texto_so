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

int main() {   
    // keypad(stdscr, TRUE);
	noecho();
    string nombreArchivo = "archivo_encriptado.txt";
    string contenido = cargarDesencriptado(nombreArchivo);

    // Inicializa la biblioteca Ncurses
    initscr();
   
    printw("Contenido desencriptado del archivo:\n\n%s", contenido.c_str());
    printw("\n\n--- Escribe el nuevo contenido (presiona Ctrl+D para guardar) ---\n");

    string nuevoContenido;
    char ch;
    while ((ch = getch()) != 4) { // Ctrl+D
        // printw("Tecla presionada: %d\n", ch);
        if (ch == KEY_BACKSPACE || ch == 127 || ch == 12) { // Detecta tecla de retroceso
            if (!nuevoContenido.empty()) {
                // nuevoContenido.pop_back();  // Elimina el último carácter de la cadena
                // int y, x;
                // getyx(stdscr, y, x);       // Obtén posición actual del cursor
                // if (x > 0) {               // Mueve el cursor hacia atrás
                //     move(y, x - 1);
                //     addch(' ');            // Borra el carácter en pantalla
                //     move(y, x - 1);        // Mueve el cursor a la posición borrada
                // }
                delch();
                refresh();
            }
        } else {
            nuevoContenido += ch;         // Agrega el carácter a la cadena
            // addch(ch);                    // Lo muestra en pantalla
        }
    }
    contenido += "\n" + nuevoContenido;

    endwin();  // Cierra Ncurses
    
    // Guarda el contenido completo encriptado
    guardarEncriptado(nombreArchivo, contenido);
    cout << "Archivo guardado exitosamente encriptado.\n";
    return 0;
}