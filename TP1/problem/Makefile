build:
	gcc ./solution/main.c ./solution/TLista.c -o ./solution/main

try: build
	./solution/main examples.txt output.txt

examples:
	python examples.py > examples.txt

test: try
	python test.py
