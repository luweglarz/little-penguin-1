#include "fortytwo_test_framework.h"

/*
*   A simple test framework for my misc device driver 
*   in order to get better at unit testing in c
*/

BEGIN_TESTING

TEST_CASE("read_test"){
    int fd;
    char buffer[256];

    fd = open(PATH_TO_DEVICE, O_RDWR);

    if (fd == -1){
        perror("Cannot open the file");
        return (1);
    }

    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read < 0){
        perror("Failed to read the file");
        close(fd);
        return (1);
    }
    printf("bytes_read: %lu\n", bytes_read);
    printf("buffer: %s\n", buffer);

    close(fd);
    assert(1 == 1);
}

END_TESTING