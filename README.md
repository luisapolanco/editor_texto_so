# Editor de Texto. Parcial #4. Sistemas Operativos

## Integrantes
- Luisa Maria Polanco Rodriguez
- Vanessa Alexandra Velez Restrepo
- Santiago Arias Higuita
- Luis Miguel Giraldo
- Miguel Angel Escudero

## Objetivo del reto
Crear un editor de texto básico que permita encriptar y desencriptar el contenido automáticamente, asegurando que nunca quede en texto plano en el disco

## Librerias Utilizadas

1. Crypto++
Descripción:
Crypto++ es una biblioteca de criptografía de código abierto ampliamente utilizada para implementar algoritmos criptográficos en C++, proporciona herramientas para encriptación, desencriptación, generación de claves, firmas digitales y otros servicios de seguridad.
Conceptos principales:
•	AES (Advanced Encryption Standard):
o	AES es un algoritmo de cifrado simétrico estándar desarrollado para proteger datos de manera eficiente.
o	Opera en bloques de datos de longitud fija (generalmente 128 bits) y utiliza claves de tamaño fijo (128, 192 o 256 bits).
•	CBC_Mode:
o	En el modo CBC, cada bloque de texto plano se combina con el bloque cifrado anterior (usando XOR) antes de ser procesado.
o	El IV es esencial para garantizar que el primer bloque tenga una semilla única, incluso si el mismo texto plano se cifra varias veces.
•	Clases principales:
o	AES::DEFAULT_KEYLENGTH: Define el tamaño predeterminado de la clave para AES (128 bits en este caso).
o	StreamTransformationFilter: Aplica transformaciones de flujo, como encriptación o desencriptación, y envía la salida a un StringSink.

2. fstream
Descripción:
La biblioteca estándar fstream de C++ se utiliza para manejar archivos. Proporciona clases como ifstream (para lectura), ofstream (para escritura) y fstream (para lectura/escritura).

3. ncurses

Descripción:
ncurses es una biblioteca de C para la manipulación de la salida en terminal. Permite crear interfaces de usuario basadas en texto con menús, ventanas y otras estructuras interactivas.
Conceptos principales:
•	Pantalla y entradas:
o	Permite el control de la pantalla del terminal, como manejar el cursor, colorear texto y recibir entradas del usuario.
o	Es útil para aplicaciones que necesitan menús o interfaces dinámicas.
4. string
Descripción:
string es una biblioteca estándar de C++ para trabajar con cadenas de texto. Proporciona una interfaz de alto nivel para manipular texto de manera eficiente.

## ¿Qué se logró?
Este proyecto es básicamente un editor de texto hecho a mano, pero con un toque de seguridad 🔒. 
- **El objetivo principal**: guardar los archivos siempre encriptados en disco y desencriptarlos automáticamente al abrirlos.
- Usamos la librería **Crypto++** para hacer la magia de la encriptación y desencriptación, específicamente el algoritmo **AES** (que es súper seguro, por cierto).
- También usamos **Ncurses** para que sea un poquito más cómodo trabajar con texto desde la terminal.
  
- ¿Qué puede hacer este editor? básicamente:
  - Crear un archivo desde cero si no existe.
  - Mostrar el contenido desencriptado para que se edite.
  - Permitir que se escribe y borre texto de manera básica.
  - Guardar todo lo que se editó, pero siempre encriptado.


## ¿Cómo correr el código?

1. **Compilar el código:**
   Se necesita el compliadir de C++ como `g++` y las librerías **Crypto++** y **Ncurses**. El código se compila con el siguiente comando:
   ```bash
   g++ main.cpp -o main -lcryptopp -lncurses
   ```

2. **Para ejecutar el programa:**
   Ejecutar el siguiente comando:
   ```bash
   ./main
   ```
   ![image](https://github.com/user-attachments/assets/8f7d26cf-587e-41b6-b0bb-01383085c64a)

## Conclusiones

Seguridad mejorada en aplicaciones básicas: Este proyecto demuestra cómo es posible incorporar seguridad avanzada, como la encriptación AES, incluso en herramientas sencillas como un editor de texto. Esto subraya la importancia de proteger la información desde la base.

Integración práctica de bibliotecas: El uso combinado de Crypto++ para la encriptación y Ncurses para la edición de texto en la terminal ejemplifica cómo diferentes tecnologías pueden unirse para resolver problemas específicos.

Facilidad de uso y experiencia del usuario: Aunque se trata de una aplicación básica, la implementación de funcionalidades como la edición en tiempo real y la encriptación transparente destaca cómo la seguridad no tiene por qué comprometer la usabilidad.

## Trabajo Futuro
- Se plantea la posibilidad de trabajo futuro de implementarlo con otros algoritmos de encriptación de la entrega pasada como RSA y cesar
