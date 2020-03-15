#pragma once
//mathz.hpp
#include <cmath>

namespace mathz
 {
   template <typename Type>
   Type dot_abs_sqrd(Type x1,Type y1, Type x2, Type y2)
   {
     return sqrt(abs(x1*x2)+abs(y1*y2));
   }

   template <typename Type>
   Type distance_euclidean(Type x1,Type y1, Type x2, Type y2)
   {
     return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
   }

   template <typename Type>
   Type distance_manhattan(Type x1,Type y1, Type x2, Type y2)
   {
     return abs(x1-x2)+abs(y1-y2);
   }

   template<typename Type>
   double dot(Type vec1,  Type vec2)
   {return ((vec1.x*vec2.x) + (vec1.y*vec2.y));}

   template<typename Type>
   Type dot( Type x, Type x2, Type y, Type y2)
   {return ((x*x2) + (y*y2));}

   template <typename T> float sign(T val) {
       return (T(0) < val) - (val < T(0));
   }

   template<typename Type>
   double Drectional_dxr(double L,Type C_vec1,Type D_vec2)
    {
      double S;
      double mx = D_vec2.x-C_vec1.x;
      double my = D_vec2.y-C_vec1.y;
    //  std::cout << '\n' << "mx: " << mx << "my" << my << '\n';

      if (mx==my)
       {
        //printf("prereutn mx==my\n");
        return ((mx*L)*(my*L));
        }
       if (mx!= my)
        {
          S = (mx)/(my);
          //printf("in drx3\n");
          return (S*(mx/L)+(mx/L)/S);
        }
      }

   template<class r_type>
   r_type normalize_and_Drectional_vector(double len, r_type vec, double x2, double y2)
   {
     r_type temp_move_vec;

     double x1 =(double) vec.x;
     double y1 =(double) vec.y;

     double dx = abs(x2-x1);
     double dy = abs(y2-y1);
 //std::cout << "normalz info:" << dy <<" dx" << dx <<std::endl;
      dx /= len;
      dy /= len;
     // std::cout << "normalz post deived:" << dy <<" dx" << dx <<std::endl;

      temp_move_vec.x =(float) dx;
      temp_move_vec.y= (float) dy;
     return temp_move_vec;
   }

   template<typename Type>
   Type slope(Type x1, Type x2, Type y1, Type y2)
   {
     return (y1-y2)/(x1-x2);
   }


   template<typename Type>
   class vector2d
   {
     public :
     Type x;
     Type y;

     vector2d() : x(0),y(0){}
     vector2d(Type xin, Type yin) : x(xin),y(yin){}

     inline Type magnitude()
      {
        return sqrt(x*x+y*y);
      }

     inline void normailize()
     {
       Type const tolerance = 0.0001;
       Type m = sqrt(x*x+y*y);
       if(m<tolerance) m =1;
       x/=m;
       y/=m;

       if(fabs(x)<tolerance) x = 0.0;
       if(fabs(y)<tolerance) x = 0.0;
      }

     inline void reverse()
     {
       x=-x;
       y=-y;
     }

     inline vector2d& operator +=(vector2d u)
      {
         x+=u.x;
         y+=u.y;
         return *this;
       }

     inline vector2d& operator -=(vector2d u)
     {
       x-=u.x;
       y-=u.y;
       return *this;
     }

     inline vector2d& operator *=(Type s)
     {
       x*=s;
       y*=s;
       return *this;
     }

     inline vector2d& operator /=(Type s)
     {
       x/=s;
       y/=s;
     }

     inline vector2d operator -()
     {
       return(-x,-y);
     }

     template<class T>
     friend vector2d<T> operator*( vector2d<T>& u, T s);

     template<class T>
     friend vector2d<T> operator -(const vector2d<T>& u, const vector2d<T>& v);

     template<class T>
     friend vector2d<T> operator+ (const vector2d<T>& u, const vector2d<T>& v);

     template<class T>
     friend T operator*(const vector2d<T>& u, const vector2d<T>& v);

     template<class T>
     friend T operator/(const vector2d<T>& u, T s);


   };

   template<class T>
   inline vector2d<T> operator*(const vector2d<T>& u, T s)
   {
     return vector2d(u.x*s,u.y*s);
   }

   template<class T>
   inline vector2d<T> operator -(const vector2d<T>& u, const vector2d<T>& v)
   {
     return vector2d(u.x-v.x,u.y-v.y);
   }

   template<class T>
  inline vector2d<T> operator +(const vector2d<T>& u, const vector2d<T>& v)
   {
     return vector2d(u.x+v.x,u.y+v.y);
   }

   template<class T>
   inline T operator*(const vector2d<T>& u, const vector2d<T>& v)
   {
     return (u.x*v.x+u.y*v.y);
   }

   template<class T>
   inline T operator/(const vector2d<T>& u, T s)
   {
     return vector2d(u.x/s,u.y/s);
   }




   template<typename Type>
   class vector3d
   {
     public :
     Type x;
     Type y;
     Type z;
     vector3d() : x(0),y(0),z(0){}
     vector3d(Type xin, Type yin,Type zin) : x(xin),y(yin), z(zin){}

     inline Type magnitude()
      {
        return sqrt(x*x+y*y+z*z);
      }

     inline void normailize()
     {
       Type const tolerance = 0.0001;
       Type m = sqrt(x*x+y*y+z*z);
       if(m<tolerance) m =1;
       x/=m;
       y/=m;
       z/=m;
       if(fabs(x)<tolerance) x = 0.0;
       if(fabs(y)<tolerance) x = 0.0;
       if(fabs(z)<tolerance) x = 0.0;
      }

     inline void reverse()
     {
       x=-x;
       y=-y;
       z=-z;
     }

     inline vector3d& operator +=(vector3d u)
      {
         x+=u.x;
         y+=u.y;
         z+=u.z;
         return *this;
       }

     inline vector3d& operator -=(vector3d u)
     {
       x-=u.x;
       y-=u.y;
       z-=u.z;
       return *this;
     }

     inline vector3d& operator *=(Type s)
     {
       x*=s;
       y*=s;
       z*=s;
       return *this;
     }

     inline vector3d& operator /=(Type s)
     {
       x/=s;
       y/=s;
       z/=s;
       return *this;
     }

     inline vector3d operator -()
     {
       return(-x,-y,-z);
     }

     template<class T>
     friend vector3d<T> operator*(vector3d<T>& u,T s);

     template<class T>
     friend vector3d<T> operator -(const vector3d<T>& u, const vector3d<T>& v);

     template<class T>
     friend vector3d<T> operator+ (const vector3d<T>& u, const vector3d<T>& v);

     template<class T>
     friend T operator*(const vector3d<T>& u, const vector3d<T>& v);

     template<class T>
     friend T operator/(const vector3d<T>& u, T s);

     template<class T>
     friend vector3d<T> operator^(const vector3d<T>& u, const vector3d<T>& v);

     template<class T>
     friend T TripleScalarProduct(const vector3d<T>& u, const vector3d<T>& v,const vector3d<T>& w);

   };

   template<class T>
   inline vector3d<T> operator*(const vector3d<T>& u, T s)
   {
     return vector3d(u.x*s,u.y*s, u.z*s);
   }

   template<class T>
   inline vector3d<T> operator -(const vector3d<T>& u, const vector3d<T>& v)
   {
     return vector3d(u.x-v.x,u.y-v.y,u.z-v.z);
   }

   template<class T>
  inline vector3d<T> operator +(const vector3d<T>& u, const vector3d<T>& v)
   {
     return vector3d(u.x+v.x,u.y+v.y,u.z+v.z);
   }

   template<class T>
   inline T operator*(const vector3d<T>& u, const vector3d<T>& v)
   {
     return (u.x*v.x+u.y*v.y+u.z*v.z);
   }

   template<class T>
   inline T operator/(const vector3d<T>& u, T s)
   {
     return vector2d(u.x/s,u.y/s,u.z/s);
   }

   template<class T>
   inline vector3d<T> operator^(const vector3d<T>& u, const vector3d<T>& v)
   {
     return vector3d(u.y*v.z-u.z*v.y,
                    -u.x*v.z+u.z*v.x,
                     u.x*v.y-u.y*v.x);

   }

   template<class T>
   inline T TripleScalarProduct(const vector3d<T>& u, const vector3d<T>& v,const vector3d<T>& w)
   {
     return ((u.x*(v.y*w.z-v.z*w.y))+
            (u.y*(-v.x*w.z+v.z*w.x))+
            (u.z*(v.x*w.y-v.y*w.x)));
   }





 }
/*

Stopping distance (SD) = mass * (currentspeed^2) / (2 * maximum braking force) and the rearrangements:

Necessary braking force (BF) = mass * (currentspeed^2) / (2 * remaining distance to target)

Maximum stoppable velocity (Vmax) = sqrt( 2 * maximum braking force * remaining distance to target / mass)

turn over point = ( (Distance to target * braking force) - ((initial velocity^2)* mass/2) ) /(accelerating force + braking force)
8/
 /*  template<typename Type, template<typename> class varclass>
   class calz
   {
     varclass<Type> mathrz;
   };
   */

   /* template<typename Type,class r_type>
    r_type normalize_and_Drectional_vector(double len, Type x, Type y, double x2, double y2)
    {
      r_type temp_move_vec;

      double x1 =(double) x;
      double y1 =(double) y;

      double dx = abs(x2-x1);
      double dy = abs(y2-y1);
  //std::cout << "normalz info:" << dy <<" dx" << dx <<std::endl;
       dx /= len;
       dy /= len;
      // std::cout << "normalz post deived:" << dy <<" dx" << dx <<std::endl;

       temp_move_vec.x =(float) dx;
       temp_move_vec.y= (float) dy;
      return temp_move_vec;
    }*/
