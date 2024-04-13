#include "parser.h"

/***
 * Checks whether the inputs contain a subshell to
 * prevent subshells being chained with a seq or para separator
 * @param input
 * @return bool
 */
int check_subshell(parsed_input* input) {
    for ( int i=0; i<input->num_inputs; i++ ) {
        if ( input->inputs[i].type == INPUT_TYPE_SUBSHELL )
            return 1;
    }
    return 0;
}
/***
 * Converts the inputs into a single pipeline to chain them with seq or para separators
 * For example: A | B ; C -> This will first create two single inputs separated with a pipe
 * Then, upon encountering a ";" symbol, It needs to convert the first two inputs into a pipeline and turn
 * the separator into a sequential separator
 * @param input
 */
void convert_to_pipeline(parsed_input* input) {
    pipeline pipeline1;
    memset(&pipeline1, 0, sizeof(pipeline));

    pipeline1.num_commands = input->num_inputs;
    for ( int i=0; i<input->num_inputs; i++ )
        memcpy(pipeline1.commands[i].args, input->inputs[i].data.cmd.args, MAX_INPUTS*sizeof(char*));

    input->num_inputs = 1;
    input->inputs[0].type = INPUT_TYPE_PIPELINE;
    memcpy(&(input->inputs[0].data.pline), &pipeline1, sizeof(pipeline));
}

/***
 * Converts a single command to pipeline after encountering pipe symbol in a sequential or parallel execution
 * @param input
 */
void convert_command_to_pipeline(parsed_input* input) {
    int input_index = input->num_inputs-1;
    pipeline pipeline1;
    memset(&pipeline1, 0, sizeof(pipeline));
    pipeline1.num_commands = 1;
    memcpy(pipeline1.commands[0].args, input->inputs[input_index].data.cmd.args, MAX_INPUTS*sizeof(char*));

    input->inputs[input_index].type = INPUT_TYPE_PIPELINE;
    memcpy(&(input->inputs[input_index].data.pline), &pipeline1, sizeof(pipeline));
}

/***
 * Fills the current input's command or argument with the current buffer
 * @param input
 * @param buffer
 * @param is_command
 */
void write_buffer(parsed_input* input, char *buffer, int is_command, int is_pipeline) {
    int input_index;
    int arg_index;
    int current_command;
    if ( is_command ) {
        input_index = input->num_inputs-is_pipeline;
        arg_index = 0;

        if ( input->inputs[input_index].type == INPUT_TYPE_PIPELINE )
            current_command = input->inputs[input_index].data.pline.num_commands;
    }
    else {
        input_index = input->num_inputs-1;
        if ( input->inputs[input_index].type == INPUT_TYPE_PIPELINE ) {
            current_command = input->inputs[input_index].data.pline.num_commands-1;
            arg_index = 1;
            for ( ; input->inputs[input_index].data.pline.commands[current_command].args[arg_index]; arg_index++);
        }
        else {
            arg_index = 1;
            for ( ; input->inputs[input_index].data.cmd.args[arg_index]; arg_index++);
        }
    }
    if ( input->inputs[input_index].type == INPUT_TYPE_PIPELINE ) {
        input->inputs[input_index].data.pline.commands[current_command].args[arg_index] =
                (char *)calloc(strlen(buffer), sizeof(char));
        strcpy(input->inputs[input_index].data.pline.commands[current_command].args[arg_index],
               buffer);
        input->inputs[input_index].data.pline.commands[current_command].args[arg_index+1] = NULL;
        if ( is_command )
            input->inputs[input_index].data.pline.num_commands++;
    }
    else {
        input->inputs[input_index].type = INPUT_TYPE_COMMAND;
        input->inputs[input_index].data.cmd.args[arg_index] = (char *)calloc(strlen(buffer), sizeof(char));
        strcpy(input->inputs[input_index].data.cmd.args[arg_index], buffer);
        input->inputs[input_index].data.cmd.args[arg_index+1] = NULL;
        if ( is_command )
            input->num_inputs++;
    }
}

