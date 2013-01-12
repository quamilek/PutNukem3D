#ifndef MESHOBJECT_H_INCLUDED
#define MESHOBJECT_H_INCLUDED

#include "engine.h"


class CMeshObject: public IMMObject
{
    public:
        AUTO_SIZE;
        CMeshObject(std::string name);
        virtual ~CMeshObject();

        void drawMesh();
        void updateModel();
        void LoadTexture(const char * image_path, GLuint* texture);

        glm::mat4 Model;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        GLuint VertexArrayID;
        GLuint vertexbuffersize;
        GLuint vertexbuffer;
        GLuint uvbuffer;
        GLuint normalbuffer;
        GLuint tex_diffuse;
        char* meshName;

    private:
        void LoadObj(std::string filename);





};


#endif // MESHOBJECT_H_INCLUDED
