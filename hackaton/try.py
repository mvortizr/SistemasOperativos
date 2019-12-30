dictOfLines = dict()
with open('numeros.txt') as fd:
   
   for line in fd:

        if line in dictOfLines:
            dictOfLines[line] += 1
        else:
            dictOfLines[line] = 1

print(dictOfLines)