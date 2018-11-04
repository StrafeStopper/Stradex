#OBJS: Files to be compiled
OBJS = main.cpp init.cpp load.cpp game.cpp fileIO.cpp menu.cpp

#OBJ_NAME: Name of the executeable
OBJ_NAME = light.exe

#COMPILER_FLAGS: flags to compile width
COMPILER_FLAGS = -w

#LINKER_FLAGS: Flags to link extra libraries to the executable
LINUX_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
WINDOWS_FLAGS = -lmingw32 -LSDL2/x86_64-w64-mingw32/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#Compile for linux
linux : $(OBJS)
	g++ $(OBJS) $(COMPILER_FLAGS) $(LINUX_FLAGS) -o light

windows : $(OBJS)
	x86_64-w64-mingw32-g++ $(OBJS) $(COMPILER_FLAGS) $(WINDOWS_FLAGS) -o light.exe
