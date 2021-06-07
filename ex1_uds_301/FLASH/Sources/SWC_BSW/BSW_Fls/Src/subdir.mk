################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_Fls/Src/DFls.c" \
"../Sources/SWC_BSW/BSW_Fls/Src/Fls.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_Fls/Src/DFls.c \
../Sources/SWC_BSW/BSW_Fls/Src/Fls.c \

OBJS += \
./Sources/SWC_BSW/BSW_Fls/Src/DFls_c.obj \
./Sources/SWC_BSW/BSW_Fls/Src/Fls_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_Fls/Src/DFls_c.obj" \
"./Sources/SWC_BSW/BSW_Fls/Src/Fls_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_Fls/Src/DFls_c.d \
./Sources/SWC_BSW/BSW_Fls/Src/Fls_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_Fls/Src/DFls_c.obj \
./Sources/SWC_BSW/BSW_Fls/Src/Fls_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_Fls/Src/DFls_c.d" \
"./Sources/SWC_BSW/BSW_Fls/Src/Fls_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_Fls/Src/DFls_c.obj: ../Sources/SWC_BSW/BSW_Fls/Src/DFls.c
	@echo 'Building file: $<'
	@echo 'Executing target #65 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Fls/Src/DFls.args" -o "Sources/SWC_BSW/BSW_Fls/Src/DFls_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_Fls/Src/%.d: ../Sources/SWC_BSW/BSW_Fls/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_Fls/Src/Fls_c.obj: ../Sources/SWC_BSW/BSW_Fls/Src/Fls.c
	@echo 'Building file: $<'
	@echo 'Executing target #66 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Fls/Src/Fls.args" -o "Sources/SWC_BSW/BSW_Fls/Src/Fls_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


