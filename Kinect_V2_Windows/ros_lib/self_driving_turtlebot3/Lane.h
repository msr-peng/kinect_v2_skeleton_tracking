#ifndef _ROS_self_driving_turtlebot3_Lane_h
#define _ROS_self_driving_turtlebot3_Lane_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace self_driving_turtlebot3
{

  class Lane : public ros::Msg
  {
    public:
      typedef double _deviation_type;
      _deviation_type deviation;
      typedef double _curvature_type;
      _curvature_type curvature;

    Lane():
      deviation(0),
      curvature(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_deviation;
      u_deviation.real = this->deviation;
      *(outbuffer + offset + 0) = (u_deviation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_deviation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_deviation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_deviation.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_deviation.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_deviation.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_deviation.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_deviation.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->deviation);
      union {
        double real;
        uint64_t base;
      } u_curvature;
      u_curvature.real = this->curvature;
      *(outbuffer + offset + 0) = (u_curvature.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_curvature.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_curvature.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_curvature.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_curvature.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_curvature.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_curvature.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_curvature.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->curvature);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_deviation;
      u_deviation.base = 0;
      u_deviation.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_deviation.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_deviation.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_deviation.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_deviation.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_deviation.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_deviation.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_deviation.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->deviation = u_deviation.real;
      offset += sizeof(this->deviation);
      union {
        double real;
        uint64_t base;
      } u_curvature;
      u_curvature.base = 0;
      u_curvature.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_curvature.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_curvature.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_curvature.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_curvature.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_curvature.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_curvature.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_curvature.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->curvature = u_curvature.real;
      offset += sizeof(this->curvature);
     return offset;
    }

    const char * getType(){ return "self_driving_turtlebot3/Lane"; };
    const char * getMD5(){ return "fdb4f5e87af4017fdf6cd402caba9344"; };

  };

}
#endif