
#ifndef RA_BULLET_PYSIC_LIB_HPP
#define RA_BULLET_PYSIC_LIB_HPP

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include <bullet/BulletSoftBody/btDefaultSoftBodySolver.h>
#include <bullet/BulletSoftBody/btSoftBodyHelpers.h>
#include <bullet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>

#include <BulletSoftBody/btSoftBody.h>
#include <BulletDynamics/Featherstone/btMultiBodyConstraintSolver.h>


#include "../../basez/3rdparty/b3BulletDefaultFileIO.h"
#include "pysic_lib.hpp"
//#include "../committee/simula_entity.hpp"
//#include <btSoftBody.h>

#define PRINTF_FLOAT "%7.3f"
constexpr static const btScalar GRAVITY_EARTH = -9.8;

constexpr float gravity = -10.0f;
constexpr float initialY = 10.0f;
constexpr float timeStep = 1.0f / 60.0f;
// TODO some combinations of coefficients smaller than 1.0
// make the ball go up higher / not lose height. Why?
constexpr float groundRestitution = 0.9f;
constexpr float sphereRestitution = 0.9f;
constexpr int maxNPoints = 500;
constexpr static const btScalar s_deltaPhase = 0.25 * 2.0 * SIMD_PI;

static int s_gridSize = 16 + 1;  // must be (2^N) + 1
static btScalar s_gridSpacing = 0.5;
static btScalar s_gridHeightScale = 0.02;
static std::vector<btVector3> collisions;


typedef unsigned char byte_t;


union py_body{
  btRigidBody* rigid_body;
  btMultiBody* multi_body;
  btSoftBody*  soft_body;
};

enum class Body_type
{
  B_RIGID_BODY,
  B_MULTI_BODY,
  B_SOFT_BODY,
};


static void convertFromFloat
(
	byte_t * p,
	btScalar value,
	PHY_ScalarType type
)

{
	btAssert(p && "null");

	switch (type) {
	case PHY_FLOAT:
	{
		btScalar * pf = (btScalar *)p;
		*pf = value;
	}
	break;

	case PHY_UCHAR:
	{
		unsigned char * pu = (unsigned char *)p;
		*pu = (unsigned char)(value / s_gridHeightScale);
	}
	break;

	case PHY_SHORT:
	{
		short * ps = (short *)p;
		*ps = (short)(value / s_gridHeightScale);
	}
	break;

	default:
		btAssert(!"bad type");
	}
};

static int getByteSize
(
	PHY_ScalarType type
)
{
	int size = 0;

	switch (type) {
	case PHY_FLOAT:
		size = sizeof(btScalar);
		break;

	case PHY_UCHAR:
		size = sizeof(unsigned char);
		break;

	case PHY_SHORT:
		size = sizeof(short);
		break;

	default:
		btAssert(!"Bad heightfield data type");
	}

	return size;
}

  inline static Body_type dirive_Body_type(void* in_body)
{
   if(typeid(in_body) == typeid(btRigidBody*))
   {
    return Body_type::B_RIGID_BODY;
   }
   else if(typeid(in_body) == typeid(btMultiBody*))
   {
     return Body_type::B_MULTI_BODY;
   }
     else if(typeid(in_body) == typeid(btSoftBody*))
     {
      return Body_type::B_SOFT_BODY;
     }
}

struct bullet_body{
  btRigidBody* rigid_body;
  btMultiBody* multi_body;
  btSoftBody*  soft_body;
  Body_type body_type;
  int bullet_shape;

  void set_bb(void * in_body)
  {

    body_type =  dirive_Body_type(in_body);

    switch (body_type) {

      case Body_type::B_RIGID_BODY :
      {
        rigid_body = static_cast<btRigidBody*> (in_body);
        bullet_shape  =rigid_body->getCollisionShape()->getShapeType();
        break;
      }
      case Body_type::B_MULTI_BODY :
      {
        multi_body =static_cast<btMultiBody*>(in_body);
      //  bullet_shape  =multi_body->getCollisionShape()->getShapeType();
        break;
      }
      case Body_type::B_SOFT_BODY :
      {
        soft_body = static_cast<btSoftBody*>(in_body);
        bullet_shape  =soft_body->getCollisionShape()->getShapeType();
        break;
      }
    }
}

void* get_body()
{
  switch (body_type) {

    case Body_type::B_RIGID_BODY :
    {
      return rigid_body;
      break;
    }
    case Body_type::B_MULTI_BODY :
    {
      return multi_body;
      break;
    }
    case Body_type::B_SOFT_BODY :
    {
      return soft_body;
      break;
    }
  }
}

};

