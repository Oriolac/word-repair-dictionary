#!/usr/bin/env python3
# -*- coding: utf-8 -*-

""" Corregeix el fitxer i retorna el text corregit i un altre text amb el nombre d'edicions """

import sys

def number_of_editions(wrong_word, corrected_word, index):
    if len(wrong_word) == index:
        return corrected_word
    return 0

def buscar_paraula_correcta(wrong_word, diccionari):
    """ Busca la paraula mes aproximada a wrong_word i retorna aquesta i el nombre d'edicions que s'han hagut de fer """
    for corrected_word in diccionari:
        print(wrong_word, corrected_word, number_of_editions(wrong_word, corrected_word, 0))

def main():
    """ Corregeix el fitxer i retorna el text corregit i un altre text amb el nombre d'edicions """

    file_diccionari = open(sys.argv[1], 'r')
    file_amb_soroll = open(sys.argv[2], 'r')
    diccionari = file_diccionari.readline().split(' ')
    file_corregit = open(sys.argv[3], 'w')
    file_num_edicions = open(sys.argv[4], 'w')

    line = file_amb_soroll.readline().split(' ')[:-1]
    for word in line:
        if word not in diccionari:
            buscar_paraula_correcta(word, diccionari)
    
    file_diccionari.close()
    file_amb_soroll.close()
    file_corregit.close()
    file_num_edicions.close()

if __name__ == "__main__":
    main()
