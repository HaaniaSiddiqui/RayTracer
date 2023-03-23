#include <iostream>
#include <fstream>
#include "Image.hpp"
#include "../world/ViewPlane.hpp"
#include "RGBColor.hpp"

Image::Image(int hres, int vres)
{
    this->hres = hres;
    this->vres = vres;

    this->colors = new RGBColor*[this->vres];
    for (int i = 0; i < this->vres; i++){
        this->colors[i] = new RGBColor[this->hres];

        for (int j = 0; j < this->hres; j++)
        {
            RGBColor temp(0, 0, 0);
            this->colors[i][j] = temp;
        }
    }
}

Image::Image(const ViewPlane& vp)
{
    this->hres = vp.hres;
    this->vres = vp.vres;

    this->colors = new RGBColor*[this->vres];
    for (int i = 0; i < this->vres; i++){
        this->colors[i] = new RGBColor[this->hres];

        for (int j = 0; j < this->hres; j++)
        {
            RGBColor temp(0, 0, 0);
            this->colors[i][j] = temp;
        }
    }
}

Image::~Image(){

    for (int i = 0; i < this->vres; i++)
    {
        delete[] colors[i];
    }

    delete[] colors;
}

void Image::set_pixel(int x, int y, const RGBColor& color)
{
    colors[y][x] = color;
}

void Image::write_ppm(std::string path) const
{
    std::ofstream file(path);
    file << "P3" << std::endl;
    file << hres << " " << vres << std::endl;
    file << 255 << std::endl;

    float max_val = 0;
    for (int x = 0; x < vres; ++x) {
        for (int y = 0; y < hres; ++y) {
            max_val = std::max(colors[x][y].r,std::max(colors[x][y].g, std::max(colors[x][y].b, max_val)));
        }
    }
    float scl = 255/max_val;

    for (int i = 0; i < vres; i++)
    {
        for (int j = 0; j < hres; j++)
        {
            file << static_cast<int>(colors[i][j].r * scl) << " ";
            file << static_cast<int>(colors[i][j].g * scl) << " ";
            file << static_cast<int>(colors[i][j].b * scl) << " ";
        }
        
        file << std::endl;
    }
    
    file.close();
}


// int main(){

//     Image img(10, 10);

//     RGBColor r(255, 0, 0);
//     img.set_pixel(9, 0, r);

//     img.write_ppm("./test.ppm");

//     return 0;
// }