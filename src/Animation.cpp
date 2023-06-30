#include "Animation.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

Animation::Animation(
    std::map<std::string, std::vector<KeyframeTranslate> > keyframes_translate,
    std::map<std::string, std::vector<KeyframeScale> > keyframes_scale,
     std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate,
    float duration
    )
:
keyframes_translate(keyframes_translate),
keyframes_scale(keyframes_scale),
keyframes_rotate(keyframes_rotate),
duration(duration)
{
}

Animation::~Animation()
{
}

float Animation::get_duration(){return this->duration;}

void Animation::set_keyframes_translate(std::map<std::string, std::vector<KeyframeTranslate> > keyframes_translate)
{
    this->keyframes_translate = keyframes_translate;
}

void Animation::set_keyframes_scale(std::map<std::string, std::vector<KeyframeScale> > keyframes_scale)
{
    this->keyframes_scale = keyframes_scale;
}

void Animation::set_keyframes_rotate( std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate)
{
    this->keyframes_rotate = keyframes_rotate;
}

template<typename Keyframe>
float Animation::get_kf_percentage(std::vector<Keyframe> kf_vect, Keyframe& curr_kf, Keyframe& next_kf)
{
    float kf_percentage = 0.0f;

    for (size_t i = 0; i < kf_vect.size(); i++)
    {
        if (this->curr_progress <= kf_vect[i].timestamp)
        {
            if (i <= 0)
                curr_kf = kf_vect[0];
            else
                  curr_kf = kf_vect[i - 1];
            next_kf = kf_vect[i];

            // evaluate current progress percentage
            if (i <= 0)
            {
                if (kf_vect[0].timestamp == 0)
                    kf_percentage = 0.0f;
                else
                    kf_percentage = this->curr_progress / kf_vect[0].timestamp;
            }
            else
                kf_percentage = (this->curr_progress - kf_vect[i - 1].timestamp) / ( kf_vect[i].timestamp - kf_vect[i - 1].timestamp);

            break ;
        }
    }
    return kf_percentage;
}

/**
 * interpolate_translate - Interpolates a translation matrix using weighted average
*/
// output = (1 - ratio) * prev kf + ratio * nextkf
glm::mat4 Animation::interpolate_translate(float delta_time, std::string body_part)
{
    KeyframeTranslate next_kf;
    KeyframeTranslate curr_kf;
    float kf_percentage = 0.0f;
    glm::mat4 m_iden(1.0f);

    std::vector<KeyframeTranslate> kf_vect = this->keyframes_translate[body_part];
    kf_percentage = this->get_kf_percentage(kf_vect, curr_kf, next_kf);

    // DO NOT REMOVE : Interpolation logic
    // const float output = (1 - kf_percentage) * curr_kf + kf_percentage * next_kf;

    // TODO custom math library should support matrix lerping
    // const glm::vec3 output = glm::mix(glm::vec3(curr_kf.transformation[3]), glm::vec3(next_kf.transformation[3]), kf_percentage);
    const float x_output =  (1 - kf_percentage) * curr_kf.pos_x + kf_percentage * next_kf.pos_x;
    const float y_output =  (1 - kf_percentage) * curr_kf.pos_y + kf_percentage * next_kf.pos_y;
    const float z_output =  (1 - kf_percentage) * curr_kf.pos_z + kf_percentage * next_kf.pos_z;

    // m_iden[3] = glm::vec4(output, 1.0f);

    // std::cout << "curr_kf " << curr_kf << "\n";
    // std::cout << "next_kf " << next_kf << "\n";
    // std::cout << "kf_percentage " << kf_percentage << "\n";
    // std::cout << "curr_progress " << curr_progress << "\n";
    // std::cout << "output " << glm::to_string(output) << "\n";
    // std::cout << "\n";
    
    return glm::translate(m_iden, glm::vec3(x_output, y_output, z_output));
}

