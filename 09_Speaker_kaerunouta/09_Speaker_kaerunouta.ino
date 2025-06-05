const int spkrPin = 3; //3:ConnectorA 4:ConnectorB

#define DO 261.6
#define _DO 277.18
#define RE 293.665
#define _RE 311.127
#define MI 329.63
#define FA 349.228
#define _FA 369.994
#define SO 391.995
#define _SO 415.305
#define RA 440
#define _RA 466.164
#define TI 493.883
#define octDO 523.251

void playmusic(){
  ledcWriteTone(spkrPin, DO);
  delay(500);
  ledcWriteTone(spkrPin, RE);
  delay(500);
  ledcWriteTone(spkrPin, MI);
  delay(500);
  ledcWriteTone(spkrPin, FA); 
  delay(500);
  ledcWriteTone(spkrPin, MI);
  delay(500);
  ledcWriteTone(spkrPin, RE);
  delay(500);
  ledcWriteTone(spkrPin, DO);
  delay(700);
  ledcWriteTone(spkrPin, MI);  
  delay(500);
  ledcWriteTone(spkrPin, FA); 
  delay(500);
  ledcWriteTone(spkrPin, SO); 
  delay(500);
  ledcWriteTone(spkrPin, RA); 
  delay(500);
  ledcWriteTone(spkrPin, SO); 
  delay(500);
  ledcWriteTone(spkrPin, FA); 
  delay(500);
  ledcWriteTone(spkrPin, MI);  
  delay(700);
  ledcWriteTone(spkrPin, 0);
  delay(200);
  ledcWriteTone(spkrPin, DO);
  delay(800);
  ledcWriteTone(spkrPin, 0);
  delay(100);
  ledcWriteTone(spkrPin, DO);
  delay(800);
  ledcWriteTone(spkrPin, 0);
  delay(100);
  ledcWriteTone(spkrPin, DO);
  delay(800);
  ledcWriteTone(spkrPin, 0);
  delay(100);
  ledcWriteTone(spkrPin, DO);
  delay(800);
  ledcWriteTone(spkrPin, 0);
  delay(100);
  ledcWriteTone(spkrPin, DO);
  delay(200);
  ledcWriteTone(spkrPin, 0);
  delay(50);
  ledcWriteTone(spkrPin, DO);
  delay(200);
  ledcWriteTone(spkrPin, 0);
  delay(50);
  ledcWriteTone(spkrPin, RE);
  delay(200);
  ledcWriteTone(spkrPin, 0);
  delay(50);
  ledcWriteTone(spkrPin, RE);
  delay(200);
  ledcWriteTone(spkrPin, 0);
  delay(50);
  ledcWriteTone(spkrPin, MI);
  delay(200);
  ledcWriteTone(spkrPin, 0);
  delay(50);
  ledcWriteTone(spkrPin, MI);
  delay(200);
  ledcWriteTone(spkrPin, 0);
  delay(50);
  ledcWriteTone(spkrPin, FA);
  delay(200);
  ledcWriteTone(spkrPin, 0);
  delay(50);
  ledcWriteTone(spkrPin, FA);
  delay(200);
  ledcWriteTone(spkrPin, MI);
  delay(500);
  ledcWriteTone(spkrPin, RE);
  delay(500);
  ledcWriteTone(spkrPin, DO);
  delay(700);
  ledcWriteTone(spkrPin, 0);
  delay(250);
}

void setup() {
  pinMode(spkrPin, OUTPUT);
  ledcAttach(spkrPin, 12000, 8); //Pin setting(Pin num, Max frequency, Resolution)
}

void loop() {
  playmusic();
  delay(3000);
}