int parse_line(char *line, parsed_input *input) {
    char *current_char;
    int buffer_index = 0;
    char buffer[INPUT_BUFFER_SIZE];
    // Initialize parsed_input
    memset(input, 0, sizeof(parsed_input));
    input->separator = SEPARATOR_NONE;
    current_char = line;

    int is_quote = 0;
    char quote_char = 0;

    int is_subshell = 0;

    int is_free = 1;
    int is_waiting_command = 1;
    int is_waiting_arg = 0;
    int is_waiting_sep = 0;

    int is_reading_command = 0;
    int is_reading_arg = 0;

    int is_pipeline = 0;
    while ( *current_char ) {
        if ( is_quote ) {
            if ( *current_char == quote_char ) {
                buffer[buffer_index] = '\0';
                buffer_index = 0;
                is_quote = 0;
                quote_char = 0;
                write_buffer(input, buffer, is_reading_command, is_pipeline);
                is_reading_command = 0;
                is_reading_arg = 0;
                is_waiting_arg = 1;
                is_free = 1;
            }
            else {
                buffer[buffer_index++] = *current_char;
            }
        }
        else if ( is_subshell ) {
            if ( *current_char == ')' ) {
                buffer[buffer_index] = '\0';
                if (input->separator == SEPARATOR_PARA || input->separator == SEPARATOR_SEQ ) {
                    fprintf(stderr, "Subshells cannot be chained with a sequential or parallel operation.\n");
                    return 0;
                }
                int input_index = input->num_inputs;
                input->inputs[input_index].type = INPUT_TYPE_SUBSHELL;
                strcpy(input->inputs[input_index].data.subshell, buffer);
                input->num_inputs++;
                buffer_index = 0;
                is_subshell = 0;
                is_free = 1;
                is_waiting_sep = 1;
            }
            else {
                buffer[buffer_index++] = *current_char;
            }
        }
        else if ( is_free ) {
            if (isspace(*current_char)) {
                current_char++;
                continue;
            }
            if ( is_waiting_command ) {
                if ( *current_char == '"' || *current_char == '\'') {
                    is_free = 0;
                    is_quote = 1;
                    quote_char = *current_char;
                    is_waiting_command = 0;
                    is_reading_command = 1;
                }
                else if ( *current_char == '(' ) {
                    is_free = 0;
                    is_subshell = 1;
                    is_waiting_command = 0;
                }
                else if ( *current_char == ';' ) {
                    fprintf(stderr, "There should be a command or a pipeline before semicolon.\n");
                    return 0;
                }
                else if ( *current_char == ',' ) {
                    fprintf(stderr, "There should be a command or a pipeline before comma.\n");
                    return 0;
                }
                else if ( *current_char == '|' ) {
                    fprintf(stderr, "There should be a command or a subshell before pipe.\n");
                    return 0;
                }
                else {
                    is_free = 0;
                    is_waiting_command = 0;
                    is_reading_command = 1;
                    buffer[buffer_index++] = *current_char;
                }
            }
            else if ( is_waiting_arg ) {
                if ( *current_char == '"' || *current_char == '\'') {
                    is_free = 0;
                    is_quote = 1;
                    quote_char = *current_char;
                    is_waiting_arg = 0;
                    is_reading_arg = 1;
                }
                else if ( *current_char == '(' ) {
                    fprintf(stderr, "There cannot be a subshell after a command. There should be a separator.\n");
                    return 0;
                }
                else if ( *current_char == ';' ) {
                    if ( input->separator == SEPARATOR_PARA ) {
                        fprintf(stderr, "There cannot be a sequential separator after parallel.\n");
                        return 0;
                    }
                    if (input->separator == SEPARATOR_PIPE) {
                        if (check_subshell(input)) {
                            fprintf(stderr, "There cannot be a sequential separator after a subshell.\n");
                            return 0;
                        }
                        convert_to_pipeline(input);
                    }
                    input->separator = SEPARATOR_SEQ;
                    is_waiting_arg = 0;
                    is_waiting_command = 1;

                    is_pipeline = 0;
                }
                else if ( *current_char == ',' ) {
                    if ( input->separator == SEPARATOR_SEQ ) {
                        fprintf(stderr, "There cannot be a parallel separator after sequential.\n");
                        return 0;
                    }
                    if (input->separator == SEPARATOR_PIPE) {
                        if (check_subshell(input)) {
                            fprintf(stderr, "There cannot be a parallel separator after a subshell.\n");
                            return 0;
                        }
                        convert_to_pipeline(input);
                    }
                    input->separator = SEPARATOR_PARA;
                    is_waiting_arg = 0;
                    is_waiting_command = 1;

                    is_pipeline = 0;
                }
                else if ( *current_char == '|' ) {
                    if (input->separator == SEPARATOR_PIPE) {
                        is_free = 1;
                        is_waiting_command = 1;
                        is_waiting_arg = 0;
                    }
                    else if ( input->separator == SEPARATOR_PARA || input->separator == SEPARATOR_SEQ ) {
                        int input_index = input->num_inputs-1;
                        if ( input->inputs[input_index].type == INPUT_TYPE_COMMAND ) {
                            convert_command_to_pipeline(input);
                        }
                        is_free = 1;
                        is_waiting_command = 1;
                        is_waiting_arg = 0;

                        is_pipeline = 1;
                    }
                    else {
                        input->separator = SEPARATOR_PIPE;
                        is_free = 1;
                        is_waiting_command = 1;
                        is_waiting_arg = 0;
                    }
                }
                else {
                    is_free = 0;
                    is_waiting_arg = 0;
                    is_reading_arg = 1;
                    buffer[buffer_index++] = *current_char;
                }
            }
            else if ( is_waiting_sep ) {
                if (isspace(*current_char)) {
                    current_char++;
                    continue;
                }

                if ( *current_char == ';' ) {
                    fprintf(stderr, "Subshells cannot be chained with a sequential operation.\n");
                    return 0;
                }
                else if ( *current_char == ',' ) {
                    fprintf(stderr, "Subshells cannot be chained with a parallel operation.\n");
                    return 0;
                }
                else if ( *current_char == '|' ) {
                    input->separator = SEPARATOR_PIPE;
                    is_waiting_sep = 0;
                    is_waiting_command = 1;
                }
                else {
                    fprintf(stderr, "Subshells should be followed by | or nothing.\n");
                    return 0;
                }
            }
        }
        else if ( is_reading_command ) {
            if (isspace(*current_char)) {
                buffer[buffer_index] = '\0';
                write_buffer(input, buffer, 1, is_pipeline);
                buffer_index = 0;
                is_reading_command = 0;
                is_waiting_arg = 1;
                is_free = 1;
            }
            else if ( *current_char == ';' ) {
                if ( input->separator == SEPARATOR_PARA ) {
                    fprintf(stderr, "There cannot be a sequential separator after parallel.\n");
                    return 0;
                }
                if (input->separator == SEPARATOR_PIPE) {
                    if (check_subshell(input)) {
                        fprintf(stderr, "There cannot be a sequential separator after a subshell.\n");
                        return 0;
                    }
                    convert_to_pipeline(input);

                    is_pipeline = 1;
                }
                buffer[buffer_index] = '\0';
                write_buffer(input, buffer, 1, is_pipeline);
                buffer_index = 0;
                input->separator = SEPARATOR_SEQ;
                is_reading_command = 0;
                is_waiting_command = 1;
                is_free = 1;

                is_pipeline = 0;
            }
            else if ( *current_char == ',' ) {
                if ( input->separator == SEPARATOR_SEQ ) {
                    fprintf(stderr, "There cannot be a parallel separator after sequential.\n");
                    return 0;
                }
                if (input->separator == SEPARATOR_PIPE) {
                    if (check_subshell(input)) {
                        fprintf(stderr, "There cannot be a parallel separator after a subshell.\n");
                        return 0;
                    }
                    convert_to_pipeline(input);

                    is_pipeline = 1;
                }
                buffer[buffer_index] = '\0';
                write_buffer(input, buffer, 1, is_pipeline);
                buffer_index = 0;
                input->separator = SEPARATOR_PARA;
                is_reading_command = 0;
                is_waiting_command = 1;
                is_free = 1;

                is_pipeline = 0;
            }
            else if ( *current_char == '|' ) {
                if (input->separator == SEPARATOR_PIPE) {
                    buffer[buffer_index] = '\0';
                    write_buffer(input, buffer, 1, is_pipeline);
                    buffer_index = 0;
                    is_reading_command = 0;
                    is_waiting_command = 1;
                    is_free = 1;
                }
                else if ( input->separator == SEPARATOR_PARA || input->separator == SEPARATOR_SEQ ) {
                    buffer[buffer_index] = '\0';
                    write_buffer(input, buffer, 1, is_pipeline);
                    buffer_index = 0;
                    int input_index = input->num_inputs-1;
                    if ( input->inputs[input_index].type == INPUT_TYPE_COMMAND ) {
                        convert_command_to_pipeline(input);
                    }

                    is_reading_command = 0;
                    is_waiting_command = 1;
                    is_free = 1;

                    is_pipeline = 1;
                }
                else {
                    buffer[buffer_index] = '\0';
                    write_buffer(input, buffer, 1, is_pipeline);
                    buffer_index = 0;
                    input->separator = SEPARATOR_PIPE;
                    is_reading_command = 0;
                    is_waiting_command = 1;
                    is_free = 1;
                }
            }
            else {
                buffer[buffer_index++] = *current_char;
            }
        }
        else if ( is_reading_arg ) {
            if (isspace(*current_char)) {
                buffer[buffer_index] = '\0';
                write_buffer(input, buffer, 0, is_pipeline);
                buffer_index = 0;
                is_reading_arg = 0;
                is_waiting_arg = 1;
                is_free = 1;
            }
            else if ( *current_char == ';' ) {
                if ( input->separator == SEPARATOR_PARA ) {
                    fprintf(stderr, "There cannot be a sequential separator after parallel.\n");
                    return 0;
                }
                if (input->separator == SEPARATOR_PIPE) {
                    if (check_subshell(input)) {
                        fprintf(stderr, "There cannot be a sequential separator after a subshell.\n");
                        return 0;
                    }
                    convert_to_pipeline(input);

                    is_pipeline = 1;
                }
                buffer[buffer_index] = '\0';
                write_buffer(input, buffer, 0, is_pipeline);
                buffer_index = 0;
                input->separator = SEPARATOR_SEQ;
                is_reading_arg = 0;
                is_waiting_command = 1;
                is_free = 1;

                is_pipeline = 0;
            }
            else if ( *current_char == ',' ) {
                if ( input->separator == SEPARATOR_SEQ ) {
                    fprintf(stderr, "There cannot be a parallel separator after sequential.\n");
                    return 0;
                }
                if (input->separator == SEPARATOR_PIPE) {
                    if (check_subshell(input)) {
                        fprintf(stderr, "There cannot be a parallel separator after a subshell.\n");
                        return 0;
                    }
                    convert_to_pipeline(input);

                    is_pipeline = 1;
                }
                buffer[buffer_index] = '\0';
                write_buffer(input, buffer, 0, is_pipeline);
                buffer_index = 0;
                input->separator = SEPARATOR_PARA;
                is_reading_arg = 0;
                is_waiting_command = 1;
                is_free = 1;

                is_pipeline = 0;
            }
            else if ( *current_char == '|' ) {
                if (input->separator == SEPARATOR_PIPE) {
                    buffer[buffer_index] = '\0';
                    write_buffer(input, buffer, 0, is_pipeline);
                    buffer_index = 0;
                    is_reading_command = 0;
                    is_waiting_command = 1;
                    is_free = 1;
                }
                else if ( input->separator == SEPARATOR_PARA || input->separator == SEPARATOR_SEQ ) {
                    buffer[buffer_index] = '\0';
                    write_buffer(input, buffer, 0, is_pipeline);
                    buffer_index = 0;
                    int input_index = input->num_inputs-1;
                    if ( input->inputs[input_index].type == INPUT_TYPE_COMMAND ) {
                        convert_command_to_pipeline(input);
                    }

                    is_reading_arg = 0;
                    is_waiting_command = 1;
                    is_free = 1;

                    is_pipeline = 1;
                }
                else {
                    buffer[buffer_index] = '\0';
                    write_buffer(input, buffer, 1, is_pipeline);
                    buffer_index = 0;
                    input->separator = SEPARATOR_PIPE;
                    is_reading_arg = 0;
                    is_waiting_command = 1;
                    is_free = 1;
                }
            }
            else {
                buffer[buffer_index++] = *current_char;
            }
        }
        current_char++;
    }
    if ( is_reading_command ) {
        buffer[buffer_index] = '\0';
        write_buffer(input, buffer, 1, is_pipeline);
    }
    else if ( is_reading_arg ) {
        buffer[buffer_index] = '\0';
        write_buffer(input, buffer, 0, is_pipeline);
    }

    return !is_waiting_command;
}

