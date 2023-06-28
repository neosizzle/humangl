#ifndef ANIMATION_H
#define ANIMATION_H

#include <glm/glm.hpp>

#include <string>
#include <map>
#include <vector>

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
     * keyframes_n : vector < map<bodypart name, transformation> > - animation keyframes
     * */
    private:
        std::string name;
        float duration;
        float curr_time;
        std::vector<std::map<std::string, glm::mat4> > keyframes_translate;
        std::vector<std::map<std::string, glm::mat4> > keyframes_scale;
        std::vector<std::map<std::string, glm::mat4> > keyframes_rotate;

        // DEV
        std::vector<float> sample_kf; // sample keyframe
        float curr_progress; // current progress duration
        float current_anim_value; // current animate value (for smoothing)

        // TODO add interp function here?

    public:
        // void set_keyframes(std::vector<std::map<std::string, glm::mat4> > keyframes);
        // std::vector<std::map<std::string, glm::mat4> > get_keyframes();

        void set_duration(float duration);
        float get_duration();

        void set_curr_time(float curr_time);
        float get_curr_time();

        /**
         * get_next_frame - interpolates and returns the next frame of current animation vector < map<bodypart name, transformation> >
         * */
        std::map<std::string, glm::mat4> get_next_frame();

        // DEV
        Animation(
        std::vector<float > sample_kf,
        float duration
        );
        void test(float deltaTime);


        Animation(
        std::vector<std::map<std::string, glm::mat4> > keyframes_translate,
        std::vector<std::map<std::string, glm::mat4> > keyframes_scale,
        std::vector<std::map<std::string, glm::mat4> > keyframes_rotate,
        float duration
        );
        ~Animation();
    };

#endif