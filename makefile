all: Jfetch

Jfetch: main.cpp
	g++ -std=c++17 -Os main.cpp -o Jfetch

install: Jfetch
	cp Jfetch /usr/local/bin/Jfetch
	chmod +x /usr/local/bin/Jfetch

uninstall:
	rm -f /usr/local/bin/Jfetch

clean:
	rm -f Jfetch

rebuild: clean all

.PHONY: all clean rebuild install uninstall
