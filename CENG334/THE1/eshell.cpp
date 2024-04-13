#include "parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void singleCommandSubshell(char*);


void pipeExecution(parsed_input* parsed) {

    int numOfCommands = parsed->num_inputs;
    int fileDescriptors[numOfCommands][2]; // File descriptor array for pipes
    pid_t pid;

    // Create all necessary pipes
    for (int i = 0; i < numOfCommands - 1; i++) { // create all necessary pipes
        if (pipe(fileDescriptors[i]) < 0) {
            perror("pipe error");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < numOfCommands; i++) {
        pid = fork();
        if (pid == -1) { 
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process

            if (i > 0) {
                dup2(fileDescriptors[i - 1][0], STDIN_FILENO);
            }
            if (i < numOfCommands - 1) {
                dup2(fileDescriptors[i][1], STDOUT_FILENO);
            }

            for (int fd = 3; fd < getdtablesize(); fd++) { // Start from 3 (STDERR_FILENO)
                if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO && fd != fileDescriptors[i][0] && fd != fileDescriptors[i][1]) {
                    close(fd);
                }
            }

            if(parsed->inputs[i].type == INPUT_TYPE_SUBSHELL){
                singleCommandSubshell(parsed->inputs[i].data.subshell);
                exit(EXIT_SUCCESS);
            }
            else{
                execvp(parsed->inputs[i].data.cmd.args[0], parsed->inputs[i].data.cmd.args);
                perror("execvp"); 
                exit(EXIT_FAILURE);
            }
        
        } 
        else { // Parent process
            
            if (i > 0) {
                close(fileDescriptors[i - 1][0]);
            }
            if (i < numOfCommands - 1) {
                close(fileDescriptors[i][1]);
            }
        }
    }

    for (int i = 0; i < numOfCommands; i++) {
        wait(NULL);
    }
}



void nestedPipeExecution(pipeline* parsed){
    int numOfCommands = parsed->num_commands;
    int fileDescriptors[numOfCommands][2]; //file descriptor array of all processes
    pid_t pid;

    //cout << "pipe" << "\n";
    for(int i = 0; i < numOfCommands - 1; i++){ // all necessary pipes are created
        if(pipe(fileDescriptors[i]) < 0){
            perror("pipe error");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < numOfCommands; i++){
        pid = fork();
        if(pid == -1){ //Error checking
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0){ // Child
            if(i > 0){ //Except first
                dup2(fileDescriptors[i-1][0], STDIN_FILENO);
                close(fileDescriptors[i - 1][0]);
                close(fileDescriptors[i - 1][1]);
                //close(STDERR_FILENO);
            }

            if(i < numOfCommands){ //Except last
                dup2(fileDescriptors[i][1], STDOUT_FILENO);
                close(fileDescriptors[i][0]);
                close(fileDescriptors[i][1]);
                //close(STDERR_FILENO);
            }

            execvp(parsed->commands[i].args[0],parsed->commands[i].args);

        }
        else{ //Parent
            if(i > 0){
                close(fileDescriptors[i-1][0]);
            }

            if(i < numOfCommands - 1){
                close(fileDescriptors[i][1]);
            }
        }

    }
    for(int i = 0; i < numOfCommands; i++){
        wait(NULL);
    }
}

void sequentialExecution(parsed_input* parsed){
    int numOfCommands = parsed->num_inputs;
    pid_t pid;
    std::cout << "";
    for(int i = 0; i < numOfCommands; i++){
        if(parsed->inputs[i].type == INPUT_TYPE_COMMAND){
            pid = fork();
            if(pid < 0){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if(pid == 0){ //Child
                execvp(parsed->inputs[i].data.cmd.args[0],parsed->inputs[i].data.cmd.args);
            }
            else{ //Parent
                wait(NULL);
            }
        }
        
        if(parsed->inputs[i].type == INPUT_TYPE_PIPELINE){
            nestedPipeExecution(&parsed->inputs[i].data.pline);
        }
    }
}

void parallelExecution(parsed_input* parsed){
    int numOfCommands = parsed->num_inputs;
        pid_t pid;
        std::cout << "";
        for(int i = 0; i < numOfCommands; i++){
            if(parsed->inputs[i].type == INPUT_TYPE_COMMAND){
                pid = fork();
                if(pid < 0){
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                else if(pid == 0){ //Child
                    execvp(parsed->inputs[i].data.cmd.args[0],parsed->inputs[i].data.cmd.args);
                }
                else{ //Parent
                    
                }
            }
            
            if(parsed->inputs[i].type == INPUT_TYPE_PIPELINE){
                nestedPipeExecution(&parsed->inputs[i].data.pline);
            }
        }
        for(int i = 0; i < numOfCommands; i++){
            wait(NULL);
        }
}

void singleCommandSubshell(char* parsed){
    parsed_input* parsedSub = new parsed_input;
    parse_line(parsed, parsedSub);
    //std::cout << "";
    //std::cout.flush();
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        if(parsedSub->num_inputs == 1 && parsedSub->inputs[0].type == INPUT_TYPE_COMMAND){
            pid_t pid1 = fork();
            if(pid1 < 0){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if(pid1 > 0){ //Parent 
                wait(NULL);
            }
            else{ //Child
                execvp(parsedSub->inputs[0].data.cmd.args[0],parsedSub->inputs[0].data.cmd.args);
            }
            exit(EXIT_SUCCESS);
        }

        else if(parsedSub->num_inputs > 1 && parsedSub->separator == SEPARATOR_PIPE){ // pipe execution

            pipeExecution(parsedSub);
            exit(EXIT_SUCCESS);
        }
        else if(parsedSub->num_inputs > 1 && parsedSub->separator == SEPARATOR_SEQ){ //sequential execution
            sequentialExecution(parsedSub);
            exit(EXIT_SUCCESS);
        }

        else if(parsedSub->num_inputs > 1 && parsedSub->separator == SEPARATOR_PARA){ // parallel execution
            parallelExecution(parsedSub);
            exit(EXIT_SUCCESS);
        }
    }
    else{
        wait(NULL);
    }    
}

using namespace std;
int main(){


    while(1){
        std::cout << "/> " << std::flush;
        string quitString = "quit";

        parsed_input *parsed = new parsed_input;
        char* input = new char[INPUT_BUFFER_SIZE];
        cin.getline(input, INPUT_BUFFER_SIZE);
        parse_line(input, parsed);

        if(parsed->inputs[0].type == INPUT_TYPE_COMMAND && parsed->num_inputs == 1){ //single-command case 
            int c;
            pid_t pid = fork();
            if(!strcmp(parsed->inputs[0].data.cmd.args[0], quitString.c_str())){ // quit
                break;
            }

            if(pid < 0){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if(pid > 0){ //Parent 
                wait(&c);
            }
            else{ //Child
                execvp(parsed->inputs[0].data.cmd.args[0],parsed->inputs[0].data.cmd.args);
            }
        } 

        if(parsed->num_inputs > 1 && parsed->separator == SEPARATOR_PIPE){ // pipe-case
            pipeExecution(parsed);
        
        }
        else if(parsed->num_inputs > 1 && parsed->separator == SEPARATOR_SEQ){ //sequential execution
            sequentialExecution(parsed);
        }

        else if(parsed->num_inputs > 1 && parsed->separator == SEPARATOR_PARA){ // parallel execution
            parallelExecution(parsed);
        }
        else if(parsed->separator == SEPARATOR_NONE){ //subshell
            singleCommandSubshell(parsed->inputs[0].data.subshell);
        }
        //pretty_print(parsed);
        free_parsed_input(parsed);
    }
    return 0;
}