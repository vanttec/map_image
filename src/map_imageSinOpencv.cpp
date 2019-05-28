#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include "custom_msgs/ObjDetectedList.h"
#include <Eigen/Dense>
#include <vector>


int length=0;
float distanceX[]={};
float Ys[]={};


void obstaculosCallback(const custom_msgs::ObjDetectedList::ConstPtr& msg)
   {
    length=msg->len;
    //float objects;
    //float objects=msg-> objects;
    //obj = msg->objects;
    //ROS_INFO("length: %i",length);

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

   ros::init(argc, argv, "map_image_no_cv");

   ros::NodeHandle n;

   //ROS Publishers for each required sensor data
   ros::Publisher map_pub = n.advertise<sensor_msgs::Image>("map_image", 1000);

   ros::Subscriber obstaculos_sub = n.subscribe("objects_detected", 1000, obstaculosCallback);


   ros::Rate loop_rate(10);


   //int count = 0;
   int pixelfirst=0;
   int pixelend=0;
   std::vector<unsigned char>::iterator it;
   //std::vector<unsigned char>::iterator2 (25,255);
   int size=0;
   unsigned char lol= 0;
    float Yactual=0;
    float Xactual = 0;

   while (ros::ok())
   {
      sensor_msgs::Image map;
      //10*10metros 1pixel=2centimetros
      map.width=500;
      map.height=500;
      map.encoding="mono8";
      //map.size=map.height*map.width;
      //map.step = 1;

      ros::spinOnce();

      loop_rate.sleep();

      map.header.stamp = ros::Time::now();

      map.is_bigendian = false;
      map.step = 1 * map.width;
      size=map.height*map.width-length*625;

    for(int i=0; i<(size);i++)
        {
           map.data.push_back(255);
           //map.data.push_back(0);
           //map.data.push_back(0);
        }

    for(int j=0; j<(length);j++)
    {
        //double* pixelfirst=map.data.data();
        Yactual=distanceX[j]*50;
        Xactual = Ys[j]*50;
        ROS_INFO("Xactual: %f",Xactual);
        ROS_INFO("Yactual: %f",Yactual);
        ROS_INFO("j: %i",j);
        pixelfirst=(Yactual*map.width)+Xactual;
            
        for (int x=0; x<25;x++)
        {
            
            it=map.data.begin()+pixelfirst;
            
            //pixelend=pixelfirst+25;
            map.data.insert (it,25,0);
            
           //map.data.push_back(255);

           //map.data.push_back(255);
           //map.data.push_back(255);


           pixelfirst=pixelfirst+map.width;
           
        }   
    }

     

   map_pub.publish(map);
   }

   return 0;
}