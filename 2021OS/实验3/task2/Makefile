all: unnamed_pipe named_pipe calc_size
unnamed_pipe :
	gcc unnamed_pipe.c -o unnamed_pipe -pthread
named_pipe :
	gcc named_pipe.c -o named_pipe -pthread
calc_size :
	gcc calc_size.c -o calc_size -pthread
clean :
	rm unnamed_pipe named_pipe calc_size
