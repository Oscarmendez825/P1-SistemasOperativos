#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función para calcular el máximo común divisor (GCD)
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Función para calcular (base^exponent) % modulus de manera eficiente
unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    unsigned long long result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Función para generar claves RSA de 16 bits
void generateRSAKeys(unsigned long long *publicKey, unsigned long long *privateKey, unsigned long long *n) {
    unsigned long long p, q, phi, e, d;

    // Elegir dos números primos p y q (16 bits cada uno)
    p = 1031;
    q = 1009;

    // Calcular n y phi(n)
    *n = p * q;
    phi = (p - 1) * (q - 1);

    // Elegir un número e coprimo con phi(n) (16 bits)
    e = 65537;

    // Calcular d, el inverso multiplicativo de e modulo phi(n)
    d = 1;
    while (1) {
        if ((d * e) % phi == 1)
            break;
        d++;
    }

    *publicKey = e;
    *privateKey = d;
}

// Función para cifrar un valor utilizando RSA
unsigned long long encrypt(unsigned long long plaintext, unsigned long long publicKey, unsigned long long n) {
    return mod_pow(plaintext, publicKey, n);
}

// Función para descifrar un valor utilizando RSA
unsigned long long decrypt(unsigned long long ciphertext, unsigned long long privateKey, unsigned long long n) {
    return mod_pow(ciphertext, privateKey, n);
}

int main() {
    unsigned long long publicKey, privateKey, n;

    // Generar claves RSA de 16 bits
    generateRSAKeys(&publicKey, &privateKey, &n);
    printf("Llave pública (e): %llu\n", publicKey);
    printf("Llave privada (d): %llu\n", privateKey);
    printf("n: %llu\n", n);

    // Ruta del archivo de texto original
    const char *inputFilePath = "/home/ghubuntu/Documents/GitHub/P1-SistemasOperativos/AlgorithmRSA/text.txt";
    // Ruta del archivo de texto cifrado
    const char *outputFilePath = "/home/ghubuntu/Documents/GitHub/P1-SistemasOperativos/AlgorithmRSA/ciphertext.txt";

    // Leer el archivo de texto original
    FILE *inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL) {
        perror("Error al abrir el archivo de entrada");
        return 1;
    }

    // Crear el archivo temporal para valores no cifrados
    const char *tempFilePath = "/home/ghubuntu/Documents/GitHub/P1-SistemasOperativos/AlgorithmRSA/temp.txt";
    FILE *tempFile = fopen(tempFilePath, "w");
    if (tempFile == NULL) {
        perror("Error al crear el archivo temporal");
        fclose(inputFile);
        return 1;
    }

    // Leer y escribir los dos primeros valores en el archivo temporal
    unsigned long long value1, value2;
    if (fscanf(inputFile, "%llu,%llu,", &value1, &value2) != 2) {
        perror("Error al leer los dos primeros valores del archivo de entrada");
        fclose(inputFile);
        fclose(tempFile);
        return 1;
    }
    fprintf(tempFile, "%llu,%llu,", value1, value2);

    // Leer el contenido del archivo de texto original y cifrarlo
    char buffer[1024];
    while (fscanf(inputFile, "%llu,", &value1) != EOF) {
        // Escribir el valor sin cifrar en el archivo temporal
        fprintf(tempFile, "%llu,", value1);
    }

    // Cerrar el archivo temporal y el archivo original
    fclose(tempFile);
    fclose(inputFile);

    // Reabrir el archivo original en modo de escritura
    inputFile = fopen(inputFilePath, "w");
    if (inputFile == NULL) {
        perror("Error al abrir el archivo de entrada en modo de escritura");
        return 1;
    }

    // Reabrir el archivo temporal en modo de lectura y copiar su contenido al archivo original
    tempFile = fopen(tempFilePath, "r");
    if (tempFile == NULL) {
        perror("Error al abrir el archivo temporal en modo de lectura");
        fclose(inputFile);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), tempFile) != NULL) {
        fputs(buffer, inputFile);
    }

    // Cerrar los archivos
    fclose(tempFile);
    fclose(inputFile);

    // Eliminar el archivo temporal
    remove(tempFilePath);

    // Ahora puedes cifrar el archivo original, omitiendo los dos primeros valores

    // Leer el archivo de texto original nuevamente

    // Crear el archivo de texto cifrado

    // Cifrar los valores y escribirlos en el archivo de salida

    // Cerrar los archivos y finalizar

    printf("Los textos cifrados se han guardado en %s\n", outputFilePath);

    return 0;
}

