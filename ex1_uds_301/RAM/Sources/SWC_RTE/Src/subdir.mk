################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_RTE/Src/Rte.c" \
"../Sources/SWC_RTE/Src/Rte_Data.c" \
"../Sources/SWC_RTE/Src/Rte_Def.c" \

C_SRCS += \
../Sources/SWC_RTE/Src/Rte.c \
../Sources/SWC_RTE/Src/Rte_Data.c \
../Sources/SWC_RTE/Src/Rte_Def.c \

OBJS += \
./Sources/SWC_RTE/Src/Rte_c.obj \
./Sources/SWC_RTE/Src/Rte_Data_c.obj \
./Sources/SWC_RTE/Src/Rte_Def_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_RTE/Src/Rte_c.obj" \
"./Sources/SWC_RTE/Src/Rte_Data_c.obj" \
"./Sources/SWC_RTE/Src/Rte_Def_c.obj" \

C_DEPS += \
./Sources/SWC_RTE/Src/Rte_c.d \
./Sources/SWC_RTE/Src/Rte_Data_c.d \
./Sources/SWC_RTE/Src/Rte_Def_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_RTE/Src/Rte_c.obj \
./Sources/SWC_RTE/Src/Rte_Data_c.obj \
./Sources/SWC_RTE/Src/Rte_Def_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_RTE/Src/Rte_c.d" \
"./Sources/SWC_RTE/Src/Rte_Data_c.d" \
"./Sources/SWC_RTE/Src/Rte_Def_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_RTE/Src/Rte_c.obj: ../Sources/SWC_RTE/Src/Rte.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_RTE/Src/Rte.args" -o "Sources/SWC_RTE/Src/Rte_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_RTE/Src/%.d: ../Sources/SWC_RTE/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_RTE/Src/Rte_Data_c.obj: ../Sources/SWC_RTE/Src/Rte_Data.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_RTE/Src/Rte_Data.args" -o "Sources/SWC_RTE/Src/Rte_Data_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_RTE/Src/Rte_Def_c.obj: ../Sources/SWC_RTE/Src/Rte_Def.c
	@echo 'Building file: $<'
	@echo 'Executing target #45 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_RTE/Src/Rte_Def.args" -o "Sources/SWC_RTE/Src/Rte_Def_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


