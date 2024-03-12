#ifndef __xunji_H
#define __xunji_H 	

#define      AIN1         PBout(10)
#define      AIN2         PBout(11)
#define      AIN3         PBout(12)
#define      AIN4         PBout(13)


#define      L      PCin(13) 
#define      M      PCin(14)
#define      R      PCin(15) 


void motor_gpio(void);
void xunji_gpio(void);
void pwm(void);
void run(void);
void Rightward(void);
void Leftward(void);
void back(void);
void stop(void);
void floorrun(void);


#endif

