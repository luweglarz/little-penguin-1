#ifndef DEBUGFS_TEST_H
# define DEBUGFS_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

# define PATH_TO_ID "/sys/kernel/debug/fortytwo/id"
# define PATH_TO_JIFFIES "/sys/kernel/debug/fortytwo/jiffies"
# define PATH_TO_FOO "/sys/kernel/debug/fortytwo/foo"

# define BEGIN_TESTING int main(int ac, char **av){
# define END_TESTING return 0;}
# define TEST_CASE(TEST_NAME) if (run_test(TEST_NAME, ac, av))

int run_test(const char *test_name, int ac, char **av){
	if (ac == 1){ return 1; }
	for (int i = 1; i < ac; i++){ if (strcmp(test_name, av[i])){ return 0;}}
}


#endif