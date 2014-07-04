#include "Director.h"
#include "State.h"
#include <iostream>
#include "FileLogger.h"

namespace sfge
{
    Director::Director(sf::RenderWindow& window) : window(window), running(false), shouldPop(false), timestep(sf::milliseconds(20)), accumulator(sf::Time::Zero)
    {
        FileLogger::setLogFile("log.txt");
    }

    Director::~Director()
    {
        FileLogger::log("deleting director");
        for(auto itr = states.begin(); itr != states.end(); itr++)
            delete (*itr);
        states.clear();
    }

    void Director::run(State* state)
    {
        pushState(state);
        running  = true;

        sf::Event event;
        frameClock.restart();

        while(running)
        {
            if(!shouldPop)
            {
                //handle
                while(window.pollEvent(event))
                {
                    handle(event);
                }
                //update
                accumulator += frameClock.getElapsedTime();
                while(accumulator >= timestep)
                {
                    update();
                    accumulator -= timestep;
                }
                frameClock.restart();
                //draw
                window.clear();
                draw();
                window.display();
            }
            else
            {
                doPop();
                frameClock.restart();
            }
        }
    }

    void Director::setTimestep(sf::Time timestep)
    {
        this->timestep = timestep;
    }

    void Director::replaceState(State* state)
    {
        FileLogger::log("replacing state");
        FileLogger::log("states: " + states.size());
        popState();
        // store and init the new state
        state->setDirector(this);
        state->setWindow(&window);
        states.insert(states.end() - 1, state);
        FileLogger::log("states: " + states.size());
    }


    void Director::pushState(State* state)
    {
        FileLogger::log("Pushing state");
        FileLogger::log("states: " + states.size());
        state->setDirector(this);
        state->setWindow(&window);

        // pause current state
        if ( !states.empty() )
            states.back()->pause();

        // store and init the new state
        states.push_back(state);
        FileLogger::log("states: " + states.size());
    }

    void Director::doPop()
    {
        FileLogger::log("Popping state");
        FileLogger::log("states: " + states.size());
        shouldPop = false;
        // cleanup the current state
        if ( !states.empty() )
        {
            FileLogger::log("deleting state");
            delete states.back();
            FileLogger::log("state deleted");
            states.pop_back();
        }

        // resume previous state
        if ( !states.empty() )
            states.back()->resume();
        else
        {
            running = false;
            window.close();
        }
        FileLogger::log("states: " + states.size());
    }

    void Director::popState()
    {
        shouldPop = true;
    }

    void Director::handle(const sf::Event& event)
    {
        if(!states.empty())
            states.back()->handle(event);
    }

    void Director::update()
    {
        if(!states.empty())
            states.back()->update(timestep);
    }

    void Director::draw()
    {
        if(!states.empty())
            states.back()->draw();
    }
}
