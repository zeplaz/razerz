//mathzII.hpp
#pragma once

#include <iostream>
#include <valarray>
#include <cmath>
constexpr int size_64 = 64;
namespace mathz
{
  #define DegreesToRad(angle) angle*M_PI/180
  #define RadToDegrees(angle) angle*180/M_PI

  template<typename Type>
  class vector3_vala
  {
    public  :

     std::valarray<Type> coordinates = decltype(coordinates)(3);

     vector3_vala() = default;
     vector3_vala(std::valarray<Type> val_in)
     {
       coordinates =val_in;
     }
     vector3_vala(Type x, Type y, Type z)
     {
        coordinates[0]=x;
        coordinates[1]=y;
        coordinates[2]=z;
     }

     Type magnitude()
     {
       Type magnitude = std::sqrt(coordinates[0]*coordinates[0]+
                                  coordinates[1]*coordinates[1]+
                                  coordinates[2]*coordinates[2]);
       return magnitude;
     }

     void absolute()
     {
       coordinates[0]= std::abs(coordinates[0]);
       coordinates[1]= std::abs(coordinates[1]);
       coordinates[2]= std::abs(coordinates[2]);
     }

    // template <typename T>
     vector3_vala<Type> New_normalize()
     {
       Type mag = magnitude();
       vector3_vala<Type> temp_vec;
       if(mag>0.0f)
       {
        Type denommag = 1.0f/mag;
        temp_vec.coordinates[0]=coordinates[0]*denommag;
        temp_vec.coordinates[1]=coordinates[1]*denommag;
        temp_vec.coordinates[2]=coordinates[2]*denommag;

        return temp_vec;
       }
       temp_vec.coordinates[0]=0;
       temp_vec.coordinates[1]=0;
       temp_vec.coordinates[2]=0;

       return temp_vec;
     }


     vector3_vala<Type> R_normalize()
     {
     Type mag = magnitude();

     if(mag>0.0f)
     {
      Type denommag = 1.0f/mag;
      coordinates[0]*=denommag;
      coordinates[1]*=denommag;
      coordinates[2]*=denommag;


     }
     return *this;
     }

     void normalize()
     {
       Type mag = magnitude();

       if(mag>0.0f)
       {
        Type denommag = 1.0f/mag;
        coordinates[0]=coordinates[0]*denommag;
        coordinates[1]=coordinates[1]*denommag;
        coordinates[2]=coordinates[2]*denommag;
       }
     }

     Type magnitude_sqr()
     {
       Type magnitude = coordinates[0]*coordinates[0]+
                        coordinates[1]*coordinates[1]+
                        coordinates[2]*coordinates[2];
      return magnitude;
     }

     void conjugate()
     {
       coordinates[0]=-1*coordinates[0];
       coordinates[1]=-1*coordinates[1];
       coordinates[2]=-1*coordinates[2];
     }

     Type dot(const vector3_vala& v) const
     {return coordinates[0]* v[0]+coordinates[1]*v[1]+coordinates[2]*v[2];}

     Type angle(const vector3_vala& v)
     {
       Type theta;
       vector3_vala u = v;
       vector3_vala m = *this;

       theta = dot(u)/(m.magnitude()*u.magnitude());
       theta = RadToDegrees(std::acos(theta));
       return theta;
     }

     vector3_vala<Type> cross(const vector3_vala& v) const
     {
      /*Type x,y,z;
            std::cout << "term1cross::" << coordinates[1]*v[2] << ' '
            <<coordinates[1]*v[2]-coordinates[2]*v[1];
       x = coordinates[1]*v[2]-coordinates[2]*v[1];
       y = coordinates[2]*v[0]-coordinates[0]*v[2];
       z = coordinates[0]*v[1]-coordinates[1]*v[0];
       return vector3_vala<Type>(x,y,z);
       */
       return vector3_vala<Type>(
         (coordinates[1]*v[2])-(coordinates[2]*v[1]),
         (coordinates[2]*v[0])-(coordinates[0]*v[2]),
         (coordinates[0]*v[1])-(coordinates[1]*v[0]));
      }

      void operator %= (const vector3_vala v)
      {
        *this = cross(v);
      }

      vector3_vala<Type>& operator -= (const vector3_vala& val3)
     {
        //std::cout << "const const -=" <<'\n';
        coordinates -= val3.coordinates;
        return (*this);
     }

     vector3_vala<Type>& operator += (const vector3_vala& val3)
     {
         coordinates += val3.coordinates;
         return (*this);
     }

     vector3_vala<Type>& operator * (Type scaler)
     {
       coordinates*scaler;
       return (*this);
     }


     const Type& operator[](int index) const
     {
       return coordinates[index];
     }

      Type& operator[](int index)
     {
       return coordinates[index];
     }

