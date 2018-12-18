#ifndef _ROS_skeletonmsgs_nu_Skeleton_h
#define _ROS_skeletonmsgs_nu_Skeleton_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "skeletonmsgs_nu/SkeletonJoint.h"

namespace skeletonmsgs_nu
{

  class Skeleton : public ros::Msg
  {
    public:
      typedef int32_t _userid_type;
      _userid_type userid;
      typedef skeletonmsgs_nu::SkeletonJoint _head_type;
      _head_type head;
      typedef skeletonmsgs_nu::SkeletonJoint _neck_type;
      _neck_type neck;
      typedef skeletonmsgs_nu::SkeletonJoint _right_hand_type;
      _right_hand_type right_hand;
      typedef skeletonmsgs_nu::SkeletonJoint _left_hand_type;
      _left_hand_type left_hand;
      typedef skeletonmsgs_nu::SkeletonJoint _right_shoulder_type;
      _right_shoulder_type right_shoulder;
      typedef skeletonmsgs_nu::SkeletonJoint _left_shoulder_type;
      _left_shoulder_type left_shoulder;
      typedef skeletonmsgs_nu::SkeletonJoint _right_elbow_type;
      _right_elbow_type right_elbow;
      typedef skeletonmsgs_nu::SkeletonJoint _left_elbow_type;
      _left_elbow_type left_elbow;
      typedef skeletonmsgs_nu::SkeletonJoint _torso_type;
      _torso_type torso;
      typedef skeletonmsgs_nu::SkeletonJoint _left_hip_type;
      _left_hip_type left_hip;
      typedef skeletonmsgs_nu::SkeletonJoint _right_hip_type;
      _right_hip_type right_hip;
      typedef skeletonmsgs_nu::SkeletonJoint _left_knee_type;
      _left_knee_type left_knee;
      typedef skeletonmsgs_nu::SkeletonJoint _right_knee_type;
      _right_knee_type right_knee;
      typedef skeletonmsgs_nu::SkeletonJoint _left_foot_type;
      _left_foot_type left_foot;
      typedef skeletonmsgs_nu::SkeletonJoint _right_foot_type;
      _right_foot_type right_foot;

    Skeleton():
      userid(0),
      head(),
      neck(),
      right_hand(),
      left_hand(),
      right_shoulder(),
      left_shoulder(),
      right_elbow(),
      left_elbow(),
      torso(),
      left_hip(),
      right_hip(),
      left_knee(),
      right_knee(),
      left_foot(),
      right_foot()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_userid;
      u_userid.real = this->userid;
      *(outbuffer + offset + 0) = (u_userid.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_userid.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_userid.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_userid.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->userid);
      offset += this->head.serialize(outbuffer + offset);
      offset += this->neck.serialize(outbuffer + offset);
      offset += this->right_hand.serialize(outbuffer + offset);
      offset += this->left_hand.serialize(outbuffer + offset);
      offset += this->right_shoulder.serialize(outbuffer + offset);
      offset += this->left_shoulder.serialize(outbuffer + offset);
      offset += this->right_elbow.serialize(outbuffer + offset);
      offset += this->left_elbow.serialize(outbuffer + offset);
      offset += this->torso.serialize(outbuffer + offset);
      offset += this->left_hip.serialize(outbuffer + offset);
      offset += this->right_hip.serialize(outbuffer + offset);
      offset += this->left_knee.serialize(outbuffer + offset);
      offset += this->right_knee.serialize(outbuffer + offset);
      offset += this->left_foot.serialize(outbuffer + offset);
      offset += this->right_foot.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_userid;
      u_userid.base = 0;
      u_userid.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_userid.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_userid.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_userid.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->userid = u_userid.real;
      offset += sizeof(this->userid);
      offset += this->head.deserialize(inbuffer + offset);
      offset += this->neck.deserialize(inbuffer + offset);
      offset += this->right_hand.deserialize(inbuffer + offset);
      offset += this->left_hand.deserialize(inbuffer + offset);
      offset += this->right_shoulder.deserialize(inbuffer + offset);
      offset += this->left_shoulder.deserialize(inbuffer + offset);
      offset += this->right_elbow.deserialize(inbuffer + offset);
      offset += this->left_elbow.deserialize(inbuffer + offset);
      offset += this->torso.deserialize(inbuffer + offset);
      offset += this->left_hip.deserialize(inbuffer + offset);
      offset += this->right_hip.deserialize(inbuffer + offset);
      offset += this->left_knee.deserialize(inbuffer + offset);
      offset += this->right_knee.deserialize(inbuffer + offset);
      offset += this->left_foot.deserialize(inbuffer + offset);
      offset += this->right_foot.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "skeletonmsgs_nu/Skeleton"; };
    const char * getMD5(){ return "4229bd747f63f2cf74f6314be0bb5c54"; };

  };

}
#endif