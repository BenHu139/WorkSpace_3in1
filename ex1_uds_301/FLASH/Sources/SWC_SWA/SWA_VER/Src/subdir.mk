################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_SWA/SWA_VER/Src/VERSION.c" \

C_SRCS += \
../Sources/SWC_SWA/SWA_VER/Src/VERSION.c \

OBJS += \
./Sources/SWC_SWA/SWA_VER/Src/VERSION_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_SWA/SWA_VER/Src/VERSION_c.obj" \

C_DEPS += \
./Sources/SWC_SWA/SWA_VER/Src/VERSION_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_SWA/SWA_VER/Src/VERSION_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_SWA/SWA_VER/Src/VERSION_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_SWA/SWA_VER/Src/VERSION_c.obj: ../Sources/SWC_SWA/SWA_VER/Src/VERSION.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_VER/Src/VERSION.args" -o "Sources/SWC_SWA/SWA_VER/Src/VERSION_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_VER/Src/%.d: ../Sources/SWC_SWA/SWA_VER/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


