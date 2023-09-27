#Transformacion de imagen a bytes

#Abre el archivo de imagen en modo binario
with open("imagenPrueba.jpg", "rb") as imagen_file:
    # Lee los bytes de la imagen
    bytes_imagen = imagen_file.read()

#Convierte los bytes de la imagen en una cadena de bytes sin corchetes cuadrados y sin espacios entre comas
cadena_de_bytes = ','.join([str(byte) for byte in bytes_imagen])

#Guarda la cadena de bytes en un archivo de texto
with open("bytes_de_imagen.txt", "w") as archivo:
    archivo.write(cadena_de_bytes)

#Printea la confirmación de la creación del archivo de texto con los bytes de la imagen
print("Los bytes de la imagen se han guardado en bytes_de_imagen.txt")
