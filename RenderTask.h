#ifndef RENDER_TASK_H_INCLUDED
#define RENDER_TASK_H_INCLUDED

#include "engine.h"



class CRenderTask : public ITask
{
    public:
        CRenderTask();
        virtual ~CRenderTask();


        bool Start();
        void Update();
        void Stop();
    private:
        float speed; //360 stopni/s
        int lastTime;
        float angle;
        void animate();
        void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
        Uint32 getpixel( SDL_Surface *surface, int x, int y );
        void LoadTexture(const char * image_path, GLuint* texture);
        GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
        GLuint locTextureMap0;
        GLuint locTextureMap1;
        GLuint locTextureMap2;

        GLuint programID;
        GLuint programID2;
        GLuint sunshader;

        std::vector<glm::vec3> g_vertex_buffer_data;
        std::vector<glm::vec2> g_uv_buffer_data;
        std::vector<glm::vec3> g_normal_buffer_data;

        glm::mat4 VP;
        glm::mat4 Projection;
        glm::mat4 View ;
        GLuint MatrixID;
        GLuint ModelMatrixID;
        GLuint ViewID;
        GLuint lightID1;

        GLuint VertexArrayID;
        GLuint vertexbuffer;
        GLuint uvbuffer;
        GLuint normalbuffer;

        CMMPointer<CMeshObject> logo3d;
        CMMPointer<CMeshObject> logo3d2;
        CMMPointer<CMeshObject> sun;

        //CMeshObject* logo3d;


        AUTO_SIZE;
};

#endif // RENDERTASK_H_INCLUDED
