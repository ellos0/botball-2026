//code for the cube grabbing robot

#include <kipr/wombat.h>
#include <stdlib.h>
#include <stdbool.h>

#define HAND_PORT 1
#define ARM_PORT 0

#define FL 3 //front left wheel
#define FR 2 //front right wheel
#define BL 0 //back left wheel
#define BR 1 //back right wheel

#define TOPHAT_PORT 1
#define LIGHT_PORT 0

//constant arm positions
#define ARM_DOWN 1580
#define ARM_UP 0
#define ARM_PALET 1424
#define ARM_RESET 500

//constant hand positions
#define HAND_HALF 200
#define HAND_OPEN 800
#define HAND_GRAB 300
#define HAND_CLOSE 0
#define HAND_RESET 0

#define TOPHAT_THRESHOLD 3400 //threshold at which a line is detected
#define TIME_INCREMENT 20 //how often the line following will check for a line


typedef enum { //line following types
    BASIC_FOLLOW,
    PRECISE_FOLLOW,
} follow_types;

void go(int p) { //moves all the wheels in one speed
    motor(FL,p);
    motor(FR,p);
    motor(BL,p);
    motor(BR,p);
}

void go_left() { //moves left via omnidirectional wheels (doesn't turn)
	motor(FR,100);
    motor(FL,-100);
    motor(BR,-100);
    motor(BL,100);
}

void go_right() { //moves right via omnidirectional wheels
	motor(FR,-100);
    motor(FL,100);
    motor(BR,100);
    motor(BL,-100);
}

void right() { //turns right
	motor(FR,-100);
    motor(BR,-100);
    motor(FL,100);
    motor(BL,100);
}

void left() { //turns left
	motor(FR,100);
    motor(BR,100);
    motor(FL,-100);
    motor(BL,-100);
}

void set_arm(int x) { //set arm position
    set_servo_position(ARM_PORT,x);
}

void set_hand(int x) { //set hand position
    set_servo_position(HAND_PORT, x);
}

void enable_both() { //enables both servos
    set_servo_enabled(HAND_PORT,1);
    set_servo_enabled(ARM_PORT,1);
}

void disable_both() { //disables both servos
    set_servo_enabled(HAND_PORT,0);
    set_servo_enabled(ARM_PORT,0);
}

void reset_both() { //resets both servos
    set_arm(ARM_RESET);
    set_hand(HAND_RESET);
}

void setup() { //sets up servos
    enable_both();
    set_arm(ARM_UP);
    set_hand(HAND_CLOSE);
    msleep(1000);
    atexit(disable_both);
}


void grab_cube() {
    set_hand(HAND_CLOSE);
    set_arm(ARM_DOWN);
    msleep(1000);
}

void grab_palet() {
    set_hand(HAND_OPEN);
	set_arm(ARM_PALET);
}

void claw_up() {
    set_arm(ARM_UP);
    msleep(1000);
}

void line_left(follow_types t) {
    if (t == BASIC_FOLLOW) {
        motor(FL,20);
        motor(BL,20);
        motor(FR,100);
        motor(BR,100);
    }
    if (t == PRECISE_FOLLOW) {
        motor(FL,-30);
        motor(BL,-30);
        motor(FR,50);
        motor(BR,50);
    }
}
void line_right(follow_types t) {
    if (t == BASIC_FOLLOW) {
        motor(FL,100);
        motor(BL,100);
        motor(FR,20);
        motor(BR,20);
    }
    if (t == PRECISE_FOLLOW) {
        motor(FL,50);
        motor(BL,50);
        motor(FR,-30);
        motor(BR,-30);
    }
}

void line_follow(int time,follow_types t) {
    int time_passed = 0;

    while (time_passed < time) {
        if (analog(TOPHAT_PORT) <= TOPHAT_THRESHOLD) { //if on line
            line_left(t); //left
        } else {
            line_right(t); //right
        }
        msleep(TIME_INCREMENT);
        //count time
        time_passed += TIME_INCREMENT;
    }
}

void run1() {
    left();
	//turning    
    msleep(1470);
    go(-100);
	//push the poms first
    msleep(3000);
    go(100);
	 //go back   
    msleep(3000);
	//align with the second poms 
    go_right();
    msleep(1200);
	//push the poms second    
    go(-100);
    msleep(2800);
    
    go(100);
    msleep(250);
    
    //square up
    go_right();
    msleep(1000);
    
    go_left();
    msleep(3000);
    
    go(-100);
    msleep(600);
    go(100);
    msleep(600);
    
    go_left();
    msleep(1900);
    
    go(-100);
    msleep(600);
    go(100);
    msleep(600);
}

float get_distance(float a, float b) {
	return abs(a - b);
}

bool is_within_distance(float a, float b, float distance) {
	return (abs(a - b) < distance);
}

void align(float angle) {
    
	for (;;) {
    	right();
        msleep(10);
        
      	bool continud = is_within_distance(get_compass_angle(), angle, 0.1);
        printf("%f\n", get_distance(get_compass_angle(),angle));
        if (continud) break;
    }
    go(0);
}


void compass_test() {
	float start_angle = get_compass_angle();
    
    left();
    msleep(1000);
    align(start_angle);
}

int main() {
    setup();
    run1();
    
    return 0;
}
