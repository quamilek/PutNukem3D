#ifndef OBJLOADER_H_INCLUDED
#define OBJLOADER_H_INCLUDED

#include "engine.h"

class CObjLoader: public Singleton<CObjLoader>
{
    public:
        CObjLoader();
        virtual ~CObjLoader();

        void LoadObj(const char * filePath,std::vector<glm::vec3>& vertex_buffer,std::vector<glm::vec2>& uv_buffer, std::vector<glm::vec3>& normal_buffer);
};

#endif // OBJLOADER_H_INCLUDED
