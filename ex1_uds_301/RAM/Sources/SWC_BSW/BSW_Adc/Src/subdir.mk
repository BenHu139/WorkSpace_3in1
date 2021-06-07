################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_Adc/Src/Adc.c" \
"../Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_Adc/Src/Adc.c \
../Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg.c \

OBJS += \
./Sources/SWC_BSW/BSW_Adc/Src/Adc_c.obj \
./Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_Adc/Src/Adc_c.obj" \
"./Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_Adc/Src/Adc_c.d \
./Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_Adc/Src/Adc_c.obj \
./Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_Adc/Src/Adc_c.d" \
"./Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_Adc/Src/Adc_c.obj: ../Sources/SWC_BSW/BSW_Adc/Src/Adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #85 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Adc/Src/Adc.args" -o "Sources/SWC_BSW/BSW_Adc/Src/Adc_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_Adc/Src/%.d: ../Sources/SWC_BSW/BSW_Adc/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg_c.obj: ../Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #86 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg.args" -o "Sources/SWC_BSW/BSW_Adc/Src/Adc_Cfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


