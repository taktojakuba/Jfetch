all: Jfetch

Jfetch: main.cpp
	g++ -std=c++17 -Os main.cpp -o Jfetch

clean:
	rm -f Jfetch

rebuild: clean all

.PHONY: all clean rebuild