class simula_entity;
struct bullet_object
{
  bool hit;
  glm::vec4 base_colour;
  simula_entity* root_entity;
  bullet_body bp_body;

  bullet_object(void* in_body, simula_entity* in_root_entity)
  {
    hit           = false;
    //body_type     =dirive_Body_type(in_body);
    bp_body.set_bb(in_body);
    root_entity   =in_root_entity;
  }

  bullet_object(void* in_body, glm::vec4 in_colour,simula_entity* in_root_entity )
  {
    hit           = false;
    bp_body.set_bb(in_body);
    base_colour   = in_colour;
    root_entity     = in_root_entity;

  }
};


//static bool callback_manfold(btManifoldPoint& cp, const btCollisionObject* o0, int id0, int index0,const btCollisionObject* o2, int id2, int index2);
//static void update_model_view(bullet_object* bul_obj, glm::mat4& model_view_matrix);



static void update_model_view(bullet_object* bul_obj, glm::mat4& model_view_matrix)
{

  switch(bul_obj->bp_body.bullet_shape)
  {
    case CUSTOM_CONVEX_SHAPE_TYPE :
    {
        break;
    }

    case BOX_SHAPE_PROXYTYPE :
    {
        break;
    }

    case UNIFORM_SCALING_SHAPE_PROXYTYPE :
    {
        break;
    }


    case COMPOUND_SHAPE_PROXYTYPE :
    {
        break;
    }

    case SPHERE_SHAPE_PROXYTYPE :
    {
    //  btSphereShape* bp_shape =  static_cast<btSphereShape*>(bul_body->getCollisionShape());
    //  float radius = bp_shape->getRadius;
      btTransform tranz;
      //bul_obj->b_body->getMotionState()->getWorldTransform(tranz);
      float mat[16];

      tranz.getOpenGLMatrix(mat);
      glm::mat4 gmmat4 = glm::make_mat4(mat);
    //  model_view_matrix*=gmmat4;
      break;
    }
  }
}



bool contactAddedCallbackBullet(
btManifoldPoint& cp,
const btCollisionObjectWrapper * colObj0,
int partId0,
int index0,
const btCollisionObjectWrapper * colObj1,
int partId1,
int index1);


class bullet_collision_detector
{
  //void bullet_tick_callback(btDynamicsWorld *dynamicsWorld, btScalar timeStep);
  btCollisionDispatcher   *dispatcher;
  btBroadphaseInterface   *broadphase_cache;

  btSequentialImpulseConstraintSolver* solver_sequential_impulse;
  //btConstraintSolver *solver_constraint;
  btDefaultCollisionConfiguration *collisionConfig;

public :
  btDiscreteDynamicsWorld *dynamicsWorld;
  btAlignedObjectArray<btCollisionShape*> collisionShapes;
  std::map<const btCollisionObject*,std::vector<btManifoldPoint*>> objectsCollisions;
  size_t nobjects;

  btAlignedObjectArray<btRigidBody*> bodiez;

//void add_collision_callbackfunc( void *(*func)(btMainfoldPoint, const btCollisionObject* , int , int ,const btCollisionObject* , int , int ));

//bool callbackFunc()

void create_debug_plane(btTransform& dp_t);
void clear_world();
void set_custom_manfold()
{
  gContactAddedCallback=contactAddedCallbackBullet;
}
bullet_collision_detector()
{
  collisionConfig = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfig);
  broadphase_cache = new btDbvtBroadphase();// can use sweep which mihgt be better.
  solver_sequential_impulse = new btSequentialImpulseConstraintSolver;
//  solver_constraint = new btConstraintSolver;
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase_cache, solver_sequential_impulse, collisionConfig);
  dynamicsWorld->setGravity(btVector3(0, GRAVITY_EARTH, 0));
  //dynamicsWorld->setGravity(getUpVector(upAxis, 0.0, -s_gravity));
