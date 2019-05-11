#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys

def main():
    DICCIONARI = open(sys.argv[1], 'r')
    TEXT_AMB_SORROLL = open(sys.argv[2], 'r')
    DICCIONARI = DICCIONARI.readline().split(' ')
    TEXT_CORREGIT = open(sys.argv[3], 'w')
    TEXT_NUM_EDICONS = open(sys.argv[4], 'w')
    

    print(DICCIONARI)

if __name__ == "__main__":
    main()