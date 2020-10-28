




class vk_renderer
{

  protected :
  //const char* instance_layers[] {KVLAYER};


  public :
  void init_create_vk_instance()
  {

    vkInstanceCreateInfo instance_create_info{};

    instance_create_info.sType = VK_STUCTURE_TYPE_INSTANCE_CREATE_INFO;

    auto err = vkCreateInstance(&instance_create_info, ---memorymangment, &)
    if(VK_SUCCESS != err)
    {
      std::cerr << "###ERROR::VULKAN insitance create faildz.!\n##############\n";
      //log to error handler?
      // que to engine handler.
    }

  }


}