/**
 * interpolate_scale - Interpolates a scale matrix using weighted average
*/
// output = (1 - ratio) * prev kf + ratio * nextkf
glm::mat4 Animation::interpolate_scale(float delta_time, std::string body_part)
{
    KeyframeScale next_kf;
    KeyframeScale curr_kf;
    float kf_percentage = 0.0f;
    glm::mat4 m_iden(1.0f);

    std::vector<KeyframeScale> kf_vect = this->keyframes_scale[body_part];
    kf_percentage = this->get_kf_percentage(kf_vect, curr_kf, next_kf);

    // DO NOT REMOVE : Interpolation logic
    // const float output = (1 - kf_percentage) * curr_kf + kf_percentage * next_kf;

    // TODO custom math library should support matrix lerping
    const float x_output =  (1 - kf_percentage) * curr_kf.scale_x + kf_percentage * next_kf.scale_x;
    const float y_output =  (1 - kf_percentage) * curr_kf.scale_y + kf_percentage * next_kf.scale_y;
    const float z_output =  (1 - kf_percentage) * curr_kf.scale_z + kf_percentage * next_kf.scale_z;

    // std::cout << "curr_kf " << curr_kf << "\n";
    // std::cout << "next_kf " << next_kf << "\n";
    // std::cout << "kf_percentage " << kf_percentage << "\n";
    // std::cout << "curr_progress " << curr_progress << "\n";
    // std::cout << "output " << glm::to_string(m_iden) << "\n";
    // std::cout << "\n";
    
    return glm::scale(m_iden, glm::vec3(x_output, y_output, z_output));
}

glm::mat4 Animation::interpolate_rotate(float delta_time, std::string body_part)
{
    KeyframeRotate next_kf;
    KeyframeRotate curr_kf;
    float kf_percentage = 0.0f;
    glm::mat4 m_iden(1.0f);

    std::vector<KeyframeRotate> kf_vect = this->keyframes_rotate[body_part];
    kf_percentage = this->get_kf_percentage(kf_vect, curr_kf, next_kf);

    // DO NOT REMOVE : Interpolation logic
    // const float output = (1 - kf_percentage) * curr_kf + kf_percentage * next_kf;

    // TODO custom math library should support matrix lerping
    // x component
    const float x_output = (1 - kf_percentage) * curr_kf.degree_x + kf_percentage * next_kf.degree_x;
    glm::mat4 x_component = glm::rotate(m_iden, glm::radians(x_output), glm::vec3(1.0f, 0.0f, 0.0f));

    // y component
    const float y_output = (1 - kf_percentage) * curr_kf.degree_y + kf_percentage * next_kf.degree_y;
    glm::mat4 y_component = glm::rotate(m_iden, glm::radians(y_output), glm::vec3(0.0f, 1.0f, 0.0f));

    // z component
    const float z_output = (1 - kf_percentage) * curr_kf.degree_z + kf_percentage * next_kf.degree_z;
    glm::mat4 z_component = glm::rotate(m_iden, glm::radians(z_output), glm::vec3(0.0f, 0.0f, 1.0f));

    // std::cout << "curr_kf " << curr_kf << "\n";
    // std::cout << "next_kf " << next_kf << "\n";
    // std::cout << "kf_percentage " << kf_percentage << "\n";
    // std::cout << "curr_progress " << curr_progress << "\n";
    // std::cout << "output " << glm::to_string(z_component) << "\n";
    // std::cout << "\n";
    
    return x_component * y_component * z_component;
}

std::map<std::string, glm::mat4> Animation::get_next_frame(float delta_time)
{
    std::map<std::string, glm::mat4> res;
    std::map<std::string, Keyframe> selectedBp;
    glm::mat4 translate_interpolated;
    glm::mat4 scale_interpolated;
    glm::mat4 rotate_interpolated;

    // loop through body parts

    // interpolate scale
    scale_interpolated = this->interpolate_scale(delta_time, "bp_1");

    // interpolate translate
    translate_interpolated = this->interpolate_translate(delta_time, "bp_1");

    // interpolate rotate
    rotate_interpolated = this->interpolate_rotate(delta_time, "bp_1");

    // combine interpolations
    glm::mat4 combined = scale_interpolated * translate_interpolated * rotate_interpolated;  
    res.insert({"bp_1", combined});

    // increment progress
    this->curr_progress += delta_time;
    if (this->curr_progress > this->duration)
        this->curr_progress = 0;

    return res;
}


void Animation::test(float delta_time)
{

    
}