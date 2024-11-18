# Editor de Texto. Parcial #4. Sistemas Operativos

## Integrantes
- [Luisa Maria Polanco Rodriguez]
- [Vanessa Alexandra Velez Restrepo]
- [Santiago Arias Higuita]
- [Luis Miguel Girald]
- [Miguel Angel Escudero]

## Objetivo del reto
Crear un editor de texto básico que permita encriptar y desencriptar el contenido automáticamente, asegurando que nunca quede en texto plano en el disco

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
   g++ main.cpp -o editor -lcryptopp -lncurses
   ```

2. **Para ejecutar el programa:**
   Ejecutar el siguiente comando:
   ```bash
   ./main
   ```
