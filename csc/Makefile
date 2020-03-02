modules := code

.PHONY: all $(modules) clean 

all: $(modules)

$(modules):
	$(MAKE) --directory=$@
	gcc code/fibo.o code/main.o -o fibo


clean:
	for d in $(modules);\
		do\
			$(MAKE) --directory=$$d clean;\
		done;\
