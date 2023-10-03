from PIL import Image

# Función para aplicar el filtro laplaciano a una imagen representada como una matriz
def aplicar_filtro_laplaciano(imagen):
    # Definimos la máscara del filtro laplaciano 3x3
    mascara = [
        [-1, -1, -1],
        [-1,  8, -1],
        [-1, -1, -1]
    ]

    # Dimensiones de la imagen
    alto, ancho = len(imagen), len(imagen[0])

    # Crear una nueva matriz para almacenar el resultado
    resultado = [[0] * ancho for _ in range(alto)]

    # Aplicar el filtro laplaciano a la imagen
    for y in range(1, alto - 1):  # Excluimos los bordes de la imagen
        for x in range(1, ancho - 1):  # Excluimos los bordes de la imagen
            suma = 0

            # Aplicar la máscara del filtro laplaciano
            for i in range(-1, 2):
                for j in range(-1, 2):
                    pixel = imagen[y + i][x + j]
                    mascara_valor = mascara[i + 1][j + 1]
                    suma += pixel * mascara_valor

            # Almacenar el valor resultante en la matriz de resultado
            resultado[y][x] = suma


    return resultado

# Leer los píxeles desde un archivo de texto
with open('images/image.txt', 'r') as archivo_entrada:
    # Leer los datos y dividirlos por comas para obtener una lista de valores
    datos = archivo_entrada.read().strip().split(',')
    # Convertir los valores a enteros
    pixeles = [int(valor) for valor in datos]

# Ancho y alto de la imagen
ancho = 128
alto = 129

# Convertir la lista de píxeles en una matriz 2D
imagen = [pixeles[i:i + ancho] for i in range(0, len(pixeles), ancho)]

# Aplicar el filtro laplaciano a la imagen
imagen_filtrada = aplicar_filtro_laplaciano(imagen)

# Escribir los píxeles resultantes en un archivo de texto con formato
with open('images/salida.txt', 'w') as archivo_salida:
    for fila in imagen_filtrada:
        fila_str = ','.join(map(str, fila))
        archivo_salida.write(fila_str + '\n')


# Crear una imagen PIL a partir de la matriz resultante
imagen_pil = Image.new('L', (ancho, alto))

for y in range(alto):
    for x in range(ancho):
        valor_pixel = imagen_filtrada[y][x]
        if valor_pixel < 0:
            valor_pixel = 0
        elif valor_pixel > 255:
            valor_pixel = 255
        imagen_pil.putpixel((x, y), valor_pixel)

# Guardar la imagen como un archivo de imagen (por ejemplo, en formato PNG)
imagen_pil.save('images/salida.png')