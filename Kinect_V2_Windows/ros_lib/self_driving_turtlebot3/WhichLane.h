#ifndef _ROS_self_driving_turtlebot3_WhichLane_h
#define _ROS_self_driving_turtlebot3_WhichLane_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace self_driving_turtlebot3
{

  class WhichLane : public ros::Msg
  {
    public:
      typedef bool _right_type;
      _right_type right;
      typedef bool _left_type;
      _left_type left;

    WhichLane():
      right(0),
      left(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_right;
      u_right.real = this->right;
      *(outbuffer + offset + 0) = (u_right.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right);
      union {
        bool real;
        uint8_t base;
      } u_left;
      u_left.real = this->left;
      *(outbuffer + offset + 0) = (u_left.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_right;
      u_right.base = 0;
      u_right.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->right = u_right.real;
      offset += sizeof(this->right);
      union {
        bool real;
        uint8_t base;
      } u_left;
      u_left.base = 0;
      u_left.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->left = u_left.real;
      offset += sizeof(this->left);
     return offset;
    }

    const char * getType(){ return "self_driving_turtlebot3/WhichLane"; };
    const char * getMD5(){ return "fec513e236dcf00a82feccdb516092e3"; };

  };

}
#endif