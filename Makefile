all:
	g++ -Ofast $(foreach warn, all extra pedantic, -W$(warn)) $(foreach dir, $(wildcard src/*), $(wildcard $(dir)/*))
	./a.out
