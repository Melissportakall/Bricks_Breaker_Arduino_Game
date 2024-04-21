/*
================KONTROLLER================

YEŞİL BUTON: MENÜDE YUKARI
SARI BUTON: MENÜDE AŞAĞI
MAVİ BUTON: MENÜDE SEÇME

POTANSİYOMETRE: PALET KONTROLÜ

LEDLER: CAN SAYISI

7 SEGMENT: SKOR

IŞIK SENSÖRÜ: RENK DEĞİŞTİRME (BEYAZ ARKAPLAN, SİYAH TUĞLA; SİYAH ARKAPLAN, BEYAZ TUĞLA)
*/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include <Adafruit_GFX.h>
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include "pitches.h"

#define TFT_DC 49
#define TFT_CS 53
#define LDR_PIN 13
#define BALL_SIZE 5 
#define BALL_COLOR ILI9341_YELLOW 
#define YUKARI_BUTTON_PIN 14
#define ASAGI_BUTTON_PIN 16
#define SECME_BUTTON_PIN 15
#define GECME_BUTTON_PIN 17
#define MENU_BASLANGIC_X 20
#define MENU_BASLANGIC_Y 20
#define MENU_ARALIK_Y 60
#define TFT_WIDTH  tft.width()
#define TFT_HEIGHT tft.height()

//BAŞLANGIÇ DEĞERLERİ
int secilenSecenek = 0;
const char* secenekler[] = {"Baslat", "Cikis"};
boolean bricksDraw = true;
boolean fillBackgroundWHITE = true;
boolean fillBackgroundBLACK = false;
boolean brickColorChanges = false;
uint16_t background = ILI9341_BLACK;
uint16_t color = ILI9341_WHITE;
int count = 0;

//7 SEGMENT DISPAY BİLGİLERİ
//a,b,c,d,e,f,g 
byte segValue[10][7] =
{
   {0,0,0,0,0,0,1}, //0
   {1,0,0,1,1,1,1}, //1
   {0,0,1,0,0,1,0}, //2
   {0,0,0,0,1,1,0}, //3
   {1,0,0,1,1,0,0}, //4
   {0,1,0,0,1,0,0}, //5
   {0,1,0,0,0,0,0}, //6
   {0,0,0,1,1,1,1}, //7
   {0,0,0,0,0,0,0}, //8
   {0,0,0,0,1,0,0}  //9  
};
byte digitPin[2] = {A0,A1}; //segment 
byte segPin[8]={2,3,4,5,6,7,8,9}; //{a,b,c,d,e,f,g,dp} 

//CAN VE SKOR
int HEALTH = 3;
int SCORE = 0;

//TOP BİLGİLERİ
float ballX = 125; 
float ballY = 210;
float ballSpeed = 0;
float ballSpeedNext = 1;
float ballSpeedX = 1; 
float ballSpeedY = 1; 

//PALET BİLGİLERİ
float paddleX = 100;
float paddleY = 250;
float paddleSpeed = 1.5;
int paddleLength = 50;
int paddleWidth = 10;
float paddleBeforeX = paddleX;
float paddleBeforeY = paddleY;

//PARÇA BİLGİLERİ
struct pieceStruct
{
  float pieceX;
  float pieceY;
  boolean pieceMoving = false;
  int brickIndex;
};

struct pieceStruct pieces[5];
int pieceIndex = 0;
float pieceSpeed = 0.65;
float pieceSize = 3;

//TUĞLA BİLGİLERİ
//tuğla boyutları 28, 13
int brickWidth = 28;
int brickHeight = 13;
int numberBlocks = 32;
int bricks[32][3] = {
  // tuğlanın durumu, x koordinati, y koordinatı 
   {1,   1,    10},
   {1,   31,   10},
   {1,   61,   10},
   {1,   91,   10},
   {1,   121,  10},
   {1,   151,  10},
   {1,   181,  10},
   {1,   211,  10},
   {1,   1,    25},
   {1,   31,   25},
   {1,   61,   25},
   {1,   91,   25},
   {1,   121,  25},
   {1,   151,  25},
   {1,   181,  25},
   {1,   211,  25},
   {1,   1,    40},
   {1,   31,   40},
   {1,   61,   40},
   {1,   91,   40}, 
   {1,   121,  40},
   {1,   151,  40},
   {1,   181,  40},
   {1,   211,  40},
   {1,   1,    55},
   {1,   31,   55},
   {1,   61,   55},
   {1,   91,   55},
   {1,   121,  55},
   {1,   151,  55},
   {1,   181,  55},
   {1,   211,  55}

};

