#include "Player.hh"

#include <cmath>

using namespace std;

/**
 * Write the name of your player and save this file
 * with a name matching the format "AIyourname.cc".
 */
#define PLAYER_NAME Ramongolo


struct PLAYER_NAME : public Player {

    /**
     * Factory: returns a new instance of this class.
     * Do not modify this function.
     */
    static Player* factory () {
        return new PLAYER_NAME;
    }


    /**
     * Attributes for your player can be defined here.
     */     
    //vector<int> my_awesome_vector_of_integers;

    //returns the index of the maximum element in a vector<int>
    int max_vec(const vector<int>& v){
    	int max = 0;
    	for (int i = 0; i < (int)v.size(); ++i) {
    		if(v[i] > v[max])
    			max = i;
    	}
    	return max;
    }

    //returns a vector with the id of all empty neighbours of vert.
    vector<int> find_empty_neighbours(const int& vert){
    	vector<int> res;
    	vector<int> nb = vertex(vert).neighbours;
    	for(int i = 0; i < (int)nb.size(); i++) {
    		int id = nb[i];
    		if(vertex(id).wall == -1 and vertex(id).bike == -1)
    			res.push_back(id);
    	}
    	return res;
    }

    //returns the index for the neighbour with the maximum empty neighbours
    int max_empty_nb(const vector<int>& empty_nb){
    	vector<int> res;
    	for(int i = 0; i < (int)empty_nb.size(); i++){
    		vector<int> nb = find_empty_neighbours(empty_nb[i]);
    		res.push_back(nb.size());
    	}
    	return max_vec(res);

    }
    /**
     * Play method.
     * 
     * This method will be invoked once per each round.
     * You have to read the board and place your actions
     * for this round.
     */
    void play () {
        vector<int> my_bikes = bikes(me());
        for (int i = 0; i < (int)my_bikes.size(); ++i) {
			
			const Bike& my_bike = bike(my_bikes[i]);
			const int& my_position = my_bike.vertex;
			
			// Do something only if this bike is alive
			if (!my_bike.alive) {
				continue;
			}
			
			//Only turbo bikes can move at odd rounds
			if (round() % 2 && my_bike.turbo_duration <= 0) {
				continue;
			}
			
			vector<int> neighbours = vertex(my_bike.vertex).neighbours;
			// Find all empty neighbours
			vector<int> empty_neighbours = find_empty_neighbours(my_position);


			// Create an empty movement
			Movement movement(my_bike.id);
			
			// Set next_vertex to a random empty neighbour, if any, or to a random neighbour otherwise
			if (!empty_neighbours.empty()) {
				int max_nb = max_empty_nb(empty_neighbours);
				movement.next_vertex = empty_neighbours[max_nb];

				//movement.next_vertex = empty_neighbours[ rand() % (int)empty_neighbours.size() ];
			} else {
				movement.next_vertex = neighbours[ rand() % (int)neighbours.size() ];
			}
			
			// Use bonus randomly when we have one
			if (my_bike.bonus != None && rand()%5 > 3) {
				movement.use_bonus = true;
			}
			
			// Command the movement
            command(movement);
			
        }
        
    }

};



/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

