/*------------------------------------------------------ 
Filename: file_operations_YaliLeshem.c
Description: basic actions used for some file operations
Author: Yali Leshem 
 -------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 128
#define FAILURE 1
#define SUCCESS 0

/*------------------------------------------------------
* Function Name - read_file
*
* Function Purpose - read the file content, and prints its letters, words and lines counters
*
* Parameters – char array of the filename
*
* Return value - 0 for SUCCESS, 1 for FAILURE
*
-------------------------------------------------------*/

int read_file (char filename[]) {
    FILE *file_ptr;
    char ch;
    int letters_count = 0, words_count = 0, lines_count = 0;
    int in_word = 0;  // will be used as flag (When switched to 1 - is in word)

    file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) { // if file opening failed
        printf("Error regarding file opening\n");
        return FAILURE;
    } 

    while ((ch = fgetc(file_ptr)) != EOF) {
        printf("%c", ch);

        if (ch == '\n')
            lines_count++; // found a new line

        if (isspace(ch)) {
            in_word = 0; // left the word
        } else {
            letters_count++;
            if (!in_word) { // first letter of a new word
                words_count++;
                in_word = 1;
            }
        }
    }

    printf("Letters count: %d, Words count: %d, Lines count: %d \n", letters_count, words_count, lines_count);
        
    fclose(file_ptr);
    return SUCCESS;
}

/*------------------------------------------------------
* Function Name - copy_file
*
* Function Purpose - copy the contents of the filename source to the filename dest
*
* Parameters – char array source of the filename to be copied, and char array dest of the filename to be copied to
*
* Return value - 0 for SUCCESS, 1 for FAILURE
*
-------------------------------------------------------*/
int copy_file (char source[], char dest[]) {
    FILE *source_file, *dest_file;
    char ch;

    source_file = fopen(source, "r");
    dest_file = fopen(dest, "w");

    if (source_file == NULL || dest_file == NULL) { // if file openings were failing
        printf("Error regarding file opening\n");
        return FAILURE;
    }

    while ((ch = fgetc(source_file)) != EOF)
        fputc(ch, dest_file); // put each character from source file to dest
        
    fclose(source_file);
    fclose(dest_file);
    return SUCCESS;
}

/*------------------------------------------------------
* Function Name - delete_line
*
* Function Purpose - delete a specific line by using a temporary text file
*
* Parameters – char array of the filename, and line number to be deleted
*
* Return value - 0 for SUCCESS, 1 for FAILURE
*
-------------------------------------------------------*/
int delete_line(char filename[], int line_num) {
    FILE *file_ptr, *temp_file_ptr;
    char ch;
    int lines_count = 1;

    file_ptr = fopen(filename, "r");
    temp_file_ptr = fopen("temp.txt", "w");
    if (file_ptr == NULL || temp_file_ptr == NULL) {
        printf("Error regarding file opening\n");
        return FAILURE;
    }

    while ((ch = fgetc(file_ptr)) != EOF) {
        if (lines_count != line_num) // if not in line 'lineNum' - copy to temp file
            fputc(ch, temp_file_ptr);
        if (ch == '\n') // found new line
            lines_count++;
    }

    fclose(file_ptr);
    fclose(temp_file_ptr);

    file_ptr = fopen(filename, "w"); // "w" mode overwrites the file
    if (file_ptr == NULL) {
        printf("Error regarding file opening\n");
        fclose(file_ptr);
        return FAILURE;
    }

    while ((ch = fgetc(file_ptr)) != EOF) {
        fputc(ch, file_ptr);
    }

    return SUCCESS;
}

/*------------------------------------------------------
* Function Name - string_count
*
* Function Purpose - find how many of a string str is found in the file
*
* Parameters – char array of the filename and the string to be looked for
*
* Return value - the number of string appearances in file if succeed, -1 for FAILURE
*
-------------------------------------------------------*/

int string_count(char filename[], char str[]) {
    FILE* file_ptr;
    char ch;
    int index = 0, str_count = 0;

    file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) { // if file opening failed
        printf("Error regarding file opening\n");
        return -1;
    }

    while ((ch = fgetc(file_ptr)) != EOF) {
        if (ch == str[index]) {
            index++; // start of the word
            if (index == strlen(str)) {
                str_count++; // if word 'str' has been found
                index = 0;
            }
        } else {
            index = 0; // not a word, reset counter
        }
    }

    fclose(file_ptr);
    printf("The string %s appears %d times in the file \n", str, str_count);
    return str_count;
}

// main returning 0 for SUCCESS and 1 for FAILURE
int main() {
    char filename[MAX_LEN], filename_copy[MAX_LEN], word[MAX_LEN];
    int num_line;

    printf("Enter file name to read: \n");
    scanf(" %s",filename);
    if (read_file(filename) == FAILURE)
        return FAILURE;

    printf("Enter file name to copy to: \n");
    scanf(" %s",filename_copy);
    if (copy_file(filename, filename_copy) == FAILURE)
        return FAILURE;


    printf("Now enter number of line to be deleted from the file: \n");
    scanf(" %d",&num_line);
    if (delete_line(filename_copy, num_line) == FAILURE)
        return FAILURE;

    printf("Enter a word to be searched for in the file: \n");
    scanf(" %s",word);
    if (string_count(filename_copy, word) == -1)
        return FAILURE;

    return SUCCESS;
}