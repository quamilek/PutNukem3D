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
        void LoadTexture(const char * image_path, GLuint* texture);
        GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
        GLuint Texture;
        GLuint programID;
        std::vector<glm::vec3> g_vertex_buffer_data;
        std::vector<glm::vec2> g_uv_buffer_data;
        std::vector<glm::vec3> g_normal_buffer_data;
        glm::mat4 MVP;
        glm::mat4 Model;
        glm::mat4 Projection;
        glm::mat4 View ;
        GLuint MatrixID;
        GLuint VertexArrayID;
        GLuint vertexbuffer;
        GLuint uvbuffer;
        GLuint normalbuffer;


        AUTO_SIZE;
};

#endif // RENDERTASK_H_INCLUDED
