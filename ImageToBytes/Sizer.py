from PIL import Image

# Abre la imagen
imagen = Image.open('imagenPrueba.jpg')

# Obtiene el tamaño de la imagen
ancho, alto = imagen.size

# Imprime el tamaño
print(f"Ancho: {ancho}px, Alto: {alto}px")

# Cierra la imagen (opcional)
imagen.close()

