//
//  receiver.cpp
//  
//
//  Created by Haoyang Yu on 3/27/15.
//
//

#include <stdio.h>
#include "newport.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <float.h>
#include <math.h>
#include "common_change.h"


using namespace std;

void startClient(Address *my_tx_addr, Address *my_rx_addr, Address *dst_addr);

int main(int argc, const char * argv[]){
    const char* hname = "192.168.2.2";
    const char* dstname = "192.168.2.1"; 
    int dst_addr_int = 10005;
    int my_rx_addr_int =10003;
    int my_tx_addr_int =10004;
    
    Address *my_tx_addr = new Address(hname, my_tx_addr_int);
    Address *my_rx_addr = new Address(hname, my_rx_addr_int);
    Address *dst_addr =  new Address(dstname, dst_addr_int);
    startClient(my_tx_addr, my_rx_addr, dst_addr);
    return EXIT_SUCCESS;
}

void startClient(Address *my_tx_addr, Address *my_rx_addr, Address *dst_addr){
    printf("Start Receiver: Node 2. \n");
    
    try {
        //Configure the transmitting port
        mySendingPort *my_tx_port = new mySendingPort();
        my_tx_port->setAddress(my_tx_addr);
        my_tx_port->setRemoteAddress(dst_addr);
        my_tx_port->init();
        
        //Configure receiving port to listen to ACK frames
        LossyReceivingPort *my_rx_port = new LossyReceivingPort(0.2);
        my_rx_port->setAddress(my_rx_addr);
        my_rx_port->init();
        
        char *part_packet;
        int i=0; 
        int mark=0;
        
        do{
            cout<<"Choose sending or receiving:"<<endl;
            cout<<"1.Sending"<<endl;
            cout<<"2.Receiving"<<endl;
            cout<<"Your choice:";
            cin>>mark;
        }while(mark!=1&&mark!=2);
        
        if(mark==2)
        {
            try {
                
                cout << "begin receiving..." <<endl;
                int flag=-1;
                int i_name = 0;
                char* rfname=new char[20];
                Packet *p;
                while(1)
                {
                    
                    Packet * my_ack_packet;
                    my_ack_packet = new Packet();
                    my_ack_packet->setPayloadSize(0);
                    PacketHdr *hdr_r = my_ack_packet->accessHeader();
                    hdr_r->setOctet('A',0);
                    hdr_r->setOctet('C',1);
                    hdr_r->setOctet('K',2);
                    
                    
                    p = my_rx_port->receivePacket();
                    if (p !=NULL)
                    {
                        
                        int i = p->accessHeader()->getIntegerInfo(3);
                        
                        if(flag!=i){
                            
                            ofstream file2(rfname,ios::app);
                            if(!file2)
                            {
                                cout<<"cannot open the receiver file!"<<endl;
                            }
                            
                            file2<<p->getPayload();
                            file2.close();
                        }
                        
                        PacketHdr *hdr_check = p->accessHeader();
                        char hdr0 = hdr_check->getOctet(0);
                        if (hdr0 =='E'){
                            cout<<"File transfer finished!"<<endl;
                            exit(-1);
                        }
                        
                        if (hdr0 =='N' && i_name==0){
                            cout<<"Someone send you a file with name "<< p->getPayload() <<endl;
                            cout<<"Enter the name of receiving file: ";
                            cin>>rfname;
                            i_name = 1;
                        }
                        
                        flag=i;
                        if (flag >=0)
                        cout << "receiving a packet of seq num " << i << "...sending ACK" << endl;
                        else
                        cout << "sending ACK for file name" << endl;
                        hdr_r->setIntegerInfo(i,3);
                        my_tx_port->sendPacket(my_ack_packet);
                    }
                }
            } catch (const char *reason ) {
                cerr << "Exception:" << reason << endl;
                exit(-1);
            }
        }
        
        if(mark==1)
        {
            //Find the file and file name
            char* sfname=new char[20];
            cout<<"Enter the name of file you want to send(text2.dat):";
            cin>>sfname;
            ifstream file1(sfname);
            if(!file1)
            {
                //char* ssfname=new char[20];
                cout<<"cannot open the sender file!"<<endl;
                exit(-1);
                /*cout<<"Enter the name of sending file:";
                 cin>>ssfname;
                 ifstream file1(ssfname);*/
            }
            file1>>noskipws;
            
            // Transfer the file name
            Packet * my_first_packet = new Packet(); //first packet is the file name
            my_first_packet->fillPayload(20,sfname);
            PacketHdr *hdr_f = my_first_packet->accessHeader();
            hdr_f->setOctet('N',0); //NAM indicates the packet type
            hdr_f->setOctet('A',1);
            hdr_f->setOctet('M',2);
            hdr_f->setIntegerInfo(-1,3); //-1 is used to indicate that this is a file name
            my_tx_port->sendPacket(my_first_packet);
            cout << "File name is sent!" <<endl;
            my_tx_port->sendPacket(my_first_packet);
            my_tx_port->lastPkt_ = my_first_packet;
            
            //Schedule retransmit for the file name (have to check the ACK)
            my_tx_port->setACKflag(false);
            my_tx_port->timer_.startTimer(2.5);
            cout << "begin waiting for ACK..." <<endl;
            Packet *pAck;
            while (!my_tx_port->isACKed()){
                pAck = my_rx_port->receivePacket();
                if (pAck!= NULL)
                {
                    PacketHdr *hdr_check = pAck->accessHeader();
                    int i_ack = hdr_check->getIntegerInfo(3);
                    char hdr0 = hdr_check->getOctet(0);
                    if ( hdr0=='A' && i_ack==-1){
                        my_tx_port->timer_.stopTimer();
                        my_tx_port->setACKflag(true);
                        cout << "The last sent packet has been acknowledged." <<endl;
                    }
                }
            }
            delete my_first_packet;
            
            //Start file transfer
            while(!file1.eof()){
                Packet * my_packet;  //create a single packet
                my_packet = new Packet();
                my_packet->setPayloadSize(1210);
                part_packet=new char[1210];
                for(int j=0;j<1000;j++) //get the file content and fill in the payload
                {
                    file1>>part_packet[j];
                }
                my_packet->fillPayload(1000,part_packet);
                
                PacketHdr *hdr_s = my_packet->accessHeader(); //configure the header information
                hdr_s->setOctet('D',0);
                hdr_s->setOctet('A',1);
                hdr_s->setOctet('T',2);
                hdr_s->setIntegerInfo(i,3);
                
                my_tx_port->sendPacket(my_packet); //send the packet
                my_tx_port->lastPkt_ = my_packet;
                cout << "packet " << i << " is sent!" <<endl;
                
                //schedule retransmit (have to check the ACK)
                my_tx_port->setACKflag(false);
                my_tx_port->timer_.startTimer(2.5);
                cout << "begin waiting for ACK..." <<endl;
                Packet *pAck;
                while (!my_tx_port->isACKed()){
                    pAck = my_rx_port->receivePacket();
                    if (pAck!= NULL){
                        int i_ack = pAck->accessHeader()->getIntegerInfo(3);
                        PacketHdr *hdr_check = pAck->accessHeader();
                        char hdr0 = hdr_check->getOctet(0);
                        if (i_ack == i && hdr0 == 'A'){
                            my_tx_port->timer_.stopTimer();
                            my_tx_port->setACKflag(true);
                            cout << "The last sent packet has been acknowledged." <<endl;
                        }
                    }
                    
                }
                i++;
                delete my_packet;
                //sleep(1);
            }
            file1.close();
            
            // Send the exit message with header "EXI"
            Packet * my_packet;
            my_packet = new Packet();
            
            PacketHdr *hdr_s = my_packet->accessHeader();
            hdr_s->setOctet('E',0);
            hdr_s->setOctet('X',1);
            hdr_s->setOctet('I',2);
            
            my_tx_port->sendPacket(my_packet);sleep(1); //send three EXI messages
            my_tx_port->sendPacket(my_packet);sleep(1);
            my_tx_port->sendPacket(my_packet);
        }
    }
    
    catch (const char *reason ) {
        cerr << "Exception:" << reason << endl;
        exit(-1);
    }
    
}
