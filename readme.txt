####################
###### README ######
####################

###### Experimentos de tiempos #######

compilación: $ make main.exe
ejecución:   $ ./main.exe < input.txt

formato del input file:
    - <num palabras diccionario> (formato entero)
    - conjunto de palabras del diccionario (tamaño n)
    - <tamaño de la sopa> (formato entero)
    - conjunto de palabras a insertar en la sopa (tamaño 20)
    Para mas clarificación, ver el ejemplo "input.txt" 
    
formato del output:
    "[Estructura de Datos] (m = [tamaño sopa]) ha encontrado [num palabras encontradas] palabras distintas en [tiempo de búsqueda]ms"
    Ejemplo:
        Sorted Vector (m = 100) ha encontrado 2958 palabras distintas en 923.139ms.
        Bloom Filter (m = 100) ha encontrado 2958 palabras distintas en 212.268ms.
        TST (m = 100) ha encontrado 2958 palabras distintas en 281.722ms.
        Double Hashing (m = 100) ha encontrado 2958 palabras distintas en 1593.43ms.
        

###### Experimentos de precisión del Filtro de Bloom ######

compilación: $ make main2.exe
ejecución:   $ ./main2.exe < input.txt

formato del input file:
    - <num palabras diccionario> (formato entero)
    - conjunto de palabras del diccionario (tamaño n)
    - <tamaño de la sopa> (formato entero)
    - conjunto de palabras a insertar en la sopa (tamaño 20)
    Para mas clarificación, ver el ejemplo "input.txt" 
    
formato del output:

    - "Coste de memoria: [tamaño en memoria de la ED]"
    - "Cantidad de hashes usados: [num de hashes usados]"
    Seguidamente imprime 5 veces (para hacer la media y evitar errores de dispersión):
        - "Número de falsos positivos [num falsos positivos encontrados]"
        - "Tiempo: [tiempo de búsqueda en ms]"
        

###### Documentación Doxygen ######

Para ver la documentación del código en formato Doxygen hay que abrir el archivo index.html en la carpeta comprimida html.tar.

