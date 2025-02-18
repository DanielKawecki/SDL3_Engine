#include "util.h"

namespace Util {

    std::string BoolToString(bool val) {
        
        if (val) return "True";
        return "False";
    }

    std::string Vec2ToSrring(vec2 v) {
        return "{" + std::to_string(v.x) + ", " + std::to_string(v.y) + "}";
    }

}


