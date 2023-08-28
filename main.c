/*
 * RTC.c
 *
 * Created: 17-Aug-22 4:05:18 PM
 * Author : Mohamed Sherif
 */ 

#include "MCAL/Timer.h"
#include "HAL/LCD.h"
#include "HAL/Keypad.h"
#include "HAL/_7seg.h"
#include "LIB/std_macros.h"

volatile unsigned char sec=0;

int main(void)
{
	char i,val,dg1,dg2,min=0,hr=0;
    LCD_vinit();
	LCD_vsend_string("Press 0");
	LCD_vmove_cursor(2,1);
	LCD_vsend_string("To Set the Clock.");
	Keypad_vinit();
	_7seg_vinit('B');
	for(i=0;i<=5;i++)SET_BIT(DDRC,i);
	_7seg_vwrite('B',0);
	Timer2_OVF_Interrupt();
    while (1) 
    {
		val=Keypad_u8read();
		if(val!=NOT_PRESSED){
			if(val=='0'){
				
				l1:
				LCD_vCLR_screen();
				LCD_vsend_string("Hours=--");
				_delay_ms(300);
				
				do{
					dg1=Keypad_u8read();
				}while(dg1==NOT_PRESSED);
				LCD_vmove_cursor(1,7);
				LCD_vsend_char(dg1);
				_delay_ms(300);
				if(dg1=='+' || dg1=='-' || dg1=='*' || dg1=='/' || dg1=='='){
					LCD_vCLR_screen();
					LCD_vsend_string("Invalid Char!");
					_delay_ms(1000);
					goto l1;
				}
				
				do{
					dg2=Keypad_u8read();
				}while(dg2==NOT_PRESSED);
				LCD_vmove_cursor(1,8);
				LCD_vsend_char(dg2);
				_delay_ms(300);
				if(dg2=='+' || dg2=='-' || dg2=='*' || dg2=='/' || dg2=='='){
					LCD_vCLR_screen();
					LCD_vsend_string("Invalid Char!");
					_delay_ms(1000);
					goto l1;
				}
				
				hr=(dg1-48)*10+(dg2-48); //Store Inserted Hours
				if(hr>=24){
					LCD_vCLR_screen();
					LCD_vsend_string("Invalid Number!");
					LCD_vmove_cursor(2,1);
					LCD_vsend_string("**Hours<24**");
					_delay_ms(1000);
					goto l1;
				}
				
				l2:
				LCD_vCLR_screen();
				LCD_vsend_string("Minutes=--");
				do{
					dg1=Keypad_u8read();
				}while(dg1==NOT_PRESSED);
				LCD_vmove_cursor(1,9);
				LCD_vsend_char(dg1);
				_delay_ms(300);
				if(dg1=='+' || dg1=='-' || dg1=='*' || dg1=='/' || dg1=='='){
					LCD_vCLR_screen();
					LCD_vsend_string("Invalid Char!");
					_delay_ms(1000);
					goto l2;
				}
				
				do{
					dg2=Keypad_u8read();
				}while(dg2==NOT_PRESSED);
				LCD_vmove_cursor(1,10);
				LCD_vsend_char(dg2);
				_delay_ms(300);
				if(dg2=='+' || dg2=='-' || dg2=='*' || dg2=='/' || dg2=='='){
					LCD_vCLR_screen();
					LCD_vsend_string("Invalid Char!");
					_delay_ms(1000);
					goto l2;
				}
				
				min=(dg1-48)*10+(dg2-48); //Store Inserted Minutes
				if(min>=60){
					LCD_vCLR_screen();
					LCD_vsend_string("Invalid Number!");
					LCD_vmove_cursor(2,1);
					LCD_vsend_string("**Minutes<60**");
					_delay_ms(1000);
					goto l2;
				}
				
				l3:
				LCD_vCLR_screen();
				LCD_vsend_string("Seconds=--");
				do{
					dg1=Keypad_u8read();
				}while(dg1==NOT_PRESSED);
				LCD_vmove_cursor(1,9);
				LCD_vsend_char(dg1);
				_delay_ms(300);
				if(dg1=='+' || dg1=='-' || dg1=='*' || dg1=='/' || dg1=='='){
					LCD_vCLR_screen();
					LCD_vsend_string("Invalid Char!");
					_delay_ms(1000);
					goto l3;
				}
				
				do{
					dg2=Keypad_u8read();
				}while(dg2==NOT_PRESSED);
				LCD_vmove_cursor(1,10);
				LCD_vsend_char(dg2);
				_delay_ms(300);
				if(dg2=='+' || dg2=='-' || dg2=='*' || dg2=='/' || dg2=='='){
					LCD_vCLR_screen();
					LCD_vsend_string("Invalid Char!");
					_delay_ms(1000);
					goto l3;
				}
				
				sec=(dg1-48)*10+(dg2-48);  //Store Inserted Seconds
				if(sec>=60){
					LCD_vCLR_screen();
					LCD_vsend_string("Invalid Number!");
					LCD_vmove_cursor(2,1);
					LCD_vsend_string("**Seconds<60**");
					_delay_ms(1000);
					goto l3;
				}
				
				LCD_vCLR_screen();
				LCD_vsend_string("Press 0");
				LCD_vmove_cursor(2,1);
				LCD_vsend_string("To Set the Clock.");
			}
		}

		for(i=0;i<=5;i++)SET_BIT(PORTC,i);
		CLR_BIT(PORTC,0);
		_7seg_vwrite('B',sec%10);
		_delay_ms(5);

		for(i=0;i<=5;i++)SET_BIT(PORTC,i);
		CLR_BIT(PORTC,1);
		_7seg_vwrite('B',sec/10);
		_delay_ms(5);

		for(i=0;i<=5;i++)SET_BIT(PORTC,i);
		CLR_BIT(PORTC,2);
		_7seg_vwrite('B',min%10);
		_delay_ms(5);

		for(i=0;i<=5;i++)SET_BIT(PORTC,i);
		CLR_BIT(PORTC,3);
		_7seg_vwrite('B',min/10);
		_delay_ms(5);

		for(i=0;i<=5;i++)SET_BIT(PORTC,i);
		CLR_BIT(PORTC,4);
		_7seg_vwrite('B',hr%10);
		_delay_ms(5);

		for(i=0;i<=5;i++)SET_BIT(PORTC,i);
		CLR_BIT(PORTC,5);
		_7seg_vwrite('B',hr/10);
		_delay_ms(5);

		if(sec==60){
			sec=0;
			min++;
		}
		if(min==60){
			min=0;
			hr++;
		}
		if(hr==24){
			hr=0;
		}
    }
}

ISR(TIMER2_OVF_vect){
	sec++;
}
