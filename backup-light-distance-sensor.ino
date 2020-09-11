
float trigger_dist = 210; // Distance to trigger relay in cm

const int trigPin = 3; // Digital pin connected to the ultrasonic sensor, trig (Tx)
const int echoPin = 2; // Digital pin connected to the ultrasonic sensor, echo (Rx)
const int relayPin = 8; // Digital pin connected to relay

int filtSize = 25; // The number of distance measurements to average. 
// Indiviudual distance measurements can be noisy. To prevent the relay from s
// on incorrect measuremwitchingents, the measurements are filtered with a "running average".
// Some number of measurements are taken and averaged, then that average is treated as
// the correct distance.

//###########################################

int filtLen = 0;
float filtAve = 0;
float filtDist = 0;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  if (filtLen >= filtSize) {
    
    filtDist = filtAve / filtLen;
    
    Serial.print("Filtered distance: ");
    Serial.println(filtDist);

    if(filtDist <= trigger_dist) {
      digitalWrite(relayPin, LOW);
    } else {
      digitalWrite(relayPin, HIGH);
    }
    
    filtAve = 0;
    filtLen = 0;
  }

  filtAve += distance;
  filtLen += 1;
  delay(1);
}
