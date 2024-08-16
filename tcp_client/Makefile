EXEC = ./bin/tcp_client
OBJS = tcp_client.o
SRC = tcp_client.c

#CC = aarch64-buildroot-linux-gnu-gcc
CC = gcc
CFLAGS += -O2 -Wall
LDFLAGS += 

# Add a POST_BUILD target to remove the .o files after building the executable
POST_BUILD = post_build_cleanup

all: $(EXEC) $(POST_BUILD)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -pthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -pthread

# Define the post-build cleanup task
post_build_cleanup:
	@rm -vf $(OBJS)

clean:
	@rm -vf $(EXEC) $(OBJS) *~