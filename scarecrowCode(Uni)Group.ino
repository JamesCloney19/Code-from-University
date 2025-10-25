// define pins
#define trigPin 8
#define echoPin 9


void setup() {
  // put your setup code here, to run once:

  // begin serial port
  Serial.begin (9600);
}

void loop() {
  // defining local variables
  long distance_cm;
  

  // function for calculating distance in cm
  distance_cm = calcDistance();
  delay(300);
  
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
}

// function that has 0 inputs and returns a the distance in cm as a float

long calcDistance()
{
  long pulseDuration, convertedDistance;

  // Set pin to OUTPUT to send trigger pulse
  pinMode(trigPin, OUTPUT);

  // trigPin is set to LOW to make sure the HIGH signal is clean
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // trigPin is triggered to send out a signal to recieve
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Switch to INPUT to listen for echo
  pinMode(echoPin, INPUT);
  pulseDuration = pulseIn(echoPin, HIGH);

  // Convert to distance in cm
  convertedDistance = pulseDuration * 0.0172;

  return convertedDistance;
}





