#include <iostream>
#include <string>
#include <vector>
#include <tiny_obj_loader.h>

int main()
{
  constexpr char filename[] = "/home/clint/projects/graphics/data/wt_teapot.obj";
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err_string;

  bool ret = tinyobj::LoadObj(shapes, materials, err_string, filename);

  if (!err_string.empty()) {
    std::cerr << err_string << std::endl;
  }

  if (!ret) {
    return -1;
  }

  std::cout << "# shapes\t:" << shapes.size() << std::endl;
  std::cout << "# materials\t:" << materials.size() << std::endl;
  std::cout << "# vertices\t:" << shapes[0].mesh.indices.size() << std::endl;

  return 0;
}
  
