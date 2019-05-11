#!/usr/bin/env python3
# -*- coding: utf-8 -*-

""" Corregeix el fitxer i retorna el text corregit i un altre text amb el nombre d'edicions """

import sys

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
            print(word)
    
    file_diccionari.close()
    file_amb_soroll.close()
    file_corregit.close()
    file_num_edicions.close()

if __name__ == "__main__":
    main()
