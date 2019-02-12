# SOURCE=symtab.c codegen.c tree.c astprint.c lex.yy.c y.tab.c aux.c extension.c
# MYPROGRAM= ../flcn
# MYINCLUDES= ./
CC=g++
CFLAGS=  -w -fpermissive -std=c++03
# $(MYPROGRAM): $(SOURCE) 
# 	lex lex.l
# 	yacc -d grammar.y
# 	$(CC) -g -I$(MYINCLUDES) $(CFLAGS) $(SOURCE) -o $(MYPROGRAM) 
DEPS = externs.h symtab.h falctypes.h symtabold.h tree.h codegen.h grammar.h extension.h

ODIR=obj
_OBJ = symtab.o codegen.o tree.o astprint.o y.tab.o lex.yy.o aux.o extension.o
_OBJ_CPP = worklist.o util.o
OBJ_C = $(patsubst %,$(ODIR)/%,$(_OBJ))
OBJ_CPP = $(patsubst %,$(ODIR)/%,$(_OBJ_CPP))

../flcn: $(OBJ_CPP) $(OBJ_C)
	$(CC) -o $@ $^ $(CFLAGS)

lex.yy.c: lex.l
	lex lex.l

y.tab.c: grammar.y
	yacc -d grammar.y

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~