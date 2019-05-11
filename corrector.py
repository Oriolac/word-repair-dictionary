#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys

def main():
    DICCIONARI = open(sys.argv[1])
    DICCIONARI = DICCIONARI.readline().split(' ')
    
    print(DICCIONARI)

if __name__ == "__main__":
    main()