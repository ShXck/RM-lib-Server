################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/server_h/Encrypter.cpp \
../src/server_h/JSONHandler.cpp \
../src/server_h/Reader.cpp \
../src/server_h/Server.cpp 

OBJS += \
./src/server_h/Encrypter.o \
./src/server_h/JSONHandler.o \
./src/server_h/Reader.o \
./src/server_h/Server.o 

CPP_DEPS += \
./src/server_h/Encrypter.d \
./src/server_h/JSONHandler.d \
./src/server_h/Reader.d \
./src/server_h/Server.d 


# Each subdirectory must supply rules for building sources it contributes
src/server_h/%.o: ../src/server_h/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/marcelo/Documents/libs/rapidjson/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


