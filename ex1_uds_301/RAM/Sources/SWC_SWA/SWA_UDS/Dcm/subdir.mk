################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm.c" \
"../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm.c" \
"../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk.c" \
"../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg.c" \
"../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg.c" \

C_SRCS += \
../Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm.c \
../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm.c \
../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk.c \
../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg.c \
../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg.c \

OBJS += \
./Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg_c.obj" \

C_DEPS += \
./Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm_c.d \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_c.d \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk_c.d \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg_c.d \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg_c.obj \
./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm_c.obj: ../Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm.args" -o "Sources/SWC_SWA/SWA_UDS/Dcm/App_Dcm_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Dcm/%.d: ../Sources/SWC_SWA/SWA_UDS/Dcm/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_c.obj: ../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Dcm/Dcm.args" -o "Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk_c.obj: ../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk.args" -o "Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cbk_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg_c.obj: ../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg.args" -o "Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Cfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg_c.obj: ../Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg.args" -o "Sources/SWC_SWA/SWA_UDS/Dcm/Dcm_Lcfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


