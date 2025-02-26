#!/usr/bin/env python3
# -*- coding: utf-8 -*-

""" Corregeix el fitxer i retorna el text corregit i un altre text amb el nombre d'edicions """

import sys


def number_of_editions(wrong_word, corrected_word, num_editions=0, min_editions=sys.maxsize):
	if corrected_word is "" or wrong_word is "":
		return max(len(corrected_word), len(wrong_word)) + num_editions
	elif wrong_word[0].__eq__(corrected_word[0]):
		return number_of_editions(wrong_word[1:], corrected_word[1:], num_editions, min_editions)
	elif num_editions < min_editions:
		num1 = number_of_editions(wrong_word[1:], corrected_word, num_editions + 1, min_editions)
		num2 = number_of_editions(wrong_word, corrected_word[1:], num_editions + 1, min_editions)
		num3 = number_of_editions(wrong_word[1:], corrected_word[1:], num_editions + 1, min_editions)
		return min(num1, num2, num3)
	else:
		return min_editions


def buscar_paraula_correcta(wrong_word, diccionari):
	""" Busca la paraula mes aproximada a wrong_word i retorna aquesta i el nombre d'edicions que s'han hagut de fer """
	min_differences = sys.maxsize
	word = ""
	for corrected_word in diccionari:
		num_differences = number_of_editions(wrong_word, corrected_word, min_editions=min_differences)
		if num_differences < min_differences:
			min_differences = num_differences
			word = corrected_word
	return word, min_differences


def main():
	""" Corregeix el fitxer i retorna el text corregit i un altre text amb el nombre d'edicions """

	file_diccionari = open(sys.argv[1], 'r')
	file_amb_soroll = open(sys.argv[2], 'r')
	diccionari = file_diccionari.readline().split(' ')
	file_corregit = open(sys.argv[3], 'w')
	file_num_edicions = open(sys.argv[4], 'w')

	line = file_amb_soroll.readline().split(' ')[:-1]

	total_num_differences = 0
	text = []

	for word in line:
		if word not in diccionari:
			corrected_word, num_differences = buscar_paraula_correcta(word, diccionari)
			total_num_differences += num_differences
			text.append(corrected_word)
		else:
			text.append(word)

	for index in list(range(len(text))):
		if index == len(text)-1:
			print(text[index], end='', file=file_corregit)
		else:
			print(text[index], end=' ', file=file_corregit)
	print('\n', end='', file=file_corregit)

	print(total_num_differences, file=file_num_edicions)
	file_diccionari.close()
	file_amb_soroll.close()
	file_corregit.close()
	file_num_edicions.close()


if __name__ == "__main__":
	main()
