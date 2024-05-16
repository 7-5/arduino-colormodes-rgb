namespace std {
    extern "C" float fmod(float x, float y);
}

//inputs
int volknob=A0;     // potentiometer pin renaming
int colormode=12;   // right button. its to change between rgb, hsv, hsl 
int subbutton=8;    // first second third in selected
// outputs
int red = 9;
int green = 10;
int blue = 11;
//internal values in use
int colormodeval=0; // rgb=0,hsv=1,hsl=2,cmyk=3
int colorpinprev=0; // 0,1. its to determine when button is released.
int subbuttonval=0; // goes between 012012012 for rgb/hsv/hsl and 0123 for cmyk
int subpinprev=0;   // 0,1. its to determine when button is released.
float v0,v1,v2,v3; // 

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(colormode,INPUT);
  pinMode(subbutton,INPUT);
}

void loop() {
  analogRead(volknob);
if(digitalRead(colormode)){
  colorpinprev=1;
}else if(colorpinprev){
  colorpinprev=0;
  colormodeval++;
  colormodeval%=4;
  if (colormodeval==0){
    subbuttonval%=3;
  }
  }
if(digitalRead(subbutton)){
  subpinprev=1;
}else if(subpinprev){
  subpinprev=0;
  subbuttonval++;
  subbuttonval%=3+colormodeval/3;}

switch (subbuttonval) {
  case 0:
    v0=analogRead(volknob);
    break;
  case 1:
    v1=analogRead(volknob);
    break;
  case 2:
    v2=analogRead(volknob);
    break;
  case 3:
    v3=analogRead(volknob);
    break;}

switch (colormodeval) {
  case 0:
    analogWrite(red, v0/4);
    analogWrite(green, v1/4);
    analogWrite(blue, v2/4);
    break;
  case 1:	
  if(1){
  double h=map(v0, 0, 1023, 0, 35999)/100.0;
	double s=map(v1, 0, 1023, 0, 100)/100.0;
	double v=map(v2, 0, 1023, 0, 100)/100.0;
	double C = v*s;
	double hh = h/60.0;
	double X = C*(1.0-abs(std::fmod(hh,2.0)-1.0));
	double r=0.0;double g=0.0;double b=0.0;
	if(hh<1){
	r = C;
	g = X;}
	else if(hh<2){
	r = X;
	g = C;}
	else if(hh<3){
	g = C;
	b = X;}
	else if(hh<4){
	g = X;
	b = C;}
	else if(hh<5){
	r = X;
	b = C;}
	else{
	r = C;
	b = X;}
	double m = v-C;
	r += m;
	g += m;
	b += m;
	r *= 255.0;
	g *= 255.0;
	b *= 255.0;
	analogWrite(red, int(r));
	analogWrite(green, int(g));
	analogWrite(blue, int(b));}
    break;
  case 2:
  if(1){
  	double h=map(v0, 0, 1023, 0, 35999)/100.0;
	double s=map(v1, 0, 1023, 0, 100)/100.0;
	double l=map(v2, 0, 1023, 0, 100)/100.0;
	double C = (1-abs(2*l-1))*s;
	double hh = h/60.0;
	double X = C*(1.0-abs(std::fmod(hh,2.0)-1.0));
	double r=0.0;double g=0.0;double b=0.0;
	if(hh<1){
	r = C;
	g = X;}
	else if(hh<2){
	r = X;
	g = C;}
	else if(hh<3){
	g = C;
	b = X;}
	else if(hh<4){
	g = X;
	b = C;}
	else if(hh<5){
	r = X;
	b = C;}
	else{
	r = C;
	b = X;}
	double m = l-C/2;
	r += m;
	g += m;
	b += m;
	r *= 255.0;
	g *= 255.0;
	b *= 255.0;
	analogWrite(red, int(r));
	analogWrite(green, int(g));
	analogWrite(blue, int(b));
  }
    break;
  case 3:
  if(1){
    float c=v0/1023.0;
    float m=v1/1023.0;
    float y=v2/1023.0;
    float k=v3/1023.0;
  
  analogWrite(red, int((1-c)*(1-k)*255));
	analogWrite(green, int((1-m)*(1-k)*255));
	analogWrite(blue, int((1-y)*(1-k)*255));
  }
  break;}
}
