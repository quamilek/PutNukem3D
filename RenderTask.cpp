#include "RenderTask.h"



CRenderTask::CRenderTask()
{
    speed=1;
    angle=0;
    lastTime=0;
}

CRenderTask::~CRenderTask()
{


}

void CRenderTask::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
 int bpp = surface->format->BytesPerPixel;
 // Here p is the address to the pixel we want to set
 Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

 switch(bpp)
 {
  case 1:
   *p = pixel;
   break;
  case 2:
   *(Uint16 *)p = pixel;
   break;
  case 3:
   if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
   {
    p[0] = (pixel >> 16) & 0xff;
    p[1] = (pixel >> 8) & 0xff;
    p[2] = pixel & 0xff;
   } else {
    p[0] = pixel & 0xff;
    p[1] = (pixel >> 8) & 0xff;
    p[2] = (pixel >> 16) & 0xff;
   }
   break;
  case 4:
   *(Uint32 *)p = pixel;
   break;
 }
}//putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)

Uint32 CRenderTask::getpixel( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}//get_pixel32( SDL_Surface *surface, int x, int y )

void CRenderTask::LoadTexture(const char * image_path, GLuint* texture)
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


}//CRenderTask::LoadTexture

GLuint CRenderTask::LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}//CRenderTask::LoadShaders


bool CRenderTask::Start()
{
    PROFILE("CRenderTask Start");
    glewExperimental = GL_TRUE;
    glewInit();

    if(GLEW_VERSION_3_1) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    } else {
       glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    std::string modelName = "kostka";
    //logo3d = new CMeshObject(modelName);
    logo3d2 = new CMeshObject(modelName);
    std::string texName = modelName + "_diffuse.bmp";
    logo3d2->LoadTexture(texName.c_str(),&logo3d2->tex_diffuse);
    texName = modelName + "_specular.bmp";
    logo3d2->LoadTexture(texName.c_str(),&logo3d2->tex_specular);
    texName = modelName + "_normal.bmp";
    logo3d2->LoadTexture(texName.c_str(),&logo3d2->tex_normal);

    modelName = "sun";
    sun = new CMeshObject(modelName);

    sun->position.y=5;
    sun->position.x=1.0f;
    sun->position.z=-2.0f;

    programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    programID2 = LoadShaders("NewVShader.vertexshader","NewFShader.fragmentshader");
    sunshader = LoadShaders("sunVshader.vs","sunFshader.fs");

    //LoadTexture("logo_diff.bmp",&Texture);



    //
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	View       = glm::lookAt(
								glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );



    return true;
}//CRenderTask::Start

void CRenderTask::animate()
{


    logo3d2->rotation.y=logo3d2->rotation.y+speed/4.0f;
    if(logo3d2->rotation.y>=360){
        logo3d2->rotation.y=(-360);
    }


}

void CRenderTask::Update()
{
    PROFILE("RenderTask Update");


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);






    sun->updateModel();

    VP = Projection * View;

    glUseProgram(sunshader);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP[0][0]);

    MatrixID = glGetUniformLocation(sunshader, "VP");
    ModelMatrixID = glGetUniformLocation(sunshader, "M");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &sun->Model[0][0]);

    sun->drawMesh();


    logo3d2->updateModel();



    glUseProgram(programID2);
    MatrixID = glGetUniformLocation(programID2, "VP");
    ModelMatrixID = glGetUniformLocation(programID2, "M");
    ViewID = glGetUniformLocation(programID2, "V");
    lightID1 = glGetUniformLocation(programID2,"LightLocation_world_space");
    GLuint locTextureMap0=glGetUniformLocation(programID2,"textureMap0");


    glUniform4f(lightID1,sun->position.x,sun->position.y,sun->position.z,1);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &logo3d2->Model[0][0]);
    glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);


    glUniform1i(locTextureMap0,0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,logo3d2->tex_diffuse);


    logo3d2->drawMesh();

    for(int k=0;k<5;k++){
    for(int j=0;j<5;j++){
    for(int i=0;i<5;i++)
    {
        logo3d2->position.x=-i*2.0f-2.0;
        logo3d2->position.z=j*2.0-2.0f;
        logo3d2->position.y=-k*2.0f;
        logo3d2->updateModel();

        glUseProgram(programID2);
        MatrixID = glGetUniformLocation(programID2, "VP");
        ModelMatrixID = glGetUniformLocation(programID2, "M");
        ViewID = glGetUniformLocation(programID2, "V");

        locTextureMap0=glGetUniformLocation(programID2,"textureMap_diffuse");
        locTextureMap1=glGetUniformLocation(programID2,"textureMap_specular");
        locTextureMap2=glGetUniformLocation(programID2,"textureMap_normal");



        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &logo3d2->Model[0][0]);
        glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,logo3d2->tex_diffuse);
        glUniform1i(locTextureMap0,0);


        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,logo3d2->tex_specular);
        glUniform1i(locTextureMap1,1);


        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D,logo3d2->tex_normal);
        glUniform1i(locTextureMap2,2);




        logo3d2->drawMesh();
    }}}



    animate();



	//if(CInputTask::mouseDown(SDL_BUTTON_LEFT))CKernel::GetSingleton().KillAllTasks();
    if(CInputTask::keyStillDown(SDLK_ESCAPE))CKernel::GetSingleton().KillAllTasks();
    if(CInputTask::keyStillDown(SDLK_RIGHT))sun->position.x-=speed*0.2f;
    if(CInputTask::keyStillDown(SDLK_LEFT))sun->position.x+=speed*0.2f;
    if(CInputTask::keyStillDown(SDLK_UP))sun->position.y+=speed*0.2f;
    if(CInputTask::keyStillDown(SDLK_DOWN))sun->position.y-=speed*0.2f;
    if(CInputTask::keyStillDown(SDLK_w))sun->position.z+=speed*0.2f;
    if(CInputTask::keyStillDown(SDLK_s))sun->position.z-=speed*0.2f;


}

void CRenderTask::Stop()
{

}


