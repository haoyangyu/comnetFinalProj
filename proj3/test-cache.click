pg :: CrnPacketGen;
mc :: Myclassifier;
ca :: Cache;

pg -> mc;

mc[0] -> Print("Request Processed") -> ca[1] ->Print("Cache Return") ->Discard;
ca[0] -> Discard;
mc[1] -> Print("Response Processed") -> Discard;
mc[2] -> Print("Update Processed") -> Discard;
