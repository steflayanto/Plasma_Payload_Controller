void setup() {
  initBME();

}

void loop() { //??? int to return val?
  // pull alt
  alt = BMEalt
  //map to flight stages, mapping
  if (alt < 100){
    return 0;
  } else{
    //w/o throttle, burn = 10 sec = 10000 ft
    //1 burn
    map(alt, 100, 10000, 0, 1)
    //2 early coast
    map(alt, 100, 1000, 1, 2)
    //3 late coast
    map(alt, 100, 1000, 2, 3)
    //4 decent = 26067 and down
    map(alt, 100, 1000, 3, 4)
    
    //w/ throttle burn = 21 sec = 15000
    //1 burn
    map(alt, 100, 15000, 0, 1)
    //2 early coast
    map(alt, 100, 1000, 1, 2)
    //3 late coast
    map(alt, 100, 1000, 2, 3)
    //4 decent = 27700 and down
    map(alt, 100, 1000, 3, 4)
  
  }
}
