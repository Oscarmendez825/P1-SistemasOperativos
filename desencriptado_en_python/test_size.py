with open('images/result.txt', 'r') as file:
    # Lee el contenido del archivo y divide los números por comas
    numeros = file.read().split(',')


    for numero in numeros:
        try:
            numero_entero = int(numero)
            if numero_entero > 65535:
                print(f"El número {numero_entero} es mayor que 65535.")
        except ValueError:
            # Ignora los valores que no se pueden convertir a enteros
            pass
    print("asd")