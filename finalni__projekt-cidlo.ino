#include <VirtualWire.h>
#include <VirtualWire_Config.h>

int s1;
int s2;
int s3;
byte z1=A0;
byte z2=A1;
byte z3=A2;
byte led_pin=13;
int a1=1;
byte count = 1;
int par=50;

void setup() {
pinMode(led_pin,OUTPUT);
vw_set_tx_pin(5);
vw_set_ptt_inverted(true);
vw_setup(1000);

}

void loop()
{
  char sek[1]={'#'};
s1=analogRead(z1);
s2=analogRead(z2);
s3=analogRead(z3);

if (s1<par) {
  sek[0] = 'j';
  vw_send((uint8_t *)sek, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  }

if (s2<par) {
  sek [0]= 'd';
  vw_send((uint8_t *)sek, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  }

if (s3<par && s3!=0) {
  sek [0]= 't';
  vw_send((uint8_t *)sek, 1);
  vw_wait_tx(); // Wait until the whole message is gone
 }
 
delay(50);
}
