################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Adafruit_GFX.obj: ../Adafruit_GFX.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=fpalib --abi=eabi -me -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" -g --gcc --define=ccs --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --printf_support=full --preproc_with_compile --preproc_dependency="Adafruit_GFX.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_OLED.obj: ../Adafruit_OLED.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=fpalib --abi=eabi -me -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" -g --gcc --define=ccs --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --printf_support=full --preproc_with_compile --preproc_dependency="Adafruit_OLED.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=fpalib --abi=eabi -me -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" -g --gcc --define=ccs --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --printf_support=full --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pinmux.obj: ../pinmux.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=fpalib --abi=eabi -me -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" -g --gcc --define=ccs --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --printf_support=full --preproc_with_compile --preproc_dependency="pinmux.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=fpalib --abi=eabi -me -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" -g --gcc --define=ccs --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --printf_support=full --preproc_with_compile --preproc_dependency="startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

test.obj: ../test.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=fpalib --abi=eabi -me -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" -g --gcc --define=ccs --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --printf_support=full --preproc_with_compile --preproc_dependency="test.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_if.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/uart_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=fpalib --abi=eabi -me -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc/" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" -g --gcc --define=ccs --define=cc3200 --diag_wrap=off --diag_warning=225 --display_error_number --printf_support=full --preproc_with_compile --preproc_dependency="uart_if.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


