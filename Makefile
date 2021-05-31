CXX		=	g++ -std=c++11 -O3
EXE		=  	viterbi

OBJ_DIR	=	objs
SRC_DIR = 	srcs

CFLAGS = -g -O3

all: $(EXE)

$(EXE): $(OBJ_DIR)/main.o $(OBJ_DIR)/util.o
	$(CXX) $^ $(CFLAGS) -o $@
	
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp util.h | obj_dir
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/util.o: $(SRC_DIR)/util.cpp util.h | obj_dir
	$(CXX) $(CFLAGS) -c $< -o $@

obj_dir:
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf *.gch objs/
