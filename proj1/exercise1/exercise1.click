//Create new packet with payload "hello"
//Creates packets consisting of DATA, emitting 1 time at a rate of 1  packet per second
RatedSource(DATA "hello", RATE 1, LIMIT 1, STOP true)->Print(Sending)->Discard;
