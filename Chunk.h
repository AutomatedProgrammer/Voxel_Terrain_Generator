#ifndef CHUNK_H
#define CHUNK_H

#include "Camera.h"
#include "Shader.h"
#include <noise/noise.h>
#include "Texture.h"
#include <vector>
using namespace noise;

class Chunk
{
    public:
    std::vector<glm::vec3> grass_Blocks;
    std::vector<glm::vec3> snow_Blocks;
    std::vector<glm::vec3> water_Blocks;
    Chunk()
    {
        
    }

    ~Chunk()
    {
    }

    void init(int seed)
    {
        noise.SetSeed(seed);
        for (int x = 0; x < CHUNK_SIZE; x++) {
                for (int z = 0; z < CHUNK_SIZE; z++) {
                    float block_height = noise.GetValue((float)x*0.01, 4, (float)z*0.01);
                    block_height *= 75;
        
                    if (block_height < 0)
                    {
                        block_height *= -1;
                    }
                    else if (block_height < 1 && block_height > 0)
                    {
                        block_height = 1;
                    }
                    else if (block_height >= 100)
                    {
                        block_height *= 100;
                    }
                    for (int y = 0; y < block_height; y++) {
                        if (y < 5)
                        {
                            water_Blocks.push_back(glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
                        }
                        else if (y >= 5 && y < 40)
                        {
                            grass_Blocks.push_back(glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
                        }
                        else if (y >= 40)
                        {
                            snow_Blocks.push_back(glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
                        }
                        
                    }
                    
                }
        }
        //-------------------------------------------------------------------------------------------------------------------------------------------
        //Grass Stuff
        
        grass_amount = grass_Blocks.size();
        glm::mat4 grass_ModelMatrices[grass_amount];
        for (int i = 0; i < grass_Blocks.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, grass_Blocks[i]);
            grass_ModelMatrices[i] = model;
        }

        width = 0;
        height = 0; 
        nrChannels = 0;
        grass_texture.init("grass.jpg", width, height, nrChannels);
        glGenVertexArrays(1, &grass_VAO);
        glGenBuffers(1, &grass_VBO);
        glGenBuffers(1, &grass_EBO);

        glBindVertexArray(grass_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, grass_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(grass_vertices), grass_vertices, GL_STATIC_DRAW);

            //Position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    

            //Texture attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grass_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grass_indices), grass_indices, GL_STATIC_DRAW);
        glBindVertexArray(0);

        glBindVertexArray(grass_VAO);

        glGenBuffers(1, &grass_InstanceVBO);
        glBindBuffer(GL_ARRAY_BUFFER, grass_InstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(grass_ModelMatrices), grass_ModelMatrices, GL_STATIC_DRAW);

        for (int i = 0; i < 4; i++) {
            glEnableVertexAttribArray(2 + i);
            glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
            glVertexAttribDivisor(2 + i, 1);
        }
        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        //-----------------------------------------------------------------------------------------------------------
        //End of grass stuff


        //-------------------------------------------------------------------------------------------------------------
        //Snow stuff
        
        snow_amount = snow_Blocks.size();
        glm::mat4 snow_ModelMatrices[snow_amount];
        for (int i = 0; i < snow_Blocks.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, snow_Blocks[i]);
            snow_ModelMatrices[i] = model;
        }
        width = 0;
        height = 0;
        nrChannels = 0;
        snow_texture.init("snow.jpg", width, height, nrChannels);
        glGenVertexArrays(1, &snow_VAO);
        glGenBuffers(1, &snow_VBO);
        glGenBuffers(1, &snow_EBO);

        glBindVertexArray(snow_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, snow_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(snow_vertices), snow_vertices, GL_STATIC_DRAW);

            //Position attribute
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    

            //Texture attribute
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, snow_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(snow_indices), snow_indices, GL_STATIC_DRAW);
        glBindVertexArray(0);

        glBindVertexArray(snow_VAO);

        glGenBuffers(1, &snow_InstanceVBO);
        glBindBuffer(GL_ARRAY_BUFFER, snow_InstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(snow_ModelMatrices), snow_ModelMatrices, GL_STATIC_DRAW);

        for (int i = 0; i < 4; i++) {
            glEnableVertexAttribArray(5 + i);
            glVertexAttribPointer(5 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
            glVertexAttribDivisor(5 + i, 1);
        }
        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //--------------------------------------------------------------------------------------------------------------------------------
        //End of snow stuff


        //--------------------------------------------------------------------------------------------------------------------------------
        //water stuff

        water_amount = water_Blocks.size();
        glm::mat4 water_ModelMatrices[water_amount];
        for (int i = 0; i < water_Blocks.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, water_Blocks[i]);
            water_ModelMatrices[i] = model;
        }
        width = 0;
        height = 0;
        nrChannels = 0;
        water_texture.init("water.jpg", width, height, nrChannels);
        glGenVertexArrays(1, &water_VAO);
        glGenBuffers(1, &water_VBO);
        glGenBuffers(1, &water_EBO);

        glBindVertexArray(water_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, water_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(water_vertices), water_vertices, GL_STATIC_DRAW);

            //Position attribute
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    

            //Texture attribute
        glEnableVertexAttribArray(7);
        glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, water_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(water_indices), water_indices, GL_STATIC_DRAW);
        glBindVertexArray(0);

