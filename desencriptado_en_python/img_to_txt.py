from PIL import Image

# Ruta de la imagen de entrada (cambia esto por la ruta de tu imagen)
input_image_path = "images/image.png"

# Abre la imagen con Pillow
image = Image.open(input_image_path)

# Convierte la imagen a escala de grises
image = image.convert("L")

# Obtiene las dimensiones de la imagen
width, height = image.size

# Ruta del archivo de salida de texto
output_txt_path = "images/image.txt"

# Abre el archivo de salida en modo de escritura
with open(output_txt_path, "w") as txt_file:
    # Escribe las dimensiones de la imagen al principio del archivo
    txt_file.write(f"{width},{height},")
    
    # Obtiene los píxeles de la imagen
    pixels = list(image.getdata())

    # Itera sobre los píxeles y escribe sus valores en el archivo de texto
    for pixel in pixels:
        txt_file.write(f"{pixel},")
