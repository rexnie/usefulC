################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/tcpl/ch7/7-3/subdir.mk
-include src/tcpl/ch3/3-3/subdir.mk
-include src/tcpl/ch3/3-2/subdir.mk
-include src/tcpl/ch3/3-1/subdir.mk
-include src/tcpl/ch2/2-9/subdir.mk
-include src/tcpl/ch2/2-8/subdir.mk
-include src/tcpl/ch2/2-7/subdir.mk
-include src/tcpl/ch2/2-6/subdir.mk
-include src/tcpl/ch2/2-5/subdir.mk
-include src/tcpl/ch2/2-4/subdir.mk
-include src/tcpl/ch2/2-3/subdir.mk
-include src/tcpl/ch2/2-10/subdir.mk
-include src/tcpl/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: UsefulC

# Tool invocations
UsefulC: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MacOS X C Linker'
	gcc  -o "UsefulC" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) UsefulC
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
