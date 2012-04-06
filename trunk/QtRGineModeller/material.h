#ifndef MATERIAL_H
#define MATERIAL_H

enum MAT_{MAT_RED,MAT_GREEN,MAT_BLUE,MAT_YELLOW,MAT_CYAN,MAT_MAGENTA,MAT_WHITE,
          MAT_GRAY_75,MAT_GRAY_50,MAT_GRAY_25};

class Material
{
public:
    Material();

    float emission[4];
    float specular[4];
    float diffuse[4];
    float shininess[1];

    void gl();
    void set(int color);
};

#endif // MATERIAL_H
