CPP = x86_64-elf-g++
AS = x86_64-elf-as
LDFLAGS = -flto
CPPFLAGS = -O3 -Wall -Wextra -ffreestanding -nostdlib -lgcc -mno-red-zone -fno-exceptions -fno-rtti

OBJDIR = build

SOURCESCPP = $(shell find ./srcremake -name *.cpp)
SOURCESASM = $(shell find ./srcremake -name *.s) 
OBJECTSCPP = $(SOURCESCPP:.cpp=.o)
OBJECTSASM = $(SOURCESASM:.s=.o)

run:
	bochs

build: $(OBJECTSCPP) $(OBJECTSASM)
	@$(CPP) -T ./src/linker.ld -o ./iso/boot/kernel.bin $^ $(CPPFLAGS) $(LDFLAGS)
	@strip ./iso/boot/kernel.bin
	@objcopy -O elf32-i386 ./iso/boot/kernel.bin
	@bash -c "grub-mkrescue /usr/lib/grub/i386-pc -o ./build/asuos.iso ./iso &> /dev/null"

all:
	build
	run

$(OBJDIR)/%.o:%.s
	@$(AS) -o $@ -c $<

$(OBJDIR)/%.o:%.cpp
	@$(CPP) -o $@ -c $< $(CPPFLAGS)

clean:
	@rm -rf $(OBJECTSCPP) $(OBJECTSASM)
	@rm ./build/asuos.iso
	@rm ./iso/boot/kernel.bin

