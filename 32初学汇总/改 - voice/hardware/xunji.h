#ifndef __xunji_H
#define __xunji_H 	

#define      AIN1         PAout(2)
#define      AIN2         PAout(3)
#define      AIN3         PAout(4)
#define      AIN4         PAout(5)
#define      BIN1         PBout(10)
#define      BIN2         PBout(11)
#define      BIN3         PBout(12)
#define      BIN4         PBout(13)

#define      L      PCin(0) 
#define      M      PCin(1)
#define      R      PCin(2) 

void run(void);
void voicerun(void);
void Rightward(void);
void Leftward(void);
void MOVER(void);
void MOVEL(void);
void back(void);
void stop(void);
void motor1_gpio(void);
void motor2_gpio(void);
void xunji_gpio(void);
void pwm(void);
void tracingMode(void);
void tracingMode0(void);


#endif

