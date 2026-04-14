//code for the cone grabbing robot

#include <kipr/wombat.h>
#include <stdlib.h>

#define FL 3
#define FR 2
#define BL 1
#define BR 0

#define NINETY_DEGREE 1700
#define TURNAROUND_TIME 3400

#define SERVO_RESET 2047
#define HAND_OPEN 1024
#define HAND_CONE 2047
#define ARM_UP 1024
#define ARM_CONE 400

#define ARM_PORT 0
#define HAND_PORT 1

#define TOPHAT_PORT 1

#define LINE_FOLLOW_THRESHOLD 3000
#define LINE_FOLLOW_TIME_INCREMENT 30

void wait_next() { //waits for 'A'
	while(!a_button_clicked()) msleep(20);
}


void set_arm(int x) {
    set_servo_position(ARM_PORT,x);
}

void set_hand(int x) {
    set_servo_position(HAND_PORT,x);
}

void disable_both() {
    set_servo_enabled(ARM_PORT,0);
    set_servo_enabled(HAND_PORT,0);
}

void end_programme() {
	set_arm(2047);
    set_hand(2047);
    msleep(1000);
    disable_both();
}

void setup() {
    set_servo_enabled(ARM_PORT,1);
    set_servo_enabled(HAND_PORT,1);
    set_arm(SERVO_RESET);
    msleep(1000);
    atexit(end_programme);
}

void go(int p) {
    motor(FL,p);
    motor(FR,p);
    motor(BL,p);
    motor(BR,p);
}

void line_left() {
    motor(FR,30);
    motor(BR,30);
    motor(FL,100);
    motor(BL,100);
}

void line_right() {
    motor(FR,100);
    motor(BR,100);
    motor(FL,30);
    motor(BL,30);
}

void back_line_left() {
	motor(FR,-100);
    motor(BR,-100);
    motor(FL,-30);
    motor(BL,-30);
}

void back_line_right() {
	motor(FR,-30);
    motor(BR,-30);
    motor(FL,-100);
    motor(BL,-100);
}

void follow_line(int time, int dir) {
    //direction determines if the robot aligns to the left or right side of the line
    int time_elapsed = 0;
    while (time_elapsed < time) {
        if (analog(TOPHAT_PORT) > LINE_FOLLOW_THRESHOLD) {
            if (dir == 1) {
            	back_line_left();
            } else {
            	back_line_right();
            }
        } else {
            if (dir == 1) {
            	back_line_right(dir);
            } else {
                back_line_left();
            }
        }
        msleep(LINE_FOLLOW_TIME_INCREMENT);
        time_elapsed += LINE_FOLLOW_TIME_INCREMENT;
    }
}



void left() {
    motor(FR,100);
    motor(BR,100);
    motor(FL,-100);
    motor(BL,-100);
}

void right() {
    motor(FR,-100);
    motor(BR,-100);
    motor(FL,100);
    motor(BL,100);
}

void run1() {
    setup();
    //go down ramp
    go(-100);
    msleep(1000);
    follow_line(14*1000,1);
	go(-100);
    msleep(2500);
    
    go(100);
    msleep(1000);
    left();
    msleep(1500);
    go(0);
    msleep(4000);
    
    go(-100);
    msleep(3650);
    left();
    msleep(NINETY_DEGREE);
    follow_line(4.25*1000,1);
    left();
    msleep(TURNAROUND_TIME);
    
    go(0);
    set_hand(HAND_OPEN);
    msleep(1000);
    set_arm(ARM_CONE);
    msleep(1000);
    set_hand(HAND_CONE);
    msleep(1000);
    
    set_arm(ARM_UP);
    msleep(1000);
    
    right();
    msleep(TURNAROUND_TIME);
    
    follow_line(5*1000,1);
}

void open_reset() {
	set_hand(HAND_OPEN);
    msleep(1000);
    set_hand(SERVO_RESET);
}


int main()
{
    open_reset();
    run1();
    return 0;
}
