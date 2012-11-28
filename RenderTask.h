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
        GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
        GLuint programID;
        GLfloat g_vertex_buffer_data[36*3];
        GLfloat g_color_buffer_data[36*3];
        glm::mat4 MVP;
        glm::mat4 Model;
        glm::mat4 Projection;
        glm::mat4 View ;
        GLuint MatrixID;
        GLuint VertexArrayID;
        GLuint vertexbuffer;
        GLuint colorbuffer;


        AUTO_SIZE;
};

#endif // RENDERTASK_H_INCLUDED
