pg :: CrnPacketGen;
mc :: Myclassifier;
ca :: Cache;
srt:: CrnServiceRequestTable;
rt :: CrnRouting;

pg->mc;
//request path
mc[0] -> Print("mc::Request Processed") -> ca;
ca[1] ->Print("ca::Cache Return") ->Discard;

srt[0] ->rt;
rt[0]->Print("rt::Request Processed")->Discard;


//content path
mc[1] -> Print("mc::Response Processed") -> ca;
ca[0] -> Print("ca::Response Processed")-> srt;
srt[1] -> Print("srt::Response Processed")-> Discard;


//update path
mc[2] -> Print("mc::Update Processed") -> rt;
rt[1] -> Print("rt::Update Processed")->Discard;

rt[2] -> Discard;