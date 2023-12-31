#ifndef CAMERAALT_H
#define CAMERAALT_H

#include <glad/glad.h>

#include "FtMath.hpp"
#include "Vector.hpp"

#include <vector>
   

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  0.05f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    Vector Position;
    Vector Front;
    Vector Up;
    Vector Right;
    Vector WorldUp;

    // euler Angles
    float Yaw;
    float Pitch;

    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
	
	// flags
	int is_clicked;

    // constructor with vectors
    Camera(Vector position = Vector(3, 0.0f), Vector up = Vector(3, {0.0f, 1.0f, 0.0f}), float yaw = YAW, float pitch = PITCH) : Front(Vector(3, {0.0f, 0.0f, -1.0f})), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(Vector(3, {0.0f, 0.0f, -1.0f})), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = Vector(3, {posX, posY, posZ});
        WorldUp = Vector(3, {upX, upY, upZ});
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    Matrix GetViewMatrix()
    {
        return ftm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction)
    {
        float velocity = MovementSpeed;
        if (direction == FORWARD)
			Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

		// dont no anything if mouse is not clicked
		if (!is_clicked)
			return ;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

	// processes input receoved from mouse click
	void ProcessMouseClick(int is_click)
	{
		is_clicked = is_click;
	}

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        Vector front(3, {
            (float)cos(ftm::radians(Yaw)) * (float)cos(ftm::radians(Pitch)),
            (float)sin(ftm::radians(Pitch)),
            (float)sin(ftm::radians(Yaw)) * (float)cos(ftm::radians(Pitch))
        });
        Front = ftm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = ftm::normalize(ftm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = ftm::normalize(ftm::cross(Right, Front));
    }
};
#endif