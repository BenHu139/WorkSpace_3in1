################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_SWA/SWA_FSM/Src/FSM.c" \
"../Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg.c" \

C_SRCS += \
../Sources/SWC_SWA/SWA_FSM/Src/FSM.c \
../Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg.c \

OBJS += \
./Sources/SWC_SWA/SWA_FSM/Src/FSM_c.obj \
./Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_SWA/SWA_FSM/Src/FSM_c.obj" \
"./Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg_c.obj" \

C_DEPS += \
./Sources/SWC_SWA/SWA_FSM/Src/FSM_c.d \
./Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_SWA/SWA_FSM/Src/FSM_c.obj \
./Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_SWA/SWA_FSM/Src/FSM_c.d" \
"./Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_SWA/SWA_FSM/Src/FSM_c.obj: ../Sources/SWC_SWA/SWA_FSM/Src/FSM.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_FSM/Src/FSM.args" -o "Sources/SWC_SWA/SWA_FSM/Src/FSM_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_FSM/Src/%.d: ../Sources/SWC_SWA/SWA_FSM/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg_c.obj: ../Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #40 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg.args" -o "Sources/SWC_SWA/SWA_FSM/Src/FSM_Cfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


