
#include "time.h"
#include "../HelperFunctions.h"
#include <iomanip>
#include "ros/ros.h"
#include "ros/package.h"
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "std_msgs/String.h"
#include <unistd.h>
#include <locale>
#include "ros/callback_queue.h"

#include "stdio.h"
#include "std_msgs/Empty.h"
using namespace std;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
   {
    cout<<msg->data.c_str();
   }

int main(int argc, char **argv)
{
	ros::init(argc, argv, "drone_publish");
	static pthread_mutex_t send_CS;
	ros::NodeHandle nh_;
	ros::NodeHandle nodee_("~");

	//gets coordinates from script that speaks with matlab
	int xcoordinate;
	nodee_.getParam("xCoordinate", xcoordinate);

	//int ycoordinate = -1;
	//nodee_.getParam("yCoordinate", ycoordinate);

//tum_ardrone_pub is the publisher that will be used to send the command to the drone
	ros::Publisher tum_ardrone_pub;
 	tum_ardrone_pub	   = nh_.advertise<std_msgs::String>(nh_.resolveName("tum_ardrone/com"),50);

 	const std::string command[] = {"moveByRel 0 0 0.5 0","moveByRel 0 0 -0.5 0","moveByRel 0 0.5 0 0","moveByRel 0 -0.5 0 0","moveByRel 0.5 0 0 0","moveByRel -0.5 0 0 0","moveByRel 0 0 0 30","moveByRel 0 0 0 -30","land"};

 	ros::Rate loop_rate(1);
 	int count = 0;

 	//checks if there are subscribers ready to listen to the command
 	while(tum_ardrone_pub.getNumSubscribers() == 0){
    loop_rate.sleep();}

	sleep(5);
	std::string exec_command = "c "+command[xcoordinate];
	std::cout<<exec_command<<std::endl;
   // double x = 4*((xcoordinate/640.0)-0.5);
	//double y = 4*((ycoordinate/360.0)-0.5);
	char bf[100];
	//std::cout<<x<<"aaaaa"<<y<<std::endl;
	////snprintf(bf,100,"c %s",xcoordinate);
 	
    //converts integer coordinate to string
    // ostringstream temp1 ;
    // temp1 << xcoordinate;
    // string goX = temp1.str();

    // ostringstream temp2 ;
    // temp2 << ycoordinate;
    // string goY = temp2.str();
   
    //creates the coomand into a string file and publishes it using publish command.
  	//std::string c;
  	////c=(string)bf;
	////std::cout<<c<<"aaaaa"<<std::endl;
 // 	c="c goto "+ goX +" "+ goY +" 0 0";
  	std_msgs::String s;
	s.data = exec_command.c_str();
	pthread_mutex_lock(&send_CS);
 	tum_ardrone_pub.publish(s);
 	pthread_mutex_unlock(&send_CS);
 	
 	sleep(2);
return 0;
}
