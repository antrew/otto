#include "SmoothCriminal.h"
#include "MyOtto.h"
#include "Arduino.h"
#include "Otto_mouths.h"

void goingUp(int tempo);
void drunk (int tempo);
void noGravity(int tempo);
void kickLeft(int tempo);
void kickRight(int tempo);
void run(int steps, int T=500);
void walk(int steps, int T=1000);
void backyard(int steps, int T=3000);
void backyardSlow(int steps, int T=5000);
void turnLeft(int steps, int T=3000);
void turnRight(int steps, int T=3000);
void moonWalkLeft(int steps, int T=1000);
void moonWalkRight(int steps, int T=1000);
void crusaito(int steps, int T=1000);
void swing(int steps, int T=1000);
void upDown(int steps, int T=1000);
void flapping(int steps, int T=1000);
void primera_parte();
void segunda_parte();
void lateral_fuerte(boolean, int);
void dance();

extern MyOtto otto;

// TEMPO: 121 BPM
int t=495;
double pause=0;

long prev;
long now;
void timestamp(const char* msg)
{
  now = millis();
  Serial.println(msg);
  Serial.println(now - prev);
  prev = now;
}
void danceSmoothCriminal(){
  otto.showMouth(heart_code);
  delay(14500);
  otto.showMouth(smile_code);

  prev = millis();
  now = millis();

  t = 497;
  Serial.println("go");
  primera_parte();
  timestamp("prime");
  t = 517;
  segunda_parte();
  timestamp("sec");
  t = 497;
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  timestamp("moonwalk");
  t = 497;
  primera_parte(); 
  timestamp("prim");

  t = 517;
  crusaito(1,t*8);
  crusaito(1,t*7);
  for (int i=0; i<16; i++){
    flapping(1,t/4);
    delay(3*t/4);
  }
  timestamp("cru flap");
 
  t = 497;
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);

  timestamp("moon");

  t = 497;
  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  drunk(t*4);

  kickLeft(t);
  kickRight(t);
  kickLeft(t);
  kickRight(t);
  timestamp("drunk kick");
  
  t = 550;

  drunk(t*8);
  drunk(t*4);
  drunk(t/2);
  delay(t*4); 
  drunk(t/2);
  delay(t*4); 
  walk(2,t*2);
  backyard(2,t*2);
  timestamp("drunk walk back");

  t = 497;
  goingUp(t*2);
  goingUp(t*1);
  goingUp(t*1);
  timestamp("up");

  t = 535;
  noGravity(t*2);
  noGravity(t*1);
  timestamp("noGrav");

  t = 515;
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*3);
  crusaito(1,t*2);
  crusaito(1,t*3);

  delay(t);

  timestamp("crus");
  t = 497;
  primera_parte();
  timestamp("prim");

  t = 500;
  for (int i=0; i<32; i++)
  {
    flapping(1,t/2);
    delay(t/2);
  }
  timestamp("flap");

  
}




////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FUNCIONES DE CONTROL//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]){
  for (int i=0; i<4; i++) {
    otto.servo[i].SetO(O[i]);
    otto.servo[i].SetA(A[i]);
    otto.servo[i].SetT(T);
    otto.servo[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<4; i++){
        otto.servo[i].refresh();
     }
  }
}

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS]; 
int oldPosition[]={90,90,90,90};

void moveNServos(int time, int  newPosition[]){
  for(int i=0;i<N_SERVOS;i++)	increment[i] = ((newPosition[i])-oldPosition[i])/(time/INTERVALTIME);
  
  final_time =  millis() + time; 
  
  iteration = 1; 
  while(millis() < final_time){ //Javi del futuro cambia esto  
      interval_time = millis()+INTERVALTIME;  
      
      oneTime=0;      
      while(millis()<interval_time){	  
          if(oneTime<1){ 
              for(int i=0;i<N_SERVOS;i++){
                  otto.servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
              }			
              iteration++;
              oneTime++;
          }
      }     
  }   

  for(int i=0;i<N_SERVOS;i++){	
    oldPosition[i] = newPosition[i];
  }   
}


//////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASOS DE BAILE////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void goingUp(int tempo){
  
      pause=millis();
      for(int i=0;i<4;i++) otto.servo[i].SetPosition(90);
      delay(tempo);
      otto.servo[0].SetPosition(80);
      otto.servo[1].SetPosition(100);
      delay(tempo);
      otto.servo[0].SetPosition(70);
      otto.servo[1].SetPosition(110);
      delay(tempo);
      otto.servo[0].SetPosition(60);
      otto.servo[1].SetPosition(120);
      delay(tempo);
      otto.servo[0].SetPosition(50);
      otto.servo[1].SetPosition(130);
      delay(tempo);
      otto.servo[0].SetPosition(40);
      otto.servo[1].SetPosition(140);
      delay(tempo);
      otto.servo[0].SetPosition(30);
      otto.servo[1].SetPosition(150);
      delay(tempo);
      otto.servo[0].SetPosition(20);
      otto.servo[1].SetPosition(160);
      delay(tempo);
      
      while(millis()<pause+8*t);

}

