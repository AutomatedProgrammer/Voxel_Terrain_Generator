#ifndef SCENE
#define SCENE_H
#include <glad/glad.h>
#include <memory>
#include <list>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Block.h"
#include <noise/noise.h>
using namespace noise;

class Scene
{
    private:
        Shader blockShader;
        int width, height, nrChannels;
        std::vector<Block*> chunk1;
        std::vector<Block*> chunk2;
        std::vector<Block*> chunk3;
        std::vector<Block*> chunk4;
        Block* block;
        const int CHUNK_SIZE = 16;
        module::Perlin noise;
        const int CHUNK_OFFSET = 16;

        void setupCube(std::vector<Block*>& chunk)
        {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                for (int y = 0; y < CHUNK_SIZE; y++) {
                    for (int z = 0; z < CHUNK_SIZE; z++) {
                        block = new Block("grass.jpg", width, height, nrChannels, glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
                        chunk.push_back(block);
                    }
                }
            }
        }

        void setupSphere(std::vector<Block*>& chunk)
        {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                for (int y = 0; y < CHUNK_SIZE; y++) {
                    for (int z = 0; z < CHUNK_SIZE; z++) {
                        if (sqrt((float)(x - CHUNK_SIZE / 2) * (x - CHUNK_SIZE / 2) + (y - CHUNK_SIZE / 2) * (y - CHUNK_SIZE / 2) + (z - CHUNK_SIZE / 2) * (z - CHUNK_SIZE / 2)) <= CHUNK_SIZE / 2) {
                            block = new Block("grass.jpg", width, height, nrChannels, glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
                            chunk.push_back(block);
                        }
                    }
                }
            }
        }

        void setupChunk(std::vector<Block*>& chunk, int input_seed, int offset)
        {
            noise.SetSeed(input_seed);
            for (int x = 0; x < CHUNK_SIZE; x++) {
                for (int z = 0; z < CHUNK_SIZE; z++) {
                    float height = noise.GetValue((float)x/10, 0.5f, (float)z/10) * CHUNK_SIZE;
                    if (height < 0)
                    {
                        height *= -1;
                    }
                    else if (height < 1 && height > 0)
                    {
                        height = 1;
                    }
                    for (int y = 0; y < height; y++) {
                        block = new Block("grass.jpg", width, height, nrChannels, glm::vec3((float)(x+offset), (float)(y+offset), (float)(z+offset)));
                        chunk.push_back(block);
                    }
                }
            }
        }   

    public:

        Scene (unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, Camera& camera, int seed)
        {
            //setupSphere();
            //setupCube();
            setupChunk(chunk1, seed, 0);
        }

        void loadShader(const char* vertexPath, const char* fragmentPath)
        {
            blockShader.loadShader(vertexPath, fragmentPath);
        }

        void moveCamera(float speed, int key, Camera& camera)
        {
            camera.moveCamera(speed, key);
        }

        void rotateCamera(double xPos, double yPos, Camera& camera)
        {
            camera.rotateCamera(xPos, yPos);
        }

        void draw(Camera& camera)
        {
            blockShader.use();
            camera.update();

            blockShader.setMat4("view", camera.getView());
            blockShader.setMat4("projection", camera.getProjection());
            
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, block->getPosition());
            blockShader.setMat4("model", model);
            
            for (const auto &pointer: chunk1)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, pointer->getPosition());
                blockShader.setMat4("model", model);
                pointer->draw();
            }

            for (const auto &pointer: chunk2)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, pointer->getPosition());
                blockShader.setMat4("model", model);
                pointer->draw();
            }

            for (const auto &pointer: chunk3)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, pointer->getPosition());
                blockShader.setMat4("model", model);
                pointer->draw();
            }

            for (const auto &pointer: chunk4)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, pointer->getPosition());
                blockShader.setMat4("model", model);
                pointer->draw();
            }
            
            
        }
         
        void unload()
        {
            for (auto &pointer: chunk1)
            {
                delete pointer;
            }
            for (auto &pointer: chunk2)
            {
                delete pointer;
            }
            for (auto &pointer: chunk3)
            {
                delete pointer;
            }
            for (auto &pointer: chunk4)
            {
                delete pointer;
            }
        }

};

#endif