// dynamicsWorld->setInternalTickCallback(bullet_tick_callback);
}


bool RaycastWorld(const btVector3 &Start, btVector3 &End, btVector3 &Normal) {


                btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
                //RayCallback.m_collisionFilterMask = FILTER_CAMERA;

                // Perform raycast
                dynamicsWorld->rayTest(Start, End, RayCallback);
                if(RayCallback.hasHit()) {

                        End = RayCallback.m_hitPointWorld;
                        Normal = RayCallback.m_hitNormalWorld;
                        return true;
                }

        return false;
}

void ray_cast_all(const btVector3 &start, btVector3& ray_end, btAlignedObjectArray<btVector3> &End_array, btAlignedObjectArray<btVector3> &Normal_array,btAlignedObjectArray<btScalar>& hit_fac_array)
{
  btCollisionWorld::AllHitsRayResultCallback RayCallback(start, ray_end);

  dynamicsWorld->rayTest(start, ray_end, RayCallback);

if(RayCallback.hasHit())
{
  for(size_t i =0; i<RayCallback.m_collisionObjects.size(); i++)
  {
    bullet_object* temp_bro = static_cast<bullet_object*>(RayCallback.m_collisionObjects[i]->getUserPointer());

    std::cout << RayCallback.m_collisionObjects[i]->getHitFraction();
    hit_fac_array.push_back(RayCallback.m_collisionObjects[i]->getHitFraction());
    End_array.push_back(RayCallback.m_hitPointWorld[i]);
    Normal_array.push_back(RayCallback.m_hitNormalWorld[i]);
  }
}
}
//void add_sphere(btTransform& dp_t, float rad, float x, float y, float z, float mass, int flagz);
void add_sphere(btTransform& dp_t, float rad, float x, float y, float z, float mass, int flagz)
{
  dp_t.setIdentity();
  dp_t.setOrigin(btVector3(x,y,z));
  btSphereShape* sphere = new   btSphereShape(rad);
  btVector3 inertia(0,0,0);
  if(mass !=0.0)
  {
    sphere->calculateLocalInertia(mass,inertia);
  }

  btMotionState* motion_def = new btDefaultMotionState(dp_t);
  btRigidBody::btRigidBodyConstructionInfo info(mass,motion_def,sphere,inertia);
  btRigidBody *sphere_body = new btRigidBody(info);
  sphere_body->setCollisionFlags(sphere_body->getCollisionFlags()|flagz);
  dynamicsWorld->addRigidBody(sphere_body);
  bodiez.push_back(sphere_body);
  sphere_body->setUserPointer(bodiez[bodiez.size()-1]);
}



};


	// 9.8 m/s^2

