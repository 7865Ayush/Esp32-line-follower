
const int sensorCount = 8;
const int sensorPins[sensorCount] = {13, 14, 16, 17, 18, 19, 21, 22};
const int lineActive = LOW;

const int weights[sensorCount] = {
  -3500, -2500, -1500, -500, 500, 1500, 2500, 3500
};

// Motor driver pins
const int leftPWM = 25;
const int leftIN1 = 26;
const int leftIN2 = 27;

const int rightPWM = 32;
const int rightIN1 = 33;
const int rightIN2 = 23;

// Control parameters
const int baseSpeed = 120;
const int maxSpeed = 220;
const float Kp = 0.035;
const float Kd = 0.12;
const int lostLineSpeed = 90;

int lastError = 0;
bool lineWasSeen = false;

// Motor control
void setMotor(int pwmPin, int in1, int in2, int speed) {
  speed = constrain(speed, -maxSpeed, maxSpeed);

  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } 
  else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } 
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  analogWrite(pwmPin, abs(speed));
}

void drive(int leftSpeed, int rightSpeed) {
  setMotor(leftPWM, leftIN1, leftIN2, leftSpeed);
  setMotor(rightPWM, rightIN1, rightIN2, rightSpeed);
}

void stopMotors() {
  drive(0, 0);
}

// Read line position
bool readLinePosition(int &position) {
  long weightedSum = 0;
  int activeCount = 0;

  for (int i = 0; i < sensorCount; i++) {
    if (digitalRead(sensorPins[i]) == lineActive) {
      weightedSum += weights[i];
      activeCount++;
    }
  }

  if (activeCount == 0) {
    return false;
  }

  position = weightedSum / activeCount;
  return true;
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < sensorCount; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  pinMode(leftPWM, OUTPUT);
  pinMode(leftIN1, OUTPUT);
  pinMode(leftIN2, OUTPUT);

  pinMode(rightPWM, OUTPUT);
  pinMode(rightIN1, OUTPUT);
  pinMode(rightIN2, OUTPUT);

  stopMotors();
  Serial.println("Line Follower Ready");
}

void loop() {
  int position = 0;

  if (!readLinePosition(position)) {
    if (lineWasSeen) {
      if (lastError < 0) {
        drive(-lostLineSpeed, lostLineSpeed);
      } else {
        drive(lostLineSpeed, -lostLineSpeed);
      }
    } else {
      stopMotors();
    }

    delay(5);
    return;
  }

  lineWasSeen = true;

  int error = position;
  int derivative = error - lastError;

  float correction = Kp * error + Kd * derivative;

  int leftSpeed = constrain(
    baseSpeed + (int)correction, 0, maxSpeed
  );

  int rightSpeed = constrain(
    baseSpeed - (int)correction, 0, maxSpeed
  );

  drive(leftSpeed, rightSpeed);
  lastError = error;

  Serial.print("Position: ");
  Serial.print(position);
  Serial.print(" | Left: ");
  Serial.print(leftSpeed);
  Serial.print(" | Right: ");
  Serial.println(rightSpeed);

  delay(5);
}
