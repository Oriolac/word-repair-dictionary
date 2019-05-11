#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define NUM_PARAM 5
#define DICTIONARY_MAX_LENGTH 140
#define WORD_MAX_LENGTH 11

int look_if_debug_mode(int argc, char ** argv);
void take_dictionary_words(FILE *file_diccionari, char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH]);
void take_word_from_file(FILE *file_diccionari, char word[WORD_MAX_LENGTH]);
void print_if_debug(int debug, const char *fmt, ...);
void print_string(const char *fmt, va_list args);

int debug_c;

void print_if_debug(int debug, const char *fmt, ...)
{
	va_list	args;

	if(debug)
	{
	    printf("DEBUG => ");
	    va_start(args,fmt);
		print_string(fmt, args);
	}
}


void print_string(const char *fmt, va_list args)
{
	char *string;
	int i;
	while( *fmt != '\0')
	{
		if(*fmt == '%' && *(fmt+1) == 's')
		{
			++fmt;
			string = va_arg(args,char*);
			printf("%s", string);
		} else if(*fmt == '%' && *(fmt+1)== 'i')
		{
			++fmt;
			i = va_arg(args,int);
			printf("%i", i);
		} else {
			printf("%c", *fmt);
		}
		++fmt;
	}
	printf("\n");
}


void take_word_from_file(FILE *file_diccionari, char word[WORD_MAX_LENGTH])
{
    char actual_c;
    int i;
    actual_c = fgetc(file_diccionari);
    i = 0;
    while(actual_c != EOF && actual_c != ' ' && actual_c != '\n')
    {
        word[i] = actual_c;
        actual_c = fgetc(file_diccionari);
        i++;
    }
}

void take_dictionary_words(FILE *file_diccionari, char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH])
{
    int i;
    char word[WORD_MAX_LENGTH];

    for(i=0; i < DICTIONARY_MAX_LENGTH; i++)
    {
        take_word_from_file(file_diccionari, word);
        print_if_debug(debug_c, "S'agafa la paraula num. %i => %s", i, word);
        strcpy(dictionary[i], word);
    }
}

int look_if_debug_mode(int argc, char ** argv)
{
    int i;
    for(i = 0; i < argc; i++)
    {
        if (strcmp("-d", argv[i]) == 0)
        {
            print_if_debug(1, "MODE DEBUG ON.");
            return 1;
        }
    }
    return 0;
}


int main(int argc, char ** argv)
{
    FILE *file_diccionari;
    FILE *file_amb_soroll;
    FILE *file_corregit;
    FILE *file_num_edicions;

    char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH];

    if(argc < NUM_PARAM)
    {
        printf("ERROR. Falten arguments\n");
        exit(-1);
    }

    debug_c = look_if_debug_mode(argc, argv);

    file_diccionari = fopen(argv[1], "r");
    file_amb_soroll = fopen(argv[2], "r");
    file_corregit = fopen(argv[3], "w");
    file_num_edicions = fopen(argv[4], "w");

    print_if_debug(debug_c, "S'agafen les paraules del fitxer.");
    take_dictionary_words(file_diccionari, dictionary);

    exit(0);
}
