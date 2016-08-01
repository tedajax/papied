ARCH = x64

ifeq ($(OS),Windows_NT) # If windows
	LIB_ROOT = external/lib/$(ARCH)/
	SDL_LFLAGS = -L$(LIB_ROOT) -lSDL2
	CC = clang++
	STD = c++14
	POST_BUILD = cp external/lib/$(ARCH)/*.dll .
	#LFLAGS =
	INCLUDE_FLAGS = -Iexternal/include/
	PLATFORM_DIR = Win
else
	SDL_LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lglew -framework OpenGL
	CC = clang++
	STD = c++14
	POST_BUILD =
	INCLUDE_FLAGS =
    SYSTEM_FLAGS =
    PLATFORM_DIR = Posix
endif

MODE = DEBUG

ifeq ($(MODE),DEBUG)
    DEBUG_FLAGS = -g -D_DEBUG
	OPT_LEVEL = 0
else
    DEBUG_FLAGS =
	OPT_LEVEL = 3
endif

TARGET		= papied.exe
CFLAGS		= -std=$(STD) -O$(OPT_LEVEL) -Wall $(DEBUG_FLAGS) $(INCLUDE_FLAGS) -Wno-unknown-pragmas

LINKER		= $(CC) -o
LFLAGS		= -Wall

SRCDIR		= src
OBJDIR		= obj
BINDIR		= .

SOURCES		:= $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/$(PLATFORM_DIR)/*.cpp)
OBJECTS		:= $(SOURCES:$(SRCDIR)%.cpp=$(OBJDIR)/%.o)$($(SRCDIR)/$(PLATFORM_DIR)%.cpp=$(OBJDIR)/$(PLATFORM_DIR)/%.o)



all: directories $(BINDIR)/$(TARGET) post-build
	@echo Done!

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo @$(LINKER) $@ $(OBJECTS) $(LFLAGS) $(SDL_LFLAGS) $(SYSTEM_FLAGS)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS) $(SDL_LFLAGS) $(SYSTEM_FLAGS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo @$(CC) $(CFLAGS) -c $< -o $@
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	@$(RM) $(OBJECTS)
	@$(RM) $(BINDIR)/$(TARGET)
	@$(RM) ./*.dll
	@$(RM) -rf $(OBJDIR)

.PHONEY: run
run: all
	./$(TARGET)

.PHONY: directories
directories: $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

post-build:
	$(POST_BUILD)