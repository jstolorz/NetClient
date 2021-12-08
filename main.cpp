#include <iostream>
#include "olc_net.h"

enum class CustomMsgType : uint32_t {
    FireBullet,
    MovePlayer
};

class CustomClient : public olc::net::Client_interface<CustomMsgType>{
public:
    bool fireBullet(float x, float y){
        olc::net::Message<CustomMsgType> msg;
        msg.header.id = CustomMsgType::FireBullet;

        msg << x << y;

        return true;
    }
};

int main() {

    CustomClient c;


    return 0;
}
