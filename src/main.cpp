#include <engine.hpp>

int main(int argc, char **argv){
    engine::init(BOARD_WIDTH * 100, BOARD_HEIGHT * 100);
    
    while (engine::runningState){
        engine::update();
        engine::render();
    }
    
    engine::clean();
    return 0; 
}
