import random as rd
import sys

if (len(sys.argv) < 5):
	print "Falta argumentos. Informe L = Largura maxima, N = numero de estrelas, P = peso maximo de cada estrela, Arquivo_Saida = nome do arquivo de saida."
else:
	maxDimensions = int(sys.argv[1])
	numStars = int(sys.argv[2])
	pesoMax = int(sys.argv[3])
	arquivo_out = sys.argv[4]
	if (maxDimensions <= 1):
		print "Informe um numero de dimensoes maior que 1."
	elif (numStars < 0):
		print "Informe um numero de estrelas positivo!"
	elif (pesoMax < 1):
		print "Informe um peso maximo maior que 0."
	else:
		with open(arquivo_out, "w") as f:
			f.write(str(maxDimensions) + " " + str(numStars) + "\n")
			for i in range(0, numStars):
				f.write(str(rd.randint(0, maxDimensions-1)))
				f.write(" ")
				f.write(str(rd.randint(0, maxDimensions-1)))
				f.write(" ")
				f.write(str(rd.randint(1, pesoMax)))
				f.write("\n")

