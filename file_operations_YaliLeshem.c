/*------------------------------------------------------ 
Filename: file_operations_YaliLeshem.c
Description: basic actions used for some file operations
Author: Yali Leshem 
 -------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 128
#define FAILURE 1
#define SUCCESS 0

/*------------------------------------------------------
* Function Name - read_file
* Function Purpose - read the file content, and prints its letters, words and lines counters
* Parameters – char array of the filename
* Return value - 0 for SUCCESS, 1 for FAILURE
-------------------------------------------------------*/

int read_file (char filename[]) {
    FILE *file_ptr;
    int ch, letters_count = 0, words_count = 0, lines_count = 0, in_word = 0, any_char = 0, last_was_newline = 0; // track last char was newline

    if (!filename)
        return FAILURE;

    file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {  // if file opening failed
        printf("Error regarding file opening\n");
        return FAILURE;
    } 

    while ((ch = fgetc(file_ptr)) != EOF) {
        any_char = 1;
        putchar(ch); // output each character

        if (ch == '\n') {
            lines_count++; // found a new line
            last_was_newline = 1;
        } else {
            last_was_newline = 0;
        }

        if (isspace(ch)) {
            in_word = 0; // left the word
        } else {
            letters_count++;
            if (!in_word) {  // first letter of a new word
                words_count++;
                in_word = 1;
            }
        }
    }

    if (any_char && !last_was_newline) // if file didn't end with newline, count last line as well
        lines_count++;

    printf("Letters count: %d, Words count: %d, Lines count: %d \n", letters_count, words_count, lines_count);
        
    fclose(file_ptr);
    return SUCCESS;
}

/*------------------------------------------------------
* Function Name - copy_file
* Function Purpose - copy the contents of the filename source to the filename dest
* Parameters – char array source of the filename to be copied, and char array dest of the filename to be copied to
* Return value - 0 for SUCCESS, 1 for FAILURE
-------------------------------------------------------*/
int copy_file (char source[], char dest[]) {
    FILE *source_file = NULL, *dest_file = NULL;
    int ch;

    if (!source || !dest) 
        return FAILURE;

    source_file = fopen(source, "r");
    dest_file = fopen(dest, "w");

    if (source_file == NULL || dest_file == NULL) { // if file openings were failing
        if (source_file)
            fclose(source_file);
        if (dest_file)
            fclose(dest_file);
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
* Function Purpose - delete a specific line by using a temporary text file
* Parameters – char array of the filename, and line number to be deleted
* Return value - 0 for SUCCESS, 1 for FAILURE
-------------------------------------------------------*/
int delete_line(char filename[], int line_num) {
    FILE *file_ptr = NULL, *temp_file_ptr = NULL;
    int ch, current_line = 1, total_lines = 0;

    if (!filename)
        return FAILURE;
    if (line_num <= 0) // in case line number is negative
        return FAILURE;

    file_ptr = fopen(filename, "r");
    temp_file_ptr = fopen("temp.txt", "w");
    if (file_ptr == NULL || temp_file_ptr == NULL) {
        if (file_ptr) fclose(file_ptr);
        if (temp_file_ptr) fclose(temp_file_ptr);
        printf("Error regarding file opening\n");
        return FAILURE;
    }

    int prev_ch = 0;
    while ((ch = fgetc(file_ptr)) != EOF) {

        if (current_line == line_num) {  
            if (ch == '\n') // end of deleted line
                current_line++;
            prev_ch = ch;
            continue; // no need to write to temp file
        }

        if (current_line != line_num)  // copy each character as should be kept
            fputc(ch, temp_file_ptr);

        if (ch == '\n') // next line in file
            current_line++;

        prev_ch = ch; // save previous character in variable
    }

    if (prev_ch == 0) // in case file was empty - no lines
        total_lines = 0;
    else 
        total_lines = current_line; // last line

    fclose(file_ptr);
    fclose(temp_file_ptr);

    if (total_lines == 0 || line_num > total_lines) { // in case file was empty or line number too large, remove file and exit
        remove("temp.txt");     
        return FAILURE;
    }

    file_ptr = fopen(filename, "w"); // open original file in write mode
    temp_file_ptr = fopen("temp.txt", "r");

    if (file_ptr == NULL || temp_file_ptr == NULL) { // handle and close files if invalid by removing temp file and exit
        if (file_ptr)
            fclose(file_ptr);

        if (temp_file_ptr)
            fclose(temp_file_ptr);

        remove("temp.txt");
        printf("Error regarding file opening\n");
        return FAILURE;
    }

    while ((ch = fgetc(temp_file_ptr)) != EOF) {
        fputc(ch, file_ptr); // copy back to original file the content char by char
    }

    fclose(file_ptr);
    fclose(temp_file_ptr);
    remove("temp.txt"); // cleanup of the temporary file
    return SUCCESS;
}

/*------------------------------------------------------
* Function Name - string_count
* Function Purpose - find how many of a string str is found in the file
* Parameters – char array of the filename and the string to be looked for
* Return value - the number of string appearances in file if succeed, -1 for FAILURE
-------------------------------------------------------*/

int string_count(const char *filename, const char *str)
{
    if (filename == NULL || str == NULL)
        return -1;
    
    FILE *file_ptr;
    int ch, count = 0, index = 0, len = strlen(str);

    if (len <= 0) // Ensure the word has a valid length
        return -1;

    file_ptr = fopen(filename, "r");
    if (file_ptr == NULL)
        return -1;

    while ((ch = fgetc(file_ptr)) != EOF) {

        if (ch == str[index]) {
            index++;

            // a full word had been found
            if (index == len) {
                count++;
                index = 0; // enable overlap in case exists
            }
        }
        else {
            // if the current char can start a new match
            if (ch == str[0])
                index = 1;
            else
                index = 0;
        }
    }

    fclose(file_ptr);
    return count;
}

// main returning 0 for SUCCESS and 1 for FAILURE
int main() {
    char filename[MAX_LEN], filename_copy[MAX_LEN], word[MAX_LEN];
    int result, num_line;

    printf("Enter file name to read: \n");
    if (scanf(" %127s",filename) != 1)
        return FAILURE;

    result = read_file(filename);
    if (result == FAILURE)
        return FAILURE;

    printf("Enter file name to copy to: \n");
    if (scanf(" %127s",filename_copy) != 1)
        return FAILURE;

    result = copy_file(filename, filename_copy);
    if (result == FAILURE) return FAILURE;

    printf("Now enter number of line to be deleted from the file: \n");
    if (scanf(" %d",&num_line) != 1)
        return FAILURE;

    result = delete_line(filename_copy, num_line);
    if (result == FAILURE)
        return FAILURE;

    printf("Enter a word to be searched for in the file: \n");
    if (scanf(" %127s",word) != 1)
        return FAILURE;

    result = string_count(filename_copy, word);
    if (result == -1)
        return FAILURE;

    printf("The word %s is found %d times in the file %s \n", word, result, filename_copy);

    return SUCCESS;
}
