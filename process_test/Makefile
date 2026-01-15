CC := gcc

system_test:system_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_test:fork_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_fd_test:fork_fd_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

secondfloor: secondfloor.c
	-$(CC) -o $@ $^

execve_test: execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_execve_test: fork_execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

waitpid_test: waitpid_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_pipe_test: unnamed_pipe_test.c
	-$(CC) -o $@ $^
	-./$@ "test"
	-rm ./$@

fifo_read:fifo_read.c
	-$(CC) -o $@ $^

fifo_write:fifo_write.c
	-$(CC) -o $@ $^

shared_mem:shared_mem.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

father_son_mq_test: father_son_mq_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

producer: producer.c
	-$(CC) -o $@ $^

consumer: consumer.c
	-$(CC) -o $@ $^

signal_test: signal_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@