  // Variables declaration
  bool BtnSwitch_LastState,BtnResetBuz_LastState,SensorReserve_LastState;                                                           //Sensors last states variables
  bool BtnSwitch, BtnResetBuz, SensorReserve;                                                                                       //Inputs variables
  bool OutSecContactron, OutBuzzer, OutLedContactronIsWorking, OutLedReserve, OutLed_1, OutLed_2, OutLed_3, OutLed_4, OutLed_5;     //Outputs variables
  int SequenceCounter=1;

//--------------------------------------------------------------
//Setup
//--------------------------------------------------------------
void setup() {

  //--------------------------------------------------------------
  //I/O setup
  pinMode(2,OUTPUT);			          //Przekaźnik sekcji(stan wysoki)
  pinMode(3,OUTPUT); 		            //Buzzer
  pinMode(4,INPUT_PULLUP);	        //Przycisk przelaczania
  pinMode(5,INPUT_PULLUP);	        //Przycisk wylaczenie buzzera
  pinMode(6,OUTPUT);			          //Dioda pracy przekaźnika
  pinMode(7,OUTPUT);			          //Dioda rezerwa siewnika
  pinMode(8,OUTPUT);			          //Dioda stanu 1/5
  pinMode(9,OUTPUT);			          //Dioda stanu 2/5
  pinMode(10,OUTPUT);		            //Dioda stanu 3/5
  pinMode(11,OUTPUT);		            //Dioda stanu 4/5
  pinMode(12,OUTPUT);		            //Dioda stanu 5/5
  pinMode(14,INPUT_PULLUP);         //Czujnik rezerwy siewnika

  //--------------------------------------------------------------
  //Read DI state and remember in lastState
  BtnSwitch_LastState=!digitalRead(4);
  BtnResetBuz_LastState=!digitalRead(5);
  SensorReserve_LastState=!digitalRead(14);
}

//--------------------------------------------------------------
//Loop
//--------------------------------------------------------------
void loop() {
  //Read inputs
  BtnSwitch=digitalRead(4);
  BtnResetBuz=digitalRead(5);
  SensorReserve=digitalRead(14);
  //--------------------------------------------------------------
  //Buzzer section
  if(SensorReserve && !SensorReserve_LastState)
  {
    OutBuzzer=1;
    delay(50);
  }
  else if(BtnResetBuz && !BtnResetBuz_LastState)
  {
    OutBuzzer=0;
    delay(50);
  }
  //--------------------------------------------------------------
  //Sequence section
  if(BtnSwitch && !BtnSwitch_LastState)
  {
    SequenceCounter++;
    if(1<=SequenceCounter>=6) SequenceCounter=1;
    delay(50);
  }

  if(SequenceCounter==1)
  {
    OutLed_1=1;
    OutLed_2=0;
    OutLed_3=0;
    OutLed_4=0;
    OutLed_5=0;
  }
  else if(SequenceCounter==2)
  {
    OutLed_1=0;
    OutLed_2=1;
    OutLed_3=0;
    OutLed_4=0;
    OutLed_5=0;
  }
  else if(SequenceCounter==3)
  {
    OutLed_1=0;
    OutLed_2=0;
    OutLed_3=1;
    OutLed_4=0;
    OutLed_5=0;
  }
  else if(SequenceCounter==4)
  {
    OutLed_1=0;
    OutLed_2=0;
    OutLed_3=0;
    OutLed_4=1;
    OutLed_5=0;
  }
  else if(SequenceCounter==1)  
  {
    OutLed_1=0;
    OutLed_2=0;
    OutLed_3=0;
    OutLed_4=0;
    OutLed_5=1;
  }
  //--------------------------------------------------------------
  //Auxiliary outputs
  OutSecContactron=OutLed_3;
  OutLedContactronIsWorking=OutSecContactron;

  //--------------------------------------------------------------
  //Remember input states
  BtnSwitch_LastState=BtnSwitch;
  BtnResetBuz_LastState=BtnResetBuz;
  SensorReserve_LastState=SensorReserve;

  //--------------------------------------------------------------
  //Write outputs
  digitalWrite(2,OutSecContactron);
  digitalWrite(3,!OutBuzzer);
  digitalWrite(6,!OutLedContactronIsWorking);
  digitalWrite(7,!OutLedReserve);
  digitalWrite(8,!OutLed_1);
  digitalWrite(9,!OutLed_2);
  digitalWrite(10,!OutLed_3);
  digitalWrite(11,!OutLed_4);
  digitalWrite(12,!OutLed_5);
}
