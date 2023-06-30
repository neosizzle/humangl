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

struct KeyframeTranslate {
    float pos_x;
    float pos_y;
    float pos_z;
    float timestamp;
};

struct KeyframeScale {
    float scale_x;
    float scale_y;
    float scale_z;
    float timestamp;
};

struct KeyframeRotate {
    float degree_x;
    float degree_y;
    float degree_z;
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
        std::map<std::string, std::vector<KeyframeTranslate> >  keyframes_translate;
        std::map<std::string, std::vector<KeyframeScale> >  keyframes_scale;
        std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate;

        glm::mat4 interpolate_translate(float delta_time, std::string body_part);
        glm::mat4 interpolate_scale(float delta_time, std::string body_part);
        glm::mat4 interpolate_rotate(float delta_time, std::string body_part);

        template<typename Keyframe>
        float get_kf_percentage(std::vector<Keyframe> kf_vect, Keyframe& curr_kf, Keyframe& next_kf);

    public:
        void set_keyframes_translate(std::map<std::string, std::vector<KeyframeTranslate> > keyframes_translate);
        void set_keyframes_scale(std::map<std::string, std::vector<KeyframeScale> > keyframes_scale);
        void set_keyframes_rotate( std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate);
        float get_duration();

        /**
         * get_next_frame - interpolates and returns the next frame of current animation vector < map<bodypart name, transformation> >
         * */
        std::map<std::string, glm::mat4> get_next_frame(float delta_time);

        // DEV
        void test(float delta_time);


        Animation(
        std::map<std::string, std::vector<KeyframeTranslate> > keyframes_translate,
        std::map<std::string, std::vector<KeyframeScale> > keyframes_scale,
         std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate,
        float duration
        );
        ~Animation();
    };

#endif