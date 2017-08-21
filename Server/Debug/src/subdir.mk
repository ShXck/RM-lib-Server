################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ModeSelector.cpp \
../src/error_handler.cpp \
../src/main.cpp \
../src/utility.cpp 

OBJS += \
./src/ModeSelector.o \
./src/error_handler.o \
./src/main.o \
./src/utility.o 

CPP_DEPS += \
./src/ModeSelector.d \
./src/error_handler.d \
./src/main.d \
./src/utility.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/marcelo/Documents/libs/rapidjson/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


