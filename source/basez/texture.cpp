//texture.cpp
#include "texture.hpp"


unsigned int TextureFromFile(const char *path, const std::string &directory,bool gamma)
  {  std::string filename = std::string(path);
     filename = directory + '/' + filename;

     unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_image_loader(filename.c_str(), &width, &height, &nrComponents);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        free_stbi_data(data);

    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        free_stbi_data(data);
        exit(STBI_LOAD_FAIL);
    }

    return textureID;
}

unsigned int TextureFromFile(std::string& file_path, bool gamma)
{
    /* std::string name = std::string(path);
    std::string filename;
    filename = directory;
    filename += '/' ;
    filename += name;
    */
    std::cout << "##TEXT_FMFILE__aitexture_file:"<<file_path;
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_image_loader(file_path.c_str(), &width, &height, &nrComponents);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        free_stbi_data(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << file_path << std::endl;
        free_stbi_data(data);
    }

    return textureID;
}

void image2::cleanup()
{
  free_stbi_data(image);
  delete [] image;
}

void image2::load(std::string& path,int in_n=0)
{

  image = stbi_image_loader(path.c_str(),&columns,&rows,&n,in_n);
  std::cout <<"stbi_loadcompleate\n";
  }


  GLenum Texture_gl::return_TextureFormat(Format formate)
  {
    switch (formate)
     {
        case Format::Format_Grayscale: return GL_LUMINANCE;
        case Format::Format_GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
        case Format::Format_RGB: return GL_RGB;
        case Format::Format_RGBA: return GL_RGBA;
        case Format::Format_RGBA8: return GL_RGBA8;
        case Format::Format_RGB8: return GL_RGB8;
        default: throw std::runtime_error("Unrecognised Bitmap::Format");
    }
  }

void Texture_gl::init_texture()
{
  glActiveTexture(GL_TEXTURE0+texture_indexUnit);
  glBindTexture(GL_TEXTURE_2D,texture_ID);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, return_TextureFormat(formate_internal), width,
              height, 0,return_TextureFormat(formate_external), GL_UNSIGNED_BYTE, image);
  free_stbi_data(image);
  glBindTexture(GL_TEXTURE_2D,0);
}

void Texture_gl::load_texture(std::string path,int force_channel,int text_unitindex)
{
  std::cout <<"stbi_begin\n";
  image = stbi_image_loader(path.c_str(),&width,&height,&n,force_channel);
  std::cout <<"stbi_loadcompleate\n";
  set_texture_unit_index(text_unitindex);
}

void Texture_gl::set_min_Mag_Filter(Filter filt,char min_mag)
  {
    switch (filt)
    {
      case Filter::LINEAR :
      {
       if(min_mag == 'i')
       minFiler = GL_LINEAR;
       if(min_mag == 'a')
       magFiler = GL_LINEAR;
       break;
      }
      case Filter::NEAREST :
      {
        if(min_mag == 'i')
        minFiler = GL_NEAREST;
        if(min_mag == 'a')
        magFiler = GL_NEAREST;
        break;
      }
      case Filter::MIPMAP :
      {
        if(min_mag == 'i')
        minFiler = GL_MIPMAP;
        if(min_mag == 'a')
        magFiler = GL_MIPMAP;
        break;
      }

      default : throw std::runtime_error("Unrecognised Bitmap::Filter");
    }
  }
