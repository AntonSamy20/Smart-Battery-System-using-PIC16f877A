// pinout setting
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

//pin direction
sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;

char wake_flag = 0;
char timer_flag = 0;
char multiplexing_flag = 0;

void interrupt()
{
    if (INTF_bit){
         INTF_bit = 0; wake_flag = 1;
    }
    if (TMR0IF_bit){
         TMR0IF_bit = 0;
         TMR0 = 255;
         multiplexing_flag = 1;
    }
    if (PIR1.TMR1IF){
        PIR1.TMR1IF = 0;
        TMR1H = 0x0B;
        TMR1L = 0xDC;
        timer_flag = 1;
    }
}

void main() {
char update_lcd=0;
char temp; char op_temp[4];
unsigned int volt; char op_volt[6];
unsigned char seg[10] = {
    0x3F,   // 0
    0x06,   // 1
    0x5B,   // 2
    0x4F,   // 3
    0x66,   // 4
    0x6D,   // 5
    0x7D,   // 6
    0x07,   // 7
    0x7F,   // 8
    0x6F    // 9
};
char j = 0, tens, ones;

// tris and port
trisd = 0; portd = 0;
trisb = 0; trisb.f0 = 1; trisc = 0;
portc.f5 = 1; portc.f6 = 0;

// interrupt
GIE_bit=1; PEIE_bit=1; PIR1.TMR1IF=0; PIE1.TMR1IE=1; INTF_bit=0;
INTE_bit = 1; TMR0IF_bit = 0; TMR0IE_bit = 1;

//timer and option_reg
TMR1L = 0xDC; TMR1H = 0x0B; TMR0 = 255;
T1con = 0b00110001; option_reg = 0x07; ADCON1=0x80;

lcd_init(); lcd_cmd(_lcd_clear);
pwm2_init(5000); pwm2_start();
Lcd_Out(1,1,"Battery System");
delay_ms(1000);
lcd_cmd(_lcd_clear);
Lcd_Cmd(_LCD_CURSOR_OFF);

while (1){
temp = adc_read(7);
temp = temp * 0.489;
volt = adc_read(6);
volt = volt * 12.0/1023.0;

if(multiplexing_flag){
    tens = temp/10;
    ones = temp%10;
    multiplexing_flag = 0;
    if(j == 1){
        PORTC.F7 = 0;
        PORTD = seg[tens];
        PORTD.F7 = 1;
        j = 0;
    }
    else{
        PORTD.F7 = 0;
        PORTD = seg[ones];
        PORTC.F7 = 1;
        j = 1;
    }
}

if (timer_flag){
  timer_flag = 0;
  ByteToStr(temp, op_temp);
  Lcd_Out(1,1,"Temp: ");
  Lcd_Out_cp(Ltrim(op_temp));

  WordToStr(volt, op_volt);
  Lcd_Out(2,1,"volt: ");
  Lcd_Out_cp(Ltrim(op_volt));
  update_lcd = 0;

}
if(wake_flag){
  wake_flag = 0;
  lcd_cmd(_lcd_clear);
  Lcd_Out(1,1,"volt: ");
  Lcd_Out_cp(Ltrim(op_volt));
  PWM2_Set_Duty(255);
  lcd_out(2,1,"FAN:ON");
}
if(temp >= 45) PWM2_Set_Duty(255);
else if(temp >= 40 && temp < 45) PWM2_Set_Duty(204);
else if(temp >= 35 && temp < 40) PWM2_Set_Duty(153);
else if(temp >= 30 && temp < 35) PWM2_Set_Duty(102);
else if(temp >= 25 && temp < 30) PWM2_Set_Duty(51);
else PWM2_Set_Duty(0);

}// while
}// main
