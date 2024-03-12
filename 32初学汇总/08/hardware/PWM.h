#ifndef __PWM_H 
#define __PWM_H

void TIM3_PWM_Init(void);

#define      AIN1         PAout(2)
#define      AIN2         PAout(3)
#define      AIN3         PAout(4)
#define      AIN4         PAout(5)
#define      BIN1         PAout(9)
#define      BIN2         PAout(10)
#define      BIN3         PAout(11)
#define      BIN4         PAout(12)

#define      IN1         PAout(6)
#define      IN2         PAout(7)
#define      IN3         PBout(0)
#define      IN4         PBout(1)


#define      L      PBin(3) 
#define      M      PBin(4)
#define      R      PBin(5)

void Forward(void);
void Rightward(void);
void Leftward(void);
void Stopward(void);
void Motor1_Init(void);
void Motor2_Init(void);

#endif



