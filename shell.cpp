/****************
LE2: Introduction to Unnamed Pipes
****************/
#include <unistd.h> // pipe, fork, dup2, execvp, close
using namespace std;

int main () {
    // lists all the files in the root directory in the long format
    char* cmd1[] = {(char*) "ls", (char*) "-al", (char*) "/", nullptr};
    // translates all input from lowercase to uppercase
    char* cmd2[] = {(char*) "tr", (char*) "a-z", (char*) "A-Z", nullptr};

    // TODO: add functionality
    // Create pipe
    int p[2];
    pipe(p);
    // Create child to run first command
    pid_t child1 = fork();
    // In child, redirect output to write end of pipe
    if (child1 == 0){
        dup2(p[1], STDOUT_FILENO);
    // Close the read end of the pipe on the child side.
        close(p[0]);
    // In child, execute the command
        execvp(cmd1[0], cmd1);
    }
    // Create another child to run second command
    pid_t child2 = fork();
    // In child, redirect input to the read end of the pipe
    if (child2 == 0){
        dup2(p[0], STDIN_FILENO);
    // Close the write end of the pipe on the child side.
        close(p[1]);
    // Execute the second command.
        execvp(cmd2[0], cmd2);
    }
    // Reset the input and output file descriptors of the parent.
    close (p[0]);
    close (p[1]);
}
