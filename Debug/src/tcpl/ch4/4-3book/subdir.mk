################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tcpl/ch4/4-3book/getch.c \
../src/tcpl/ch4/4-3book/getop.c \
../src/tcpl/ch4/4-3book/main.c \
../src/tcpl/ch4/4-3book/stack.c 

OBJS += \
./src/tcpl/ch4/4-3book/getch.o \
./src/tcpl/ch4/4-3book/getop.o \
./src/tcpl/ch4/4-3book/main.o \
./src/tcpl/ch4/4-3book/stack.o 

C_DEPS += \
./src/tcpl/ch4/4-3book/getch.d \
./src/tcpl/ch4/4-3book/getop.d \
./src/tcpl/ch4/4-3book/main.d \
./src/tcpl/ch4/4-3book/stack.d 


# Each subdirectory must supply rules for building sources it contributes
src/tcpl/ch4/4-3book/%.o: ../src/tcpl/ch4/4-3book/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/Users/niedaocai/Documents/workspace/c/usefulC/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


