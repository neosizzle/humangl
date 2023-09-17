#ifndef ANIMATION_H
#define ANIMATION_H

#include "FtMath.hpp"

#include <string>
#include <map>
#include <vector>

/**
 * Put this code in main for testing.
 * 
*/

// dev test area
// #include "Animation.hpp"
// Animation dev_fn()
// {
//     std::vector<std::string> body_parts;
//     Matrix m_iden(4, 1.0f);

//     body_parts.push_back("bp_1");
//     // create translation keyframes for 1 bp
//     std::map<std::string, std::vector<KeyframeTranslate> > translation_keyframes;
//     std::vector<KeyframeTranslate> kfs_1;
//     kfs_1.push_back({
//         0.0f,
//         0.0f,
//         0.0f,
//         0.0f
//     });
//     kfs_1.push_back({
//         -1.0f,
//         0.0f,
//         0.0f,
//         1.0f
//     });
//     kfs_1.push_back({
//         0.0f,
//         0.0f,
//         0.0f,
//         2.0f
//     });
//     translation_keyframes.insert({"bp_1", kfs_1});

//     // create scaling keyframes
//     std::map<std::string, std::vector<KeyframeScale> > scale_keyframes;
//     std::vector<KeyframeScale> kfs_2;
//     kfs_2.push_back({
//         1.0f,
//         1.0f,
//         1.0f,
//         0.0f
//     });
//     kfs_2.push_back({
//         2.5f,
//         2.5f,
//         2.5f,
//         1.0f
//     });
//     kfs_2.push_back({
//         1.0f,
//         1.0f,
//         1.0f,
//         2.0f
//     });
//     scale_keyframes.insert({"bp_1", kfs_2});

//     // crete rotation keyframes
//     std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate;
//     std::vector<KeyframeRotate> kfs_3;
//     kfs_3.push_back({
//         0.0f,
//         0.0f,
//         0.0f,
//         0.0f,
//     });
//     kfs_3.push_back({
//         0.0f,
//         0.0f,
//         180.0f,
//         1.0f,
//     });
//         kfs_3.push_back({
//         0.0f,
//         0.0f,
//         0.0f,
//         2.0f,
//     });
//     keyframes_rotate.insert({"bp_1", kfs_3});

//     // insert bp keyframes into a vector
//     Animation anim(
//         body_parts,
//         translation_keyframes,
//         scale_keyframes,
//         keyframes_rotate,
//         2.0f
//     );

//     // std::cout << glm::to_string( glm::rotate(m_iden, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f))) << "\n";
//     // for(size_t i = 0; i < 101; i++)
//     // {
//     //    std::map<std::string, glm::mat4> frame = anim.get_next_frame(0.01f);
//     // //    std::cout << glm::to_string(frame["bp_1"]) << "\n";
//     // }
//     return anim;
// }
// dev fn
// Animation anim = dev_fn();

/**
 * Put this in the render loop to apply animations
*/
// // apply animations
// std::map<std::string, glm::mat4> frame = anim.get_next_frame(deltaTime);
// model = frame["bp_1"] * model;

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
        std::vector<std::string> body_parts;
        std::map<std::string, std::vector<KeyframeTranslate> >  keyframes_translate;
        std::map<std::string, std::vector<KeyframeScale> >  keyframes_scale;
        std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate;

        Matrix interpolate_translate(float delta_time, std::string body_part);
        Matrix interpolate_scale(float delta_time, std::string body_part);
        Matrix interpolate_rotate(float delta_time, std::string body_part);

        template<typename Keyframe>
        float get_kf_percentage(std::vector<Keyframe> kf_vect, Keyframe& curr_kf, Keyframe& next_kf);

        float _deltaTime = 0;
        float _lastFrame = 0;

    public:
        void set_keyframes_translate(std::map<std::string, std::vector<KeyframeTranslate> > keyframes_translate);
        void set_keyframes_scale(std::map<std::string, std::vector<KeyframeScale> > keyframes_scale);
        void set_keyframes_rotate( std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate);
        float get_duration();

        /**
         * get_next_frame - interpolates and returns the next frame of current animation vector < map<bodypart name, transformation> >
         * */
        std::map<std::string, Matrix> get_next_frame(float delta_time);

        // DEV
        float getDeltaTime(void);
        float getLastFrame(void); 

        void setDeltaTime(float deltaTime);
        void setLastFrame(float lastFrame);

        Animation(
            std::vector<std::string> body_parts,
            std::map<std::string, std::vector<KeyframeTranslate> > keyframes_translate,
            std::map<std::string, std::vector<KeyframeScale> > keyframes_scale,
            std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate,
            float duration
        );
        ~Animation();
};
#endif