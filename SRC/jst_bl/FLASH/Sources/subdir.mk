################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/API.c" \
"../Sources/BL.c" \
"../Sources/CI2C1.c" \
"../Sources/Cpu.c" \
"../Sources/Events.c" \
"../Sources/IFsh1.c" \
"../Sources/InpB1.c" \
"../Sources/Vectors.c" \
"../Sources/WDog1.c" \
"../Sources/main.c" \
"../Sources/timer.c" \

ASM_SRCS += \
../Sources/asm_main.asm \

C_SRCS += \
../Sources/API.c \
../Sources/BL.c \
../Sources/CI2C1.c \
../Sources/Cpu.c \
../Sources/Events.c \
../Sources/IFsh1.c \
../Sources/InpB1.c \
../Sources/Vectors.c \
../Sources/WDog1.c \
../Sources/main.c \
../Sources/timer.c \

ASM_SRCS_QUOTED += \
"../Sources/asm_main.asm" \

OBJS += \
./Sources/API_c.obj \
./Sources/BL_c.obj \
./Sources/CI2C1_c.obj \
./Sources/Cpu_c.obj \
./Sources/Events_c.obj \
./Sources/IFsh1_c.obj \
./Sources/InpB1_c.obj \
./Sources/Vectors_c.obj \
./Sources/WDog1_c.obj \
./Sources/asm_main_asm.obj \
./Sources/main_c.obj \
./Sources/timer_c.obj \

ASM_DEPS += \
./Sources/asm_main_asm.d \

OBJS_QUOTED += \
"./Sources/API_c.obj" \
"./Sources/BL_c.obj" \
"./Sources/CI2C1_c.obj" \
"./Sources/Cpu_c.obj" \
"./Sources/Events_c.obj" \
"./Sources/IFsh1_c.obj" \
"./Sources/InpB1_c.obj" \
"./Sources/Vectors_c.obj" \
"./Sources/WDog1_c.obj" \
"./Sources/asm_main_asm.obj" \
"./Sources/main_c.obj" \
"./Sources/timer_c.obj" \

C_DEPS += \
./Sources/API_c.d \
./Sources/BL_c.d \
./Sources/CI2C1_c.d \
./Sources/Cpu_c.d \
./Sources/Events_c.d \
./Sources/IFsh1_c.d \
./Sources/InpB1_c.d \
./Sources/Vectors_c.d \
./Sources/WDog1_c.d \
./Sources/main_c.d \
./Sources/timer_c.d \

ASM_DEPS_QUOTED += \
"./Sources/asm_main_asm.d" \

C_DEPS_QUOTED += \
"./Sources/API_c.d" \
"./Sources/BL_c.d" \
"./Sources/CI2C1_c.d" \
"./Sources/Cpu_c.d" \
"./Sources/Events_c.d" \
"./Sources/IFsh1_c.d" \
"./Sources/InpB1_c.d" \
"./Sources/Vectors_c.d" \
"./Sources/WDog1_c.d" \
"./Sources/main_c.d" \
"./Sources/timer_c.d" \

OBJS_OS_FORMAT += \
./Sources/API_c.obj \
./Sources/BL_c.obj \
./Sources/CI2C1_c.obj \
./Sources/Cpu_c.obj \
./Sources/Events_c.obj \
./Sources/IFsh1_c.obj \
./Sources/InpB1_c.obj \
./Sources/Vectors_c.obj \
./Sources/WDog1_c.obj \
./Sources/asm_main_asm.obj \
./Sources/main_c.obj \
./Sources/timer_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/API_c.obj: ../Sources/API.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/API.args" -o "Sources/API_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/BL_c.obj: ../Sources/BL.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/BL.args" -o "Sources/BL_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/CI2C1_c.obj: ../Sources/CI2C1.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/CI2C1.args" -o "Sources/CI2C1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Cpu_c.obj: ../Sources/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/Cpu.args" -o "Sources/Cpu_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/Events.args" -o "Sources/Events_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/IFsh1_c.obj: ../Sources/IFsh1.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/IFsh1.args" -o "Sources/IFsh1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/InpB1_c.obj: ../Sources/InpB1.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/InpB1.args" -o "Sources/InpB1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Vectors_c.obj: ../Sources/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/Vectors.args" -o "Sources/Vectors_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/WDog1_c.obj: ../Sources/WDog1.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/WDog1.args" -o "Sources/WDog1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/asm_main_asm.obj: ../Sources/asm_main.asm
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: S12Z Assembler'
	"$(S12Z_ToolsDirEnv)/as12lisa" -ArgFile"Sources/asm_main.args" -Objn"Sources/asm_main_asm.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.asm
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/timer_c.obj: ../Sources/timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/timer.args" -o "Sources/timer_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


