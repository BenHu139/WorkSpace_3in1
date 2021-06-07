################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 90
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Sources/SWC_SWA/SWA_VER/Src/subdir.mk
-include Sources/SWC_SWA/SWA_UDS/Nvm/subdir.mk
-include Sources/SWC_SWA/SWA_UDS/Det/subdir.mk
-include Sources/SWC_SWA/SWA_UDS/Dem/subdir.mk
-include Sources/SWC_SWA/SWA_UDS/Debug/Src/subdir.mk
-include Sources/SWC_SWA/SWA_UDS/Dcm/subdir.mk
-include Sources/SWC_SWA/SWA_UDS/Common/subdir.mk
-include Sources/SWC_SWA/SWA_UDS/CanTp/subdir.mk
-include Sources/SWC_SWA/SWA_UDS/CanIf/subdir.mk
-include Sources/SWC_SWA/SWA_TMR/Src/subdir.mk
-include Sources/SWC_SWA/SWA_TCM/Src/subdir.mk
-include Sources/SWC_SWA/SWA_ST/Src/subdir.mk
-include Sources/SWC_SWA/SWA_SAM/Src/subdir.mk
-include Sources/SWC_SWA/SWA_OSM/Src/subdir.mk
-include Sources/SWC_SWA/SWA_MSM/Src/subdir.mk
-include Sources/SWC_SWA/SWA_FSM/Src/subdir.mk
-include Sources/SWC_SWA/SWA_DSM/Src/subdir.mk
-include Sources/SWC_SWA/SWA_BT/Src/subdir.mk
-include Sources/SWC_RTE/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Wdg/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Uds/Src/subdir.mk
-include Sources/SWC_BSW/BSW_UART/Src/subdir.mk
-include Sources/SWC_BSW/BSW_ScM/Src/subdir.mk
-include Sources/SWC_BSW/BSW_STB/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Rtc/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Port/Src/subdir.mk
-include Sources/SWC_BSW/BSW_PIT/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Mcu/Src/subdir.mk
-include Sources/SWC_BSW/BSW_IoHwAb/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Fls/Src/subdir.mk
-include Sources/SWC_BSW/BSW_EcuM/Src/subdir.mk
-include Sources/SWC_BSW/BSW_EMIOS_PWM/Src/subdir.mk
-include Sources/SWC_BSW/BSW_E2PE/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Dio/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Can/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Calibration/Src/subdir.mk
-include Sources/SWC_BSW/BSW_BOF/Src/subdir.mk
-include Sources/SWC_BSW/BSW_Adc/Src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
STATICLIB += \

STATICLIB_QUOTED += \

STATICLIB_OS_FORMAT += \

EXECUTABLES += \

EXECUTABLES_QUOTED += \

EXECUTABLES_OS_FORMAT += \


# All Target
all: warning-messages explicit-dependencies ex1_uds_102.elf

# Tool invocations
ex1_uds_102.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/MPC5602B_RAM.lcf
	@echo 'Building target: $@'
	@echo 'Executing target #91 $@'
	@echo 'Invoking: PowerPC Linker'
	"$(PAToolsDirEnv)/mwldeppc" -o "ex1_uds_102.elf" @@"ex1_uds_102.args"  $(USER_OBJS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(STATICLIB_QUOTED) "./*/*/*.obj" "./*/*/*/*/*.obj" "./*/*/*/*.obj" "./*/*/*/*/*/*.obj" "./*/*.obj"  $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) $(S_UPPER_DEPS_QUOTED) $(CXX_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(C++_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*/*.d" "./*/*/*/*/*.d" "./*/*/*/*.d" "./*/*/*/*/*/*.d" "./*/*.d"  $(ProjDirPath)/RAM/ex1_uds_102.elf
	-@echo ' '

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/MPC5602B_RAM.lcf 

warning-messages: 

