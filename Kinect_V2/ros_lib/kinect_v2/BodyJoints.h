#ifndef _ROS_kinect_v2_BodyJoints_h
#define _ROS_kinect_v2_BodyJoints_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace kinect_v2
{

  class BodyJoints : public ros::Msg
  {
    public:
      typedef int32_t _user_id_type;
      _user_id_type user_id;
      typedef const char* _tracked_type;
      _tracked_type tracked;
      geometry_msgs::Pose joints[16];

    BodyJoints():
      user_id(0),
      tracked(""),
      joints()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_user_id;
      u_user_id.real = this->user_id;
      *(outbuffer + offset + 0) = (u_user_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_user_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_user_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_user_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->user_id);
      uint32_t length_tracked = strlen(this->tracked);
      varToArr(outbuffer + offset, length_tracked);
      offset += 4;
      memcpy(outbuffer + offset, this->tracked, length_tracked);
      offset += length_tracked;
      for( uint32_t i = 0; i < 16; i++){
      offset += this->joints[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_user_id;
      u_user_id.base = 0;
      u_user_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_user_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_user_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_user_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->user_id = u_user_id.real;
      offset += sizeof(this->user_id);
      uint32_t length_tracked;
      arrToVar(length_tracked, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_tracked; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_tracked-1]=0;
      this->tracked = (char *)(inbuffer + offset-1);
      offset += length_tracked;
      for( uint32_t i = 0; i < 16; i++){
      offset += this->joints[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    const char * getType(){ return "kinect_v2/BodyJoints"; };
    const char * getMD5(){ return "61535990ee807ee844649627b51297c2"; };

  };

}
#endif