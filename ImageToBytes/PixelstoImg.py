from PIL import Image

# Especifica las dimensiones de la imagen original
ancho_original = 500  # Reemplaza con el ancho de tu imagen original
alto_original = 500   # Reemplaza con el alto de tu imagen original

# Lee la cadena de bytes desde el archivo de texto
with open("bytes_de_imagen.txt", "r") as archivo:
    cadena_de_bytes = archivo.read()

# Divide la cadena de bytes en una lista de enteros
bytes_imagen = [int(byte) for byte in cadena_de_bytes.split(',')]

# Convierte la lista de enteros en una cadena de bytes
bytes_imagen = bytes(bytes_imagen)

# Crea la imagen utilizando PIL
imagen = Image.frombytes("RGB", (ancho_original, alto_original), bytes_imagen)

# Guarda la imagen reconstruida
imagen.save("imagen_generada.jpg")

# Printea la confirmación de la creación de la imagen
print("La imagen se ha generado y guardado como imagen_generada.jpg")

