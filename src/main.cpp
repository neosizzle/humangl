#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.hpp"
#include "Body.hpp"
#include "CameraAlt.hpp"

#include "FtMath.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(Vector(3, {0.0f, 0.0f, 3.0f}));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// dev test area
#include "Animation.hpp"
Animation dev_fn()
{
    std::vector<std::string> body_parts;
    Matrix m_iden(4, 1.0f);

    body_parts.push_back("bp_1");
    // create translation keyframes for 1 bp
    std::map<std::string, std::vector<KeyframeTranslate> > translation_keyframes;
    std::vector<KeyframeTranslate> kfs_1;
    kfs_1.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    kfs_1.push_back({
        -1.0f,
        0.0f,
        0.0f,
        1.0f
    });
    kfs_1.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    translation_keyframes.insert({"bp_1", kfs_1});

    // create scaling keyframes
    std::map<std::string, std::vector<KeyframeScale> > scale_keyframes;
    std::vector<KeyframeScale> kfs_2;
    kfs_2.push_back({
        1.0f,
        1.0f,
        1.0f,
        0.0f
    });
    kfs_2.push_back({
        2.5f,
        2.5f,
        2.5f,
        1.0f
    });
    kfs_2.push_back({
        1.0f,
        1.0f,
        1.0f,
        2.0f
    });
    scale_keyframes.insert({"bp_1", kfs_2});

    // crete rotation keyframes
    std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate;
    std::vector<KeyframeRotate> kfs_3;
    kfs_3.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f,
    });
    kfs_3.push_back({
        0.0f,
        0.0f,
        180.0f,
        1.0f,
    });
        kfs_3.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f,
    });
    keyframes_rotate.insert({"bp_1", kfs_3});

    // insert bp keyframes into a vector
    Animation anim(
        body_parts,
        translation_keyframes,
        scale_keyframes,
        keyframes_rotate,
        2.0f
    );

    // std::cout << glm::to_string( glm::rotate(m_iden, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f))) << "\n";
    // for(size_t i = 0; i < 101; i++)
    // {
    //    std::map<std::string, glm::mat4> frame = anim.get_next_frame(0.01f);
    // //    std::cout << glm::to_string(frame["bp_1"]) << "\n";
    // }
    return anim;
}

int main()
{
    // dev fn
    Animation anim = dev_fn();
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile shaders
    Shader ourShader("src/shaders/vertex-basic.glsl", "src/shaders/fragment-basic.glsl");

    // initialize options

    // create / initialize animations

    // create our body

    // set up vertex data (and buffer(s)) and configure vertex attributes
    Body Body;

    // DEV
    float angle = 20.0f;

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        anim.setDeltaTime(currentFrame - anim.getLastFrame());
        anim.setLastFrame(currentFrame);

        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(ourShader.ID);

        // pass projection matrix to shader (note that in this case it could change every frame)
        Matrix _projection = ftm::perspective(ftm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", _projection);

        // camera/view transformation
        Matrix view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        Body.draw(anim, ourShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteProgram(ourShader.ID);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) 
               camera.ProcessMouseClick(action == GLFW_PRESS);
}