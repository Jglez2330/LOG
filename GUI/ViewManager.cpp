#include <atomic>
#include <thread>
#include <chrono>
#include "ViewManager.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

ViewManager::ViewManager() {
    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_install_audio();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_acodec_addon();

    bool t =al_init_primitives_addon();

    int fps = 60;

    this->timer = al_create_timer(1.0/fps);
    this->timerDraw = al_create_timer(1.0*2/fps);
    this->eventQueue = al_create_event_queue();


    al_register_event_source(this->eventQueue,al_get_mouse_event_source());
    al_register_event_source(this->eventQueue,al_get_keyboard_event_source());
    al_register_event_source(this->eventQueue,al_get_timer_event_source(this->timer));
    al_register_event_source(this->eventQueue,al_get_timer_event_source(this->timerDraw));

    showing = true;

    /*
    // ==================== INITIALIZE THREAD ====================================

    std::atomic<bool> running { true } ;
    const unsigned int update_interval = 20 ; // update after every second
    std::thread update_thread(Controller::run, std::ref(running), update_interval);
    // ============================================================================
    */
}

void ViewManager::showDisplay() {

    al_set_new_window_title("Menu");
    this->menuDisplay = al_create_display(595,340);
    al_register_event_source(this->eventQueue,al_get_display_event_source(this->menuDisplay));


    image = al_load_bitmap("../GUI/LOG.png");

    al_reserve_samples(1);
    music = al_load_sample("../GUI/Ameno.wav");
    //al_play_sample(music,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,0);



    al_start_timer(this->timer);
    al_start_timer(this->timerDraw);
    ALLEGRO_KEYBOARD_STATE keyMenu;
    ALLEGRO_EVENT event;

    while (showing) {

        al_wait_for_event(this->eventQueue, &event);

        al_draw_bitmap(image,0,0, 0);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            showing = false;
            destroyWindow();
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            if (event.timer.source == this->timer) {
                al_get_keyboard_state(&keyMenu);
                if(al_key_down(&keyMenu,ALLEGRO_KEY_E)) {
                  //empieza el nivel en dificultad facil
                   mainLoop();

                }else if(al_key_down(&keyMenu,ALLEGRO_KEY_N)) {
                    //empieza el nivel en dificultad normal
                    mainLoop();

                }if(al_key_down(&keyMenu,ALLEGRO_KEY_H)) {
                    //empieza el nivel en dificultad dificil
                    mainLoop();
                }
            }


        }


    }
    al_destroy_timer(timer);
    al_destroy_sample_instance(songInstance);
    al_destroy_sample(music);
    al_destroy_event_queue(eventQueue);
    al_destroy_bitmap(image);
}

void ViewManager::mainLoop() {
    al_destroy_display(this->menuDisplay);
    al_set_new_window_title("LOG");
    this->ptrDisplay = al_create_display(this->Height,this->Width);


    al_register_event_source(this->eventQueue,al_get_display_event_source(this->ptrDisplay));

    al_start_timer(this->timer);
    al_start_timer(this->timerDraw);

    ALLEGRO_FONT *font = al_load_font("arial.ttf",72,0 );

    /*  0 = LineSight
     *  1 = Prim
     *  2 = Kruskal
     *  3 = Dijkstra
     *  4 = A Star
     */
    //this->levelNumber = 1;

    this->map = new Graph(50,50,levelNumber+1);
    this->map->generateGrid();

    this->playerPopulation = new Population();
    this->playerPopulation->setMap(map);
    this->playerPopulation->setDrawPopulationRatio(this->relationRatio);

    this->enemiesPopulation = new EnemiesPopulation(25, map);
    this->enemiesPopulation->setRelationRatio(this->relationRatio);

    this->gem = new Gem();

    this->map->getKeyTable()[0][49]->setObjectID(10);
    std::list<Cell<int>*>* path = nullptr;
    ALLEGRO_MOUSE_STATE mouseState;
    ALLEGRO_KEYBOARD_STATE keyState;
    int yGraph = 0;
    int xGraph = 0;

    this->gameLevel = LevelBuilder::getLevel(levelNumber);
    ALLEGRO_EVENT event;
    while (showing){

        al_wait_for_event(this->eventQueue,&event);

        //std::cout << event.type;

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            showing = false;
            destroyWindow();
        } else if (event.type == ALLEGRO_EVENT_TIMER){
            if (event.timer.source == this->timer){
                //drawPlayer();
                al_get_mouse_state(&mouseState);
                al_get_keyboard_state(&keyState);

                if (mouseState.buttons & 1 || mouseState.buttons & 2){

                    if (mouseState.x > 0 && mouseState.x < this->Width  &&
                    mouseState.y > 0 && mouseState.y < this->Height ) {
                        xGraph = mouseState.x / this->relationRatio;
                        yGraph = mouseState.y / this->relationRatio;
                    }
                    playerPopulation->setPath(gameLevel, xGraph, yGraph); // Le da un path a todos los jugadores según el lugar donde se dio click
                }
                if(al_key_down(&keyState,ALLEGRO_KEY_Q)) {
                    std::cout << "Q \n";
                    //metodo para ataque desbloqueado
                    this->playerPopulation->setAttack(1);

                }else if (al_key_down(&keyState, ALLEGRO_KEY_W) && levelNumber > 0) {
                    std::cout << "W \n";
                    //metodo para ataque desbloqueado
                    this->playerPopulation->setAttack(1);

                }else if (al_key_down(&keyState, ALLEGRO_KEY_D)&& levelNumber > 3) {
                    std::cout << "E \n";
                    //metodo para ataque desbloqueado
                    this->playerPopulation->setAttack(4);

                }else if (al_key_down(&keyState, ALLEGRO_KEY_A)&& levelNumber > 1) {
                    std::cout << "A \n";
                    //metodo para ataque desbloqueado
                    this->playerPopulation->setAttack(2);

                }else if (al_key_down(&keyState, ALLEGRO_KEY_S)&& levelNumber > 2) {

                    std::cout << "S \n";
                    //metodo para ataque desbloqueado
                    this->playerPopulation->setAttack(3);
                }

                if(playerPopulation->collideWithGem(gem) && levelNumber < 4) {
                    this->nextLevel();
                }



            } else if (event.timer.source == this->timerDraw){

                playerPopulation->updatePlayers(); // Hace que los jugadores se muevan según el path
                al_clear_to_color(al_map_rgb(255,255,255));
                drawMap(map);
                playerPopulation->draw(); // Dibuja todos los jugadores
                enemiesPopulation->draw();
                enemiesPopulation->collisionPlayer(this->playerPopulation);


                gem->draw();

                //Obtiene una nueva generacion cada vez que se dibuja, si molesta a la hora de probar, se pude comentar
                //qenemiesPopulation->getNextGeneration();

                al_flip_display();
            }
        }

    }
    delete(path);
    delete(map);
    delete(gem);

}




