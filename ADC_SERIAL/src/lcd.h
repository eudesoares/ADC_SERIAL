/*
 * lcd.h
 *
 * Created: 6/11/2017 7:07:16 PM
 *  Author: dinho
 */ 

#ifndef LCD_H_
#define LCD_H_
#define EN				PORT_PB04
#define RS				PORT_PB05
#define EN_ON			port_pin_set_output_level(EN,1)
#define EN_OFF			port_pin_set_output_level(EN,0)
#define RS_ON			port_pin_set_output_level(RS,1)
#define RS_OFF			port_pin_set_output_level(RS,0)
#define	PDADOS			PORTB
#define CURSOR_PISCA_F  0x0D
#define CURSOR_OFF      0x0C
#define CURSOR_ON       0x0E
#define CLEAR_DISPLAY   0x01
#define	CURSOR_INC      0x02
#define	CURSOR_DEC      0x00

void send_byte(char BYTE);
void lcd_init();
void lcd_putc(char dado);
void lcd_print(char* dado[]);
void lcd_cmd(char  instrucao);
void lcd_goto(char y, char x);


void send_byte(char BYTE){
	PDADOS= (((BYTE>>4)&0x0F)|(PDADOS&0xF0));
	EN_ON;
	cpu_delay_us(45);
	EN_OFF;
	PDADOS= (BYTE&0x0F)|(PDADOS&0xF0);
	EN_ON;
	cpu_delay_us(45);
	EN_OFF;
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////Executa os passos para a inicialização do display////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void lcd_init(){
	struct port_config config_port;
	config_port.direction = PORT_PIN_DIR_OUTPUT;
	port_group_set_config(PORTB,0xFF,config_port);
	EN_OFF;
	RS_OFF;
	cpu_delay_ms(15);
	PDADOS=0b00000011;
	EN_ON;
	cpu_delay_us(5400);
	EN_OFF;
	PDADOS=0b00000011;
	EN_ON;
	cpu_delay_us(5400);
	EN_OFF;
	PDADOS=0b00000011;
	EN_ON;
	cpu_delay_us(5400);
	EN_OFF;
	PDADOS=0b00000010;
	EN_ON;
	cpu_delay_us(5400);
	EN_OFF;
	send_byte(CURSOR_PISCA_F );    //Seta o cursor
	EN_OFF;
	send_byte(0x28);    //Define o numero de linhas e a fonte
}
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////Envia uma string para o display lcd, caracteres um a um///////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void lcd_print(char* dado[]){
	int i=0;
	RS=1;
	while(dado[i]!='\0'){
		send_byte(dado[i]);
		i++;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////Converte char em uma sequencia de char a partir do valor decimal////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void lcd_print_val(char valor){
	char data[3]="000\0";
	data[1]=valor/10+'0';
	data[2]=valor%10+'0';
	lcd_print(data);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Envia apenas um caractere para o lcd////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void lcd_putc(char dado){
	int i=0;
	RS=1;
	send_byte(dado);
}
///////////////////////////////////////////////////////////////////////////////////////////
/////////Envia um comando para o display, como o deslocamento e o tipo de cursor///////////
///////////////////////////////////////////////////////////////////////////////////////////
void lcd_cmd(char  instrucao){
	RS=0;
	send_byte(instrucao);
}
///////////////////////////////////////////////////////////////////////////////////////////
/////////////Posiciona o cursor no display para inserir um novo caractere//////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void lcd_goto(char y, char x){
	if(y==0)
	lcd_cmd(0x80+x);
	else
	lcd_cmd(0xC0+x);
}


#endif /* LCD_H_ */