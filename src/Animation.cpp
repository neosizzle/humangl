#include "Animation.hpp"
#include <iostream>
#include "FtMath.hpp"

Animation::Animation(
    std::vector<std::string> body_parts,
    std::map<std::string, std::vector<KeyframeTranslate> > keyframes_translate,
    std::map<std::string, std::vector<KeyframeScale> > keyframes_scale,
    std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate,
    float duration
    )
:
body_parts(body_parts),
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
Matrix Animation::interpolate_translate(float delta_time, std::string body_part)
{
    KeyframeTranslate next_kf;
    KeyframeTranslate curr_kf;
    float kf_percentage = 0.0f;
    Matrix m_iden(4, 1.0f);

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
    
    return ftm::translate(m_iden, Vector(3, {x_output, y_output, z_output}));
}

/**
 * interpolate_scale - Interpolates a scale matrix using weighted average
*/
// output = (1 - ratio) * prev kf + ratio * nextkf
Matrix Animation::interpolate_scale(float delta_time, std::string body_part)
{
    KeyframeScale next_kf;
    KeyframeScale curr_kf;
    float kf_percentage = 0.0f;
    Matrix m_iden(4, 1.0f);

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
    
    return ftm::scale(m_iden, Vector(3, {x_output, y_output, z_output}));
}

Matrix Animation::interpolate_rotate(float delta_time, std::string body_part)
{
    KeyframeRotate next_kf;
    KeyframeRotate curr_kf;
    float kf_percentage = 0.0f;
    Matrix m_iden(4, 1.0f);

    std::vector<KeyframeRotate> kf_vect = this->keyframes_rotate[body_part];
    kf_percentage = this->get_kf_percentage(kf_vect, curr_kf, next_kf);

    // DO NOT REMOVE : Interpolation logic
    // const float output = (1 - kf_percentage) * curr_kf + kf_percentage * next_kf;

    // TODO custom math library should support matrix lerping
    // x component
    const float x_output = (1 - kf_percentage) * curr_kf.degree_x + kf_percentage * next_kf.degree_x;
    Matrix x_component = ftm::rotate(m_iden, ftm::radians(x_output), Vector(3, {1.0f, 0.0f, 0.0f}));

    // y component
    const float y_output = (1 - kf_percentage) * curr_kf.degree_y + kf_percentage * next_kf.degree_y;
    Matrix y_component = ftm::rotate(m_iden, ftm::radians(y_output), Vector(3, {0.0f, 1.0f, 0.0f}));

    // z component
    const float z_output = (1 - kf_percentage) * curr_kf.degree_z + kf_percentage * next_kf.degree_z;
    Matrix z_component = ftm::rotate(m_iden, ftm::radians(z_output), Vector(3, {0.0f, 0.0f, 1.0f}));

    // std::cout << "curr_kf " << curr_kf << "\n";
    // std::cout << "next_kf " << next_kf << "\n";
    // std::cout << "kf_percentage " << kf_percentage << "\n";
    // std::cout << "curr_progress " << curr_progress << "\n";
    // std::cout << "output " << glm::to_string(z_component) << "\n";
    // std::cout << "\n";
    
    return x_component * y_component * z_component;
}

std::map<std::string, Matrix> Animation::get_next_frame(float delta_time)
{
    std::map<std::string, Matrix> res;
    Matrix translate_interpolated;
    Matrix scale_interpolated;
    Matrix rotate_interpolated;

    // loop through body parts
    for (int i = 0; i < this->body_parts.size(); i++) {
        std::string body_part = this->body_parts[i];

        // interpolate scale
        scale_interpolated = this->interpolate_scale(delta_time, body_part);

        // interpolate translate
        translate_interpolated = this->interpolate_translate(delta_time, body_part);

        // interpolate rotate
        rotate_interpolated = this->interpolate_rotate(delta_time, body_part);

        // combine interpolations
        Matrix combined = scale_interpolated * translate_interpolated * rotate_interpolated;  
        res.insert({body_part, combined});

    }

    // increment progress
    this->curr_progress += delta_time;
    if (this->curr_progress > this->duration)
        this->curr_progress = 0;

    _frame = res;
    return res;
}


float Animation::getDeltaTime(void)
{
    return (_deltaTime);
}

float Animation::getLastFrame(void)
{
    return (_lastFrame);
}

std::map<std::string, Matrix> Animation::get_current_frame(void)
{
    return (_frame);
}

void Animation::setDeltaTime(float deltaTime)
{
    _deltaTime = deltaTime;
}

void Animation::setLastFrame(float lastFrame)
{
    _lastFrame = lastFrame;
}