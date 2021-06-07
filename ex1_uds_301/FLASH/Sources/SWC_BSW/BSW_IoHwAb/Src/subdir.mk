################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb.c" \
"../Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb.c \
../Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L.c \

OBJS += \
./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_c.obj \
./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_c.obj" \
"./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_c.d \
./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_c.obj \
./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_c.d" \
"./Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_c.obj: ../Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb.c
	@echo 'Building file: $<'
	@echo 'Executing target #63 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb.args" -o "Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_IoHwAb/Src/%.d: ../Sources/SWC_BSW/BSW_IoHwAb/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L_c.obj: ../Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L.c
	@echo 'Building file: $<'
	@echo 'Executing target #64 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L.args" -o "Sources/SWC_BSW/BSW_IoHwAb/Src/IoHwAb_L_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