int direction = 0;
enum MenuDurumu
{
  MENU_GOSTER,
  MENU_KAPAT
};

MenuDurumu menuDurumu = MENU_GOSTER;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup()
{ 
  Serial.begin(9600);
  randomSeed(analogRead(A3));

  for(int i = 2; i < 10; i++)
    pinMode(i, OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(digitPin[0], OUTPUT);
  pinMode(digitPin[1], OUTPUT);
  digitalWrite(digitPin[0], LOW); 
  digitalWrite(digitPin[1], LOW); 

  
  pinMode(YUKARI_BUTTON_PIN, INPUT_PULLUP);
  pinMode(ASAGI_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SECME_BUTTON_PIN, INPUT_PULLUP);
  pinMode(GECME_BUTTON_PIN, INPUT_PULLUP);

  pinMode(LDR_PIN, INPUT);
  ballX = paddleX + (paddleLength / 2);
  ballY = paddleY - BALL_SIZE - 1;
  tft.begin();
  
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_RED);
  tft.setCursor(MENU_BASLANGIC_X, MENU_BASLANGIC_Y);
  tft.println("HOSGELDINIZ!");

  

  secenekGoster(secilenSecenek);
}


void loop()
{
  if (menuDurumu == MENU_GOSTER) {
    if(digitalRead(YUKARI_BUTTON_PIN) == LOW) {
      secilenSecenek = (secilenSecenek - 1 + sizeof(secenekler) / sizeof(secenekler[0])) % (sizeof(secenekler) / sizeof(secenekler[0]));
      secenekGoster(secilenSecenek);
      delay(250);
    }
    
    if(digitalRead(ASAGI_BUTTON_PIN) == LOW) {
      secilenSecenek = (secilenSecenek + 1) % (sizeof(secenekler) / sizeof(secenekler[0]));
      secenekGoster(secilenSecenek);
      delay(250);
    }

    if(digitalRead(SECME_BUTTON_PIN) == LOW) {
      if (secilenSecenek == 0) {
        menuDurumu = MENU_KAPAT;
      }
      else {
        secenekSecildi(secilenSecenek);
      }
      delay(250);
    }
  }

  else if (menuDurumu == MENU_KAPAT)
  {
   
    tft.fillScreen(ILI9341_BLACK); //MENÜYÜ TEMİZLE
   
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_BLUE);
    tft.setCursor(30, 150);
    tft.println("Oyun baslatildi!");
    delay (2000);
    tft.fillScreen(ILI9341_BLACK);
 
    while (true)
    {
      if(digitalRead(LDR_PIN) == LOW) //AYDINLIK ORTAM, SIYAH ARKAPLAN, BEYAZ TUĞLA
      {
        background = ILI9341_BLACK;
        color = ILI9341_WHITE;
        if(!fillBackgroundWHITE)
        {
          tft.fillScreen(background);
          bricksColorChange();
          fillBackgroundWHITE = true;
          fillBackgroundBLACK = false;
        }
      }

      if(digitalRead(LDR_PIN) == HIGH) //KARANLIK ORTAM, BEYAZ ARKAPLAN, SİYAH TUĞLA
      {
        background = ILI9341_WHITE;
        color = ILI9341_BLACK;
        if(!fillBackgroundBLACK)
        {
          tft.fillScreen(background);
          bricksColorChange();
          fillBackgroundBLACK = true;
          fillBackgroundWHITE = false;
        }
      }

      if(bricksDraw) //TUĞLALARI ÇİZ
      {
        drawBricks();
        bricksDraw = false;
      }
      
      draw();                    //ÇİZ
      ArrangeLed();              //CANI GÖSTER
      showScoreOnSegment(SCORE); //PUANI GÖSTER

      //SKOR + HİÇ OLUŞMAYAN TUĞLALARIN TOPLAMI 36YA MODU 0 İSE VEYA BUTONA BASILDIĞINDA SONRAKİ BÖLÜME GEÇ
      if((count + SCORE) % numberBlocks == 0 || digitalRead(GECME_BUTTON_PIN) == LOW)
      {
        resetLevel();
        delay(5000);
      }

      if(HEALTH < 0) //CAN BİTTİĞİNDE TÜM DEĞERLERİ SIFIRLAYIP WHILE DÖNGÜSÜNDEN ÇIK VE LOOPTAN MENÜYE DÖNMEYİ SAĞLA
      {
        resetLevel();
        tft.setCursor(30, 90);
        tft.setTextSize(2);
        tft.setTextColor(ILI9341_WHITE);
        tft.println("Kaybettiniz.");
        tft.setCursor(30, 120);
        tft.println("Skorunuz:");
        tft.setCursor(30, 180);
        tft.setTextSize(4);
        tft.println(SCORE);

        menuDurumu = MENU_GOSTER;
        ballSpeed = 1;
        SCORE = 0;

        delay(3000);

        tft.fillScreen(ILI9341_BLACK);
        tft.setTextSize(2);
        tft.setTextColor(ILI9341_RED);
        tft.setCursor(MENU_BASLANGIC_X, MENU_BASLANGIC_Y);
        tft.println("HOSGELDINIZ!");
        secenekGoster(secilenSecenek);

        break;
      }
    }
  }
}