ViewManager* ViewManager::getInstance() {
    auto* ptrInstance = new ViewManager();
    ptrInstance->viewManagerInstance = ptrInstance;
    return ptrInstance;
}

bool ViewManager::isShowing() const {
    return showing;
}

void ViewManager::destroyWindow() {
    showing = false;
    al_destroy_display(this->ptrDisplay);

}

int ViewManager::getHeight() const {
    return Height;
}

int ViewManager::getWidth() const {
    return Width;
}

ALLEGRO_DISPLAY* ViewManager::getPtrDisplay() const {
    return ptrDisplay;
}

ViewManager::~ViewManager() {
    delete(viewManagerInstance);
    if (showing){
        this->destroyWindow();
    }
}


void ViewManager::drawPath(std::list<Cell<int>*>* pList) {
    if (pList != nullptr) {
        for (auto currentCell : *pList) {
            //al_draw_rectangle((float)node->getXpos(),(float)node->getYpos(),node->getXpos() + this->getWidth()/19,node->getXpos() + this->getWidth()/19,al_map_rgb(0, 255, 0), 255);
            float x = currentCell->getXpos() * this->relationRatio;
            float y = currentCell->getYpos() * this->relationRatio;
            al_draw_filled_rectangle(x, y ,x+this->relationRatio,y + this->relationRatio, al_map_rgb(0, 255, 255));
        }
    }
}

void ViewManager::drawMap(Graph *graph) {
    for (int i = 0; i < graph->getHeight() ; i++) {
        for (int j = 0; j < graph->getWidth() ; j++) {
            Cell<int>* cellCurrent = graph->getKeyTable()[i][j];
            ALLEGRO_COLOR obstacleColor = al_map_rgb(255, 255, 255);
            if (cellCurrent->getObjectID() == 1) {
                obstacleColor = al_map_rgb(0, 0, 0);
            }
            else if (cellCurrent->getObjectID() == 2) {
                obstacleColor = al_map_rgb(0, 255, 0);
            }
            else if (cellCurrent->getObjectID() == 3) {
                obstacleColor = al_map_rgb(255, 0, 0);
            }
            al_draw_filled_rectangle(cellCurrent->getXpos() * this->relationRatio, cellCurrent->getYpos() * this->relationRatio,
                                     cellCurrent->getXpos() * this->relationRatio + this->relationRatio, cellCurrent->getYpos() * this->relationRatio + this->relationRatio,
                                     obstacleColor);
        }

    }

}

void ViewManager::nextLevel() {

    //Limpia el Heap
    delete(map);
    delete(playerPopulation);
    delete(gameLevel);
    delete(gem);
    //Aumenta el nivel
    levelNumber++;
    //Obtiene un nuevo algoritmo de busqueda
    gameLevel = LevelBuilder::getLevel(levelNumber);

    //Genera una nueva gema
    gem = new Gem();
    //Carga el nuevo mapa
    this->map = new Graph(50,50,levelNumber+ 1);
    this->map->generateGrid();

    this->map->getKeyTable()[0][49]->setObjectID(10);

    //Setea el mapa y obtiene nuevos enemigos con el GA
    enemiesPopulation->setMap(this->map);
    enemiesPopulation->getNextGeneration();

    //Obtiene nuevos jugadores
    playerPopulation = new Population();
    playerPopulation->setMap(this->map);
    playerPopulation->setDrawPopulationRatio(this->relationRatio);
}
