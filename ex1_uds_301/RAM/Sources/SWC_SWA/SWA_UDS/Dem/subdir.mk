################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_SWA/SWA_UDS/Dem/Dem.c" \
"../Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk.c" \
"../Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg.c" \

C_SRCS += \
../Sources/SWC_SWA/SWA_UDS/Dem/Dem.c \
../Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk.c \
../Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg.c \

OBJS += \
./Sources/SWC_SWA/SWA_UDS/Dem/Dem_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/Dem/Dem_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg_c.obj" \

C_DEPS += \
./Sources/SWC_SWA/SWA_UDS/Dem/Dem_c.d \
./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk_c.d \
./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_SWA/SWA_UDS/Dem/Dem_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/Dem/Dem_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_SWA/SWA_UDS/Dem/Dem_c.obj: ../Sources/SWC_SWA/SWA_UDS/Dem/Dem.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Dem/Dem.args" -o "Sources/SWC_SWA/SWA_UDS/Dem/Dem_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Dem/%.d: ../Sources/SWC_SWA/SWA_UDS/Dem/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk_c.obj: ../Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk.args" -o "Sources/SWC_SWA/SWA_UDS/Dem/Dem_Cbk_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg_c.obj: ../Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg.args" -o "Sources/SWC_SWA/SWA_UDS/Dem/Dem_Lcfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


