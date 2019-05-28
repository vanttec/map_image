#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include "custom_msgs/ObjDetectedList.h"
#include <Eigen/Dense>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


int length=0;
float distanceX[]={};
float Ys[]={};


void obstaculosCallback(const custom_msgs::ObjDetectedList::ConstPtr& msg)
   {
    length=msg->len;
    //float objects;
    //float objects=msg-> objects;
    //obj = msg->objects;
    ROS_INFO("length: %i",length);

    distanceX [length]={};
    //int boxes [length];
    Ys [length]={};

    for (int i; i<(length); i++)
    {
        distanceX[i]=msg->objects[i].X;
        Ys[i]=msg->objects[i].Y;
        //S_INFO("Xactual: %f",Xactual);
        //S_INFO("Yactual: %f",Yactual);
        //boxes[i]=(msg->objects[i].x,msg->objects[i].y,msg->objects[i].w,msg->objects[i].h);//boxes.append([data.objects[i].x,data.objects[i].y,data.objects[i].w,data.objects[i].h]);
     }   
        

   }



int main(int argc, char **argv)
{

    ros::init(argc, argv, "map_image_cv");

   ros::NodeHandle n;

   //ROS Publishers for each required sensor data
   ros::Subscriber obstaculos_sub = n.subscribe("objects_detected", 1000, obstaculosCallback);


   ros::Rate loop_rate(10);

    cv::Mat A;

   A = cv::Mat(1000,1000,CV_8UC1, cv::Scalar::all(0));

   //int count = 0;

    float Yactual=0;
    float Xactual = 0;

   while (ros::ok())
   {
      //sensor_msgs::Image map;
      //10*10metros 1pixel=2centimetros
      //map.width=500;
      //map.height=500;
      //map.encoding="mono8";
      //map.size=map.height*map.width;
      //map.step = 1;

      ros::spinOnce();

      loop_rate.sleep();

      //map.header.stamp = ros::Time::now();

      //map.is_bigendian = false;
     // map.step = 1 * map.width;
      A = cv::Mat(1000,1000,CV_8UC1, cv::Scalar::all(0)); 
        cv::waitKey(0);

    for(int j=0; j<(length);j++)
    {

        //double* pixelfirst=map.data.data();
        Xactual=distanceX[j]*50+12.5;
        Yactual = Ys[j]*50+500;
        ROS_INFO("Xm: %f",distanceX[j]);
        ROS_INFO("Ym: %f",Ys[j]);
        ROS_INFO("Xactual: %f",Xactual);
        ROS_INFO("Yactual: %f",Yactual);
        ROS_INFO("j: %i",j);

        cv::circle( A, cv::Point( Xactual, Yactual ), 12.5, cv::Scalar( 255 ), -1, 8 ); 
        /*for (int x=Xactual; x<25;x++)
        {
           // A.at<uchar>(cv::Point(Yactual, x)) = 1;  // setting the pixel (x,y) to 0
          
        }  
        Yactual=Yactual+1;*/
    }
        cv::imshow("map", A);


        ros::spinOnce();

      loop_rate.sleep();
   }

   return 0;
}