CC = g++
LOGO = logo.gif
CPP = tokens.cpp  blocks.cpp  file_functions.cpp  exceptions.cpp  misc.cpp LexicalAnalyzer.cpp  SyntaxAnalyzer.cpp  jstidy.cpp
OPT = -O3 -w
OUT = jstidy.exe

$(OUT) : $(CPP)
	$(CC) -o $(OUT) $(OPT) $(CPP)
	@echo "Make is finished !"

.PHONY : clean
clean :
	rm -f *.o $(OUT)
	@echo "Clean is finished !"
