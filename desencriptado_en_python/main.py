import math


# Función para calcular la exponenciación modular de manera eficiente
def fast_modular_exponentiation(base, exponent, modulus):
    result = 1
    base = base % modulus
    while exponent > 0:
        if exponent % 2 == 1:
            result = (result * base) % modulus
        base = (base**2) % modulus
        exponent = exponent // 2
    return result


# Claves RSA (reemplaza estos valores con tus propias claves)
# D N
private_key = (87162023, 264930973)  # Clave privada (exponente de descifrado y módulo)

# Lee los números cifrados desde el archivo de texto
with open("pixelesEncriptados.txt", "r") as file:
    line = file.readline()
    encrypted_pixels = [int(pixel) for pixel in line.strip().split(",")]

# Desencripta los píxeles y reconstruye la imagen
decrypted_pixels = []
for encrypted_pixel in encrypted_pixels:
    decrypted_pixel = fast_modular_exponentiation(
        encrypted_pixel, private_key[0], private_key[1]
    )
    decrypted_pixels.append(decrypted_pixel)

# Ahora tienes los píxeles desencriptados en `decrypted_pixels`
# Debes convertirlos en una imagen RGB y guardarla (esto depende del formato de imagen que estés usando).

# A continuación, se muestra cómo convertir los píxeles en una imagen PNG utilizando la biblioteca Pillow.
from PIL import Image

# Especifica el ancho y alto de la imagen (ajusta esto según tus necesidades)
width = 800
height = 503

# Crea una nueva imagen vacía
img = Image.new("L", (width, height))

# Llena la imagen con los píxeles desencriptados
img.putdata(decrypted_pixels)

# Guarda la imagen en un archivo
img.save("asd.png")

print("Imagen desencriptada y guardada como 'decrypted_image.png'")
