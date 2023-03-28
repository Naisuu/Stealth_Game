# Makefile
CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=-lMLV
EXEC=Stealth
SRC=./src/
INC=./include/
BIN=./bin/

$(SRC)$(EXEC) : $(BIN)Main.o $(BIN)Menu.o $(BIN)Game.o $(BIN)Move.o $(BIN)Display.o $(BIN)Check.o $(BIN)Score.o $(BIN)Skill.o $(BIN)Collide.o $(BIN)Util.o $(BIN)Initialization.o

	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(BIN)Main.o : $(SRC)Main.c $(INC)Menu.h

	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(BIN)Menu.o : $(SRC)Menu.c $(INC)Menu.h $(INC)Game.h

$(BIN)Game.o : $(SRC)Game.c $(INC)Game.h $(INC)Move.h

$(BIN)Move.o : $(SRC)Move.c $(INC)Move.h $(INC)Display.h

$(BIN)Display.o : $(SRC)Display.c $(INC)Display.h $(INC)Check.h

$(BIN)Check.o : $(SRC)Check.c $(INC)Check.h $(INC)Score.h

$(BIN)Score.o : $(SRC)Score.c $(INC)Score.h $(INC)Skill.h

$(BIN)Skill.o : $(SRC)Skill.c $(INC)Skill.h $(INC)Collide.h

$(BIN)Collide.o : $(SRC)Collide.c $(INC)Collide.h $(INC)Util.h

$(BIN)Util.o : $(SRC)Util.c $(INC)Util.h $(INC)Initialization.h

$(BIN)Initialization.o : $(SRC)Initialization.c $(INC)Initialization.h

$(BIN)%.o : $(SRC)%.c $(INC)%.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean :
	rm -f $(SRC)$(EXEC) $(BIN)*.o $(BIN)score.bin
