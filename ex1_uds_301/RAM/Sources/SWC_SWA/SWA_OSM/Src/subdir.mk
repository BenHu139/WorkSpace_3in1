################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_SWA/SWA_OSM/Src/OSM.c" \
"../Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg.c" \

C_SRCS += \
../Sources/SWC_SWA/SWA_OSM/Src/OSM.c \
../Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg.c \

OBJS += \
./Sources/SWC_SWA/SWA_OSM/Src/OSM_c.obj \
./Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_SWA/SWA_OSM/Src/OSM_c.obj" \
"./Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg_c.obj" \

C_DEPS += \
./Sources/SWC_SWA/SWA_OSM/Src/OSM_c.d \
./Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_SWA/SWA_OSM/Src/OSM_c.obj \
./Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_SWA/SWA_OSM/Src/OSM_c.d" \
"./Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_SWA/SWA_OSM/Src/OSM_c.obj: ../Sources/SWC_SWA/SWA_OSM/Src/OSM.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_OSM/Src/OSM.args" -o "Sources/SWC_SWA/SWA_OSM/Src/OSM_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_SWA/SWA_OSM/Src/%.d: ../Sources/SWC_SWA/SWA_OSM/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg_c.obj: ../Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg.args" -o "Sources/SWC_SWA/SWA_OSM/Src/OSM_Cfg_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


