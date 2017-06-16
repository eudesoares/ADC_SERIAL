/*
 * setup_function.h
 *
 * Created: 6/7/2017 11:02:33 PM
 *  Author: Eude Soares
 */ 


#ifndef SETUP_FUNCTION_H_
#define SETUP_FUNCTION_H_

void setup_adc(void);
void setup_UART(void);
void UART_print(const char *msg);
void adc_complete_callback(const struct adc_module *const module);

#define ADC_SAMPLES 1
uint16_t adc_result_buffer[ADC_SAMPLES];
struct adc_module adc_instance;

void setup_adc(){

	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	config_adc.clock_source = GCLK_GENERATOR_0;
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV512;
	config_adc.reference = ADC_REFERENCE_INTVCC1;
	config_adc.positive_input = ADC_POSITIVE_INPUT_PIN4;
	config_adc.negative_input=ADC_NEGATIVE_INPUT_GND;
	config_adc.resolution = ADC_RESOLUTION_16BIT;
	config_adc.reference_compensation_enable = true;
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);

	adc_register_callback(&adc_instance, adc_complete_callback, ADC_CALLBACK_READ_BUFFER);
	adc_enable_callback(&adc_instance, ADC_CALLBACK_READ_BUFFER);
	adc_start_conversion(&adc_instance);
}

struct usart_module usart_instance;
void setup_UART(){
	
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate = 9600;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	while (usart_init(&usart_instance,
	EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	}
	usart_enable(&usart_instance);
}
void UART_print(const char *msg){
	uint8_t size=0;
	while(msg[size++]!=0);
	usart_write_buffer_job(&usart_instance,(uint8_t *)msg,size);
}
#endif /* SETUP_FUNCTION_H_ */