#source file search paths
VPATH = ./src 

	# compiler include search paths
INCS = -I./include \
	-I../windex/include \


LIBS = \
	-lgdiplus -lgdi32 -lcomdlg32 -lstdc++fs \
	#-mwindows

static_link_flags = -static-libstdc++ -static-libgcc -static -lComctl32

# folders
ODIR = ./.vscode/obj

OPT = -g
CCflags = -std=c++17 $(OPT) -D_mingw_

# sources
OBJ_starter = \
	$(ODIR)/main.o \
	$(ODIR)/cxyz.o \
	$(ODIR)/cxyzUnitTest.o \
	$(ODIR)/cBuilding.o \

### COMPILE

$(ODIR)/%.o: %.cpp cxyz.h cBuilding.h
	g++ $< \
	-c -o $@  $(INCS) $(CCflags)

starter: $(OBJ_starter)
	g++ $(OPT) \
	-o bin/roomfinder.exe $^  \
	$(static_link_flags) $(LIBS)

.PHONY: clean
clean:
	del /q .vscode\\obj\\*.o

