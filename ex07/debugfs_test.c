#include "debugfs_test.h"
#include <pthread.h>

pthread_barrier_t barrier;

static void *write_file(void *arg){
    char buffer[getpagesize()];
    int fd = *(int *)arg;
    memset(buffer, 'l', sizeof(buffer));
    printf("Thread 1 is waiting...\n");
    pthread_barrier_wait(&barrier);
    printf("Thread 1 is running\n");
    for (int i = 0 ; i < 1000000; i++){
        ssize_t bytes_write = write(fd, buffer, getpagesize());
    }
    pthread_exit(NULL);
}

static void *read_file(void *arg){
    char buffer[getpagesize()];
    int fd = *(int *)arg;
    printf("Thread 2 is waiting...\n");
    pthread_barrier_wait(&barrier);
    printf("Thread 2 is running\n");
    for (int i = 0 ; i < 1000000; i++){
        ssize_t bytes_write = read(fd, buffer, getpagesize());
    }
    printf("buffer: %s\n", buffer);
    pthread_exit(NULL);
}

BEGIN_TESTING

TEST_CASE("id_test"){
    printf("ID test case:\n");
    int id_fd;
    char buffer[getpagesize()];

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
    char buffer[getpagesize()];

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
    printf("jiffies: %s\n\n", buffer);

    close(jiffies_fd);
    assert(1 == 1);
}

TEST_CASE("foo_test"){
    printf("foo test case:\n");
    int foo_fd;
    pthread_t tid[2];
     
    pthread_barrier_init(&barrier, NULL, 2);
    foo_fd = open(PATH_TO_FOO, O_RDWR);
    if (foo_fd == -1){
        perror("Cannot open the file \"foo\"");
        return (1);
    }

    if (pthread_create(&(tid[0]), NULL, write_file, (void *)&foo_fd) != 0) {
        perror("Error creating thread");
        return 1;
    }

    if (pthread_create(&(tid[1]), NULL, read_file, (void *)&foo_fd) != 0) {
        perror("Error creating thread");
        return 1;
    }

    if (pthread_join(tid[0], NULL) != 0) {
        perror("Error joining thread");
        return 1;
    }

    if (pthread_join(tid[1], NULL) != 0) {
        perror("Error joining thread");
        return 1;
    }

    pthread_barrier_destroy(&barrier);

    close(foo_fd);
    assert(1 == 1);
}

END_TESTING