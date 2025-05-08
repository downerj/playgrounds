all: bin/JSEngine.class bin/JSCanvas.class

bin/JSEngine.class: src/console/JSEngine.java
	javac -d bin/ src/console/JSEngine.java

bin/JSCanvas.class: src/fxcanvas/JSCanvas.java
	javac -d bin/ src/fxcanvas/JSCanvas.java

clean:
	rm bin/*.class
