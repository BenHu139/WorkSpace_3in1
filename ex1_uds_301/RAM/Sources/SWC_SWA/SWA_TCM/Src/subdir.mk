################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_SWA/SWA_TCM/Src/TCM.c" \

C_SRCS += \
../Sources/SWC_SWA/SWA_TCM/Src/TCM.c \

OBJS += \
./Sources/SWC_SWA/SWA_TCM/Src/TCM_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_SWA/SWA_TCM/Src/TCM_c.obj" \

C_DEPS += \
./Sources/SWC_SWA/SWA_TCM/Src/TCM_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_SWA/SWA_TCM/Src/TCM_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_SWA/SWA_TCM/Src/TCM_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_SWA/SWA_TCM/Src/TCM_c.obj: ../Sources/SWC_SWA/SWA_TCM/Src/TCM.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_TCM/Src/TCM.args" -o "Sources/SWC_SWA/SWA_TCM/Src/TCM_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_TCM/Src/%.d: ../Sources/SWC_SWA/SWA_TCM/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


