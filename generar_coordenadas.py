def coordenadas(lista,posicion,aumento):
	while lista[posicion]<400:
		lista[posicion]+=aumento
		for x in lista:
			print(x,end=" ")
		print("")

while True:
	lista=str(input("ingrese las coordenadas :")).split(" ")
	lista=[int(x) for x in lista]
	posicion=int(input("posicion :"))
	aumento=int(input("aumento :"))
	coordenadas(lista,posicion,aumento)
