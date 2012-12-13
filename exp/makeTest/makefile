# Arduino Makefile
# Arduino adaptation by mellis, eighthave, oli.keller
#
# This makefile allows you to build sketches from the command line
# without the Arduino environment (or Java).
#
# Note, this Makefile has been edited by the Debian package maintainer, so
# there's a reasonable chance it'll simply work without the need to edit it
# but just in case, here are the instructions:
#
# Detailed instructions for using the makefile:
#
#  1. Copy this file into the folder with your sketch. There should be a
#     file with the same name as the folder and with the extension .pde
#     (e.g. foo.pde in the foo/ folder).
#
#  2. Modify the line containg "INSTALL_DIR" to point to the directory that
#     contains the Arduino installation (for example, under Mac OS X, this
#     might be /Applications/arduino-0012).
#
#  3. Modify the line containing "PORT" to refer to the filename
#     representing the USB or serial connection to your Arduino board
#     (e.g. PORT = /dev/tty.USB0).  If the exact name of this file
#     changes, you can use * as a wildcard (e.g. PORT = /dev/tty.usb*).
#
#  4. Set the line containing "MCU" to match your board's processor. 
#     Older one's are atmega8 based, newer ones like Arduino Mini, Bluetooth
#     or Diecimila have the atmega168.  If you're using a LilyPad Arduino,
#     change F_CPU to 8000000.
#
#  5. At the command line, change to the directory containing your
#     program's file and the makefile.
#
#  6. Type "make" and press enter to compile/verify your program.
#
#  7. Type "make upload", reset your Arduino board, and press enter to
#     upload your program to the Arduino board.
#
# $Id$

TARGET = $(notdir $(CURDIR))
#INSTALL_DIR = ../../..
PORT = /dev/ttyACM0
#UPLOAD_RATE = 57600
AVRDUDE_PROGRAMMER = arduino
#stk500v1
#MCU = atmega168
#F_CPU = 16000000
ARDUINO_BASE=/usr/share/arduino
BOARDFILE=../../res/boards.txt
MODEL=uno


############################################################################
# Below here nothing should be changed...

