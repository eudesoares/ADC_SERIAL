/* Configuraçoes de comunicação Serial e Leitura do ADC
   O ADC esta configurado para o pino PB4 com referencia GND.
   A serial está configurada com baud 9600

*/
#include <asf.h>
#include <setup_function.h>

//Variáves globais
uint16_t result=20;

/*Função chamada quando a interrupção ADC acontece. Responsavel por:
		leitura do ADC
		Composição do valor lido
		Escrita na serial
 */
void adc_complete_callback(const struct adc_module *const module)
{
	adc_read_buffer_job(&adc_instance, adc_result_buffer, 1);
	uint8_t valor[6];
	valor[5]='\n';
	valor[0]=adc_result_buffer[0]/10000+'0';
	valor[1]=(adc_result_buffer[0]%10000)/1000+'0';
	valor[2]=(adc_result_buffer[0]%1000)/100+'0';
	valor[3]=(adc_result_buffer[0]%100)/10+'0';
	valor[4]=(adc_result_buffer[0]%10)+'0';
	usart_write_buffer_job(&usart_instance,valor,6);
}

int main (void)
{ 		
	system_init();
	setup_adc();
	setup_UART();
	system_interrupt_enable_global();
	adc_read_buffer_job(&adc_instance, adc_result_buffer, 1);
	while (1) {
	}
}
