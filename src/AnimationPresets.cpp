#include "AnimationPresets.hpp"

Animation get_jumping_animaton()
{
 	std::vector<std::string> body_parts;

    body_parts.push_back("a_hip");
    body_parts.push_back("a_lthigh");
    body_parts.push_back("a_llowerpart");
    body_parts.push_back("a_rthigh");
    body_parts.push_back("a_rlowerpart");
    body_parts.push_back("a_lupperarm");
    body_parts.push_back("a_rupperarm");

	// translation keyframes
    std::map<std::string, std::vector<KeyframeTranslate> > translation_keyframes;
    
    // keyframes for hip
    std::vector<KeyframeTranslate> translation_kf_hip;
    translation_kf_hip.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    translation_kf_hip.push_back({
        0.0f,
        -0.5f,
        0.0f,
        1.0f
    });
    translation_kf_hip.push_back({
        0.0f,
        1.5f,
        0.0f,
        2.0f
    });
    translation_keyframes.insert({"a_hip", translation_kf_hip});

    // keyframes for lthigh
    std::vector<KeyframeTranslate> translation_kf_lthigh;
    translation_kf_lthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    translation_kf_lthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        1.0f
    });
    translation_kf_lthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    translation_keyframes.insert({"a_lthigh", translation_kf_lthigh});

    // translation for lowerpart
    std::vector<KeyframeTranslate> translation_kf_llower;
    translation_kf_llower.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    translation_kf_llower.push_back({
        0.0f,
        0.0f,
        -1.0f,
        1.0f
    });
    translation_kf_llower.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    translation_keyframes.insert({"a_llowerpart", translation_kf_llower});

    // keyframes for rthigh
    std::vector<KeyframeTranslate> translation_kf_rthigh;
    translation_kf_rthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    translation_kf_rthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        1.0f
    });
    translation_kf_rthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    translation_keyframes.insert({"a_rthigh", translation_kf_rthigh});

    // translation for lowerpart
    std::vector<KeyframeTranslate> translation_kf_rlower;
    translation_kf_rlower.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    translation_kf_rlower.push_back({
        0.0f,
        0.0f,
        -1.0f,
        1.0f
    });
    translation_kf_rlower.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    translation_keyframes.insert({"a_rlowerpart", translation_kf_rlower});

    // translation for lupperarm
    std::vector<KeyframeTranslate> translation_kf_lupperarm;
    translation_kf_lupperarm.push_back({
        1.0f,
        0.3f,
        0.0f,
        0.0f
    });
    translation_kf_lupperarm.push_back({
        1.0f,
        0.3f,
        0.0f,
        1.0f
    });
    translation_kf_lupperarm.push_back({
        1.0f,
        0.3f,
        0.0f,
        2.0f
    });
    translation_keyframes.insert({"a_lupperarm", translation_kf_lupperarm});

    // translation for rupperarm
    std::vector<KeyframeTranslate> translation_kf_rupperarm;
    translation_kf_rupperarm.push_back({
        -1.0f,
        0.3f,
        0.0f,
        0.0f
    });
    translation_kf_rupperarm.push_back({
        -1.0f,
        0.3f,
        0.0f,
        1.0f
    });
    translation_kf_rupperarm.push_back({
        -1.0f,
        0.3f,
        0.0f,
        2.0f
    });
    translation_keyframes.insert({"a_rupperarm", translation_kf_rupperarm});


    // create scaling keyframes
    std::map<std::string, std::vector<KeyframeScale> > scale_keyframes;
    std::vector<KeyframeScale> scale_kf_hip;

    scale_kf_hip.push_back({
        1.0f,
        1.0f,
        1.0f,
        0.0f
    });
    scale_kf_hip.push_back({
        1.0f,
        1.0f,
        1.0f,
        1.0f
    });
    scale_kf_hip.push_back({
        1.0f,
        1.0f,
        1.0f,
        2.0f
    });
    scale_keyframes.insert({"a_hip", scale_kf_hip});

    // scale keyframes for lthigh
    std::vector<KeyframeScale> scale_kf_lthigh;
    scale_kf_lthigh.push_back({
        1.0f,
        1.0f,
        1.0f,
        0.0f
    });
    scale_kf_lthigh.push_back({
        1.0f,
        1.0f,
        1.0f,
        1.0f
    });
    scale_kf_lthigh.push_back({
        1.0f,
        1.0f,
        1.0f,
        2.0f
    });
    scale_keyframes.insert({"a_lthigh", scale_kf_lthigh});

    // scale keyframes for llower
    std::vector<KeyframeScale> scale_kf_llower;
    scale_kf_llower.push_back({
        1.0f,
        1.0f,
        1.0f,
        0.0f
    });
    scale_kf_llower.push_back({
        1.0f,
        1.0f,
        1.0f,
        1.0f
    });
    scale_kf_llower.push_back({
        1.0f,
        1.0f,
        1.0f,
        2.0f
    });
    scale_keyframes.insert({"a_llowerpart", scale_kf_llower});

    // scale keyframes for rthigh
    std::vector<KeyframeScale> scale_kf_rthigh;
    scale_kf_rthigh.push_back({
        1.0f,
        1.0f,
        1.0f,
        0.0f
    });
    scale_kf_rthigh.push_back({
        1.0f,
        1.0f,
        1.0f,
        1.0f
    });
    scale_kf_rthigh.push_back({
        1.0f,
        1.0f,
        1.0f,
        2.0f
    });
    scale_keyframes.insert({"a_rthigh", scale_kf_rthigh});

    // scale keyframes for llower
    std::vector<KeyframeScale> scale_kf_rlower;
    scale_kf_rlower.push_back({
        1.0f,
        1.0f,
        1.0f,
        0.0f
    });
    scale_kf_rlower.push_back({
        1.0f,
        1.0f,
        1.0f,
        1.0f
    });
    scale_kf_rlower.push_back({
        1.0f,
        1.0f,
        1.0f,
        2.0f
    });
    scale_keyframes.insert({"a_rlowerpart", scale_kf_rlower});

    // scale keyframes for lupperarm
    std::vector<KeyframeScale> scale_kf_lupperarm;
    scale_kf_lupperarm.push_back({
        1.0f,
        1.0f,
        1.0f,
        0.0f
    });
    scale_kf_lupperarm.push_back({
        1.0f,
        1.0f,
        1.0f,
        1.0f
    });
    scale_kf_lupperarm.push_back({
        1.0f,
        1.0f,
        1.0f,
        2.0f
    });
    scale_keyframes.insert({"a_lupperarm", scale_kf_lupperarm});

    // scale keyframes for rupperarm
    std::vector<KeyframeScale> scale_kf_rupperarm;
    scale_kf_rupperarm.push_back({
        1.0f,
        1.0f,
        1.0f,
        0.0f
    });
    scale_kf_rupperarm.push_back({
        1.0f,
        1.0f,
        1.0f,
        1.0f
    });
    scale_kf_rupperarm.push_back({
        1.0f,
        1.0f,
        1.0f,
        2.0f
    });
    scale_keyframes.insert({"a_rupperarm", scale_kf_rupperarm});

    // crete rotation keyframes
    std::map<std::string, std::vector<KeyframeRotate> > rotate_keyframes;
    std::vector<KeyframeRotate> rotate_kf_hip;

    rotate_kf_hip.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    rotate_kf_hip.push_back({
        0.0f,
        0.0f,
        0.0f,
        1.0f
    });
    rotate_kf_hip.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    rotate_keyframes.insert({"a_hip", rotate_kf_hip});


    // rotate keyframes for lthigh
    std::vector<KeyframeRotate> rotate_kf_lthigh;

    rotate_kf_lthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    rotate_kf_lthigh.push_back({
        50.0f,
        0.0f,
        0.0f,
        1.0f
    });
    rotate_kf_lthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    rotate_keyframes.insert({"a_lthigh", rotate_kf_lthigh});

    // rotate keyframes for llower
    std::vector<KeyframeRotate> rotate_kf_llower;

    rotate_kf_llower.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    rotate_kf_llower.push_back({
        -50.0f,
        0.0f,
        0.0f,
        1.0f
    });
    rotate_kf_llower.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    rotate_keyframes.insert({"a_llowerpart", rotate_kf_llower});

    // rotate keyframes for rthigh
    std::vector<KeyframeRotate> rotate_kf_rthigh;

    rotate_kf_rthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    rotate_kf_rthigh.push_back({
        50.0f,
        0.0f,
        0.0f,
        1.0f
    });
    rotate_kf_rthigh.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    rotate_keyframes.insert({"a_rthigh", rotate_kf_rthigh});

    // rotate keyframes for rlower
    std::vector<KeyframeRotate> rotate_kf_rlower;

    rotate_kf_rlower.push_back({
        0.0f,
        0.0f,
        0.0f,
        0.0f
    });
    rotate_kf_rlower.push_back({
        -50.0f,
        0.0f,
        0.0f,
        1.0f
    });
    rotate_kf_rlower.push_back({
        0.0f,
        0.0f,
        0.0f,
        2.0f
    });
    rotate_keyframes.insert({"a_rlowerpart", rotate_kf_rlower});

    // rotate keyframes for lupperarm
    std::vector<KeyframeRotate> rotate_kf_lupperarm;

    rotate_kf_lupperarm.push_back({
        0.0f,
        -50.0f,
        90.0f,
        0.0f
    });
    rotate_kf_lupperarm.push_back({
        0.0f,
        0.0f,
        90.0f,
        1.0f
    });
    rotate_kf_lupperarm.push_back({
        0.0f,
        -150.0f,
        90.0f,
        2.0f
    });
    rotate_keyframes.insert({"a_lupperarm", rotate_kf_lupperarm});

    // rotate keyframes for rupperarm
    std::vector<KeyframeRotate> rotate_kf_rupperarm;

    rotate_kf_rupperarm.push_back({
        0.0f,
        50.0f,
        -90.0f,
        0.0f
    });
    rotate_kf_rupperarm.push_back({
        0.0f,
        0.0f,
        -90.0f,
        1.0f
    });
    rotate_kf_rupperarm.push_back({
        0.0f,
        150.0f,
        -90.0f,
        2.0f
    });
    rotate_keyframes.insert({"a_rupperarm", rotate_kf_rupperarm});

    // insert bp keyframes into a vector
    Animation anim(
        body_parts,
        translation_keyframes,
        scale_keyframes,
        rotate_keyframes,
        2.0f
    );
    return anim;
}

