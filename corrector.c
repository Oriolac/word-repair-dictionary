#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PARAM 4
#define DICTIONARY_MAX_LENGTH 140
#define WORD_MAX_LENGTH 11

void take_dictionary_words(FILE *file_diccionari, char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH]);
void take_word_from_file(FILE *file_diccionari, char word[WORD_MAX_LENGTH]);

void take_word_from_file(FILE *file_diccionari, char word[WORD_MAX_LENGTH])
{
    
}

void take_dictionary_words(FILE *file_diccionari, char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH])
{
    int i;
    char word[WORD_MAX_LENGTH];

    for(i=0; i < DICTIONARY_MAX_LENGTH; i++)
    {
        take_word_from_file(file_diccionari, word);
        strcpy(dictionary[i], word);
    }
}

int main(int argc, char ** argv)
{
    FILE *file_diccionari;
    FILE *file_amb_soroll;
    FILE *file_corregit;
    FILE *file_num_edicions;

    char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH];

    if(argc != NUM_PARAM)
    {
        printf("ERROR. Falten arguments\n");
        exit(-1);
    }

    file_diccionari = fopen(argv[1], "r");
    file_amb_soroll = fopen(argv[2], "r");
    file_corregit = fopen(argv[3], "w");
    file_num_edicions = fopen(argv[4], "w");

    take_dictionary_words(file_diccionari, dictionary);

    exit(0);
}
