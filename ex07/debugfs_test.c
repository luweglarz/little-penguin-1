#include "debugfs_test.h"

BEGIN_TESTING

TEST_CASE("id_test"){
    printf("ID test case:\n");
    int id_fd;
    char buffer[256];

    memset(buffer, 0, sizeof(buffer));
    id_fd = open(PATH_TO_ID, O_RDWR);
    if (id_fd == -1){
        perror("Cannot open the file \"id\"");
    }

    ssize_t bytes_read = read(id_fd, buffer, sizeof(buffer));
    if (bytes_read < 0){
        perror("Failed to read the file \"id\"");
        close(id_fd);
        return (1);
    }
    printf("bytes_read: %lu\n", bytes_read);
    printf("buffer: %s\n", buffer);
    const char *login = "lweglarz";
    ssize_t bytes_write = write(id_fd, login, sizeof(login));
    if (bytes_write < 0){
        perror("Failed to write into the file");
        close(id_fd);
        return (1);
    }
    printf("bytes_write: %lu\n\n", bytes_write);

    close(id_fd);
    assert(1 == 1);
}

TEST_CASE("jiffies_test"){
    printf("jiffies test case:\n");
    int jiffies_fd;
    char buffer[256];

    memset(buffer, 0, sizeof(buffer));
    jiffies_fd = open(PATH_TO_JIFFIES, O_RDWR);
    if (jiffies_fd == -1){
        perror("Cannot open the file \"jiffies\"");
        return (1);
    }

    ssize_t bytes_read = read(jiffies_fd, buffer, 250);
    if (bytes_read < 0){
        perror("Failed to read the file \"jiffies\"");
        close(jiffies_fd);
        return (1);
    }
    printf("bytes_read: %lu\n", bytes_read);
    printf("buffer: %s\n\n", buffer);

    close(jiffies_fd);
    assert(1 == 1);
}

TEST_CASE("foo_test"){
    printf("foo test case:\n");
    int foo_fd;
    char buffer[getpagesize()];

    memset(buffer, 'l', sizeof(buffer));
    foo_fd = open(PATH_TO_FOO, O_RDWR);
    if (foo_fd == -1){
        perror("Cannot open the file \"foo\"");
        return (1);
    }

    ssize_t bytes_write = write(foo_fd, buffer, 150);
    if (bytes_write < 0){
        perror("Failed to write into the file \"foo\"");
        close(foo_fd);
        return (1);
    }
    printf("bytes_write: %lu\n", bytes_write);
    memset(buffer, 'l', sizeof(buffer));
    ssize_t bytes_read = read(foo_fd, buffer, sizeof(buffer));
    if (bytes_read < 0){
        perror("Failed to read the file \"foo\"");
        close(foo_fd);
        return (1);
    }
    printf("bytes_read: %lu\n", bytes_read);
    printf("buffer: %s\n", buffer);

    close(foo_fd);
    assert(1 == 1);
}

END_TESTING