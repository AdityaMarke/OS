#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    int source = open(argv[1], O_RDONLY);
    if (source < 0) {
        perror("Error opening source file");
        return 1;
    }

    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error opening destination file");
        close(source);
        return 1;
    }

    char buffer[50];
    int bytes;
    while ((bytes = read(source, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytes);
    }

    close(source);
    close(dest);
    return 0;
}
