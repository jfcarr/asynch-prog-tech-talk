default:
	@echo 'Targets:'
	@echo '  run'
	@echo '  build'
	@echo '  clean'

run: build
	java -cp bin App

build:
	javac src/App.java -d bin

clean:
	-rm -rf bin/