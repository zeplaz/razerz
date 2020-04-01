#include "bullet_collision.hpp"
#include "../committee/simula_entity.hpp"



bool contactAddedCallbackBullet(
btManifoldPoint& cp,
const btCollisionObjectWrapper * colObj0,
int partId0,
int index0,
const btCollisionObjectWrapper * colObj1,
int partId1,
int index1)
{
  bullet_object* temp_obj1  = static_cast<bullet_object*>(colObj0->m_collisionObject->getUserPointer());
  bullet_object* temp_obj2  = static_cast<bullet_object*>(colObj1->m_collisionObject->getUserPointer());
temp_obj1->hit=true;
temp_obj2->hit=true;
  return false;
}


void bullet_collision_detector::create_debug_plane(btTransform& dp_t)
{
  dp_t.setIdentity();
  dp_t.setOrigin(btVector3(0,0,0));
  btStaticPlaneShape* plane = new   btStaticPlaneShape(btVector3(0,1,0),btScalar(0));
  btMotionState* motion_def = new btDefaultMotionState(dp_t);
  btRigidBody::btRigidBodyConstructionInfo info(0.0,motion_def,plane);
  btRigidBody *db_planebody = new btRigidBody(info);
  dynamicsWorld->addRigidBody(db_planebody);
  bodiez.push_back(db_planebody);
  db_planebody->setUserPointer(bodiez[bodiez.size()-1]);
}


void  bullet_collision_detector::clear_world()
{
  if(dynamicsWorld)
  {
    int i;
    for(i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
      btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
      btRigidBody* body = btRigidBody::upcast(obj);
      if (body && body->getMotionState())
      {
        delete body->getMotionState();
      }
      dynamicsWorld->removeCollisionObject(obj);
      delete obj;
    }
    //delete collision shapes
    for (int j = 0; j < collisionShapes.size(); j++)
    {
      btCollisionShape* shape = collisionShapes[j];
      delete shape;
    }
    collisionShapes.clear();

    // delete raw heightfield data
  }
  delete   dispatcher;
  delete broadphase_cache;

  delete solver_sequential_impulse;
  //btConstraintSolver *solver_constraint;
  delete collisionConfig;
  }



















/*
void bullet_collision_detector::bullet_tick_callback(btDynamicsWorld *dynamicsWorld, btScalar timeStep)
{
  objectsCollisions.clear();
  int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
  for (int i = 0; i < numManifolds; i++) {
    btPersistentManifold *contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
    auto *objA = contactManifold->getBody0();
    auto *objB = contactManifold->getBody1();
    auto& collisionsA = objectsCollisions[objA];
    auto& collisionsB = objectsCollisions[objBcalc_fire_solution];
    int numContacts = contactManifold->getNumContacts();
    for (int j = 0; j < numContacts; j++) {
        btManifoldPoint& pt = contactManifold->getContactPoint(j);
        collisionsA.push_back(&pt);
        collisionsB.push_back(&pt);
    }
  }
}*/
/*
bullet_collision_detector::bullet_collision_detector()
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
/*
void bullet_ground::set_ground()
{

   groundTransform.setIdentity();
   groundTransform.setOrigin(btVector3(0, 0, 0));
   groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), -1);
   collisionShapes.push_back(groundShape);
   myMotionState = new btDefaultMotionState(groundTransform);
   rbInfo(0, myMotionState, groundShape, btVector3(0, 0, 0));
   ground_body = new btRigidBody(rbInfo);
   ground_body->setRestitution(groundRestitution);
   dynamicsWorld->addRigidBody(ground_body);
}
*/