void free_command(command *cmd) {
    if (cmd == NULL) return;
    // Free each argument in the command
    for (int i = 0; i < MAX_ARGS && cmd->args[i] != NULL; i++) {
        free(cmd->args[i]); // Free each argument string
    }
    // No need to free cmd itself since it's part of an array or union
}

void free_pipeline(pipeline *pline) {
    if (pline == NULL) return;
    // Free each command in the pipeline
    for (int i = 0; i < pline->num_commands; i++) {
        free_command(&pline->commands[i]); // Free each command structure
    }
    // No need to free pline itself since it's part of an array or union
}

void free_single_input(single_input *input) {
    if (input == NULL) return;
    switch (input->type) {
        case INPUT_TYPE_SUBSHELL:
            // Since subshell uses a fixed-size char array, there's no dynamic memory to free
            break;
        case INPUT_TYPE_COMMAND:
            free_command(&input->data.cmd); // Free the command structure
            break;
        case INPUT_TYPE_PIPELINE:
            free_pipeline(&input->data.pline); // Free the pipeline structure
            break;
        default: // No action needed for unknown types
            break;
    }
}

void free_parsed_input(parsed_input *input) {
    if (input == NULL) return;
    // Free each single_input in the inputs array
    for (int i = 0; i < input->num_inputs; i++) {
        free_single_input(&input->inputs[i]);
    }
    // Since inputs is a fixed-size array within the structure, no need to free it separately
}

