//  PARAMETER
const int precess = 1;
const float nbE = 160;
// END PARAMETER
const float freq = 16000000 / nbE;       //Declaration des variables
const float maxFreq = 16000000; 
const int outPin = 9; 
const int D2 = 2;
const int D5 = 5;
const int D6 = 6;
const int D7 = 7;
int  i,j, maxValue ;
int median;
int medianE;
float val = 0;
void setFrequency(float frequency)            //Fonction pour modifier la fréquence
{
  if(frequency >=0 || frequency <=16000000){  
    TCCR1A=0b10000010;
    unsigned int v=0;
    int indscale=0;
    float prescale[] = {1.0,8.0,64.0,256.0,1024.0};
    float period=1/frequency;
    while(v==0){
      float curfreq=maxFreq/prescale[indscale];
      float tickperiod=1/curfreq;
      float nbtick=period/tickperiod;
      if(nbtick>65535) {indscale=indscale+1;}
      else {v=nbtick;}}
    int c=prescale[indscale];
     switch (c) {
         case 1: TCCR1B=0b00011001; break;
         case 8: TCCR1B=0b00011010; break;
         case 64: TCCR1B=0b00011011; break;
         case 256: TCCR1B=0b00011100; break;
         case 1024: TCCR1B=0b00011101; break;
         default: TCCR1B=0b00011000;}
    ICR1=v; 
    OCR1A=v/2; 
  }}
void setup() {              //Ici la fonction setup pour initialiser
  Serial.begin(115200);
  pinMode(outPin,OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(D2, OUTPUT);
  
  digitalWrite(D2, HIGH);
}
void loop() {              // Fonction principal se repétant a l'infini
maxValue=0;
median = 0;
                                            
 
for(j=0;j<precess;j++){     // précision sur plusisuers valeur pour éviter les parasites
 for(i=1;i<nbE+1;i++){
    setFrequency(206700);   //frequence de coupure
    val = analogRead(A0);
    if(val > maxValue){
      medianE = medianE + val;}}
      medianE = medianE / nbE;
  median = median + medianE;}   
median = median / precess;   // Calcule de la moyenne 
Serial.println(median); 

if( median <= 155 && median >= 135  )
{
digitalWrite(D5, LOW);
digitalWrite(D7, LOW);
digitalWrite(D6, LOW);
}
else if ( median <= -38 && median >= -50)
{
digitalWrite(D5,HIGH);
digitalWrite(D7,LOW);
digitalWrite(D6,LOW);
}

else if( median <= 0 && median >= -37  )
{
digitalWrite(D5, HIGH);
digitalWrite(D7, HIGH);
digitalWrite(D6, LOW);
}
else if ( median <= -50 && median >= -200)
{
digitalWrite(D5,HIGH);
digitalWrite(D7,HIGH);
digitalWrite(D6,HIGH);
}
}




