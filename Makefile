#OBJS: Files to be compiled
OBJS = main.cpp init.cpp load.cpp game.cpp fileIO.cpp menu.cpp

#OBJ_NAME: Name of the executeable
OBJ_NAME = light.exe

#COMPILER_FLAGS: flags to compile width
COMPILER_FLAGS = -w

#LINKER_FLAGS: Flags to link extra libraries to the executable
LINUX_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
WINDOWS_FLAGS = -lmingw32 -LSDL2/i686-w64-mingw32/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#All
all:
	@echo "Type \"make linux\" to compile for linux"
	@echo "Type \"make windows\" to compile for windows"

#Compile for linux
linux : $(OBJS)
	g++ $(OBJS) $(COMPILER_FLAGS) $(LINUX_FLAGS) -o light

#Compile for windows
windows : $(OBJS)
	i686-w64-mingw32-g++ $(OBJS) $(COMPILER_FLAGS) $(WINDOWS_FLAGS) -o light.exe
