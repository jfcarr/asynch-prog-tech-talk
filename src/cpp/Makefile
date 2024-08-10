COMPILER = g++
SEQUENTIAL1 = 1_sequential
ASYNC1 = 2_async

default:
	@echo 'Targets:'
	@echo '  run-sequential     Run sequential ($(SEQUENTIAL1))'
	@echo '  build-sequential   Build sequential ($(SEQUENTIAL1))'
	@echo '  run-async          Run async ($(ASYNC1))'
	@echo '  build-async        Build async ($(ASYNC1))'
	@echo '  clean              Remove compiled binaries'

run-sequential: build-sequential
	@./$(SEQUENTIAL1)

build-sequential:
	$(COMPILER) $(SEQUENTIAL1).cpp -o $(SEQUENTIAL1)

run-async: build-async
	@./$(ASYNC1)

build-async:
	$(COMPILER) $(ASYNC1).cpp -o $(ASYNC1)

clean:
	-rm -f $(SEQUENTIAL1)
	-rm -f $(ASYNC1)
