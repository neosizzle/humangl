#include "Animation.hpp"
#include <glm/glm.hpp>

Animation::Animation(
    std::vector<std::map<std::string, glm::mat4> > keyframes_translate,
    std::vector<std::map<std::string, glm::mat4> > keyframes_scale,
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

// DEV
Animation::Animation(
    std::vector<float > sample_kf,
    float duration
    )
{
    this->duration = duration;
    this->sample_kf = sample_kf;
    this->curr_progress = 0.0f;
    this->current_anim_value = 1.0f;
}

void Animation::set_duration(float duration) {this->duration = duration;}

float Animation::get_duration(){return this->duration;}

void Animation::set_curr_time(float curr_time) {this->curr_time = curr_time;}

float Animation::get_curr_time(){return this->curr_time;}

std::map<std::string, glm::mat4> Animation::get_next_frame()
{
    std::map<std::string, glm::mat4> res;

    // loop through current keyframes

    // do some interpolation magick

    // return interpolated 
    return res;
}

#include <iostream>
void Animation::test(float deltaTime)
{
    // determine current total progress percentage ( 0 - 1 )
    const float prog_percentage = curr_progress / this->duration;

    // determine next keyframe
    const int next_step = this->sample_kf.size() * prog_percentage ;
    // std::cout << "next_step " << next_step << " size " << this->sample_kf.size() << " PROG perentage " << prog_percentage << "\n";    

    // interpolate
    // get value for next kf
    const float next_value = this->sample_kf[next_step];

    // determine progress to next keyframe (0-1) ((curr animate value - prev value) / next step
    int prev_idx;
    if (next_step <= 0)
        prev_idx = 0;
    else
        prev_idx = next_step - 1;
    
    const float next_kf_progress = (this->current_anim_value - this->sample_kf[prev_idx]) / next_step;
    
    // determine rate of increase based on duration
    const float rate_of_increase = deltaTime / this->duration ;

    // evaluate next animate value
    const float next_anim_value = this->current_anim_value + (next_value * rate_of_increase);

    std::cout << "next_kf_progress " << next_kf_progress << " next_step " << next_step <<"\n";
    // std::cout << "next_value " << next_value << " next_anim_value " << next_anim_value <<  " rate_of_increase " << rate_of_increase << "\n";

    // imcrement progress counter
    this->curr_progress += deltaTime;
    if (this->curr_progress >= duration)
        this->curr_progress = 0;

    // set current animate values
    this->current_anim_value = next_anim_value; 
}