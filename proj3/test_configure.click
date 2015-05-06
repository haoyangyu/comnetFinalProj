pg::CrnPacketGen;
rt::CrnRouting;

pg->rt;

rt[0]->Print("Request Process")->Discard;
rt[1]->Print("Content Process")->Discard;
rt[2]->Print("Update Process")->Discard;
