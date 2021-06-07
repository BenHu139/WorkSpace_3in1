################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_ScM/Src/ScM.c" \
"../Sources/SWC_BSW/BSW_ScM/Src/intc_software.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_ScM/Src/ScM.c \
../Sources/SWC_BSW/BSW_ScM/Src/intc_software.c \

OBJS += \
./Sources/SWC_BSW/BSW_ScM/Src/ScM_c.obj \
./Sources/SWC_BSW/BSW_ScM/Src/intc_software_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_ScM/Src/ScM_c.obj" \
"./Sources/SWC_BSW/BSW_ScM/Src/intc_software_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_ScM/Src/ScM_c.d \
./Sources/SWC_BSW/BSW_ScM/Src/intc_software_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_ScM/Src/ScM_c.obj \
./Sources/SWC_BSW/BSW_ScM/Src/intc_software_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_ScM/Src/ScM_c.d" \
"./Sources/SWC_BSW/BSW_ScM/Src/intc_software_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_ScM/Src/ScM_c.obj: ../Sources/SWC_BSW/BSW_ScM/Src/ScM.c
	@echo 'Building file: $<'
	@echo 'Executing target #54 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_ScM/Src/ScM.args" -o "Sources/SWC_BSW/BSW_ScM/Src/ScM_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_ScM/Src/%.d: ../Sources/SWC_BSW/BSW_ScM/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_ScM/Src/intc_software_c.obj: ../Sources/SWC_BSW/BSW_ScM/Src/intc_software.c
	@echo 'Building file: $<'
	@echo 'Executing target #55 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_ScM/Src/intc_software.args" -o "Sources/SWC_BSW/BSW_ScM/Src/intc_software_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