struct bullet_ground
{
btTransform groundTransform;
btCollisionShape* groundShape;
btDefaultMotionState* myMotionState;
btRigidBody::btRigidBodyConstructionInfo rbInfo;
btRigidBody* ground_body;

void set_ground();
void clear()
{
  //delete[] m_rawHeightfieldData;
  //m_rawHeightfieldData = NULL;
}
//byte_t* load_terrian_file(const pathz& in_path,	btScalar& minHeight, btScalar& maxHeight, PHY_ScalarType type);
byte_t* load_terrian_file(const pathz& in_path,	btScalar& minHeight, btScalar& maxHeight, PHY_ScalarType type)
{
  b3BulletDefaultFileIO fileIO;
  char relativeFileName[1024];
  int found = fileIO.findFile(in_path.full_path, relativeFileName, 1024);

  btAlignedObjectArray<char> buffer;
  buffer.reserve(1024);
  int fileId = fileIO.fileOpen(relativeFileName,"rb");
  if (fileId>=0)
  {
      int size = fileIO.getFileSize(fileId);
      if (size>0)
      {
          buffer.resize(size);
          int actual = fileIO.fileRead(fileId,&buffer[0],size);
          if (actual != size)
          {
            //  b3Warning("STL filesize mismatch!\n");
              buffer.resize(0);
          }
      }
      fileIO.fileClose(fileId);
  }
  if (buffer.size())
        {
            int width, height,n;

            unsigned char* image = stbi_image_from_memory((const unsigned char*)&buffer[0], buffer.size(), &width, &height, &n, 3);
            if (image)
            {
              printf("width=%d, height=%d at %d channels\n", width,height, n);
              //have loger run to sysm object of some type..
                s_gridSize = width;
                s_gridSpacing = 0.2;
                s_gridHeightScale = 0.2;
                fileIO.fileClose(fileId);
                long nElements = ((long)s_gridSize) * s_gridSize;
                std::cout << "  nElements = " << nElements << "\n";
                int bytesPerElement = getByteSize(type);//getByteSize(type);
                //	std::cerr << "  bytesPerElement = " << bytesPerElement << "\n";
                btAssert(bytesPerElement > 0 && "bad bytes per element");

                long nBytes = nElements * bytesPerElement;
                //	std::cerr << "  nBytes = " << nBytes << "\n";
                byte_t * raw = new byte_t[nBytes];
                btAssert(raw && "out of memory");

                byte_t * p = raw;

                for (int j = 0; j < width; ++j)
        {

  for (int i = 0; i < width; ++i)
            {
    float x = i * s_gridSpacing;
                float y = j * s_gridSpacing;
    float heightScaling = (14. / 256.);
    float z = double(image[(width - 1 - i) * 3 + width*j * 3]) * heightScaling;
                convertFromFloat(p, z, type);
    // update min/max
    if (!i && !j) {
      minHeight = z;
      maxHeight = z;
    }
    else {
      if (z < minHeight) {
        minHeight = z;
      }
      if (z > maxHeight) {
        maxHeight = z;
      }
    }

                p += bytesPerElement;
            }
        }
        return raw;
}
}
return 0;
}
};

struct bp_plane
{
  BT_DECLARE_ALIGNED_ALLOCATOR();
  btVector3 normal;
  btScalar plane_const;
};

constexpr float SPHERE_FIX_SIZE_04 = 0.4;
struct bp_sphere
{
  btScalar radius;

  void cal_local_Inertia(btScalar mass, btVector3& local_intrtia)
  {
    btScalar el = btScalar(SPHERE_FIX_SIZE_04)* mass * radius;
    local_intrtia.setValue(el,el,el);
  }
};

struct bp_bbox{
  BT_DECLARE_ALIGNED_ALLOCATOR();
  btVector3 box_half_extents;
    double piez = M_PI;
    double pie2 = M_PI_2;
    double pie4 = M_PI_4;
};
#endif

/*
void update_model_view_sphere(btRigidBody* sphere, glm::Mat4& model_view_matrix)
{
  if(sphere->getCollisionShape()->getShapeType()!=SPHERE_SHAPE_PROXYTYPE)
  return;
  //glTranslatef(x,y,z)
}*/
//btVector3 getHalfExtentsWithoutMargin() for btCylinderShape
//cylnder need reotated 90 for x acess glm::roatate(90,0,0);
/*
BOX_SHAPE_PROXYTYPE
CAPSULE_SHAPE_PROXYTYPE
COMPOUND_SHAPE_PROXYTYPE
CONCAVE_SHAPES_END_HERE
CONCAVE_SHAPES_START_HERE
CONE_SHAPE_PROXYTYPE
CONVEX_HULL_SHAPE_PROXYTYPE
CONVEX_SHAPE_PROXYTYPE
CONVEX_TRIANGLEMESH_SHAPE_PROXYTYPE
CYLINDER_SHAPE_PROXYTYPE
EMPTY_SHAPE_PROXYTYPE
FAST_CONCAVE_MESH_PROXYTYPE
GIMPACT_SHAPE_PROXYTYPE
IMPLICIT_CONVEX_SHAPES_START_HERE
INVALID_SHAPE_PROXYTYPE
MAX_BROADPHASE_COLLISION_TYPES
MINKOWSKI_DIFFERENCE_SHAPE_PROXYTYPE
MINKOWSKI_SUM_SHAPE_PROXYTYPE
MULTI_SPHERE_SHAPE_PROXYTYPE
MULTIMATERIAL_TRIANGLE_MESH_PROXYTYPE
SCALED_TRIANGLE_MESH_SHAPE_PROXYTYPE
SOFTBODY_SHAPE_PROXYTYPE
SPHERE_SHAPE_PROXYTYPE
STATIC_PLANE_PROXYTYPE
TERRAIN_SHAPE_PROXYTYPE
TETRAHEDRAL_SHAPE_PROXYTYPE
TRIANGLE_MESH_SHAPE_PROXYTYPE
TRIANGLE_SHAPE_PROXYTYPE
UNIFORM_SCALING_SHAPE_PROXYTYPE

*/


