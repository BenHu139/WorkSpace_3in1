################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_Mcu/Src/Mcu.c" \
"../Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_Mcu/Src/Mcu.c \
../Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg.c \

OBJS += \
./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_c.obj \
./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_c.obj" \
"./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_c.d \
./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_c.obj \
./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_c.d" \
"./Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_Mcu/Src/Mcu_c.obj: ../Sources/SWC_BSW/BSW_Mcu/Src/Mcu.c
	@echo 'Building file: $<'
	@echo 'Executing target #61 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Mcu/Src/Mcu.args" -o "Sources/SWC_BSW/BSW_Mcu/Src/Mcu_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_Mcu/Src/%.d: ../Sources/SWC_BSW/BSW_Mcu/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg_c.obj: ../Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #62 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg.args" -o "Sources/SWC_BSW/BSW_Mcu/Src/Mcu_Cfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


