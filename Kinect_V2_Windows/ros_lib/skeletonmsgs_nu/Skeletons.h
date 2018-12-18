#ifndef _ROS_skeletonmsgs_nu_Skeletons_h
#define _ROS_skeletonmsgs_nu_Skeletons_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "skeletonmsgs_nu/Skeleton.h"

namespace skeletonmsgs_nu
{

  class Skeletons : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t skeletons_length;
      typedef skeletonmsgs_nu::Skeleton _skeletons_type;
      _skeletons_type st_skeletons;
      _skeletons_type * skeletons;

    Skeletons():
      header(),
      skeletons_length(0), skeletons(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->skeletons_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->skeletons_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->skeletons_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->skeletons_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->skeletons_length);
      for( uint32_t i = 0; i < skeletons_length; i++){
      offset += this->skeletons[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t skeletons_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      skeletons_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      skeletons_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      skeletons_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->skeletons_length);
      if(skeletons_lengthT > skeletons_length)
        this->skeletons = (skeletonmsgs_nu::Skeleton*)realloc(this->skeletons, skeletons_lengthT * sizeof(skeletonmsgs_nu::Skeleton));
      skeletons_length = skeletons_lengthT;
      for( uint32_t i = 0; i < skeletons_length; i++){
      offset += this->st_skeletons.deserialize(inbuffer + offset);
        memcpy( &(this->skeletons[i]), &(this->st_skeletons), sizeof(skeletonmsgs_nu::Skeleton));
      }
     return offset;
    }

    const char * getType(){ return "skeletonmsgs_nu/Skeletons"; };
    const char * getMD5(){ return "3d673547febdc9b93fc78fb55390c688"; };

  };

}
#endif