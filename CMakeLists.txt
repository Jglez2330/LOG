cmake_minimum_required(VERSION 3.12)
project(LOG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(LOG main.cpp ADTStructures/LinkedList.cpp ADTStructures/LinkedList.h ADTStructures/Cell.cpp ADTStructures/Cell.h ADTStructures/NodeLinkedList.cpp ADTStructures/NodeLinkedList.h Algorithms/AStar.cpp Algorithms/AStar.h GUI/GameObjects/Enemy/EnemiesPopulation.cpp GUI/GameObjects/Enemy/EnemiesPopulation.h GUI/GameObjects/Enemy/DNA.cpp GUI/GameObjects/Enemy/DNA.h GUI/ViewManager.cpp GUI/ViewManager.h Levels/AstarLevel.cpp Levels/AstarLevel.h Levels/Level.cpp Levels/Level.h GUI/LevelBuilder.cpp GUI/LevelBuilder.h  Algorithms/Prim.cpp Algorithms/Prim.h ADTStructures/Graph.cpp ADTStructures/Graph.h GUI/ViewManager.h GUI/GameObjects/Population.cpp GUI/GameObjects/Population.h GUI/GameObjects/Population.cpp GUI/GameObjects/Population.h GUI/GameObjects/Player.cpp GUI/GameObjects/Player.h Algorithms/Dijkstra.cpp Algorithms/Dijkstra.h Levels/DijkstraLevel.cpp Levels/DijkstraLevel.h Algorithms/LineSight.cpp Algorithms/LineSight.h Algorithms/Kruskal.cpp Algorithms/Kruskal.h Levels/PrimLevel.cpp Levels/PrimLevel.h Levels/KruskalLevel.cpp Levels/KruskalLevel.h GUI/GameObjects/Enemy/EnemyUnit.cpp GUI/GameObjects/Enemy/EnemyUnit.h GUI/GameObjects/Gem.cpp GUI/GameObjects/Gem.h Levels/LineSightLevel.cpp Levels/LineSightLevel.h GUI/GameObjects/AttackOne.cpp GUI/GameObjects/AttackOne.h GUI/GameObjects/Attack.cpp GUI/GameObjects/Attack.h)
target_link_libraries(LOG -lallegro -lallegro_font -lallegro_image -lallegro_audio  -lallegro_ttf -lallegro_primitives -lallegro_acodec )
