################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/SWC_BSW/BSW_UART/Src/Uart.c" \
"../Sources/SWC_BSW/BSW_UART/Src/Uart_Data.c" \
"../Sources/SWC_BSW/BSW_UART/Src/Uart_Drv.c" \
"../Sources/SWC_BSW/BSW_UART/Src/Uart_Trans.c" \
"../Sources/SWC_BSW/BSW_UART/Src/cmd_queue.c" \

C_SRCS += \
../Sources/SWC_BSW/BSW_UART/Src/Uart.c \
../Sources/SWC_BSW/BSW_UART/Src/Uart_Data.c \
../Sources/SWC_BSW/BSW_UART/Src/Uart_Drv.c \
../Sources/SWC_BSW/BSW_UART/Src/Uart_Trans.c \
../Sources/SWC_BSW/BSW_UART/Src/cmd_queue.c \

OBJS += \
./Sources/SWC_BSW/BSW_UART/Src/Uart_c.obj \
./Sources/SWC_BSW/BSW_UART/Src/Uart_Data_c.obj \
./Sources/SWC_BSW/BSW_UART/Src/Uart_Drv_c.obj \
./Sources/SWC_BSW/BSW_UART/Src/Uart_Trans_c.obj \
./Sources/SWC_BSW/BSW_UART/Src/cmd_queue_c.obj \

OBJS_QUOTED += \
"./Sources/SWC_BSW/BSW_UART/Src/Uart_c.obj" \
"./Sources/SWC_BSW/BSW_UART/Src/Uart_Data_c.obj" \
"./Sources/SWC_BSW/BSW_UART/Src/Uart_Drv_c.obj" \
"./Sources/SWC_BSW/BSW_UART/Src/Uart_Trans_c.obj" \
"./Sources/SWC_BSW/BSW_UART/Src/cmd_queue_c.obj" \

C_DEPS += \
./Sources/SWC_BSW/BSW_UART/Src/Uart_c.d \
./Sources/SWC_BSW/BSW_UART/Src/Uart_Data_c.d \
./Sources/SWC_BSW/BSW_UART/Src/Uart_Drv_c.d \
./Sources/SWC_BSW/BSW_UART/Src/Uart_Trans_c.d \
./Sources/SWC_BSW/BSW_UART/Src/cmd_queue_c.d \

OBJS_OS_FORMAT += \
./Sources/SWC_BSW/BSW_UART/Src/Uart_c.obj \
./Sources/SWC_BSW/BSW_UART/Src/Uart_Data_c.obj \
./Sources/SWC_BSW/BSW_UART/Src/Uart_Drv_c.obj \
./Sources/SWC_BSW/BSW_UART/Src/Uart_Trans_c.obj \
./Sources/SWC_BSW/BSW_UART/Src/cmd_queue_c.obj \

C_DEPS_QUOTED += \
"./Sources/SWC_BSW/BSW_UART/Src/Uart_c.d" \
"./Sources/SWC_BSW/BSW_UART/Src/Uart_Data_c.d" \
"./Sources/SWC_BSW/BSW_UART/Src/Uart_Drv_c.d" \
"./Sources/SWC_BSW/BSW_UART/Src/Uart_Trans_c.d" \
"./Sources/SWC_BSW/BSW_UART/Src/cmd_queue_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/SWC_BSW/BSW_UART/Src/Uart_c.obj: ../Sources/SWC_BSW/BSW_UART/Src/Uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #49 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_UART/Src/Uart.args" -o "Sources/SWC_BSW/BSW_UART/Src/Uart_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_UART/Src/%.d: ../Sources/SWC_BSW/BSW_UART/Src/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SWC_BSW/BSW_UART/Src/Uart_Data_c.obj: ../Sources/SWC_BSW/BSW_UART/Src/Uart_Data.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_UART/Src/Uart_Data.args" -o "Sources/SWC_BSW/BSW_UART/Src/Uart_Data_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_UART/Src/Uart_Drv_c.obj: ../Sources/SWC_BSW/BSW_UART/Src/Uart_Drv.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_UART/Src/Uart_Drv.args" -o "Sources/SWC_BSW/BSW_UART/Src/Uart_Drv_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_UART/Src/Uart_Trans_c.obj: ../Sources/SWC_BSW/BSW_UART/Src/Uart_Trans.c
	@echo 'Building file: $<'
	@echo 'Executing target #52 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_UART/Src/Uart_Trans.args" -o "Sources/SWC_BSW/BSW_UART/Src/Uart_Trans_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/SWC_BSW/BSW_UART/Src/cmd_queue_c.obj: ../Sources/SWC_BSW/BSW_UART/Src/cmd_queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #53 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/SWC_BSW/BSW_UART/Src/cmd_queue.args" -o "Sources/SWC_BSW/BSW_UART/Src/cmd_queue_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


