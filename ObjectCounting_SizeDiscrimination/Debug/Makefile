################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../IR_Distance.c \
../lcd.c \
../ObjectCounting_SizeDiscrimination.c \
../SerialCommunication.c \
../ServoPositionControl.c \
../USS_distance.c \
../util.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
IR_Distance.o \
lcd.o \
ObjectCounting_SizeDiscrimination.o \
SerialCommunication.o \
ServoPositionControl.o \
USS_distance.o \
util.o

OBJS_AS_ARGS +=  \
IR_Distance.o \
lcd.o \
ObjectCounting_SizeDiscrimination.o \
SerialCommunication.o \
ServoPositionControl.o \
USS_distance.o \
util.o

C_DEPS +=  \
IR_Distance.d \
lcd.d \
ObjectCounting_SizeDiscrimination.d \
SerialCommunication.d \
ServoPositionControl.d \
USS_distance.d \
util.d

C_DEPS_AS_ARGS +=  \
IR_Distance.d \
lcd.d \
ObjectCounting_SizeDiscrimination.d \
SerialCommunication.d \
ServoPositionControl.d \
USS_distance.d \
util.d

OUTPUT_FILE_PATH +=ObjectCounting_SizeDiscrimination.elf

OUTPUT_FILE_PATH_AS_ARGS +=ObjectCounting_SizeDiscrimination.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atmega128 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="ObjectCounting_SizeDiscrimination.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=atmega128  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "ObjectCounting_SizeDiscrimination.elf" "ObjectCounting_SizeDiscrimination.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "ObjectCounting_SizeDiscrimination.elf" "ObjectCounting_SizeDiscrimination.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "ObjectCounting_SizeDiscrimination.elf" > "ObjectCounting_SizeDiscrimination.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "ObjectCounting_SizeDiscrimination.elf" "ObjectCounting_SizeDiscrimination.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-size.exe" "ObjectCounting_SizeDiscrimination.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "ObjectCounting_SizeDiscrimination.elf" "ObjectCounting_SizeDiscrimination.a" "ObjectCounting_SizeDiscrimination.hex" "ObjectCounting_SizeDiscrimination.lss" "ObjectCounting_SizeDiscrimination.eep" "ObjectCounting_SizeDiscrimination.map" "ObjectCounting_SizeDiscrimination.srec" "ObjectCounting_SizeDiscrimination.usersignatures"
	