void secenekGoster(int secenekIndex)
{
  for(int i = 0; i < sizeof(secenekler) / sizeof(secenekler[0]); i++) {
   
    int butonX = MENU_BASLANGIC_X;
    int butonY = MENU_BASLANGIC_Y + (i + 1) * MENU_ARALIK_Y - 15;
    
    tft.fillRect(butonX + 10, butonY + 3, 20, 15, ILI9341_BLACK); 
    
    tft.setTextColor(ILI9341_WHITE); 
    tft.setCursor(butonX + 10, butonY + 3); 
    tft.print((i == secenekIndex) ? "> " : "  "); 
    
    tft.setCursor(butonX + 40, butonY + 5); 
    tft.println(secenekler[i]); 
  }
}


void secenekSecildi(int secenekIndex)
{
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(30, 30);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_RED);
  tft.println("Secilen secenek:");

  tft.setTextSize(3);
  tft.setCursor(30, 100);
  tft.setTextColor(ILI9341_WHITE);
  tft.println(secenekler[secenekIndex]);
  delay(1000);

  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(30, 90);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("Oyunumuza");
  tft.setCursor(30, 120);
  tft.println("gosterdiginiz");
  tft.setCursor(30, 150);
  tft.println("ilgi icin");
  tft.setCursor(30, 180);
  tft.println("tesekkurler!");
  return;
}


void draw()
{
  drawPaddle();
  drawBall();
  drawPieceMove();
}


void drawBall() //TOPU ÇİZ
{
  tft.fillCircle(ballX, ballY, BALL_SIZE, background);
  
  if(paddleX != paddleBeforeX)
  {
    ballSpeed = 1;
    ballX += ballSpeedX * ballSpeed * ballSpeedNext;
    ballY += ballSpeedY * ballSpeed * ballSpeedNext;
  }

  if (ballX >= tft.width() - BALL_SIZE || ballX <= BALL_SIZE)
  {
    ballSpeedX = -ballSpeedX;
  }

  if (ballY <= BALL_SIZE)
  {
    ballSpeedY = -ballSpeedY;
  }

  if (ballY >= tft.height())  //TOP AŞAĞI DÜŞER
  {  
    paddleBeforeX = paddleX;
    paddleBeforeY = paddleY;
    ballX = paddleX + (paddleLength / 2);
    ballY = paddleY - BALL_SIZE - 1;
    HEALTH--;
    ballSpeed = 0;
  }

  tft.fillCircle(ballX, ballY, BALL_SIZE, BALL_COLOR);

  brickCollisionControl(); //TUĞLA ÇARPIM KONTROLÜ

  tft.fillCircle(ballX, ballY, BALL_SIZE, BALL_COLOR);

  palletCollisionControl(); //PALET ÇARPIM KONTROLÜ
}


