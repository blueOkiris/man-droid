#pragma once

#include <tuple>
#include <string>

namespace mandroid {
    class Servo {
        private:
            static float _dutyFromAngle(const int &angle);
        
        public:
            Servo();

            void start() const;
            void setAngle(const int &angle) const;
            void stop() const;
    };
}
