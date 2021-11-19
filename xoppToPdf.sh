#!/bin/bash

# Argumentos:
# 1. basePath: carpeta desde donde se realiza la conversion. Default=$PWD
#       
# Funcion:
# Agarra todos los archivos de tipo .xopp que haya dentro de la carpeta seleccionada (se fija de forma recursiva)
# y los convierte a PDF. El nombre del nuevo archivo será igual al original pero con la extensión cambiada a PDF.
#
# IMPORTANTE:
# Este script NO va a convertir archivos si ya tiene un PDF asociado, es decir, si vos tenés tito.xopp y tito.pdf
# en la misma carpeta, el script no va a volver a realizar la conversión, si querés que se haga primero borrá el 
# archivo pdf.

function convertFile(){
    local file=${1}
    local fileAsPdf=${2}
    echo "[INFO] Convirtiendo ${file} a ${fileAsPdf}"
    xournalpp -p ${fileAsPdf} ${file}
}

function recursiveXoppToPdf(){
    for file in "$1"/*
    do
        if [ ! -d "${file}" ]; then #Si es un archivo
            if [[ $file == *.xopp ]]; then #Si la extension es xopp la quiero pasar a pdf
                local fileAsPdf="${file%.xopp}.pdf"
                if [[ ! -f ${fileAsPdf} ]]; then #Solo convierto el archivo si su PDF no fue creado todavia
                    convertFile ${file} ${fileAsPdf}
                fi
            fi
        else #Si no es un archivo entonces es un directorio y entro a cada carpeta recursivamente
            echo "[INFO] Entrando a carpeta ${file}"
            recursiveXoppToPdf "${file}"
        fi
    done
}

function main(){
    basePath=${1}
    recursiveXoppToPdf ${basePath}
}

basePath=${1}

if [ -z "$1" ]; then # Si no pasaste ningun parametro se corre el codigo desde el directorio actual
    basePath=${PWD} 
fi

main ${basePath}
