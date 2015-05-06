pg :: MyPacketGen;
mc :: MyClassifier;

pg -> mc;

mc[0] -> Print("Request Processed") -> Discard;
mc[1] -> Print("Response Processed") -> Discard;
mc[2] -> Print("Update Processed") -> Discard;