/*
Collisionflagsz

btCollisionObject::CF_STATIC_OPJECT
btCollisionObject::CF_KINEMATIC_OBJECT
btCollisionObject::CF_NO_CONTACT_RESPONSE
btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK//somthing about tirnalzmesh uses for costumcallback!
btCollisionObject::CF_CHARACTER_OBJECT
*/

/*
collisionObjecttypes
CO_COLLISION_OBJECT
CO_RIGID_BODY

*/



/*
class bp_Heightfield : public CommonRigidBodyMTBase//CommonRigidBodyBase
{
public:
//virtual void initPhysics();
  int					upAxis;
	//PHY_ScalarType				m_type;
	byte_t *				rawHeightfieldData;
	btScalar				minHeight;
	btScalar				maxHeight;
	float					phase;	// for dynamics
	bool					isDynamic;
	btHeightfieldTerrainShape * heightfieldShape;

  bp_Heightfield() : upAxis{2},rawHeightfieldData{NULL}, phase{0.0},
	isDynamic{true},
heightfieldShape{0}
  {

  }
};*/
/*

//===========================================================================
class IMotionStateCallback
{
public:
	virtual void		OnMotionStateChanged ( const btTransform& worldTrans ) = 0;
};

//===========================================================================
class MotionState : public btMotionState
{
public:
						MotionState			( const btTransform& startTrans = btTransform::getIdentity())
						: worldTrans_		( startTrans )
						, stateChangedCallbacks_ ()
						{ }

	//---------------------------------------------------------------------------
	// btMotionState interface.

	/// Synchronizes world transform from user to physics
	virtual void		getWorldTransform	( btTransform& centerOfMassWorldTrans ) const
	{
		centerOfMassWorldTrans = worldTrans_;
	}

	///synchronizes world transform from physics to user
	///Bullet only calls the update of worldtransform for active objects
	virtual void		setWorldTransform	( const btTransform& centerOfMassWorldTrans )
	{
		worldTrans_ = centerOfMassWorldTrans;
		if (!stateChangedCallbacks_.empty())
		{
			for (MotionStateCallbacks_t::const_iterator it = stateChangedCallbacks_.begin(),
					it_end = stateChangedCallbacks_.end(); it != it_end; ++it)
			{
				(*it)->OnMotionStateChanged (worldTrans_);
			}
		}
	}

	// Internal interface.
	const btTransform&	getWorldTransform	() const
	{
		return worldTrans_;
	}

	void				setWorldTransform	( const btTransform& centerOfMassWorldTrans
											, bool invokeCallbacks = true )
	{
		worldTrans_ = centerOfMassWorldTrans;
		if (invokeCallbacks && !stateChangedCallbacks_.empty())
		{
			for (MotionStateCallbacks_t::const_iterator it = stateChangedCallbacks_.begin(),
					it_end = stateChangedCallbacks_.end(); it != it_end; ++it)
			{
				(*it)->OnMotionStateChanged (worldTrans_);
			}
		}
	}

	void				AddMotionStateCallback ( IMotionStateCallback* callback )
	{
		IwAssert(PHYSICS, stateChangedCallbacks_.find ( callback ) < 0);
		stateChangedCallbacks_.push_back ( callback );
	}

	void				RemoveMotionStateCallback ( IMotionStateCallback* callback )
	{
		IwAssert(PHYSICS, stateChangedCallbacks_.find (callback) >= 0);
		stateChangedCallbacks_.find_and_remove_fast ( callback );
	}

private:
	typedef std::vector<IMotionStateCallback*>	MotionStateCallbacks_t;

	btTransform								worldTrans_;
	MotionStateCallbacks_t					stateChangedCallbacks_;
};

*/
