################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Settings/Startup_Code/MPC5602B_HWInit.c" \
"../Project_Settings/Startup_Code/MPC5602B_Startup.c" \
"../Project_Settings/Startup_Code/MPC5602B_init_flash.c" \
"../Project_Settings/Startup_Code/__ppc_eabi_init.c" \

C_SRCS += \
../Project_Settings/Startup_Code/MPC5602B_HWInit.c \
../Project_Settings/Startup_Code/MPC5602B_Startup.c \
../Project_Settings/Startup_Code/MPC5602B_init_flash.c \
../Project_Settings/Startup_Code/__ppc_eabi_init.c \

OBJS += \
./Project_Settings/Startup_Code/MPC5602B_HWInit_c.obj \
./Project_Settings/Startup_Code/MPC5602B_Startup_c.obj \
./Project_Settings/Startup_Code/MPC5602B_init_flash_c.obj \
./Project_Settings/Startup_Code/__ppc_eabi_init_c.obj \

OBJS_QUOTED += \
"./Project_Settings/Startup_Code/MPC5602B_HWInit_c.obj" \
"./Project_Settings/Startup_Code/MPC5602B_Startup_c.obj" \
"./Project_Settings/Startup_Code/MPC5602B_init_flash_c.obj" \
"./Project_Settings/Startup_Code/__ppc_eabi_init_c.obj" \

C_DEPS += \
./Project_Settings/Startup_Code/MPC5602B_HWInit_c.d \
./Project_Settings/Startup_Code/MPC5602B_Startup_c.d \
./Project_Settings/Startup_Code/MPC5602B_init_flash_c.d \
./Project_Settings/Startup_Code/__ppc_eabi_init_c.d \

OBJS_OS_FORMAT += \
./Project_Settings/Startup_Code/MPC5602B_HWInit_c.obj \
./Project_Settings/Startup_Code/MPC5602B_Startup_c.obj \
./Project_Settings/Startup_Code/MPC5602B_init_flash_c.obj \
./Project_Settings/Startup_Code/__ppc_eabi_init_c.obj \

C_DEPS_QUOTED += \
"./Project_Settings/Startup_Code/MPC5602B_HWInit_c.d" \
"./Project_Settings/Startup_Code/MPC5602B_Startup_c.d" \
"./Project_Settings/Startup_Code/MPC5602B_init_flash_c.d" \
"./Project_Settings/Startup_Code/__ppc_eabi_init_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/MPC5602B_HWInit_c.obj: ../Project_Settings/Startup_Code/MPC5602B_HWInit.c
	@echo 'Building file: $<'
	@echo 'Executing target #87 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Project_Settings/Startup_Code/MPC5602B_HWInit.args" -o "Project_Settings/Startup_Code/MPC5602B_HWInit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/%.d: ../Project_Settings/Startup_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Project_Settings/Startup_Code/MPC5602B_Startup_c.obj: ../Project_Settings/Startup_Code/MPC5602B_Startup.c
	@echo 'Building file: $<'
	@echo 'Executing target #88 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Project_Settings/Startup_Code/MPC5602B_Startup.args" -o "Project_Settings/Startup_Code/MPC5602B_Startup_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/MPC5602B_init_flash_c.obj: ../Project_Settings/Startup_Code/MPC5602B_init_flash.c
	@echo 'Building file: $<'
	@echo 'Executing target #89 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Project_Settings/Startup_Code/MPC5602B_init_flash.args" -o "Project_Settings/Startup_Code/MPC5602B_init_flash_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/__ppc_eabi_init_c.obj: ../Project_Settings/Startup_Code/__ppc_eabi_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #90 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Project_Settings/Startup_Code/__ppc_eabi_init.args" -o "Project_Settings/Startup_Code/__ppc_eabi_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


