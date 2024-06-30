EE_BIN = ps2menu.elf
EE_OBJS = main.o

# Pengaturan PS2SDK
PS2SDK = $(shell ps2sdk-config --ps2sdk-path)
PS2SDK_LIBS = -L$(PS2SDK)/ee/lib -lps2sdkc -lc -lkernel

all: $(EE_BIN)

$(EE_BIN): $(EE_OBJS)
	ee-gcc -o $(EE_BIN) $(EE_OBJS) $(PS2SDK_LIBS)

clean:
	rm -f $(EE_BIN) $(EE_OBJS)
