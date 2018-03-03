
/* 2. 报文过滤接收程序 */

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <net/if.h>

#include <sys/ioctl.h>

#include <sys/socket.h>

#include <linux/can.h>

#include <linux/can/raw.h>
#include<iostream>
#include<iomanip>
using namespace std;

 

int main_can_rec()

{
using namespace std;
cout.setf(ios::right|ios::hex);
    int s, nbytes;

    struct sockaddr_can addr;

    struct ifreq ifr;

    struct can_frame frame;

    struct can_filter rfilter[2];

    s = socket(PF_CAN, SOCK_RAW, CAN_RAW); //创建套接字

    strcpy(ifr.ifr_name, "can0" );

    ioctl(s, SIOCGIFINDEX, &ifr); //指定 can0 设备

    addr.can_family = AF_CAN;

    addr.can_ifindex = ifr.ifr_ifindex;

    bind(s, (struct sockaddr *)&addr, sizeof(addr)); //将套接字与 can0 绑定

    //定义接收规则，只接收表示符等于 0x11 的报文

    rfilter[0].can_id = 0x11;

    rfilter[0].can_mask = CAN_SFF_MASK;

    rfilter[1].can_id = 0x12;

    rfilter[1].can_mask = CAN_SFF_MASK;
    //设置过滤规则

    setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

    while(1)

    {
	// cout<<"hello,world"<<endl;
  
        nbytes = read(s, &frame, sizeof(frame)); //接收报文

        //显示报文

        if(nbytes > 0)

        {
 	//	cout<<"hello,2"<<endl;

	cout<<"printf:"<<endl;
        printf("ID=0x%X DLC=%d\n", frame.can_id,frame.can_dlc);
        printf("data[0]=0x%X   data[1]=0x%X\n", frame.data[0], frame.data[1]);
       	printf("data[2]=0x%X   data[3]=0x%X\n", frame.data[2], frame.data[3]);
	printf("data[4]=0x%X   data[5]=0x%X\n", frame.data[4], frame.data[5]);
	printf("data[6]=0x%X   data[7]=0x%X\n", frame.data[6], frame.data[7]);

	    //cout only print id ????? 
	    //cout <<"cout :"<<endl;
	    //cout<<"ID="<<hex<<frame.can_id<<endl;
	    //cout<<"DLC="<<hex<<frame.can_dlc<<endl;
            //cout<<"data[0]="<<hex<<frame.data[0]<<endl;
	
	  //  cout<<endl;

        }
  	 //cout<<"hello,3"<<endl;

    }

    close(s);

    return 0;

}

void Can_rec_fork(int s) 
{
		
    struct can_frame frame;
	int nbytes;
	nbytes = read(s, &frame, sizeof(frame)); //接收报文

        //显示报文

        if(nbytes > 0)

        {
 	//	cout<<"hello,2"<<endl;

		cout<<"printf:"<<endl;
   	 	printf("ID=0x%X DLC=%d\n", frame.can_id,frame.can_dlc);
    	printf("data[0]=0x%X   data[1]=0x%X\n", frame.data[0], frame.data[1]);
    	printf("data[2]=0x%X   data[3]=0x%X\n", frame.data[2], frame.data[3]);
		printf("data[4]=0x%X   data[5]=0x%X\n", frame.data[4], frame.data[5]);
		printf("data[6]=0x%X   data[7]=0x%X\n", frame.data[6], frame.data[7]);

		}

}
