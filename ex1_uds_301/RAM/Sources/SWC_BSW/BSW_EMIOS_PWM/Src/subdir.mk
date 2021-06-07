################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM.c" \
"../Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM.c \
../Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg.c \

OBJS += \
./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_c.obj \
./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_c.obj" \
"./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_c.d \
./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_c.obj \
./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_c.d" \
"./Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_c.obj: ../Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM.c
	@echo 'Building file: $<'
	@echo 'Executing target #69 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM.args" -o "Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_EMIOS_PWM/Src/%.d: ../Sources/SWC_BSW/BSW_EMIOS_PWM/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg_c.obj: ../Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #70 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg.args" -o "Sources/SWC_BSW/BSW_EMIOS_PWM/Src/PWM_Cfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


