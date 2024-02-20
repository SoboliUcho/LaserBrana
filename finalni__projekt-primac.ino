#include <DHT.h>
#define pinDHT 31
#define typDHT11 DHT11 
DHT teplo(pinDHT, typDHT11);

#include <LiquidCrystal.h>
#include <VirtualWire.h>
#include <VirtualWire_Config.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int primac=28;
byte prim_on_off=39;

char i;
int pr;

int dis=0;
byte dis_cl=47;
int tl;

byte zel=37;
byte  cer=38;

byte ov_tep=26;
int ov;
byte tep; 

byte disp = 53;
byte podsv=10;
int svetlo = 1;

void setup() {
  // put your setup code here, to run once:
teplo.begin();
pinMode(pinDHT, INPUT_PULLUP);
pinMode (prim_on_off, OUTPUT);
pinMode (zel, OUTPUT);
pinMode (cer, OUTPUT);
pinMode (dis_cl, INPUT);
pinMode (ov_tep, INPUT);
pinMode (disp, INPUT);
pinMode (podsv, OUTPUT);
digitalWrite (prim_on_off, HIGH);
vw_set_rx_pin(primac);
    //vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(1000);  // Bits per sec

    vw_rx_start(); 
    
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Start cidel");
  delay (5000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        
  for (i = 0; i < buflen; i++)
  { pr=buf[i];   
  }
    lcd.setCursor(5,0);
    lcd.print("Vstup:");
    lcd.setCursor(0,1);
    
    if (pr==106){
     lcd.print("Sektor 1");
     dis=1;
    }
     if (pr==100){
     lcd.print("Sektor 2");
     dis=1;
    }
     if (pr==116){
     lcd.print("Sektor 3");
     dis=1;
    } 
}
svetlo = digitalRead (disp);
if (svetlo == 0)
{digitalWrite (podsv, LOW);}
else 
{digitalWrite (podsv, HIGH);}

tl=digitalRead(dis_cl);
  if (tl==1){
   lcd.clear();
   dis=0;
   }
if (dis==0){
  digitalWrite (cer, LOW);
  digitalWrite (zel, HIGH);
  }
if (dis==1){
  digitalWrite (zel, LOW);
  digitalWrite (cer, HIGH);
  }

tep=digitalRead (ov_tep);
int cel = teplo.readTemperature();
int proc = teplo.readHumidity();
if (tep==1){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Teplota  Vlhkost");
lcd.setCursor(2,1);
lcd.print(cel);
lcd.print("'C");
lcd.setCursor(11,1);
lcd.print(proc);
lcd.print("%");
delay (10000);
lcd.clear();
}
}