Animation get_walking_animaton()
{
	std::vector<std::string> body_parts;
    Matrix m_iden(4, 1.0f);

    body_parts.push_back("bp_1");
    body_parts.push_back("bp_2");

    // create translation keyframes for 1 bp
    std::map<std::string, std::vector<KeyframeTranslate> > translation_keyframes;
    std::vector<KeyframeTranslate> kfs_1;
    translation_keyframes.insert({"bp_1", kfs_1});

    // translation keyframes for bp 2
    std::vector<KeyframeTranslate> kfs_1_bp2;
    translation_keyframes.insert({"bp_2", kfs_1_bp2});

    // create scaling keyframes
    std::map<std::string, std::vector<KeyframeScale> > scale_keyframes;
    std::vector<KeyframeScale> kfs_2;
    scale_keyframes.insert({"bp_1", kfs_2});
    scale_keyframes.insert({"bp_2", kfs_2});

    // crete rotation keyframes
    std::map<std::string, std::vector<KeyframeRotate> > keyframes_rotate;
    std::vector<KeyframeRotate> kfs_3;
    keyframes_rotate.insert({"bp_2", kfs_3});

    // insert bp keyframes into a vector
    Animation anim(
        body_parts,
        translation_keyframes,
        scale_keyframes,
        keyframes_rotate,
        2.0f
    );
    return anim;
}