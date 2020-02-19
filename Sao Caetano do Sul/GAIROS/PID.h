#define Kp 4
#define Ki 0
#define Kd 0
int previous_error=0;
int P=0;
int I=0;
int previous_I=0;
int D=0;
int PID_value=0;

void CalculatePID(int error) {
  P = error;
  I = I + error;
  D = error - previous_error;
  PID_value = (Kp*P) + (Ki*I) + (Kd*D);
  previous_error=error;
}

