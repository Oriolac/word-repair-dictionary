#!/usr/bin/env python3
# -*- coding: utf-8 -*-

""" Corregeix el fitxer i retorna el text corregit i un altre text amb el nombre d'edicions """

import sys


def number_of_editions(wrong_word, corrected_word, visited=0):
	if corrected_word is "" or wrong_word is "":
		return max(len(corrected_word), len(wrong_word)) + visited
	elif wrong_word[0].__eq__(corrected_word[0]):
		return number_of_editions(wrong_word[1:], corrected_word[1:], visited)
	else:
		num1 = number_of_editions(wrong_word[1:], corrected_word, visited + 1)
		num2 = number_of_editions(wrong_word, corrected_word[1:], visited + 1)
		num3 = number_of_editions(wrong_word[1:], corrected_word[1:], visited + 1)
	return min(num1,num2,num3)


def buscar_paraula_correcta(wrong_word, diccionari):
	""" Busca la paraula mes aproximada a wrong_word i retorna aquesta i el nombre d'edicions que s'han hagut de fer """
	min = sys.maxsize
	word = ""
	for corrected_word in diccionari:
		num_differences = number_of_editions(wrong_word, corrected_word)
		if num_differences < min:
			min = num_differences
			word = corrected_word
	return word


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
			corrected_word = buscar_paraula_correcta(word, diccionari)

	file_diccionari.close()
	file_amb_soroll.close()
	file_corregit.close()
	file_num_edicions.close()


if __name__ == "__main__":
	main()
