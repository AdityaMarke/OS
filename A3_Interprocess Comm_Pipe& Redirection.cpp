#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    int src_file = open(argv[1], O_RDONLY);
    if(src_file == -1) {
        perror("Unable to open source file");
        return 1;
    }

    dup2(src_file, STDIN_FILENO);
    close(src_file);

    pid_t fork_val = fork();

    if(fork_val > 0) { // Parent process: sort
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execl("/usr/bin/sort", "sort", NULL);
        perror("execl failed for sort");
    }
    else if(fork_val == 0) { // Child process: unique
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);

        int dest_file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(dest_file == -1) {
            perror("Unable to open destination file");
            return 1;
        }

        dup2(dest_file, STDOUT_FILENO);
        close(dest_file);
        close(fd[0]);

        execl("/usr/bin/uniq", "uniq", NULL);
        perror("execl failed for uniq");
    }
    else {
        perror("Fork failed");
        return 1;
    }
    return 0;
}