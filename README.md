# PIC C Template 

[![Build Status](https://travis-ci.org/nahueespinosa/pic_c_template.svg?branch=master)](https://travis-ci.org/nahueespinosa/pic_c_template)

Plantilla para ejercicios con PIC16F887 en lenguaje C.  
Se utiliza el entorno de desarrollo MPLAB X v5.30 y el compilador XC8 v2.20.

## Archivos base del proyecto de MPLAB X IDE

- nbproject/configurations.xml
- nbproject/project.xml
- Makefile
- main.c

## Archivos para integración continua (CI)

- .travis.yml
- travis-install-dependencies.sh

## Archivos adicionales

- circuit.pdsprj:  
    Proyecto de `Proteus Design Suite 8.9` utilizado para simulación.

- mplab_conf.zip:  
    Archivo de opciones exportado del MPLAB X IDE.
    Se puede importar a partir del menú `Tools -> Options -> Import...`.

- .gitignore:  
    Archivo para configurar qué directorios debe ignorar `git`.