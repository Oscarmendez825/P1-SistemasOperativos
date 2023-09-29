#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

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

int main() {
    unsigned long long publicKey, privateKey, n;

    // Generar claves RSA de 16 bits
    generateRSAKeys(&publicKey, &privateKey, &n);
    printf("Llave pública (e): %llu\n", publicKey);
    printf("Llave privada (d): %llu\n", privateKey);
    printf("n: %llu\n", n);

    // Ruta del archivo de texto original
    const char *inputFilePath = "/home/gonzalo/Documentos/GitHub/P1-SistemasOperativos/AlgorithmRSA/text.txt";
    // Ruta del archivo de texto cifrado
    const char *outputFilePath = "/home/gonzalo/Documentos/GitHub/P1-SistemasOperativos/AlgorithmRSA/ciphertext.txt";

    // Leer el archivo de texto original
    FILE *inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL) {
        perror("Error al abrir el archivo de entrada");
        return 1;
    }

    // Crear el archivo de texto cifrado
    int fd = open(outputFilePath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error al abrir el archivo de salida");
        fclose(inputFile);
        return 1;
    }

    // Obtener el tamaño del archivo de entrada
    fseek(inputFile, 0, SEEK_END);
    long file_size = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Truncar el archivo de salida al tamaño del archivo de entrada
    if (ftruncate(fd, file_size) == -1) {
        perror("Error al truncar el archivo");
        fclose(inputFile);
        close(fd);
        return 1;
    }

    // Mapear el archivo de salida en memoria
    char *file_contents = mmap(NULL, file_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (file_contents == MAP_FAILED) {
        perror("Error al mapear el archivo de salida");
        fclose(inputFile);
        close(fd);
        return 1;
    }

    // Leer el contenido del archivo de texto original, cifrarlo y escribirlo en el archivo de salida separado por comas
    char buffer[1024];
    unsigned long long plaintext;
    int offset = 0;
    int isFirstValue = 1; // Para evitar agregar una coma antes del primer valor
    while (fscanf(inputFile, "%llu,", &plaintext) != EOF) {
        // Cifrar el valor
        unsigned long long ciphertext = mod_pow(plaintext, publicKey, n);

        // Convertir el valor cifrado a una cadena
        char ciphertext_str[20]; // Suficientemente grande para contener el número cifrado
        snprintf(ciphertext_str, sizeof(ciphertext_str), "%llu", ciphertext);

        // Escribir el valor cifrado en el archivo de salida
        if (isFirstValue) {
            isFirstValue = 0;
        } else {
            offset += sprintf(file_contents + offset, ",");
        }
        offset += sprintf(file_contents + offset, "%s", ciphertext_str);

        printf("Texto original: %llu\n", plaintext);
        printf("Texto cifrado: %llu\n", ciphertext);
    }

    // Liberar recursos
    fclose(inputFile);
    munmap(file_contents, file_size);
    close(fd);

    printf("Los textos cifrados se han guardado en %s\n", outputFilePath);

    return 0;
}
