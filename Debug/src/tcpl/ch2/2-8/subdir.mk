################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tcpl/ch2/2-8/rightrot.c 

OBJS += \
./src/tcpl/ch2/2-8/rightrot.o 

C_DEPS += \
./src/tcpl/ch2/2-8/rightrot.d 


# Each subdirectory must supply rules for building sources it contributes
src/tcpl/ch2/2-8/%.o: ../src/tcpl/ch2/2-8/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/Users/niedaocai/Documents/workspace/c/usefulC/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


