#include "ObjLoader.h"

CObjLoader::CObjLoader()
{

}//CObjLoader::CObjLoader()

CObjLoader::~CObjLoader()
{

}//CObjLoader::~CObjLoader()


void CObjLoader::LoadObj(const char * filePath,std::vector<glm::vec3>& vertex_buffer,std::vector<glm::vec2>& uv_buffer, std::vector<glm::vec3>& normal_buffer)
{
    std::vector<glm::vec3> vertex_list;
    std::vector<glm::vec2> uv_list;
    std::vector<glm::vec3> normal_list;
    std::vector<glm::vec3> vertex_ind;
    std::vector<glm::vec3> uv_ind;
    std::vector<glm::vec3> normal_ind;
    FILE * file = fopen(filePath,"r");

    while(1)
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

    for(int i=0;i<vertex_ind.size();i++)
    {
        for(int j=0;j<3;j++)
        {
            vertex_buffer.push_back(vertex_list[vertex_ind[i][j]-1]);
            uv_buffer.push_back(uv_list[uv_ind[i][j]-1]);
            normal_buffer.push_back(normal_list[normal_ind[i][j]-1]);
        }
    }

}
