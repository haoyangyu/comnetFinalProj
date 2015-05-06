pg :: CrnPacketGen;
srt:: CrnServiceRequestTable;
rt :: CrnRouting;
pg->srt;

srt[0]->Print("SRT Request Process")->rt;
srt[1]->Print("SRT Content Process")->Discard;

rt[0]->Print("Routing Request Process")->Discard;
rt[1]->Print("Routing Content Process")->Discard;
rt[2]->Print("Routing Update Process")->Discard;
