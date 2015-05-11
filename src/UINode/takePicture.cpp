#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ardrone_autonomy/Navdata.h>
#include "ros/package.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Image.h"
#include "tf/tfMessage.h"
#include "tf/transform_listener.h"
#include "tf/transform_broadcaster.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ardrone_autonomy/Navdata.h"
#include <opencv2/opencv.hpp>
using namespace std;
string status = "";
bool unlock = false;
ros::NodeHandle* nh;
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
   cv_bridge::CvImagePtr cv_ptr;
      try
      {
        // cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        std::string filename = "/home/michael/CUT_Drone/raw_data/raw_image";
  
        filename=filename +".jpg";
  
        cv_bridge::CvImagePtr cv_ptr2 = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGRA8);
  
        cv::imwrite(filename,cv_ptr2->image);
		ros::shutdown();
      }
      catch (cv_bridge::Exception& e)
      {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
}
void chatterCallback(const ardrone_autonomy::NavdataConstPtr navdataPtr)
{
	 

	
	switch(	navdataPtr->state )
	{
		case 0: status = "Unknown";break;
		case 1: status = "Init"; break;
		case 2: status = "Landed";break;
		case 3: status = "Flying"; break;
		case 4: status = "Hovering";break;
		case 5: status = "Test"; break;
		case 6: status = "Taking off";break;
		case 7: status = "Goto Fix Point"; break;
		case 8: status = "Landing";break;
		case 9: status = "Looping"; break;
	}
	
	if ((navdataPtr->rotX>=-0.3) && (navdataPtr->rotX<=0.3) && (navdataPtr->rotY>=-0.3) && (navdataPtr->rotY<=0.3) && (navdataPtr->altd>750) && (unlock==true)){

		cout<<"take a picture"<<endl;
		
 		image_transport::ImageTransport it(*nh);
  		image_transport::Subscriber sub = it.subscribe("ardrone/image_raw", 1000, imageCallback);
		unlock=false;

		ros::spin();
	}
	if(!((navdataPtr->rotX>=-0.3) && (navdataPtr->rotX<=0.3) && (navdataPtr->rotY>=-0.3) && (navdataPtr->rotY<=0.3)) &&(status!="Unknown")){

		unlock=true;
		cout<<"X tilt: "<<navdataPtr->rotX<<"Y tilt: "<<navdataPtr->rotY<<endl;
	}
	
	cout<<"Altitude: "<<navdataPtr->altd<<endl;

}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");
ros::NodeHandle n;
nh=&n;

  ros::Rate r(1);

  ros::Subscriber ub = n.subscribe("ardrone/navdata", 1000, chatterCallback);

  

  ros::spin();


   
  


  return 0;
}

