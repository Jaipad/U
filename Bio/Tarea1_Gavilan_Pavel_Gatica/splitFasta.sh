#!/bin/bash


# Verificar que se hayan proporcionado los argumentos requeridos
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <archivo_fasta> <directorio>"
    exit 1
fi
archivoFasta=$1
directorio=$2

# Crear el directorio
mkdir -p "$directorio"

# Dividir el archivo FASTA en archivos individuales
awk -v directorio="$directorio" '/^>/ {
archivo = substr($0, 2, 5) substr($0, length($0)-4, 5) ".fasta"
    archivo_salida = directorio "/" archivo
    print > archivo_salida
}; !/^>/ {print >> archivo_salida}' "$archivoFasta"

echo "Se han generado los archivos FASTA en el directorio '$directorio'."
#bastian Gavilan
#luciano Pavel
#Manuel Gatica