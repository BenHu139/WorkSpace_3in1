################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN.c \

OBJS += \
./Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN_c.obj: ../Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #48 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN.args" -o "Sources/SWC_BSW/BSW_Uds/Src/UDS_CAN_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_Uds/Src/%.d: ../Sources/SWC_BSW/BSW_Uds/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


