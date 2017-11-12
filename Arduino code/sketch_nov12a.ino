void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 int val;                
  double temp;          
  val=analogRead(10);      
  temp=Thermister(val);   
  Serial.println(temp);   
//  Serial.print("\n"); 
  delay(2000); 
}



double Thermister(int RawADC) {  
 double Temp;
 Temp = log(((10240000/RawADC) - 10000));
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;              
 return Temp;
}

