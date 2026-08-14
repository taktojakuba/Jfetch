modules = "modules/"

all: Jfetch

Jfetch: main.cpp
	g++ -std=c++17 -Os -march=native -flto main.cpp modules/hostname.cpp modules/kernel.cpp modules/osname.cpp modules/shell.cpp modules/term.cpp modules/uptime.cpp modules/wm.cpp -o jf

install: Jfetch
	cp jf /usr/local/bin/jf
	chmod +x /usr/local/bin/jf

uninstall:
	rm -f /usr/local/bin/jf

clean:
	rm -f jf

rebuild: clean all

.PHONY: all clean rebuild install uninstall
