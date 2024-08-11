default:
	@echo 'Targets:'
	@echo ' run-sequential'
	@echo ' build-sequential'
	@echo ' run-async'
	@echo ' build-async'
	@echo ' clean'

all: run-sequential run-async

run-sequential: build-sequential
	./1_sequential

build-sequential: 1_sequential

1_sequential: 1_sequential.c
	gcc -o 1_sequential 1_sequential.c -std=gnu99

run-async: build-async
	./2_async

build-async: 2_async

2_async: 2_async.c
	gcc -o 2_async 2_async.c -std=gnu99

clean:
	-rm -f 1_sequential
	-rm -f 2_async