void drawPieceMove() //PARÇAYI ÇİZ
{
  for(int i = 0; i < 5; i++)
  {
    if(pieces[i].pieceMoving)
    {
      if(pieces[i].brickIndex < 8) //İLK SIRADAN PARÇA DÜŞERSE ALTINDAKİ TUĞLALARI YENİDEN ÇİZ
      {
        if(bricks[pieces[i].brickIndex + 8][0] == 1)
        tft.fillRect(bricks[pieces[i].brickIndex + 8][1], bricks[pieces[i].brickIndex + 8][2], brickWidth, brickHeight, color);

        if(bricks[pieces[i].brickIndex + 16][0] == 1)
          tft.fillRect(bricks[pieces[i].brickIndex + 16][1], bricks[pieces[i].brickIndex + 16][2], brickWidth, brickHeight, color);

        if(bricks[pieces[i].brickIndex + 24][0] == 1)
          tft.fillRect(bricks[pieces[i].brickIndex + 24][1], bricks[pieces[i].brickIndex + 24][2], brickWidth, brickHeight, color);
      }

      else if(pieces[i].brickIndex < 16) //İKİNCİ SIRADAN PARÇA DÜŞERSE ALTINDAKİ TUĞLALARI YENİDEN ÇİZ
      {
        if(bricks[pieces[i].brickIndex + 8][0] == 1)
        tft.fillRect(bricks[pieces[i].brickIndex + 8][1], bricks[pieces[i].brickIndex + 8][2], brickWidth, brickHeight, color);

        if(bricks[pieces[i].brickIndex + 16][0] == 1)
          tft.fillRect(bricks[pieces[i].brickIndex + 16][1], bricks[pieces[i].brickIndex + 16][2], brickWidth, brickHeight, color);
      }

      else if(pieces[i].brickIndex < 24) //ÜÇÜNCÜ SIRADAN PARÇA DÜŞERSE ALTINDAKİ TUĞLALARI YENİDEN ÇİZ
      {
        if(bricks[pieces[i].brickIndex + 8][0] == 1)
          tft.fillRect(bricks[pieces[i].brickIndex + 8][1], bricks[pieces[i].brickIndex + 8][2], brickWidth, brickHeight, color);
      }


      tft.fillCircle(pieces[i].pieceX, pieces[i].pieceY - 1, pieceSize, background);

      pieces[i].pieceY += pieceSpeed;

      if(pieces[i].pieceY > tft.height()) //PARÇA EKRANDAN ÇIKTIYSA SİL
      {
        pieces[i].pieceMoving = false;
        tft.fillCircle(pieces[i].pieceX, pieces[i].pieceY - 1, pieceSize, background);
      }
      
      else //PARÇA EKRANDAYSA AŞAĞI DÜŞÜR
      {
        tft.fillCircle(pieces[i].pieceX, pieces[i].pieceY - 1, pieceSize, color);
      }

      //PARÇA PALETE DEĞERSE PARÇAYI SİL VE CANI 1 ARTTIR
      if(pieces[i].pieceY > paddleY && pieces[i].pieceY < paddleY + paddleWidth && pieces[i].pieceX >= paddleX && pieces[i].pieceX < paddleX + paddleLength)
      {
        pieces[i].pieceMoving = false;
        tft.fillCircle(pieces[i].pieceX, pieces[i].pieceY - 1, pieceSize, background);
        HEALTH++;

        if(HEALTH == 4)
          HEALTH = 3;
      }
    }

    else
    {
      delay(1);
    }
  }
}


void drawPaddle() //PALETİ ÇİZ
{
  tft.fillRect(paddleX, paddleY, paddleLength, paddleWidth, ILI9341_GREEN);
  
  direction = analogRead(A2);

  if(direction + 90 < 1023 / 2 && paddleX > 0) //SOLA
  {
   paddleX -= paddleSpeed;
   tft.fillRect(paddleX + paddleLength, paddleY, 2, paddleWidth, background);
  }

  if(direction - 70 > 1023 / 2 && paddleX + paddleLength < tft.width()) //SAĞA
  {
   paddleX += paddleSpeed;
   tft.fillRect(paddleX - 2, paddleY, 2, paddleWidth, background);
  }
}


void drawBricks()
{
  for(int i = 0; i < numberBlocks; i++)
  {
    if(random(5) == 0) //%80 ŞANSLA TUĞLA OLUŞTUR BÖYLECE BÖLÜM ÇEŞİTLİLİĞİ SAĞLANSIN
      bricks[i][0] = 0;


    if(bricks[i][0] == 1) //TUĞLALARI ÇİZ
    {
      int brickX = bricks[i][1];
      int brickY = bricks[i][2];

      tft.fillRect(brickX, brickY, brickWidth, brickHeight, color);
    }
  }

  for(int i = 0; i < numberBlocks; i++) //BAŞTA SİLİNEN TUĞLALARI SAYDIR
    if(bricks[i][0] == 0)
      count++;
}


void bricksColorChange() //IŞIĞA GÖRE TUĞLALARIN RENGİNİ DEĞİŞTİR
{
  for(int i = 0; i < numberBlocks; i++)
  {
    if(bricks[i][0] == 1)
    {
      int brickWidth = 28;
      int brickHeight = 13;

      int brickX = bricks[i][1];
      int brickY = bricks[i][2];

      tft.fillRect(brickX, brickY, brickWidth, brickHeight, color);
    }
  }
}


void segClear() //SEGMENTİ TEMİZLE
{ 
  for(int i=0;i<8;i++)
    digitalWrite(segPin[i], HIGH);        
}


void drawSevenSeg(int d,int score) //SEGMENTİ YAK
{
  segClear();
  digitalWrite(digitPin[d], HIGH); 

  for(int i=0;i<7;i++)
     digitalWrite(segPin[i], segValue[score][i]);        

  delay(1);
  digitalWrite(digitPin[d], LOW); 
}


