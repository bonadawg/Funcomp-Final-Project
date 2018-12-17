
CMP = g++
CLASS = snake
LIB = gfxnew
MAIN = project
EXEC = snake

$(EXEC): $(CLASS).o $(MAIN).o $(LIB).o
	$(CMP) $(CLASS).o $(MAIN).o $(LIB).o -lX11 -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c -std=c++11 -lX11 $(CLASS).cpp -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c -std=c++11 -lX11 $(MAIN).cpp -o $(MAIN).o

clean:
	rm $(MAIN).o $(EXEC).o  $(EXEC)

