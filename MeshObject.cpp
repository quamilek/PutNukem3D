#include "MeshObject.h"


CMeshObject::CMeshObject(std::string name)
{
    rotation.x=0.0f;
    rotation.y=0.0f;
    rotation.z=0.0f;

    position.x=0.0f;
    position.y=0.0f;
    position.z=0.0f;

    scale.x=1.0f;
    scale.y=1.0f;
    scale.z=1.0f;

    LoadObj(name);


}//CMesh()

CMeshObject::~CMeshObject()
{

}//~CMesh()

void CMeshObject::drawMesh()
{


    //przygotowanie buforów na potrzeby shaderów

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,0,(void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,0,(void*)0);

    glDrawArrays(GL_TRIANGLES, 0, vertexbuffersize); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}//drawMesh()

void CMeshObject::updateModel()
{
    //uaktualnianie przesuniêcia obiektu. transformacja z przestrzeni ogólnej do modelu(przesuniêcie, obrót, skala
    Model = glm::mat4(1.0f);

    Model = glm::gtc::matrix_transform::translate(Model,position);

	Model = glm::gtc::matrix_transform::rotate(Model,rotation.x,glm::vec3(1.0f,0.0f,0.0f));
	Model = glm::gtc::matrix_transform::rotate(Model,rotation.y,glm::vec3(0.0f,1.0f,0.0f));
	Model = glm::gtc::matrix_transform::rotate(Model,rotation.z,glm::vec3(0.0f,0.0f,1.0f));


	Model = glm::gtc::matrix_transform::scale(Model,scale);

}//updateModel()

void CMeshObject::LoadObj(std::string filename)
{

    std::vector<glm::vec3> vertex_list;   //pomocnicze tablice do konwersji z formatu obj na coœ co rozumie OpanGL
    std::vector<glm::vec2> uv_list;
    std::vector<glm::vec3> normal_list;
    std::vector<glm::vec3> vertex_ind;
    std::vector<glm::vec3> uv_ind;
    std::vector<glm::vec3> normal_ind;    rotation.x=0.0f;

    std::vector<glm::vec3> vertex_buffer_data;
    std::vector<glm::vec2> uv_buffer_data;
    std::vector<glm::vec3> normal_buffer_data;


    filename+=".obj";

    FILE * file = fopen(filename.c_str(),"r");

    while(1)                                //petla parsuj¹ca plik
    {
            char header[256];
            int result = fscanf(file,"%s", header);
            if (result == EOF) break;

            if(strcmp(header,"v")==0)
            {
                glm::vec3 vertex_temp;
                fscanf(file,"%f %f %f\n",&vertex_temp.x,&vertex_temp.y,&vertex_temp.z);
                vertex_list.push_back(vertex_temp);
            }
            else if(strcmp(header,"vt")==0)
            {
                glm::vec2 uv_temp;
                fscanf(file,"%f %f\n",&uv_temp.x,&uv_temp.y);
                uv_list.push_back(uv_temp);
            }
            else if(strcmp(header,"vn")==0)
            {
                glm::vec3 normal_temp;
                fscanf(file,"%f %f %f\n",&normal_temp.x,&normal_temp.y,&normal_temp.z);
                normal_list.push_back(normal_temp);
            }
            else if(strcmp(header,"f")==0)
            {
                int v[3],u[3],n[3];
                glm::vec3 vertex,uv,normal;
                result = fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                &v[0],&u[0],&n[0],
                                &v[1],&u[1],&n[1],
                                &v[2],&u[2],&n[2]);
                vertex.x = v[0];
                vertex.y = v[1];
                vertex.z = v[2];
                uv.x = u[0];
                uv.y = u[1];
                uv.z = u[2];
                normal.x = n[0];
                normal.y = n[1];
                normal.z = n[2];
                vertex_ind.push_back(vertex);
                uv_ind.push_back(uv);
                normal_ind.push_back(normal);
            }
    }

    for(int i=0;i<vertex_ind.size();i++)                    //pêtla zapisuj¹ca dane do formatu wykorzystanego przy generacji buforów
    {
        for(int j=0;j<3;j++)
        {
            vertex_buffer_data.push_back(vertex_list[vertex_ind[i][j]-1]);
            uv_buffer_data.push_back(uv_list[uv_ind[i][j]-1]);
            normal_buffer_data.push_back(normal_list[normal_ind[i][j]-1]);
        }
    }

    glGenVertexArrays(1, &VertexArrayID);                 //w³asciwa generacja buforow wykorzystanych przy rysowania VAO

	glBindVertexArray(VertexArrayID);

    glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,vertex_buffer_data.size()*sizeof(glm::vec3), &vertex_buffer_data[0], GL_STATIC_DRAW);

	vertexbuffersize=vertex_buffer_data.size();

	glGenBuffers(1,&uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
	glBufferData(GL_ARRAY_BUFFER,uv_buffer_data.size()*sizeof(glm::vec2),&uv_buffer_data[0],GL_STATIC_DRAW);


	glGenBuffers(1,&normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER,normal_buffer_data.size()*sizeof(glm::vec3),&normal_buffer_data[0],GL_STATIC_DRAW);


}//LoadObj()

void CMeshObject::LoadTexture(const char * image_path, GLuint* texture)
{

    SDL_Surface *surface;	// This surface will tell us the details of the image
    GLenum texture_format;
    GLint  nOfColors;

    if ( (surface = SDL_LoadBMP(image_path)) ) {

        // Check that the image's width is a power of 2
        if ( (surface->w & (surface->w - 1)) != 0 ) {
            printf("warning: image.bmp's width is not a power of 2\n");
        }

        // Also check if the height is a power of 2
        if ( (surface->h & (surface->h - 1)) != 0 ) {
            printf("warning: image.bmp's height is not a power of 2\n");
        }

        // get the number of channels in the SDL surface
        nOfColors = surface->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }

        // Have OpenGL generate a texture object handle for us
        glGenTextures( 1, texture );

        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, *texture );

        // Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        glGenerateMipmap(GL_TEXTURE_2D);

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );
    }
    else {
        printf("SDL could not load image.bmp: %s\n", SDL_GetError());
        SDL_Quit();
    }

    // Free the SDL_Surface only if it was successfully created
    if ( surface ) {
        SDL_FreeSurface( surface );
    }


}//LoadTexture
