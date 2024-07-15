################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/APP.c" \
"../Sources/Events.c" \
"../Sources/main.c" \
"../Sources/timer.c" \

C_SRCS += \
../Sources/APP.c \
../Sources/Events.c \
../Sources/main.c \
../Sources/timer.c \

OBJS += \
./Sources/APP_c.obj \
./Sources/Events_c.obj \
./Sources/main_c.obj \
./Sources/timer_c.obj \

OBJS_QUOTED += \
"./Sources/APP_c.obj" \
"./Sources/Events_c.obj" \
"./Sources/main_c.obj" \
"./Sources/timer_c.obj" \

C_DEPS += \
./Sources/APP_c.d \
./Sources/Events_c.d \
./Sources/main_c.d \
./Sources/timer_c.d \

C_DEPS_QUOTED += \
"./Sources/APP_c.d" \
"./Sources/Events_c.d" \
"./Sources/main_c.d" \
"./Sources/timer_c.d" \

OBJS_OS_FORMAT += \
./Sources/APP_c.obj \
./Sources/Events_c.obj \
./Sources/main_c.obj \
./Sources/timer_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/APP_c.obj: ../Sources/APP.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/APP.args" -o "Sources/APP_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/Events.args" -o "Sources/Events_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/timer_c.obj: ../Sources/timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/timer.args" -o "Sources/timer_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


