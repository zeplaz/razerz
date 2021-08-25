

#include <memory>

/*
modifed FROM // David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2020
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13
*/
static int NEXT_ID_SYM = 0;

#define MC_SET_IDER(next,in_id) do { typeof(in_id) SWAP = in_id; in_id = next; next++; } while (0)


class sym_object{

protected :
int id;

sym_object()
{
  MC_SET_IDER(NEXT_ID_SYM,this->id);
}

public :
inline int get_id()
{
  return id;
}
};


class Spatial :public  sym_object
{
 private :
  Spatial* spt_parent;

 protected :
   Spatial();
   virtual void UpdateWorldData(double applicationTime);
   virtual void UpdateWorldBound() = 0;
   void PropagateBoundToRoot();

 public:

        std::string name;

        // Abstract base class.
        virtual ~Spatial();

        inline void set_parant(Spatial* parent)
        {
          spt_parent = parent;
        }


        void Update(double applicationTime = 0.0, bool initiator = true);

        // Access to the parent object, which is null for the root of the
        // hierarchy.
        inline Spatial* GetParent()
        {
            return spt_parent;
        }
};




class state : public sym_object
{



};
class gemetic : public Spatial
{

};

class Node : public Spatial
{
public :
virtual ~Node();
Node() = default;
int GetNumChildren() const;

int AttachChild(std::shared_ptr<Spatial> const& child);
int DetachChild(std::shared_ptr<Spatial> const& child);
std::shared_ptr<Spatial> DetachChildAt(int i);

std::shared_ptr<Spatial> SetChild(int i, std::shared_ptr<Spatial> const& child);

std::shared_ptr<Spatial> GetChild(int i);
void DetachAllChildren();

 protected:
        // Support for geometric updates.
        virtual void UpdateWorldData(double applicationTime) override;
        virtual void UpdateWorldBound() override;

        // Support for hierarchical culling.
        virtual void GetVisibleSet(std::shared_ptr<Lenz> const& camera, bool noCull) override;

        // Child pointers.
        std::vector<std::shared_ptr<Spatial>> mChild;
    };

};



struct lighting
{

  glm::vec4 ambient;

  glm::vec4 diffuse;

  glm::vec4 speclar;

//pi/2,0,1,1
  glm::vec4 spotcutoff;

//const,lin,qudaritc,intesity1,0,0,1
  glm::vec4 attenuation;
};
