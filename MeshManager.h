#ifndef MESHMANAGER_H_INCLUDED
#define MESHMANAGER_H_INCLUDED


#include "engine.h"

class CMeshManager: public Singleton<CMeshManager>
{
    public:
        CMeshManager();
        virtual ~CMeshManager();
        void addMesh(const char * filePath);

    protected:
        //std::list< CMMPointer<CMesh> > meshList;
    private:
        void LoadObj(const char * filePath,std::vector<glm::vec3>& vertex_buffer,std::vector<glm::vec2>& uv_buffer, std::vector<glm::vec3>& normal_buffer);
};

#endif // MESHMANAGER_H_INCLUDED
