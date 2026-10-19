cmake_minimum_required(VERSION 3.26)
project(progetto2 C)

set(CMAKE_C_STANDARD 99)

add_executable(progetto2 main.c
        carteCfu.c
        carteCfu.h
        carteOstacolo.c
        carteOstacolo.h
        giocatori.c
        giocatori.h
)

# Copia i file necessari nella cartella di esecuzione.
foreach(file carte.txt ostacoli.txt personaggi.txt)
    configure_file(${file} ${file} COPYONLY)
endforeach()