void primera_parte(){
  
  int move1[4] = {60,120,90,90};
  int move2[4] = {90,90,90,90};
  int move3[4] = {40,140,90,90};
  
  for(int x=0; x<3; x++){
    for(int i=0; i<3; i++){
      lateral_fuerte(1,t/2);
      lateral_fuerte(0,t/4);
      lateral_fuerte(1,t/4);
      delay(t);
    }
  
    pause=millis();
    for(int i=0;i<4;i++) otto.servo[i].SetPosition(90);
    moveNServos(t*0.4,move1);
    moveNServos(t*0.4,move2);
    while(millis()<(pause+t*2));
  }
  
  for(int i=0; i<2; i++){
    lateral_fuerte(1,t/2);
    lateral_fuerte(0,t/4);
    lateral_fuerte(1,t/4);
    delay(t);
  }
    
  pause=millis();
  for(int i=0;i<4;i++) otto.servo[i].SetPosition(90);
  crusaito(1,t*1.4);
  moveNServos(t*1,move3);
  for(int i=0;i<4;i++) otto.servo[i].SetPosition(90);
  while(millis()<(pause+t*4));
}

void segunda_parte(){
  
  int move1[4] = {90,90,80,100};
  int move2[4] = {90,90,100,80};
  int move3[4] = {90,90,80,100};
  int move4[4] = {90,90,100,80};
    
  int move5[4] = {40,140,80,100};
  int move6[4] = {40,140,100,80};
  int move7[4] = {90,90,80,100};
  int move8[4] = {90,90,100,80};
       
  int move9[4] = {40,140,80,100};
  int move10[4] = {40,140,100,80};
  int move11[4] = {90,90,80,100};
  int move12[4] = {90,90,100,80};
  
  for(int x=0; x<7; x++){ 
    for(int i=0; i<3; i++){
      pause=millis();
      moveNServos(t*0.15,move1);
      moveNServos(t*0.15,move2);
      moveNServos(t*0.15,move3);
      moveNServos(t*0.15,move4);
      while(millis()<(pause+t));
    }
    pause=millis();
    moveNServos(t*0.15,move5);
    moveNServos(t*0.15,move6);
    moveNServos(t*0.15,move7);
    moveNServos(t*0.15,move8);
    while(millis()<(pause+t));
  }
 
  for(int i=0; i<3; i++){
    pause=millis();
    moveNServos(t*0.15,move9);
    moveNServos(t*0.15,move10);
    moveNServos(t*0.15,move11);
    moveNServos(t*0.15,move12);
    while(millis()<(pause+t));
  }
}

void lateral_fuerte(boolean side, int tempo){
  
  for(int i=0;i<4;i++) otto.servo[i].SetPosition(90);
  if (side) otto.servo[0].SetPosition(40);
  else otto.servo[1].SetPosition(140);
  delay(tempo/2);
  otto.servo[0].SetPosition(90);
  otto.servo[1].SetPosition(90);
  delay(tempo/2);

}

void drunk (int tempo){
  
  pause=millis();
  
  int move1[] = {60,70,90,90};
  int move2[] = {110,120,90,90};
  int move3[] = {60,70,90,90};
  int move4[] = {110,120,90,90};
  
  moveNServos(tempo*0.235,move1);
  moveNServos(tempo*0.235,move2);
  moveNServos(tempo*0.235,move3);
  moveNServos(tempo*0.235,move4);
  while(millis()<(pause+tempo));

}


void noGravity(int tempo){
  
  int move1[4] = {120,140,90,90};
  int move2[4] = {140,140,90,90};
  int move3[4] = {120,140,90,90};
  int move4[4] = {90,90,90,90};
  
  
  for(int i=0;i<4;i++) otto.servo[i].SetPosition(90);
  for(int i=0;i<N_SERVOS;i++) oldPosition[i]=90;
  moveNServos(tempo*2,move1);
  moveNServos(tempo*2,move2);
  delay(tempo*2);
  moveNServos(tempo*2,move3);
  moveNServos(tempo*2,move4);

 

}

void kickLeft(int tempo){
  for(int i=0;i<4;i++) otto.servo[i].SetPosition(90);
  delay(tempo);
  otto.servo[0].SetPosition(50); //pie derecho
  otto.servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
  otto.servo[0].SetPosition(80); //pie derecho
  otto.servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  otto.servo[0].SetPosition(30); //pie derecho
  otto.servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  otto.servo[0].SetPosition(80); //pie derecho
  otto.servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  otto.servo[0].SetPosition(30); //pie derecho
  otto.servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  otto.servo[0].SetPosition(80); //pie derecho
  otto.servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
}

void kickRight(int tempo){
for(int i=0;i<4;i++) otto.servo[i].SetPosition(90);
  delay(tempo);
  otto.servo[0].SetPosition(110); //pie derecho
  otto.servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  otto.servo[0].SetPosition(110); //pie derecho
  otto.servo[1].SetPosition(100); //pie izquiero
  delay(tempo/4);
  otto.servo[0].SetPosition(110); //pie derecho
  otto.servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  otto.servo[0].SetPosition(110); //pie derecho
  otto.servo[1].SetPosition(80); //pie izquiero
  delay(tempo/4);
  otto.servo[0].SetPosition(110); //pie derecho
  otto.servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  otto.servo[0].SetPosition(110); //pie derecho
  otto.servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}

void walk(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void run(int steps, int T){
    int A[4]= {10, 10, 10, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyard(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyardSlow(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}


void turnLeft(int steps, int T){
    int A[4]= {20, 20, 10, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void turnRight(int steps, int T){
    int A[4]= {20, 20, 30, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkRight(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15 ,15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkLeft(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void crusaito(int steps, int T){
    int A[4]= {25, 25, 30, 30};
    int O[4] = {- 15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void swing(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void flapping(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0], A[1], 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void test(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0] + 10, A[1] - 10, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}