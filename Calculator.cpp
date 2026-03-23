#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

byte LCD_ADDR = 0x00;
LiquidCrystal_I2C* lcd = nullptr;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String expression = "";
bool resultShown = false;

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

double applyOp(double a, double b, char op) {
  switch(op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
      if (b == 0) return NAN;
      return a / b;
  }
  return 0;
}

double evaluate(String expr) {
  double numStack[16];
  char opStack[16];
  int nTop = 0, oTop = 0;
  int i = 0;
  int len = expr.length();

  while (i < len) {
    char c = expr[i];
    if (isDigit(c) || c == '.') {
      String numStr = "";
      while (i < len && (isDigit(expr[i]) || expr[i] == '.')) {
        numStr += expr[i++];
      }
      numStack[nTop++] = numStr.toFloat();
      continue;
    }
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (oTop > 0 && precedence(opStack[oTop-1]) >= precedence(c)) {
        double b = numStack[--nTop];
        double a = numStack[--nTop];
        char op = opStack[--oTop];
        double r = applyOp(a, b, op);
        if (isnan(r)) return NAN;
        numStack[nTop++] = r;
      }
      opStack[oTop++] = c;
      i++;
      continue;
    }
    i++;
  }

  while (oTop > 0) {
    double b = numStack[--nTop];
    double a = numStack[--nTop];
    char op = opStack[--oTop];
    double r = applyOp(a, b, op);
    if (isnan(r)) return NAN;
    numStack[nTop++] = r;
  }

  return numStack[0];
}

void updateDisplay() {
  lcd->clear();
  String top = expression;
  if (top.length() > 16) top = top.substring(top.length() - 16);
  lcd->setCursor(0, 0);
  lcd->print(top);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("Scanning I2C...");
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      LCD_ADDR = addr;
      Serial.print("Found at 0x");
      Serial.println(addr, HEX);
      break;
    }
  }

  if (LCD_ADDR == 0x00) {
    Serial.println("No I2C device found. Check wiring.");
    while (true);  // halt
  }

  lcd = new LiquidCrystal_I2C(LCD_ADDR, 16, 2);
  lcd->init();
  lcd->backlight();
  lcd->setCursor(0, 0);
  lcd->print("  Calculator");
  delay(1200);
  lcd->clear();
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;

  if (key == 'C') {
    expression = "";
    resultShown = false;
    lcd->clear();
    return;
  }

  if (key == '=') {
    double result = evaluate(expression);
    lcd->clear();
    lcd->setCursor(0, 0);
    String top = expression;
    if (top.length() > 16) top = top.substring(top.length() - 16);
    lcd->print(top);
    lcd->setCursor(0, 1);
    if (isnan(result)) {
      lcd->print("ERROR: Dividing by 0");
    } else {
      String res = String(result, 6);
      if (res.indexOf('.') >= 0) {
        while (res.endsWith("0")) res.remove(res.length()-1);
        if (res.endsWith(".")) res.remove(res.length()-1);
      }
      if (res.length() > 16) res = res.substring(0, 16);
      lcd->print("= " + res);
    }
    resultShown = true;
    return;
  }

  if (resultShown) {
    if (isDigit(key) || key == '.') {
      expression = "";
    }
    resultShown = false;
  }

  expression += key;
  updateDisplay();
}
