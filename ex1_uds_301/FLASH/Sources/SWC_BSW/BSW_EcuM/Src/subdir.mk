################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_EcuM/Src/EcuM.c" \
"../Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_EcuM/Src/EcuM.c \
../Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs.c \

OBJS += \
./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_c.obj \
./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_c.obj" \
"./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_c.d \
./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_c.obj \
./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_c.d" \
"./Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_EcuM/Src/EcuM_c.obj: ../Sources/SWC_BSW/BSW_EcuM/Src/EcuM.c
	@echo 'Building file: $<'
	@echo 'Executing target #67 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_EcuM/Src/EcuM.args" -o "Sources/SWC_BSW/BSW_EcuM/Src/EcuM_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_EcuM/Src/%.d: ../Sources/SWC_BSW/BSW_EcuM/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs_c.obj: ../Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs.c
	@echo 'Building file: $<'
	@echo 'Executing target #68 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs.args" -o "Sources/SWC_BSW/BSW_EcuM/Src/EcuM_Callouts_Stubs_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


