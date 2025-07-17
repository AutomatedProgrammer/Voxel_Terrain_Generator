#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>


class Camera
{
    private:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        
        float FoV = 90.0f;
        unsigned int SCREEN_HEIGHT = 600, SCREEN_WIDTH = 800;

        glm::mat4 view;
        glm::mat4 projection;

        float lastX = SCREEN_HEIGHT/2;
        float lastY = SCREEN_WIDTH/2;

        double cursor_x = 0.0f, cursor_y = 0.0f;

        float xoffset = 0.0f;
        float yoffset = 0.0f;

        float yaw = -90.0f;
        float pitch = 0.0f;

        bool firstMouse = true;

    public:
        Camera()
        {

        }

        Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, unsigned int SCREEN_HEIGHT, unsigned int SCREEN_WIDTH, float FoV)
        {
            this->position = cameraPos;
            this->front = cameraFront;
            this->up = cameraUp;
            this->SCREEN_HEIGHT = SCREEN_HEIGHT;
            this->SCREEN_WIDTH = SCREEN_WIDTH;
            this->FoV = FoV;
        }

        Camera(unsigned int SCREEN_HEIGHT, unsigned int SCREEN_WIDTH)
        {
            this->SCREEN_HEIGHT = SCREEN_HEIGHT;
            this->SCREEN_WIDTH = SCREEN_WIDTH;
        }

        void update()
        {
            view = glm::lookAt(position, position + front, up);
            projection = glm::perspective(glm::radians(FoV), float(SCREEN_WIDTH)/float(SCREEN_HEIGHT), 0.1f, 100.0f);
        }

        void init(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
        {
            this->SCREEN_HEIGHT = SCR_HEIGHT;
            this->SCREEN_WIDTH = SCR_WIDTH;
        }

        void init(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, unsigned int SCR_HEIGHT, unsigned int SCR_WIDTH, float FoV)
        {
            this->position = cameraPos;
            this->front = cameraFront;
            this->up = cameraUp;
            this->SCREEN_HEIGHT = SCR_HEIGHT;
            this->SCREEN_WIDTH = SCR_WIDTH;
            this->FoV = FoV;
        }

        void moveCamera(float speed, int key) //0 is W, 1 is S, 2 is A, 3 is D
        {
            switch(key)
            {
                case 0:
                {
                    position += speed * front;
                    break;
                }
                case 1:
                {
                    position -= speed * front;
                    break;
                }
                case 2:
                {
                    position -= glm::normalize(glm::cross(front, up)) * speed;
                    break;
                }
                case 3:
                {
                    position += glm::normalize(glm::cross(front, up)) * speed;
                    break;
                }
            }
        }

        void rotateCamera(double xPos, double yPos)
        {
            cursor_x += xPos;
            cursor_y += yPos;
            if (firstMouse)
            {
                lastX = cursor_x;
                lastY = cursor_y;
                firstMouse = false;
            }

            xoffset = cursor_x - lastX;
            yoffset = lastY - cursor_y;
            
            std::cout << "Mouse X:" << lastX << std::endl;
            std::cout << "Mouse Y:" << lastY << std::endl;

            lastX = cursor_x;
            lastY = cursor_y;
            
            

            float sensitivity = 0.1f;
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            yaw += xoffset;
            pitch += yoffset;

            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;

            glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            front = glm::normalize(direction);
        }

        void setFront(glm::vec3 front)
        {
            this->front = front;
        }

        glm::vec3 getPosition()
        {
            return position;
        }

        glm::vec3 getFront()
        {
            return front;
        }

        glm::vec3 getUp()
        {
            return up;
        }

        glm::mat4 getView()
        {
            return view;
        }

        glm::mat4 getProjection()
        {
            return projection;
        }
        
};

#endif