################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_SWA/SWA_UDS/CanTp/CanTp.c" \
"../Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg.c" \

C_SRCS += \
../Sources/SWC_SWA/SWA_UDS/CanTp/CanTp.c \
../Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg.c \

OBJS += \
./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_c.obj \
./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg_c.obj" \

C_DEPS += \
./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_c.d \
./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_c.obj \
./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_c.d" \
"./Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_c.obj: ../Sources/SWC_SWA/SWA_UDS/CanTp/CanTp.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/CanTp/CanTp.args" -o "Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/CanTp/%.d: ../Sources/SWC_SWA/SWA_UDS/CanTp/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg_c.obj: ../Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg.args" -o "Sources/SWC_SWA/SWA_UDS/CanTp/CanTp_PBCfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


