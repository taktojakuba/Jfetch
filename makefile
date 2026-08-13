all: Jfetch

Jfetch: main.cpp
	g++ -std=c++17 -Os main.cpp -o jf

install: Jfetch
	cp jf /usr/local/bin/jf
	chmod +x /usr/local/bin/jf

uninstall:
	rm -f /usr/local/bin/jf

clean:
	rm -f jf

rebuild: clean all

.PHONY: all clean rebuild install uninstall
