################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_STB/Src/stdby.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_STB/Src/stdby.c \

OBJS += \
./Sources/SWC_BSW/BSW_STB/Src/stdby_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_STB/Src/stdby_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_STB/Src/stdby_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_STB/Src/stdby_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_STB/Src/stdby_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_STB/Src/stdby_c.obj: ../Sources/SWC_BSW/BSW_STB/Src/stdby.c
	@echo 'Building file: $<'
	@echo 'Executing target #56 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_STB/Src/stdby.args" -o "Sources/SWC_BSW/BSW_STB/Src/stdby_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_STB/Src/%.d: ../Sources/SWC_BSW/BSW_STB/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


