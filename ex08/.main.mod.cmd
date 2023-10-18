cmd_/root/little-penguin-1/ex08/main.mod := printf '%s\n'   main.o | awk '!x[$$0]++ { print("/root/little-penguin-1/ex08/"$$0) }' > /root/little-penguin-1/ex08/main.mod
