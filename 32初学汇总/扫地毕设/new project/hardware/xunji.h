#ifndef __xunji_H
#define __xunji_H 	

#define      AIN1         PBout(10)
#define      AIN2         PBout(11)
#define      AIN3         PBout(12)
#define      AIN4         PBout(13)


#define      L      PBin(3) 
#define      M      PBin(4)
#define      R      PBin(5) 


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

