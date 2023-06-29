#ifndef ANIMATION_H
#define ANIMATION_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <string>
#include <map>
#include <vector>

struct Keyframe {
    glm::mat4 transformation;
    float timestamp;
};

struct KeyframeRotate {
    glm::mat4 transformation_x;
    glm::mat4 transformation_y;
    glm::mat4 transformation_z;
    float timestamp;
};

/**
 * Animation - represents one animation (series of keyframes)
 *
 */
class Animation
{
    /**
     * name - name of animation
     * duration - duration of animation
     * curr_time - current timeframe
     * curr_progress - current progress duration
     * keyframes_n : vector < map<bodypart name, transformation> > - animation keyframes
     * */
    private:
        std::string name;
        float duration;
        float curr_progress;
        std::map<std::string, std::vector<Keyframe> >  keyframes_translate;
        std::map<std::string, std::vector<Keyframe> >  keyframes_scale;
        std::vector<std::map<std::string, glm::mat4> > keyframes_rotate;

        glm::mat4 interpolate_translate(float delta_time, std::string body_part);
        glm::mat4 interpolate_scale(float delta_time, std::string body_part);

    public:
        void set_keyframes_translate(std::map<std::string, std::vector<Keyframe> > keyframes_translate);
        void set_keyframes_scale(std::map<std::string, std::vector<Keyframe> > keyframes_scale);
        float get_duration();

        /**
         * get_next_frame - interpolates and returns the next frame of current animation vector < map<bodypart name, transformation> >
         * */
        std::map<std::string, glm::mat4> get_next_frame(float delta_time);

        // DEV
        void test(float delta_time);


        Animation(
        std::map<std::string, std::vector<Keyframe> > keyframes_translate,
        std::map<std::string, std::vector<Keyframe> > keyframes_scale,
        std::vector<std::map<std::string, glm::mat4> > keyframes_rotate,
        float duration
        );
        ~Animation();
    };

#endif