#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

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

int main() {
    // Clave privada y n (modulus) que se utilizarán para descifrar
    unsigned long long privateKey = 701153; // Reemplaza con tu clave privada
    unsigned long long n = 1040279; // Reemplaza con el valor de n correspondiente

    // Ruta del archivo de texto cifrado
    const char *inputFilePath = "/home/ghubuntu/Documents/GitHub/P1-SistemasOperativos/AlgorithmRSA/ciphertext.txt";
    // Ruta del archivo de texto descifrado
    const char *outputFilePath = "/home/ghubuntu/Documents/GitHub/P1-SistemasOperativos/AlgorithmRSA/descifrado.txt";

    // Leer el archivo de texto cifrado
    FILE *inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL) {
        perror("Error al abrir el archivo cifrado");
        return 1;
    }

    // Crear el archivo de texto descifrado
    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        perror("Error al crear el archivo descifrado");
        fclose(inputFile);
        return 1;
    }

    // Leer y descifrar el contenido del archivo cifrado
    unsigned long long ciphertext;
    while (fscanf(inputFile, "%llu,", &ciphertext) != EOF) {
        // Descifrar el valor
        unsigned long long plaintext = mod_pow(ciphertext, privateKey, n);

        // Escribir el valor descifrado en el archivo de salida
        fprintf(outputFile, "%llu,", plaintext);
    }

    // Cerrar archivos
    fclose(inputFile);
    fclose(outputFile);

    printf("Archivo descifrado guardado en %s\n", outputFilePath);

    return 0;
}

