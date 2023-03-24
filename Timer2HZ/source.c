#include <mega32.h>

// Declare your global variables here
int Timer0 = 0, Timer2 = 0, counter = 0;
// Timer 0 overflow interrupt service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (1<<CS01) | (1<<CS00);
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (1<<CS21) | (1<<CS20);
TCNT0=0xC2;
TCNT2=0x83;
counter = 0;
}

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
TCNT0=0xC2;
    if(256 <= Timer0)
    {
       Timer0 = 0;
       PORTC.0 =~ PORTC.0;
       ++counter;
       if(counter > 1)
       {
            TCCR0 = 0;
            TCCR2 = 0;
       } 
    }
    ++Timer0;
}

// Timer2 overflow interrupt service routine
interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
TCNT2=0x83;
    if(128 <= Timer2)
        {
           PORTC.0 =~ PORTC.0;
           Timer2 = 0; 
        }
    ++Timer2;
}

void main(void)
{

DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (1<<PORTC0);

DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (1<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 15/625 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
// Timer Period: 3/968 ms
TCNT0=0xC2;
OCR0=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 31/250 kHz
// Mode: Normal top=0xFF
// OC2 output: Disconnected
// Timer Period: 4 ms
ASSR=0<<AS2;
TCNT2=0x83;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (1<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

GICR|=(1<<INT1) | (0<<INT0) | (0<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(1<<INTF1) | (0<<INTF0) | (0<<INTF2);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      }
}
