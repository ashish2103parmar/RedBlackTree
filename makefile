SRCS  := $(wildcard *.c) $(wildcard source/*.c)
TARGET := RBTREEDEMO
CFLAG := -I include/

all : ${TARGET} 

${TARGET}:${SRCS}
	gcc  $^ ${LFLAG} ${CFLAG} -o $@

clean:
		rm ${TARGET}
