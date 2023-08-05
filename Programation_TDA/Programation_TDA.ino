////Programção TDAA
//https://www.arduinoecia.com.br/sensor-temperatura-umidade-hdc1080-arduino

////////////////////////////TEMPERATURA////////////////////////////
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//Define o endereco I2C do display e qtde de colunas e linhas
//LiquidCrystal_I2C lcd(0x3B, 16, 2);
LiquidCrystal_I2C lcd(0x27,16,2);
//Array que desenha o simbolo de grau
byte grau[8] = {B00110, B01001, B01001, B00110,
                B00000, B00000, B00000, B00000,};
double temp_amb;
double temp_obj;
////////////////////////////TEMPERATURA////////////////////////////

////////////////////////////VARIAVEIS//////////////////////////////
    (ENTRADAS/SAÍDAS):
    int sensorpr = 10; //SENSOR DE PRESENÇA
    int bomba = 11;    //RELE QUE LIGA A BOMBA
    
    (TRAVA):
    int flag=0;
    
    (DELAYS):
    int delay0=50; // Tempo de captação de Temperatura 3x
    int delay1=500; // Tempo que a bomba ficará ligada
    int delay2=500; // Tempo de Troca de Usuário
////////////////////////////VARIAVEIS//////////////////////////////

void setup(){

////////////////////////////TEMPERATURA////////////////////////////
Serial.begin(9600);
//Inicializa o display LCD I2C
lcd.init();
lcd.backlight();
//Atribui a "1" o valor do array "grau", que desenha o simbolo de grau
lcd.createChar(1, grau);
//Inicializa o MLX90614
mlx.begin();
Serial.begin(9600);
////////////////////////////TEMPERATURA////////////////////////////
    
//DEFINIÇÃO DE ENTRADAS/SAÍDAS:
    pinMode(sensorpr, INPUT);
    pinMode(bomba, OUTPUT); 
    digitalWrite(bomba,HIGH);
    lcd.setBacklight(LOW);}
///////////////////////////////////////////////////////////////////

    void loop(){

    if (digitalRead(sensorpr)==LOW){
      if (flag==0) {flag=1;}
    }
    else
    {
        if (flag==2){
        delay(delay2);
        lcd.clear()
        lcd.setBacklight(LOW);
        flag=0;}
     }
      
    if (flag==1)
    {
    temp_amb = mlx.readAmbientTempC();
    temp_obj = mlx.readObjectTempC();
    delay(delay0);
    temp_amb = mlx.readAmbientTempC();
    temp_obj = mlx.readObjectTempC();
    delay(delay0);
    temp_amb = mlx.readAmbientTempC();
    temp_obj = mlx.readObjectTempC();
    delay(delay0);

    if (digitalRead(sensorpr)==LOW)
    {
    digitalWrite(bomba,LOW);
    delay(delay1);
    digitalWrite(bomba,HIGH);
    
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Ambiente:");
    lcd.setCursor(10, 0);
    lcd.print(temp_amb);
    lcd.setCursor(15, 0);
    lcd.write(1);
    lcd.setCursor(0, 1);
    lcd.print("Objeto:");
    lcd.setCursor(10, 1);
    lcd.print(temp_obj);
    lcd.setCursor(15, 1);
    lcd.write(1);
    
    flag=2;} else {flag=2;}
    }
  }