        glBindVertexArray(water_VAO);

        glGenBuffers(1, &water_InstanceVBO);
        glBindBuffer(GL_ARRAY_BUFFER, water_InstanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(water_ModelMatrices), water_ModelMatrices, GL_STATIC_DRAW);

        for (int i = 0; i < 4; i++) {
            glEnableVertexAttribArray(8 + i);
            glVertexAttribPointer(8 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
            glVertexAttribDivisor(8 + i, 1);
        }
        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void draw_grass()
    {
        grass_texture.use();
        glBindVertexArray(grass_VAO);
        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, grass_amount);
        glBindVertexArray(0);
    }
    
    void draw_snow()
    {
        snow_texture.use();
        glBindVertexArray(snow_VAO);
        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, snow_amount);
        glBindVertexArray(0);
    }

    void draw_water()
    {
        water_texture.use();
        glBindVertexArray(water_VAO);
        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, water_amount);
        glBindVertexArray(0);
    }

    void unload()
    {
        glDeleteVertexArrays(1, &grass_VAO);
        glDeleteVertexArrays(1, &snow_VAO);
        glDeleteVertexArrays(1, &water_VAO);
        glDeleteBuffers(1, &grass_VBO);
        glDeleteBuffers(1, &snow_VBO);
        glDeleteBuffers(1, &water_VBO);
        glDeleteBuffers(1, &grass_InstanceVBO);
        glDeleteBuffers(1, &snow_InstanceVBO);
        glDeleteBuffers(1, &water_InstanceVBO);
        glDeleteBuffers(1, &grass_EBO);
        glDeleteBuffers(1, &snow_EBO);
        glDeleteBuffers(1, &water_EBO);
    }

    

    
    private:
        const int CHUNK_SIZE = 64;
        float grass_vertices[120] = {
    //Position            //Texture
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  
    -0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,

     0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f
};

float snow_vertices[120] = {
    //Position            //Texture
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  
    -0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,

     0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f
};

float water_vertices[120] = {
    //Position            //Texture
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  
    -0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,

     0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f
};

        unsigned int grass_indices[36] = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4, 
    8, 9, 10, 10, 11, 8, 
    12, 13, 14, 14, 15, 12, 
    16, 17, 18, 18, 19, 16, 
    20, 21, 22, 22, 23, 20 
};

unsigned int snow_indices[36] = {
    0, 1, 2, 2, 3, 0, 
    4, 5, 6, 6, 7, 4, 
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12, 
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20 
};

unsigned int water_indices[36] = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20 
};

    unsigned int grass_VBO, grass_VAO, grass_InstanceVBO;
    unsigned int grass_EBO;

    unsigned int snow_VBO, snow_VAO, snow_InstanceVBO;
    unsigned int snow_EBO;

    unsigned int water_VBO, water_VAO, water_InstanceVBO;
    unsigned int water_EBO;
    Texture grass_texture;
    Texture snow_texture;
    Texture water_texture;
    int width, height, nrChannels;
    module::Perlin noise;
    int grass_amount = 0;
    int snow_amount = 0;
    int water_amount = 0;
};

#endif