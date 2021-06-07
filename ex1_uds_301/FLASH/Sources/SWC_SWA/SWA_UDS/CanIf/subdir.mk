################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf.c" \
"../Sources/SWC_SWA/SWA_UDS/CanIf/CanIf.c" \
"../Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg.c" \

C_SRCS += \
../Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf.c \
../Sources/SWC_SWA/SWA_UDS/CanIf/CanIf.c \
../Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg.c \

OBJS += \
./Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf_c.obj \
./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_c.obj \
./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg_c.obj" \

C_DEPS += \
./Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf_c.d \
./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_c.d \
./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf_c.obj \
./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_c.obj \
./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf_c.d" \
"./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_c.d" \
"./Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf_c.obj: ../Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf.args" -o "Sources/SWC_SWA/SWA_UDS/CanIf/App_CanIf_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/CanIf/%.d: ../Sources/SWC_SWA/SWA_UDS/CanIf/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_c.obj: ../Sources/SWC_SWA/SWA_UDS/CanIf/CanIf.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/CanIf/CanIf.args" -o "Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg_c.obj: ../Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg.args" -o "Sources/SWC_SWA/SWA_UDS/CanIf/CanIf_Lcfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


