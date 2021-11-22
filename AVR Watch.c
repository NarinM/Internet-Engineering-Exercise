#include <mega16.h>
#include <alcd.h>
#include <stdio.h>

int seconds = 0;
int minuts = 0;
int hours = 0;

interrupt[TIM2_OVF] void timer2_ovf_isr(void) {
  char buffer[10];

  seconds = seconds + 1;
  if (seconds == 60) {
    seconds = 0;
    minuts = minuts + 1;

    if (minuts == 60) {
      minuts = 0;
      hours = hours + 1;

      if (hours == 24)
        hours = 0;
    }
  }

  sprintf(buffer, "%02d:%02d:%02d", hours, minuts, seconds);
  lcd_gotoxy(0, 0);
  lcd_puts(buffer);
}

void main(void) {
  lcd_init(16);

  TIMSK = 0x40;
  TIFR = 0x40;
  ASSR = 0x08;
  TCNT2 = 0x00;
  TCCR2 = 0x05;

  #asm("sei")

  while (1);
}