     Type operator()(const char inloc)
     {
       switch (inloc)
       {
       case 'x' :
       {return coordinates[0];
       break;}

       case 'y' :
       {return coordinates[1];
       break;}

       case 'z' :
       {return coordinates[2];
       break;}

       default : return NULL;
      }
     }

     friend std::ostream& operator << (std::ostream &s, const vector3_vala<Type> &v3)
     {
       return s << '['<<v3[0] << ','<<' ' << v3[1] <<','<<' ' << v3[2] <<']';
     }


     template<typename T>
     friend  vector3_vala<T> operator - (const vector3_vala<T>& rhs, const vector3_vala<T>& lhs)
          {
       std::cout << "\n inside lefhandrighthand\n";
       return (vector3_vala<T>(rhs.coordinates - lhs.coordinates));
     }

     template<typename T>
     friend  vector3_vala<T> operator + (const vector3_vala<T>& rhs, const vector3_vala<T>& lhs)
          {
       std::cout << "\n inside lefhandrighthand\n";
       return (vector3_vala<T>(rhs.coordinates + lhs.coordinates));
     }

     //unused or broken opratorz
     /*vector3_vala<Type>& operator =(const vector3_vala<Type> & vec3d)
     {
       coordinates = vec3d.coordinates;
       return *this;
     }*/

     /*void operator -= (const vector3_vala& val3)
     {
       coordinates -= val3.coordinates;
     }*/

     /*friend std::ostream& operator >> (std::ostream &s,  vector3_vala<T> &v3)
     {
       std::cout << "ENter X y z with whitespace inbetween:";
       s >> v3[0] >> v3[1] >>v3[2];
     }
     */

  };

template<typename Type>
Type Dot_vec_3d(vector3_vala<Type>& v1,vector3_vala<Type>& v2)
{
  return v1.dot(v2);
}





  template<typename Type>
  class Quaternion4D
  {
    private :
    Type s;
    vector3_vala<Type> v;
    public :
    Quaternion4D() = default;
    Quaternion4D(Type uS,vector3_vala<Type>& uV) :s(uS), v(uV){}
    Quaternion4D(const Quaternion4D& value) = default;

    Quaternion4D(Quaternion4D &&old) noexcept
    {
      v = std::move(old.v);
      s = std::move(old.s);
    }

    Quaternion4D& operator = (Quaternion4D&& source)
    {
      if(this !=&source)
      {
        v = std::move(source.v);
        s = std::move(source.s);
      }
      return *this;
    }


  /*  Quaternion4D& operator = (Quaternion4D source)
    {
      v.swap(source.v);
      std::swap(s,source.s);
      return *this;
    }*/

    void operator+=(const Quaternion4D& q)
    {
      s+=q.s;
      v+=q.v;
    }

    Quaternion4D operator+(const Quaternion4D& q)const
    {
      Type scalar =s+q.s;
      vector3_vala<Type> temp = v+q.v;
      return Quaternion4D(scalar,temp);
    }

    void operator-=(const Quaternion4D& q)
    {
      s-=q.s;
      v-=q.v;
    }


  /*
template<typename T>
  Quaternion4D operator-(const Quaternion4D<Type>& q)
    {
      Type scalar =s-q.s;
      vector3_vala<Type> temp = v-q.v;
      return Quaternion4D(scalar,temp);
    }*/

    template<typename T>
    Quaternion4D operator-(const Quaternion4D<T>& q)const
    { std::cout <<  "oprator - constcosnt" <<'\n';
      Type scalar =s-q.s;
      vector3_vala<T> temp = v-q.v;
      return Quaternion4D(scalar,temp);
    }
/*
    Quaternion4D operator-(const Quaternion4D& q) const
    {
      Type scalar = s-q.s;
      vector3_vala tempz = v-q.v;
      return Quaternion4D(scalar,tempz);
    }
    */



    template<typename T>
    friend std::ostream& operator<< (std::ostream& stream, const Quaternion4D<T>& Q4d);

  };

template<typename T>
  std::ostream& operator << (std::ostream& stream, const Quaternion4D<T>& Q4d)
  {
    Quaternion4D<T> temp = const_cast<Quaternion4D<T>&&>(Q4d);

          return ( stream << "scaler::" <<Q4d.s <<'\n'

              << "Corndatex:" <<

               temp.v('x')  <<"  Corndatey:" << temp.v[1]
              << "  cornadtez:"<< temp.v[2] << '\n');

  }


  template<typename Type>
  class vector3_4valA
  {
    public  :
    //vector3_4valA() : _M_size(4) {};
     std::valarray<Type> coordinates = decltype(coordinates)(4);
     //_Tp* _M_first; size_t _M_size;
  };



}
