# EXEC = ./bin/tcp_server 
# OBJS = tcp_server.o
# SRC  = tcp_server.c
# SRC += Modbus.c
# CCFLAGS += -Iinc

# CC = aarch64-buildroot-linux-gnu-gcc
# #CC = gcc
# CFLAGS += -O2 -Wall
# LDFLAGS += 

# all:$(EXEC)

# $(EXEC):$(OBJS)
# 	$(CC) $(LDFLAGS) -o $@ $(OBJS) -pthread

# %.o:%.c
# 	$(CC) $(CFLAGS) -c $< -o $@ -pthread

# clean:
# 	@rm -vf $(EXEC) *.o *~

#TARGET:tcp_server
#CC:aarch64-buildroot-linux-gnu-gcc
#tcp_server: Modbus.o tcp_server.o
#	$(CC) -o tcp_server Modbus.o tcp_server.o
 
#Modbus.o: Modbus.c inc/Modbus.h
#	$(CC) -c Modbus.c
 
#tcp_server.o: tcp_server.c
#	$(CC) -c tcp_server.c    
 
#.PHONY:clean
#clean:
#	rm -f *.o $(TARGET)

# 变量定义
TARGET = tcp_server
CC = aarch64-buildroot-linux-gnu-gcc
CFLAGS = -Iinc -Wall -g
LDFLAGS = 

# 源文件和目标文件
SRC_FILES = Modbus.c tcp_server.c
OBJ_FILES = $(SRC_FILES:.c=.o)

# 默认规则
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJ_FILES)
	$(CC) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

# 生成对象文件规则
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理规则
.PHONY: clean
clean:
	rm -f $(OBJ_FILES) $(TARGET)
