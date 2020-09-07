
float trigger_dist = 100; // Distance to trigger relay in cm

//###########################################

const int trigPin = 3;
const int echoPin = 2;
const int relayPin = 8;

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

  if (filtLen >= 25) {
    
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