void pretty_print(parsed_input *input) {
    for (int i = 0; i < input->num_inputs; i++) {
        single_input *inp = &input->inputs[i];
        printf("Input %d: ", i + 1);
        switch (inp->type) {
            case INPUT_TYPE_SUBSHELL:
                printf("Subshell: %s\n", inp->data.subshell);
                break;
            case INPUT_TYPE_COMMAND:
                printf("Command: ");
                for (char **arg = inp->data.cmd.args; *arg != NULL; arg++) {
                    printf("%s ", *arg);
                }
                printf("\n");
                break;
            case INPUT_TYPE_PIPELINE:
                printf("Pipeline with %d commands:\n", inp->data.pline.num_commands);
                for (int j = 0; j < inp->data.pline.num_commands; j++) {
                    printf("  Command %d: ", j + 1);
                    command *cmd = &inp->data.pline.commands[j];
                    for (char **arg = cmd->args; *arg != NULL; arg++) {
                        printf("%s ", *arg);
                    }
                    printf("\n");
                }
                break;
        }
        if (i < input->num_inputs - 1) {
            switch (input->separator) {
                case SEPARATOR_PIPE: printf("Followed by: SEPARATOR_PIPE\n"); break;
                case SEPARATOR_SEQ: printf("Followed by: SEPARATOR_SEQ\n"); break;
                case SEPARATOR_PARA: printf("Followed by: SEPARATOR_PARA\n"); break;
                default: break; // Should not happen
            }
        }
    }
}

