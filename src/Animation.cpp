#include "Animation.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

Animation::Animation(
    std::map<std::string, std::vector<Keyframe> > keyframes_translate,
    std::map<std::string, std::vector<Keyframe> > keyframes_scale,
    std::vector<std::map<std::string, glm::mat4> > keyframes_rotate,
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

void Animation::set_keyframes_translate(std::map<std::string, std::vector<Keyframe> > keyframes_translate)
{
    this->keyframes_translate = keyframes_translate;
}

void Animation::set_keyframes_scale(std::map<std::string, std::vector<Keyframe> > keyframes_scale)
{
    this->keyframes_scale = keyframes_scale;
}
/**
 * interpolate_translate - Interpolates a translation matrix using weighted average
*/
// output = (1 - ratio) * prev kf + ratio * nextkf
glm::mat4 Animation::interpolate_translate(float delta_time, std::string body_part)
{
    Keyframe next_kf;
    Keyframe curr_kf;
    float kf_percentage = 0.0f;
    glm::mat4 m_iden(1.0f);

    std::vector<Keyframe> kf_vect = this->keyframes_translate[body_part];
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

    // DO NOT REMOVE : Interpolation logic
    // const float output = (1 - kf_percentage) * curr_kf + kf_percentage * next_kf;

    // TODO custom math library should support matrix lerping
    const glm::vec3 output = glm::mix(glm::vec3(curr_kf.transformation[3]), glm::vec3(next_kf.transformation[3]), kf_percentage);
    m_iden[3] = glm::vec4(output, 1.0f);

    // std::cout << "curr_kf " << curr_kf << "\n";
    // std::cout << "next_kf " << next_kf << "\n";
    // std::cout << "kf_percentage " << kf_percentage << "\n";
    // std::cout << "curr_progress " << curr_progress << "\n";
    // std::cout << "output " << glm::to_string(output) << "\n";
    // std::cout << "\n";
    
    return m_iden;
}

/**
 * interpolate_scale - Interpolates a scale matrix using weighted average
*/
// output = (1 - ratio) * prev kf + ratio * nextkf
glm::mat4 Animation::interpolate_scale(float delta_time, std::string body_part)
{
    Keyframe next_kf;
    Keyframe curr_kf;
    float kf_percentage = 0.0f;
    glm::mat4 m_iden(1.0f);

    std::vector<Keyframe> kf_vect = this->keyframes_scale[body_part];
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

    // DO NOT REMOVE : Interpolation logic
    // const float output = (1 - kf_percentage) * curr_kf + kf_percentage * next_kf;

    // TODO custom math library should support matrix lerping
    const glm::vec3 output0 = glm::mix(glm::vec3(curr_kf.transformation[0]), glm::vec3(next_kf.transformation[0]), kf_percentage);
    const glm::vec3 output1 = glm::mix(glm::vec3(curr_kf.transformation[1]), glm::vec3(next_kf.transformation[1]), kf_percentage);
    const glm::vec3 output2 = glm::mix(glm::vec3(curr_kf.transformation[2]), glm::vec3(next_kf.transformation[2]), kf_percentage);

    m_iden[0] = glm::vec4(output0, 0.0f);
    m_iden[1] = glm::vec4(output1, 0.0f);
    m_iden[2] = glm::vec4(output2, 0.0f);

    // std::cout << "curr_kf " << curr_kf << "\n";
    // std::cout << "next_kf " << next_kf << "\n";
    // std::cout << "kf_percentage " << kf_percentage << "\n";
    // std::cout << "curr_progress " << curr_progress << "\n";
    // std::cout << "output " << glm::to_string(m_iden) << "\n";
    // std::cout << "\n";
    
    return m_iden;
}

std::map<std::string, glm::mat4> Animation::get_next_frame(float delta_time)
{
    std::map<std::string, glm::mat4> res;
    std::map<std::string, Keyframe> selectedBp;
    glm::mat4 translate_interpolated;
    glm::mat4 scaled_interpolated;

    // loop through body parts

    // interpolate scale
    scaled_interpolated = this->interpolate_scale(delta_time, "bp_1");

    // interpolate translate
    translate_interpolated = this->interpolate_translate(delta_time, "bp_1");

    // interpolate rotate

    // combine interpolations
    glm::mat4 combined = scaled_interpolated * translate_interpolated;  
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