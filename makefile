# MAKEFILE: emplearemos esta utilidad para preparar ejecutables en los que 
# intervienen varias clases, de forma que con una unica instruccion 
# se compilan o linkan los ficheros estrictamente necesarios.
#
# Si en el directorio solo hay un proyecto y un makefile, para ejecutar este
# simplemente se escribe "make"
#
# Nuestros makefile se componen de una creación de variables seguida de
# una serie de instrucciones con la estructura:
#
#           fichero1":" lista de ficheros 
#           "tabulador" instrucción de compilación o linkado	
#
#           fichero2":" lista de ficheros 
#           "tabulador" instrucción de compilación o linkado	
#        
#           etc
#
# Esto significa: para obtener el fichero1 es necesario que existan todos
# los ficheros de su lista; si no existe o es más antiguo que alguno de
# ellos, se obtiene o actualiza con su instruccion; si no existe alguno de
# los ficheros de la lista, el proceso acaba con error; lo mismo para el
# fichero2, etc
#
# Mediante este esquema, cada uno de nuestros makefile ha de contener todas
# las instrucciones que sean necesarias para obtener los .exe del
# proyecto correspondiente.
#
# La siguiente instruccion significa:
# para obtener main.exe es necesario que existan todos los ficheros de la lista de ficheros;
# si main.exe no existe o algún fichero de la lista se ha actualizado,
# se obtiene con el g++ -o ... (el tabulador antes de g++ es necesario)
#
main.exe: diccBloomFilter.cc diccDHashing.cc diccSortedVector.cc diccTrie.cc LibreriaSolvers.cc main.cc Sopa.cc
	g++ -O2 -Wall -o main.exe main.cc

main2.exe: diccBloomFilter.cc diccTrie.cc LibreriaSolvers.cc mainPrecisionBloom.cc Sopa.cc
	g++ -O2 -Wall -o main2.exe mainPrecisionBloom.cc

html:
	doxygen Doxyfile
	tar -cvf html.tar DOC/html

practica.tar:
	make html
	tar -cvf practica.tar diccBloomFilter.cc diccBloomFilter.hh diccDHashing.cc diccDHashing.hh diccSortedVector.cc diccSortedVector.hh diccTrie.cc diccTrie.hh Documentacion_Proyecto_A.pdf Doxyfile html.tar input.txt LibreriaSolvers.cc main.cc mainPrecisionBloom.cc makefile readme.txt ReducedDicc20.txt Sopa.cc Sopa.hh tiempo.c 


# Esta última opción sirve para limpiar el directorio de ficheros 
# innecesarios; se ejecuta mediante el comando "make clean"
#
clean:
	rm -f *.exe *.tar
