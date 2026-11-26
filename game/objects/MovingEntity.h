//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/09
//
// File Name : MovingEntity.h
// 
// 움직이는 개체용 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef MOVING_ENTITY
#define MOVING_ENTITY


#include <cassert>
#include "CGameObject.h"

enum {clockwise = 1, anticlockwise = -1};



class MovingEntity :public CGameObject
{

#define Node GetSceneNode()

protected:
 
  vector3df		m_vVelocity;

  f32				m_dMass;
 
  f32				m_dMaxSpeed;
 
  f32				m_dMaxForce;
 
  f32				m_dMaxTurnRate;

  f32				m_dBoundingRadius;

  f32				m_dNormalSpeed;

  u32				m_uLastUpdatedTime;

public:

	MovingEntity(OwnerType owner,s32 objtype,
		f32   max_speed ,
		f32   mass ,
		f32   turn_rate ,
		f32   max_force, 
		f32   nspeed,
		const	vector3df& pos,
		const	vector3df& rot,
		const	vector3df& scale)
		:CGameObject(owner, objtype, pos, rot, scale),
		m_dMass(mass),
		m_dMaxSpeed(max_speed),
		m_dMaxTurnRate(turn_rate),
		m_dMaxForce(max_force),
		m_dNormalSpeed(nspeed),
		m_uLastUpdatedTime(0)
  {
    
    	
  }

MovingEntity(OwnerType owner,u32 obj_id,
			 s32		objtype,
			 f32   max_speed ,
			 f32   mass ,
			 f32   turn_rate ,
			 f32   max_force, 
			 f32   nspeed,
			 const	vector3df& pos,
			 const	vector3df& rot,
			 const	vector3df& scale)
			 :CGameObject(owner, obj_id, objtype, pos, rot, scale),
			 m_dMass(mass),
			 m_dMaxSpeed(max_speed),
			 m_dMaxTurnRate(turn_rate),
			 m_dMaxForce(max_force),
			 m_dNormalSpeed(nspeed),
			 m_uLastUpdatedTime(0)
{


}



  virtual ~MovingEntity() {};

  virtual	void				control(){}

  virtual	void				render(){};

  virtual	void				OnCommand(){};

  virtual	void				update(u32 timeMs){};

 
  //accessors
  vector3df Velocity()const{return m_vVelocity;}
  void      SetVelocity(const vector3df& NewVel){m_vVelocity = NewVel;}
  
  f32  GetMass()const{return m_dMass;}

  vector3df Pos() {return vector3df(0,0,0); }
  void		SetPos(vector3df& pos) { }


  f32	GetNormalSpeed() const {return m_dNormalSpeed; }

  
  vector3df Side(); 

  f32  MaxSpeed()const{return m_dMaxSpeed;}                       
  void      SetMaxSpeed(f32 new_speed){m_dMaxSpeed = new_speed;}
  
  f32  MaxForce()const{return m_dMaxForce;}
  void      SetMaxForce(f32 mf){m_dMaxForce = mf;}

  bool      IsSpeedMaxedOut()const{return m_dMaxSpeed*m_dMaxSpeed >= m_vVelocity.getLength();}
  f32  Speed()const{return m_vVelocity.getLength();}
  f32  GetSpeedSq()const{return m_vVelocity.getLength();}
  
  vector3df Heading();
  void      SetHeading(const vector3df& new_heading);
  bool      RotateHeadingToFacePosition(vector3df target);

  f32  GetMaxTurnRate()const{return m_dMaxTurnRate;}
  void      SetMaxTurnRate(f32 val){m_dMaxTurnRate = val;}


  inline	double	CalculateTimeToReachPosition(vector3df& pos);
  inline	bool	isAtPosition(const vector3df& pos);

  
};


/*======================================================*/
// 전방을 목표방향으로 돌리기
/*======================================================*/
inline bool MovingEntity::RotateHeadingToFacePosition(vector3df target)
{
  
  
  return false;
}


/*======================================================*/
// 전방을 목표방향으로 바꾸기
/*======================================================*/
inline void MovingEntity::SetHeading(const vector3df& new_heading)
{

	vector3df offset = new_heading;// - Pos();

	offset.normalize();

	vector3df nodeRotation = offset;
	 
	nodeRotation.X = 0.0f;
	 

  //the side vector must always be perpendicular to the heading
  //m_vSide = m_vHeading.Perp();
}


/*======================================================*/
// 전방 벡터 가져오기
/*======================================================*/
inline vector3df MovingEntity::Heading() 
{


	vector3df heading(0, 0, 0); 

	heading.normalize();
	
	return heading;
}


/*======================================================*/
// 사이드 벡터 가져오기
/*======================================================*/
inline vector3df MovingEntity::Side() 
{
	
	vector3df vside(0, 1, 2); 

	vside.normalize();

	return vside;
}


/*======================================================*/
// 포지션에 도달할 수 있는 시간 구하기
/*======================================================*/
inline double MovingEntity::CalculateTimeToReachPosition( vector3df& pos )
{
	return ((Pos() -pos).getLength()) / (MaxSpeed());
}


/*======================================================*/
// 특정 포지션에 있는지
/*======================================================*/
inline	bool MovingEntity::isAtPosition(const vector3df& pos)
{
	const static double tolerance = 10;

	return (Pos() - pos).getLength() < (tolerance * tolerance);
}




#endif