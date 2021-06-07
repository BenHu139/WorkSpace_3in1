################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo.c" \
"../Sources/SWC_SWA/SWA_UDS/Common/bl_common.c" \
"../Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2.c" \
"../Sources/SWC_SWA/SWA_UDS/Common/bl_security.c" \
"../Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg.c" \
"../Sources/SWC_SWA/SWA_UDS/Common/security.c" \
"../Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle.c" \

C_SRCS += \
../Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo.c \
../Sources/SWC_SWA/SWA_UDS/Common/bl_common.c \
../Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2.c \
../Sources/SWC_SWA/SWA_UDS/Common/bl_security.c \
../Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg.c \
../Sources/SWC_SWA/SWA_UDS/Common/security.c \
../Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle.c \

OBJS += \
./Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/bl_common_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/bl_security_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/security_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_common_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_security_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Common/security_c.obj" \
"./Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle_c.obj" \

C_DEPS += \
./Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo_c.d \
./Sources/SWC_SWA/SWA_UDS/Common/bl_common_c.d \
./Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2_c.d \
./Sources/SWC_SWA/SWA_UDS/Common/bl_security_c.d \
./Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg_c.d \
./Sources/SWC_SWA/SWA_UDS/Common/security_c.d \
./Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/bl_common_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/bl_security_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/security_c.obj \
./Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_common_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_security_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Common/security_c.d" \
"./Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo_c.obj: ../Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo.args" -o "Sources/SWC_SWA/SWA_UDS/Common/bl_access_udsdemo_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Common/%.d: ../Sources/SWC_SWA/SWA_UDS/Common/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Common/bl_common_c.obj: ../Sources/SWC_SWA/SWA_UDS/Common/bl_common.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Common/bl_common.args" -o "Sources/SWC_SWA/SWA_UDS/Common/bl_common_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2_c.obj: ../Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2.args" -o "Sources/SWC_SWA/SWA_UDS/Common/bl_crc32_bzip2_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Common/bl_security_c.obj: ../Sources/SWC_SWA/SWA_UDS/Common/bl_security.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Common/bl_security.args" -o "Sources/SWC_SWA/SWA_UDS/Common/bl_security_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg_c.obj: ../Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg.args" -o "Sources/SWC_SWA/SWA_UDS/Common/bl_security_cfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Common/security_c.obj: ../Sources/SWC_SWA/SWA_UDS/Common/security.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Common/security.args" -o "Sources/SWC_SWA/SWA_UDS/Common/security_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle_c.obj: ../Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle.args" -o "Sources/SWC_SWA/SWA_UDS/Common/uds_main_schudle_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


