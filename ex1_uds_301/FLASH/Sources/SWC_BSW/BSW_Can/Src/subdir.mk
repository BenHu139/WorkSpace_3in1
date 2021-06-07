################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_Can/Src/CAN.c" \
"../Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF.c" \
"../Sources/SWC_BSW/BSW_Can/Src/CAN_INTC.c" \
"../Sources/SWC_BSW/BSW_Can/Src/CAN_STACK.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_Can/Src/CAN.c \
../Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF.c \
../Sources/SWC_BSW/BSW_Can/Src/CAN_INTC.c \
../Sources/SWC_BSW/BSW_Can/Src/CAN_STACK.c \

OBJS += \
./Sources/SWC_BSW/BSW_Can/Src/CAN_c.obj \
./Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF_c.obj \
./Sources/SWC_BSW/BSW_Can/Src/CAN_INTC_c.obj \
./Sources/SWC_BSW/BSW_Can/Src/CAN_STACK_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_Can/Src/CAN_c.obj" \
"./Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF_c.obj" \
"./Sources/SWC_BSW/BSW_Can/Src/CAN_INTC_c.obj" \
"./Sources/SWC_BSW/BSW_Can/Src/CAN_STACK_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_Can/Src/CAN_c.d \
./Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF_c.d \
./Sources/SWC_BSW/BSW_Can/Src/CAN_INTC_c.d \
./Sources/SWC_BSW/BSW_Can/Src/CAN_STACK_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_Can/Src/CAN_c.obj \
./Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF_c.obj \
./Sources/SWC_BSW/BSW_Can/Src/CAN_INTC_c.obj \
./Sources/SWC_BSW/BSW_Can/Src/CAN_STACK_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_Can/Src/CAN_c.d" \
"./Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF_c.d" \
"./Sources/SWC_BSW/BSW_Can/Src/CAN_INTC_c.d" \
"./Sources/SWC_BSW/BSW_Can/Src/CAN_STACK_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_Can/Src/CAN_c.obj: ../Sources/SWC_BSW/BSW_Can/Src/CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #76 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Can/Src/CAN.args" -o "Sources/SWC_BSW/BSW_Can/Src/CAN_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_Can/Src/%.d: ../Sources/SWC_BSW/BSW_Can/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF_c.obj: ../Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF.c
	@echo 'Building file: $<'
	@echo 'Executing target #77 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF.args" -o "Sources/SWC_BSW/BSW_Can/Src/CAN_CFG_SELF_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_Can/Src/CAN_INTC_c.obj: ../Sources/SWC_BSW/BSW_Can/Src/CAN_INTC.c
	@echo 'Building file: $<'
	@echo 'Executing target #78 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Can/Src/CAN_INTC.args" -o "Sources/SWC_BSW/BSW_Can/Src/CAN_INTC_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_Can/Src/CAN_STACK_c.obj: ../Sources/SWC_BSW/BSW_Can/Src/CAN_STACK.c
	@echo 'Building file: $<'
	@echo 'Executing target #79 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Can/Src/CAN_STACK.args" -o "Sources/SWC_BSW/BSW_Can/Src/CAN_STACK_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


