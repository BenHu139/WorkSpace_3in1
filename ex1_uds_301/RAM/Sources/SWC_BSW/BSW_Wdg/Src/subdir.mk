################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_Wdg/Src/SWdg.c" \
"../Sources/SWC_BSW/BSW_Wdg/Src/Wdg.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_Wdg/Src/SWdg.c \
../Sources/SWC_BSW/BSW_Wdg/Src/Wdg.c \

OBJS += \
./Sources/SWC_BSW/BSW_Wdg/Src/SWdg_c.obj \
./Sources/SWC_BSW/BSW_Wdg/Src/Wdg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_Wdg/Src/SWdg_c.obj" \
"./Sources/SWC_BSW/BSW_Wdg/Src/Wdg_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_Wdg/Src/SWdg_c.d \
./Sources/SWC_BSW/BSW_Wdg/Src/Wdg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_Wdg/Src/SWdg_c.obj \
./Sources/SWC_BSW/BSW_Wdg/Src/Wdg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_Wdg/Src/SWdg_c.d" \
"./Sources/SWC_BSW/BSW_Wdg/Src/Wdg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_Wdg/Src/SWdg_c.obj: ../Sources/SWC_BSW/BSW_Wdg/Src/SWdg.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Wdg/Src/SWdg.args" -o "Sources/SWC_BSW/BSW_Wdg/Src/SWdg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_Wdg/Src/%.d: ../Sources/SWC_BSW/BSW_Wdg/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_Wdg/Src/Wdg_c.obj: ../Sources/SWC_BSW/BSW_Wdg/Src/Wdg.c
	@echo 'Building file: $<'
	@echo 'Executing target #47 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_Wdg/Src/Wdg.args" -o "Sources/SWC_BSW/BSW_Wdg/Src/Wdg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