ARDUINO =$(ARDUINO_BASE)/hardware/arduino/cores/arduino
#/home/shared/Downloads/Arduino-master/hardware/arduino/cores/arduino
AVR_TOOLS_PATH = /usr/bin
CORE_SRCS = $(wildcard $(ARDUINO)/*.c )
#$(ARDUINO)/pins_arduino.c $(ARDUINO)/wiring.c \
$(ARDUINO)/wiring_analog.c $(ARDUINO)/wiring_digital.c \
$(ARDUINO)/wiring_pulse.c $(ARDUINO)/wiring_shift.c \
$(ARDUINO)/WInterrupts.c
VIRTUAL_PURE=applet/virtualPure.cpp
CORE_CXXSRC=$(wildcard $(ARDUINO)/*.cpp)
#$(ARDUINO)/HardwareSerial.cpp $(ARDUINO)/WMath.cpp \
$(ARDUINO)/Print.cpp

INO_SRC=$(wildcard src/*.ino)
SRC=$(INO_SRC:src/%.ino=applet/%.cpp) $(wildcard src/*.cpp) $(wildcard src/*.c) $(wildcard src/*.cxx) 
FORMAT = ihex
#
# Set up values according to what the IDE uses:
#
UPLOAD_RATE= $(shell grep "^$(MODEL)\." $(BOARDFILE) | grep upload.speed | sed 's/.*=//')
MCU = $(shell grep "^$(MODEL)\." $(BOARDFILE) | grep build.mcu | sed 's/.*=//')
F_CPU = $(shell grep "^$(MODEL)\." $(BOARDFILE) | grep build.f_cpu | sed 's/.*=//')


# Name of this Makefile (used for "make depend").
MAKEFILE = Makefile

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
DEBUG = stabs

OPT = s

# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU)
CXXDEFS = -DF_CPU=$(F_CPU)

# Place -I options here
CINCS = -I$(ARDUINO) -Iinc
#-I/home/shared/Downloads/Arduino-master/hardware/arduino/variants/mega/
CXXINCS = -I$(ARDUINO) -Iinc
#-I/home/shared/Downloads/Arduino-master/hardware/arduino/variants/mega/

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99
CDEBUG = -g$(DEBUG)
CWARN = -Wall -Wstrict-prototypes
CTUNING = -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
#CEXTRA = -Wa,-adhlns=$(<:.c=.lst)

# Extra flags to match what the Arduino 1.0 IDE is doing:
# Something about the -ffunction-sections -fdata-sections reduces
# final text size by roughly half!
CEXTRA= -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -DARDUINO=100

CFLAGS = $(CDEBUG) $(CDEFS) $(CINCS) -O$(OPT) $(CWARN) $(CSTANDARD) $(CEXTRA)
CXXFLAGS = $(CDEFS) $(CINCS) -O$(OPT)
#ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs 
LDFLAGS = -lm


# Programming support using avrdude. Settings and variables.
AVRDUDE_PORT = $(PORT)
AVRDUDE_WRITE_FLASH = -U flash:w:applet/$(TARGET).hex
AVRDUDE_FLAGS = -V -F \
-p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) \
-b $(UPLOAD_RATE)

# Program settings
CC = $(AVR_TOOLS_PATH)/avr-gcc
CXX = $(AVR_TOOLS_PATH)/avr-gcc
#++
OBJCOPY = $(AVR_TOOLS_PATH)/avr-objcopy
OBJDUMP = $(AVR_TOOLS_PATH)/avr-objdump
AR  = $(AVR_TOOLS_PATH)/avr-ar
SIZE = $(AVR_TOOLS_PATH)/avr-size
NM = $(AVR_TOOLS_PATH)/avr-nm
AVRDUDE = $(AVR_TOOLS_PATH)/avrdude
REMOVE = rm -f
MV = mv -f

# Define all object files.
CORE_OBJS = $(CORE_SRCS:/%.c=build/%.o) $(CORE_CXXSRC:/%.cpp=build/%.o) $(ASRC:/%.S=build/%.o) $(VIRTUAL_PURE:applet/%.cpp=build/%.o)

SRC_OBJS = $(SRC:src/%.c=obj/%.o)  $(SRC:src/%.cpp=obj/%.c) $(SRC:src/%.cxx=obj/%.o)

# Define all listing files.
LST = $(ASRC:/%.S=build/%.lst) $(CORE_CXXSRC:/%.cpp=build/%.lst) $(CORE_SRCS:/%.c=build/%.lst)

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)
ALL_CXXFLAGS = -mmcu=$(MCU) -I. $(CXXFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)


# Default target.
all: dirs applet_files build sizeafter

# Code Blocks targets:
Release: all

Debug: all

cleanDebug: clean

cleanRelease: clean

build: dirs elf hex 

dirs:
	mkdir -p build 
	mkdir -p obj
	mkdir -p applet

build/$(TARGET).pde: src/$(TARGET).ino
	cat $< > $@

applet_files: $(SRC)
#applet/$(TARGET).cpp
$(VIRTUAL_PURE):
	mkdir -p applet
	echo "extern \"C\" void __cxa_pure_virtual() { while (1) ; }" > $@

applet/$(TARGET).cpp: build/$(TARGET).pde
	# Here is the "preprocessing".
	# It creates a .cpp file based with the same name as the .pde file.
	# On top of the new .cpp file comes the WProgram.h header.
	# At the end there is a generic main() function attached.
	# Then the .cpp file will be compiled. Errors during compile will
	# refer to this new, automatically generated, file. 
	# Not the original .pde file you actually edit...
	test -d applet || mkdir applet
	echo '#include "WProgram.h"' > applet/$(TARGET).cpp
	# Required:
	cat build/$(TARGET).pde >> applet/$(TARGET).cpp
	cat $(ARDUINO)/main.cpp >> applet/$(TARGET).cpp

elf: applet/$(TARGET).elf
hex: applet/$(TARGET).hex
eep: applet/$(TARGET).eep
lss: applet/$(TARGET).lss 
sym: applet/$(TARGET).sym

# Program the device.  
upload: applet/$(TARGET).hex
	stty -F $(AVRDUDE_PORT) hupcl ; sleep 0.1 ; stty -F $(AVRDUDE_PORT) -hupcl
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)


	# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) applet/$(TARGET).hex
ELFSIZE = $(SIZE)  applet/$(TARGET).elf
sizebefore:
	@if [ -f applet/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(HEXSIZE); echo; fi

sizeafter:
	@if [ -f applet/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(HEXSIZE); echo; fi


# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000 


coff: applet/$(TARGET).elf
	$(COFFCONVERT) -O coff-avr applet/$(TARGET).elf $(TARGET).cof


extcoff: applet/$(TARGET).elf
	$(COFFCONVERT) -O coff-ext-avr applet/$(TARGET).elf $(TARGET).cof


.SUFFIXES: .elf .hex .eep .lss .sym

.elf.hex:
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

.elf.eep:
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
.elf.lss:
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
.elf.sym:
	$(NM) -n $< > $@

	# Link: create ELF output file from library.
applet/$(TARGET).elf: $(SRC) applet/core.a 
	$(CXX) $(ALL_CXXFLAGS) -o $@ $(SRC) -L. applet/core.a $(LDFLAGS)

applet/core.a: $(CORE_OBJS)
	@for i in $(CORE_OBJS); do echo $(AR) rcs applet/core.a $$i; $(AR) rcs applet/core.a $$i; done



# Compile: create object files from C++ source files.
build/%.o: /%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@ 

build/%.o : applet/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@ 

# Compile: create object files from C source files.
build/%.o: /%.c
	mkdir -p $(dir $@)
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 


# Compile: create assembler files from C source files.
build/%.s: /%.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@

obj/%.o : src/%.c
	mkdir -p $(dir $@)
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 

obj/%.o : src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@ 

obj/%.o : src/%.cxx
	mkdir -p $(dir $@)
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@ 

# Assemble: create object files from assembler source files.
.S.o:
	$(CC) -c $(ALL_ASFLAGS) $< -o $@


# Automatic dependencies
build/%.d: /%.c
	mkdir -p $(shell dirname $@)
	$(CC) -M $(ALL_CFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@

build/%.d: /%.cpp
	mkdir -p $(shell dirname $@)
	$(CXX) -M $(ALL_CXXFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@


# Target: clean project.
clean:
	rm -Rf applet obj build
#	$(REMOVE) applet/$(TARGET).hex applet/$(TARGET).eep applet/$(TARGET).cof applet/$(TARGET).elf \
	applet/$(TARGET).map applet/$(TARGET).sym applet/$(TARGET).lss applet/core.a \
	$(CORE_OBJS) $(LST) $(CORE_SRCS:%.c=build%.s) $(CORE_SRCS:%.c=build%.d) $(CORE_CXXSRC:%.cpp=build%.s) $(CORE_CXXSRC:%.cpp=build%.d)

.PHONY:	all build elf hex eep lss sym program coff extcoff clean applet_files sizebefore sizeafter

-include $(CORE_SRCS:/%.c=build/%.d)
-include $(CORE_CXXSRC:/%.cpp=build/%.d)
