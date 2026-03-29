# Electronics and Embedded Systems

Collection of Arduino-based projects focused on control systems, embedded logic, and hardware interfacing.  
All projects are designed and simulated using Tinkercad.

## Projects

### 1. Washing Machine Motor Controller
**What it Does:**  
Simulates a washing machine motor cycle using a bidirectional DC motor with controlled speed variation and cycle completion alerts.

**Core Idea:**  
Motor control using an H-bridge with PWM-based speed modulation.

**Components Used:**  
	•	Arduino  
	•	L293D H-bridge motor driver  
	•	DC motor  
	•	LED (status indication)  
	•	Buzzer  

**How it Works:**  
The L293D H-bridge enables bidirectional control of the DC motor, allowing it to switch between clockwise and counterclockwise rotation. PWM signals from the Arduino are used to gradually ramp motor speed up and down, mimicking washing cycles. LEDs indicate the state of operation, and a buzzer signals completion of the cycle.

**Features:**  
	•	Bidirectional motor control  
	•	PWM-based speed ramping  
	•	Visual status indication via LED  
	•	Audio alert on cycle completion  

**Stack:** Arduino (C++)

<p align="center">
<img src="Assets/Washing-Machine.jpeg" width="800"></p>

### 2. 4-Function Calculator

**What it Does:**  
Implements a basic calculator capable of evaluating arithmetic expressions with correct operator precedence.

**Core Idea:**  
Expression parsing using the shunting-yard algorithm.

**Components Used:**  
	•	Arduino  
	•	4x4 keypad  
	•	16x2 LCD display (I2C)  

**How it Works:**  
User input is taken through the keypad and parsed using a stack-based shunting-yard algorithm to ensure correct operator precedence. The processed expression is evaluated and displayed on the LCD. The system dynamically detects the I2C address of the display and handles runtime errors such as division by zero. Results can be reused in subsequent calculations.

**Features:**  
	•	Correct operator precedence handling  
	•	Dynamic I2C address scanning  
	•	Division-by-zero error handling  
	•	Result chaining for continuous calculations  

**Stack:** Arduino (C++)

<p align="center">
<img src="Assets/Calculator.jpeg" width="500"></p>

### 3. Digital Piano

**What it Does:**  
Implements a minimal digital piano using an Arduino and piezo buzzer, mapping discrete button inputs to musical frequencies in real time.

**Core Idea:**  
Real-time mapping of discrete human input to frequency generation. 

**How it Works:**  
The system continuously scans button states in a polling loop. When a button is pressed, it triggers a corresponding frequency output through a piezo buzzer. The implementation prioritizes low latency over architectural complexity, ensuring immediate auditory feedback.

**Features:**  
	•	8-button real-time input system  
	•	Direct mapping of inputs to musical frequencies  
	•	Immediate sound generation using Arduino `tone()` function  

**Stack:** Arduino (C++)

<p align="center">
<img src="Assets/Piano.jpeg" width="500"></p>
