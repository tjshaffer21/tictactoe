#include "main.h"

int main() {
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Tic Tac Toe");

	Board::Board b(&App);

    while(App.IsOpened()) {
		b.draw();
	
        sf::Event Event;
        while(App.GetEvent(Event)) {
            if(Event.Type == sf::Event::Closed) { App.Close(); }
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)) { App.Close(); }
        
			b.checkEvents(&Event);
		}

        App.Display();
    }

    return EXIT_SUCCESS;
}
