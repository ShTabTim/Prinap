#include <Windows.h>
#include "FundLibs/ShRendCPU/ShWin.h"
#include "FundLibs/Keys/Keys.h"
#include "FundLibs/math/vec2.h"
#include "FundLibs/noises/Simplex.h"
#include "Scenes/solar_sys_sc.h"
#include "game_objs/player.h"
#include <time.h>

class MainRenderer : public ShWinRendCPU {

    vec2i v;
    scene* sys;
    player pl0;
    sptRGB background;

    bool initSim() {
        AppName = L"Prinap";
        v.x = 50;
        v.y = 50;
        key_loop(hWnd);
        pl0.init(this);
        sys = new solar_sys_sc();
        //set_cursor(v.x, v.y);
        sys->init_sc(&pl0);
        ((solar_sys_sc*) sys)->init(time(0), L"0st.ss");

        background.init(256, 256);
        std::memset(background.get_buf(), 0, 256*256*3);
        for (uint32_t g(2000); g--;) {
            uint32_t hj = ((rand() % 256)*256 + (rand() % 256))*3;
            (background.get_buf())[hj++] = 128 + rand() % 128;
            (background.get_buf())[hj++] = 128 + rand() % 128;
            (background.get_buf())[hj] = 128 + rand() % 128;
        }
        return 1;
    }

    bool loopSim(float dt) {
        key_loop(hWnd);
        if (GetKey(VK_ESCAPE).bPressed) return 0;
        
        ///////////////////////////////////loop
        //v.x = get_x()*db.get_w()/width ;
        //v.y = get_y()*db.get_h()/height;

        sys->loop_sc(dt);
        //pl0.loop(dt);
        ///////////////////////////////////draw
        db.draw_spt_offseted(0, 0, -pl0.get_pos_from_player_x(0)*0.0625f, -pl0.get_pos_from_player_y(0)*0.0625f, &background);

        sys->draw_sc(&db);

        //pl0.draw(&db);
        return 1;
    }
    bool finitSim() {
        return 1;
    }
};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR sCmdLine, int iShow) {
    MainRenderer simulation;
    if (simulation.init(hInst, 512+256, 512+256, 256, 256))
        simulation.Start();
    return 0;
}