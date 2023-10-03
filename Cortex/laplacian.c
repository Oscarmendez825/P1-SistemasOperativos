#include "encode.h"
#include "laplacian.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

void laplacian_set_zeros(volatile unsigned short **sdram_addr)
{
    int limit = (*sdram_addr)[0] * (*sdram_addr)[1] + 2;
    for (int i = 2; i < limit; i++)
        (*sdram_addr)[i] = (unsigned short)0;
}

// Función para aplicar el filtro laplaciano a una imagen unidimensional
void laplacian(volatile unsigned short **sdram_addr)
{
    int width = (*sdram_addr)[0];
    int height = (*sdram_addr)[1];
    int base_offset = width * height + 2;
    int result_offset = 2;

    unsigned short percentage = (*sdram_addr)[width * height * 2 + 2];

    // Definimos la máscara del filtro laplaciano
    int mask[3][3] = {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1}};

    // Iteramos a través de la imagen
    for (int y = height * percentage / 100 + 1; y < height - 1; y++)
    {
        // Excluimos los bordes de la imagen
        for (int x = 1; x < width - 1; x++)
        {
            // Excluimos los bordes de la imagen
            int total = 0;

            // Aplicamos la máscara del filtro laplaciano
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int pixel = (*sdram_addr)[(y + i) * width + (x + j) + base_offset];
                    int mask_value = mask[i + 1][j + 1];
                    total += pixel * mask_value;
                }
            }

            // Almacenamos el valor resultante en el arreglo de resultado
            if (total < 0)
                total = 0;
            else if (total > 255)
                total = 255;
            (*sdram_addr)[y * width + x + result_offset] = (unsigned short)total;
        }
    }
}

int write_results(volatile unsigned short **sdram_addr)
{
    int width = (*sdram_addr)[0];
    int height = (*sdram_addr)[1];
    int size = width * height;
    int decoded_offset = size + 2;

    FILE *file;
    file = fopen("images/decoded.txt", "w");

    if (file == NULL)
    {
        perror("Error al abrir el file");
        return 1;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d", (*sdram_addr)[i + decoded_offset]);
        if (i < size - 1)
        {
            fprintf(file, ",");
        }
    }

    fclose(file);

    FILE *file2;
    file2 = fopen("images/laplacian.txt", "w");

    if (file2 == NULL)
    {
        perror("Error al abrir el file");
        return 1;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file2, "%d", (*sdram_addr)[i + 2]);
        if (i < size - 1)
        {
            fprintf(file2, ",");
        }
    }

    fclose(file2);

    unsigned char *image = malloc((size) * sizeof(unsigned char));
    for (int i = 0; i < size; i++)
        image[i] = (unsigned char)((*sdram_addr)[i + 2]);

    stbi_write_png("images/laplacian.png", width, height, 1, image, width * 1);

    for (int i = 0; i < size; i++)
        image[i] = (unsigned char)((*sdram_addr)[i + decoded_offset]);

    stbi_write_png("images/decoded.png", width, height, 1, image, width * 1);

    free(image);

    return 0;
}
