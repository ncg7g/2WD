#include <Servo.h>      // Ιmport Servo library 
#include <NewPing.h>    // Import Ultrasonic Sensor library 

// *** 2WD CAR FOR HC-SR04 AND SG90 ***

//                 *PIN DEFINITIONS*
const int LeftMotorForward   = 6; // Left Motor Forward 
const int LeftMotorBackward= 7; // Left Motor Backward 
const int RightMotorForward =4; // Right Motor Forward 
const int RightMotorBackward = 5; // Right Motor Backward 

//             *SENSOR PINS *
const int trig_pin = A1; // Transmitter 
const int echo_pin = A2; // Receiver 

//            *CONSTANTS & VARIABLES* 
#define maximum_distance 200 // Max distance (cm) 
#define OBSTACLE_DIST 30 // Obstacle limit (cm) 
int distance = 100; // Distance variable

//                 *Initialize Objects* 
NewPing sonar (trig_pin, echo_pin, maximum_distance); 
Servo servo_motor;

//                     *****  SETUP *****
void setup () 
{
  //                     *Configure Motor Pins *
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  //                   * Initialize Servo *
  servo_motor.attach(10); 
  servo_motor.write(90); // Center Position 
  delay (1000);   // Τime Delay


  //                    * First reading *
  distance = readPing();
  delay (100); // Τime Delay
}

//                ****  LOOP ****
void loop()
 {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50); // Small delay 

  //                    *Check for Obstacle* 
  if (distance <= OBSTACLE_DIST) {     // Ιf the distance is less than or equal to Distance  variable
    //         *1. Stop *
    moveStop();   //Stop
    delay(200);     // Τime Delay
  //          *2. Move Backward *
    moveBackward();  // Move Backward
    delay(300);     // Τime Delay
  //         * 3. Stop *
    moveStop();
    delay(200);
  //           *4. Look Right *
    distanceRight = lookRight(); //Look Right
    delay(300);   // Τime Delay

    //        *5. Look Left*
    distanceLeft = lookLeft(); //Look Left
    delay(300);     // Τime Delay

    //        *Compare & Turn*
    if (distanceRight >= distanceLeft) {  //Ιf the distance to the right is greater than or equal to the distance to the left
      turnRight(); //Turn right
    } else {
      turnLeft();  //Turn left
    }

    moveStop(); // Stop after turn 
  

  } else {
    moveForward();// No Obstacle -> Forward 
  }
  
  distance = readPing();  // Read Distance again
}

//           ****SENSOR FUNCTIONS****

int readPing() {  //Simple Sensor
  delay(70); // Required delay for sensor
  int cm = sonar.ping_cm();
    
  if (cm == 0) {   // If 0, it means out of range (very far)
    cm = 250; 
  }
  return cm;
}

//         * Look Right*
int lookRight() {
  servo_motor.write(40);      // Turn Servo 
  delay(200);                 // Wait 
  int dist = readPing();      // Measure 
  delay(100);
  servo_motor.write(90);      // Center
  return dist;
}

//         *Look Left* 
int lookLeft() {
  servo_motor.write(140);     // Turn Servo 
  delay(200);                 // Wait 
  int dist = readPing();      // Measure 
  delay(100);
  servo_motor.write(90);      // Center 
  return dist;
}

//           *****MOVEMENT FUNCTIONS****

void moveStop() {
   //              *All Low Motor  Stop*
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward() {
    //                  *Motors Forward ON* 
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    //                   *Motors Backward OFF* 
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  }

void moveBackward() {
  //              *Motors Backward ON* 
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  //              *Motors Forward OFF* 
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnRight() {
  //              *Left Forward* 
  digitalWrite(LeftMotorForward, HIGH);
  //              *Right Backward*
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(180);   // Τime Delay
}

void turnLeft() {
  //           *Left Backward*
  digitalWrite(LeftMotorBackward, HIGH);
  //            *Right Forward*
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  delay(180);   // Τime Delay
}
