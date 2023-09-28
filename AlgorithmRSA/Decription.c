#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

int main() {
    FILE* clavePrivadaArchivo = fopen("clave_privada.pem", "rb");
    FILE* archivoCifrado = fopen("archivo_cifrado.txt", "rb");
    FILE* archivoDesencriptado = fopen("archivo_desencriptado.txt", "wb");

    RSA* rsa = RSA_new();
    rsa = PEM_read_RSAPrivateKey(clavePrivadaArchivo, &rsa, NULL, NULL);

    if (rsa == NULL) {
        fprintf(stderr, "Error al leer la clave privada\n");
        return 1;
    }

    unsigned char enc_buf[128];
    unsigned char dec_buf[128];
    int enc_len, dec_len;

    while ((enc_len = fread(enc_buf, 1, 128, archivoCifrado)) > 0) {
        RSA_private_decrypt(enc_len, enc_buf, dec_buf, rsa, RSA_PKCS1_PADDING);
        fwrite(dec_buf, 1, dec_len, archivoDesencriptado);
    }

    fclose(clavePrivadaArchivo);
    fclose(archivoCifrado);
    fclose(archivoDesencriptado);

    RSA_free(rsa);
    return 0;
}