void showScoreOnSegment(int score) //BASAMAKLARA GÖRE SEGMENTİ YAK
{
  int hex = score % 10;
  int dec = (score % 100) / 10;
  drawSevenSeg(1, hex);
  drawSevenSeg(0, dec);
}


void ArrangeLed() //CANA GÖRE LEDLERİ YAK
{
  if(HEALTH == 3)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
  }

  if(HEALTH == 2)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
  }

  if(HEALTH == 1)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
  }

  if(HEALTH == 0)
  {
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
  }
}


void resetLevel() //SONRAKİ SEVİYEYE GEÇİLDİĞİNDE DEĞERLERİ SIFIRLA VE YENİ BÖLÜMÜ BAŞLAT
{
  tft.fillScreen(background);

  for(int i = 0; i < numberBlocks; i++)
  {
    if(bricks[i][0] == 1)
      SCORE++;

    bricks[i][0] = 1;
  }
    
  bricksDraw = true;

  paddleX = 100;
  paddleY = 250;
  paddleBeforeX = paddleX;
  paddleBeforeY = paddleY;

  ballX = paddleX + (paddleLength / 2);
  ballY = paddleY - BALL_SIZE - 1;
  ballSpeedNext += 0.2;

  HEALTH = 3;

  for(int i = 0; i < 10; i++)
  {
    pieces[i].pieceX = 0;
    pieces[i].pieceY = 0;
    pieces[i].pieceMoving = false;
    pieces[i].brickIndex = 0;
  }
  
  pieceIndex = 0;

}

void palletCollisionControl() //PALETE ÇARMA KONTROLÜ
{
  if (ballX + BALL_SIZE >= paddleX && ballX - BALL_SIZE <= paddleX + paddleLength &&      
    ballY + BALL_SIZE >= paddleY && ballY - BALL_SIZE <= paddleY + paddleWidth)
  {
    bool hitPaddleTop = (ballY <= paddleY && ballY >= paddleY - BALL_SIZE);
    bool hitPaddleRight = (ballX >= paddleX + paddleLength && ballX <= paddleX + paddleLength + BALL_SIZE);
    bool hitPaddleLeft = (ballX <= paddleX && ballX >= paddleX - BALL_SIZE);

    
    if (hitPaddleTop)
    {
        ballSpeedY = -ballSpeedY;
    }

    if (hitPaddleLeft || hitPaddleRight)
    {
        ballSpeedX = -ballSpeedX;
    }
  }
}

void brickCollisionControl()
{
  for (int i = 0; i < numberBlocks; i++)       //TUĞLALARA ÇARPMA KONTROLÜ
  { 
    if (bricks[i][0] == 1)
    {
      //TUĞLA KOORDİNATLARI
      int brickLeft = bricks[i][1];
      int brickRight = brickLeft + 28;
      int brickTop = bricks[i][2];
      int brickBottom = brickTop + 13;

      //TUĞLA ÇARPIMI KONTROLÜ
      bool hitTop = (ballY - BALL_SIZE <= brickBottom && ballY - BALL_SIZE >= brickTop && ballX >= brickLeft && ballX <= brickRight);
      bool hitBottom = (ballY + BALL_SIZE >= brickTop && ballY + BALL_SIZE <= brickBottom && ballX >= brickLeft && ballX <= brickRight);
      bool hitLeft = (ballX - BALL_SIZE <= brickRight && ballX - BALL_SIZE >= brickLeft && ballY >= brickTop && ballY <= brickBottom);
      bool hitRight = (ballX + BALL_SIZE >= brickLeft && ballX + BALL_SIZE <= brickRight && ballY >= brickTop && ballY <= brickBottom);

      if (hitTop || hitBottom)
        ballSpeedY = -ballSpeedY;

      if (hitLeft || hitRight)
        ballSpeedX = -ballSpeedX;

      //KIRILAN TUĞLAYI SİL VE DURUMUNU GÜNCELLE
      if (hitTop || hitBottom || hitLeft || hitRight) 
      {
        bricks[i][0] = 0;
        tft.fillRect(brickLeft, brickTop, 28, 13, background);

        SCORE++;

        if(random(10) == 0) //%10 ŞANSLA PARÇA DÜŞÜR
        {
          pieces[pieceIndex].brickIndex = i;
          pieces[pieceIndex].pieceX = bricks[i][1] + 14 - pieceSize / 2;
          pieces[pieceIndex].pieceY = bricks[i][2] + 13;
          pieces[pieceIndex].pieceMoving = true;
          pieceIndex++;

          if(pieceIndex == 10)
            pieceIndex = 0;
        }
      }
    } 
  }
}