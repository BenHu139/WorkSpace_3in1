################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_E2PE/Src/CRC16.c" \
"../Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg.c" \
"../Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_E2PE/Src/CRC16.c \
../Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg.c \
../Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR.c \

OBJS += \
./Sources/SWC_BSW/BSW_E2PE/Src/CRC16_c.obj \
./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg_c.obj \
./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_E2PE/Src/CRC16_c.obj" \
"./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg_c.obj" \
"./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_E2PE/Src/CRC16_c.d \
./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg_c.d \
./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_E2PE/Src/CRC16_c.obj \
./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg_c.obj \
./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_E2PE/Src/CRC16_c.d" \
"./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg_c.d" \
"./Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_E2PE/Src/CRC16_c.obj: ../Sources/SWC_BSW/BSW_E2PE/Src/CRC16.c
	@echo 'Building file: $<'
	@echo 'Executing target #71 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_E2PE/Src/CRC16.args" -o "Sources/SWC_BSW/BSW_E2PE/Src/CRC16_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_E2PE/Src/%.d: ../Sources/SWC_BSW/BSW_E2PE/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg_c.obj: ../Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #72 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg.args" -o "Sources/SWC_BSW/BSW_E2PE/Src/E2PE_Cfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR_c.obj: ../Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR.c
	@echo 'Building file: $<'
	@echo 'Executing target #73 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR.args" -o "Sources/SWC_BSW/BSW_E2PE/Src/E2PE_MGR_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


