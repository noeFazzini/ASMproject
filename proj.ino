#include <LiquidCrystal.h>

// pin led
int led = 13;

// pin sensore ultrasuoni
int triggerPort = 7;
int echoPort = 8;

// connessione display (rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode( triggerPort, OUTPUT );
  pinMode( echoPort, INPUT );
  pinMode( led, OUTPUT);
 
  Serial.begin( 9600 );
  Serial.println( "Sensore ultrasuoni: ");

  lcd.begin(16, 2);
}

void loop() {
  //porta bassa l'uscita del trigger
  digitalWrite( triggerPort, LOW );
  //invia un impulso di 10microsec su trigger
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 100 );
  digitalWrite( triggerPort, LOW );
  
  long duration = pulseIn( echoPort, HIGH );
  long r = 0.034 * duration / 2;
  
  Serial.print( "durata: " );
  Serial.print( duration );
  Serial.print( " , " );
  Serial.print( "distanza: " );
  
  if( duration > 38000 ){
    Serial.println( "fuori portata");
    lcd.setCursor(0,0);
    lcd.print("Fuori portata");
  }    
  else { 
    Serial.print( r ); 
    Serial.println( "cm" );
   }

   // pulisco display
   lcd.setCursor(0,0);
   lcd.print("                ");
   lcd.setCursor(0,1);
   lcd.print("                ");
   
  if(r > 99){
    lcd.setCursor(0,0);
    lcd.print("Distanza:");
    lcd.setCursor(10, 0);
    lcd.print(r);
    lcd.setCursor(14, 0);
    lcd.print("cm");}
  if(r <= 99 && r > 9){
    lcd.setCursor(0,0);
    lcd.print("Distanza:");
    lcd.setCursor(11, 0);
    lcd.print(r);
    lcd.setCursor(14, 0);
    lcd.print("cm");}
  if(r <= 9 && r > 3){
    lcd.setCursor(0,0);
    lcd.print("Distanza:");
    lcd.setCursor(12, 0);
    lcd.print(r);
    lcd.setCursor(14, 0);
    lcd.print("cm");}
    //Operazioni sotto-soglia
  if(r <= 3){
    lcd.setCursor(0,0);
    lcd.print("! Sotto-soglia !");
    lcd.setCursor(0,1);
    lcd.print("Distanza:");
    lcd.setCursor(11, 1);
    lcd.print(r);
    lcd.setCursor(13, 1);
    lcd.print("cm");
   
    Serial.println( "! Sotto-soglia !");

    // led sotto-soglia intermittente
    digitalWrite(led, HIGH);
    delay(250);
    digitalWrite(led, LOW);
    delay(250);
  }
  
  delay(300);
    
}
