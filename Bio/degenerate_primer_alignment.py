import sys
def buscaCadena(cadena,newSeq,posiciones):
    length = len(newSeq)
    i=0
    for i in range(len(cadena)):
        if cadena[i:i+length]==newSeq:
            posiciones.append((i,cadena[i:i+length]))

def validaSec(cadena,secuencia,posiciones):   # ACATGTATGATCTGGTGATTTGTAAGA
    newSeq=secuencia
    aux=''
    index=1
    if newSeq[index]=='A' or newSeq[index]=='C' or newSeq[index]=='G' or newSeq[index]=='T':
        index+=1
        if index<len(secuencia):
            buscaCadena(cadena,newSeq,posiciones)
    else:
        if newSeq[index] == 'R':
            newSeq[index]='G'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='A'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'Y':
            newSeq[index]='T'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='C'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'M':
            newSeq[index]='A'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='C'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'K':
            newSeq[index]='G'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='T'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'S':
            newSeq[index]='G'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='C'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'W':
            newSeq[index]='A'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='T'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'H':
            newSeq[index]='A'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='C'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='T'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'B':
            newSeq[index]='G'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='T'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='C'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'V':
            newSeq[index]='G'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='C'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='A'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'D':
            newSeq[index]='G'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='A'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='T'  
            validaSec(cadena,newSeq,posiciones)
        if newSeq[index] == 'N':
            newSeq[index]='G'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='A'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='T'  
            validaSec(cadena,newSeq,posiciones)
            newSeq[index]='C'  
            validaSec(cadena,newSeq,posiciones)
def main():
    if len(sys.argv) != 3:
        print("Se requiere excatamente 2 argumentos.")
        print(" Uso: python nombredelarchivo.py argumento1 argumento2")
        sys.exit(1)
    cadena = list(sys.argv[1])
    subcadena = list(sys.argv[2])
    posiciones = []
    validaSec(cadena,subcadena,posiciones)
    
    print("pos seqn")
    for pos, seqn in posiciones:
        print(pos,"".join(seqn))
if __name__=="__main__":
    main()
