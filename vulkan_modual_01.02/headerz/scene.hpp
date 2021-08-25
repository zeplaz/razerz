

#ifndef SCENE_01_HPP
#define SCENE_01_HPP

#include "symz.hpp"

#include "vk_defintions.hpp"


struct material_emissions{
	glm::vec4 emissive;
	// (r,g,b,*): default (0,0,0,1)
	glm::vec4 ambient;

	// (r,g,b,a): default (0,0,0,1)
		glm::vec4 diffuse;

	// (r,g,b,specularPower): default (0,0,0,1)
	glm::vec4 specular;
};

template <int N, typename Real>
std::valarray<Real> HLift(td::valarray<Real> const& v, Real last)
{
		std::valarray<Real> result(N+1);
		for (int i = 0; i < N; ++i)
		{
				result[i] = v[i];
		}
		result[N] = last;
		return result;
	}
/*
    std::array<Real,N + 1> HLift(std::array<Real,N> const& v, Real last)
    {
        std::array<Real,N + 1> result;
        for (int i = 0; i < N; ++i)
        {
            result[i] = v[i];
        }
        result[N] = last;
        return result;
    }*/

template <typename Real>
	 class BoundingSphere
	 {
	 public:
		         // (center, radius) = (c0, c1, c2, r)
		  std::array<Real, 4> mTuple;
			BoundingSphere()
				 :
				 mTuple{ (Real)0, (Real)0, (Real)0, (Real)0 }

				 BoundingSphere& operator=(BoundingSphere const& sphere)
			         {
			             mTuple = sphere.mTuple;
			             return *this;
			         }

				 inline void SetCenter(glm::vec3 const& center)
					       {
					            mTuple[0] = center.x;
					            mTuple[1] = center.y;
					            mTuple[2] = center.z;
					        }

					inline void SetRadius(Real radius)
								  {
								            mTuple[3] = (radius >= (Real)0 ? radius : (Real)0);
								  }


			inline std::array<Real,3> GetCenter() const
			{
					return std::array<Real,3>{ mTuple[0], mTuple[1], mTuple[2] };
			}

			inline Real GetRadius() const
			{
					return mTuple[3];
			}

			void TransformBy(glm::mat4 const& hmatrix, BoundingSphere& sphere) const
			{
					// The spectral norm (maximum absolute value of the eigenvalues)
					// is smaller or equal to max-row-sum and max-col-sum norm.
					// Therefore, 'norm' is an approximation to the maximum scale.
#if defined (GTE_USE_MAT_VEC)
					glm::vec4 hcenter = hmatrix * HLift(GetCenter(), (Real)1);
					sphere.SetCenter(HProject(hcenter));

					// Use the max-row-sum matrix norm.
					Real r0 = std::fabs(hmatrix(0, 0)) + std::fabs(hmatrix(0, 1)) + std::fabs(hmatrix(0, 2));
					Real r1 = std::fabs(hmatrix(1, 0)) + std::fabs(hmatrix(1, 1)) + std::fabs(hmatrix(1, 2));
					Real r2 = std::fabs(hmatrix(2, 0)) + std::fabs(hmatrix(2, 1)) + std::fabs(hmatrix(2, 2));
					Real norm = std::max(std::max(r0, r1), r2);
#else
					glm::vec4 hcenter = HLift(GetCenter(), (Real)1) * hmatrix;
					sphere.SetCenter(HProject(hcenter));

					// Use the max-col-sum matrix norm.
					Real r0 = std::fabs(hmatrix(0, 0)) + std::fabs(hmatrix(1, 0)) + std::fabs(hmatrix(2, 0));
					Real r1 = std::fabs(hmatrix(0, 1)) + std::fabs(hmatrix(1, 1)) + std::fabs(hmatrix(2, 1));
					Real r2 = std::fabs(hmatrix(0, 2)) + std::fabs(hmatrix(1, 2)) + std::fabs(hmatrix(2, 2));
					Real norm = std::max(std::max(r0, r1), r2);
#endif
					sphere.SetRadius(norm * GetRadius());
			}

	 };
class scene_state : public state
{

	void run_scene_inialze();

};

class render_able : public Spatial
{
	public :
	virtual ~render_able()=default;

	  // Public member access.
	BoundingSphere<float> modelBound;

	bool UpdateModelBound();
	bool UpdateModelNormals();
protected:
			 // Support for geometric updates.
			 inline virtual void UpdateWorldBound() override
			 {
					 modelBound.TransformBy(worldTransform, worldBound);
			 }


};


class spacial_visual_effect
{

//void update();
//virtual void update() =0;
virtual void set_location() =0;
virtual void inialze_vulkan_depent() = 0;
virtual void draw() = 0;

} ;

class scene{

protected :
scene();

std::shared_ptr<vulkan_api> vk_api_ptr;
public :

scene(vulkan_api& in_api)
{
vk_api_ptr	 = std::make_shared<vulkan_api>(in_api);
}

void  setup_partical_A();


void  createDescriptorSetLayout();
void  create_semaphore_fencez();
void  createGraphicsPipeline();
void  createComputePipeline();
void  createCommandPool();
void  createFramebuffers();
void  createVertexBuffer();

void  createUniformBuffers();

void  createDescriptorPool();
void  createDescriptorSets();

void  build_compute_comand_buffers();

void createCommandBuffers();
};
#endif
