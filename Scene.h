#ifndef SCENE
#define SCENE_H
#include "Shader.h"
#include "Camera.h"
#include "Chunk.h"

class Scene
{
    private:
        Shader blockShader;
        Chunk chunk;
        Shader snowShader;
        Shader waterShader;

    public:

        Scene (int seed)
        {
            chunk.init(seed);
            blockShader.loadShader("BlockShader.vert", "BlockShader.frag");
            snowShader.loadShader("BlockShader_snow.vert", "BlockShader_snow.frag");
            waterShader.loadShader("BlockShader_water.vert", "BlockShader_water.frag");
        }

        Scene()
        {

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
            

            blockShader.setMat4("view", camera.getView());
            blockShader.setMat4("projection", camera.getProjection());
            
            
            chunk.draw_grass();

            snowShader.use();
            
            snowShader.setMat4("view", camera.getView());
            snowShader.setMat4("projection", camera.getProjection());
            chunk.draw_snow();

            waterShader.use();
            
            waterShader.setMat4("view", camera.getView());
            waterShader.setMat4("projection", camera.getProjection());
            chunk.draw_water();
            
            camera.update();
        }
         
        void unload()
        {
            chunk.unload();
        }

};

#endif