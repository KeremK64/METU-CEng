#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define INPUT_BUFFER_SIZE 256
#define MAX_ARGS 20
#define MAX_INPUTS 10

typedef enum {
    INPUT_TYPE_NON, INPUT_TYPE_SUBSHELL, INPUT_TYPE_COMMAND, INPUT_TYPE_PIPELINE
} SINGLE_INPUT_TYPE;
typedef enum {
    SEPARATOR_NONE, SEPARATOR_PIPE, SEPARATOR_SEQ, SEPARATOR_PARA
} SEPARATOR;

typedef struct {
    char *args[MAX_ARGS]; // Null-terminated arguments
} command;

typedef struct {
    command commands[MAX_INPUTS]; // Array of commands
    int num_commands;
} pipeline;

typedef union {
    char subshell[INPUT_BUFFER_SIZE]; // Entire subshell string
    command cmd;                      // Single command
    pipeline pline;                   // Pipeline of commands
} single_input_union;

typedef struct {
    SINGLE_INPUT_TYPE type; // Type of the inputs
    single_input_union data; // Actual input which is union.
} single_input;

typedef struct {
    single_input inputs[MAX_INPUTS]; // Array of inputs
    SEPARATOR separator; // Separators for the input
    int num_inputs; // Number of inputs
} parsed_input;

/***
 * Parses one input line and fills the parsed_input struct given as a pointer.
 * It can handle any number of spaces between arguments and separators.
 * It has support for single or double-quoted commands and arguments.
 * It returns 1 if it is a valid input and 0 otherwise.
 * @param line
 * @param input
 * @return
 */
int parse_line(char *line, parsed_input *input);

/***
 * Frees the allocated characters inside the inputs to prevent memory leaks.
 * It is recommended that you use this function after executing the commands inside the parsed_input struct.
 * @param input
 */
void free_parsed_input(parsed_input *input);

/***
 * Prints the contents of the parsed_input struct nicely for checking.
 * You should look at how different inputs are stored to understand how parse_line works.
 * Please do not forget to delete this before submission to prevent unnecessary output from being printed.
 * @param input
 */
void pretty_print(parsed_input *input);
#ifdef __cplusplus
}
#endif
#endif //PARSER_H


