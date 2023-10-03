#include "encode.h"
#include "laplacian.h"

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

    // Definimos la máscara del filtro laplaciano
    int mask[3][3] = {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1}};

    // Iteramos a través de la imagen
    for (int y = 1; y < height - 1; y++)
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
