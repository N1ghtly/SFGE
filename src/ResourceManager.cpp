#include "ResourceManager.h"
#include <iostream>

sfge::ResourceManager* sfge::ResourceManager::mgr = 0;

namespace sfge
{
    ResourceManager::ResourceManager() : textureDir(""), audioDir(""), fontDir("")
    {
        //ctor
    }

    ResourceManager::~ResourceManager()
    {
        //dtor
    }

    ResourceManager* ResourceManager::instance()
    {
        if(mgr == NULL)
            mgr = new ResourceManager;

        return mgr;
    }

    sf::Texture& ResourceManager::getTexture(const std::string& name)
    {
        if(textures.find(name) != textures.end())
            return(*textures[name]);
        else
        {
            sf::Texture* texture = new sf::Texture;

            if(!texture->loadFromFile(textureDir + name))
                std::cout<<"Could not load image "<<textureDir+name;
            else
            {
                textures[name] = texture;
            }
            return *texture;
        }
    }

    sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& name)
    {
        if(soundBuffers.find(name) != soundBuffers.end())
            return(*soundBuffers[name]);
        else
        {
            sf::SoundBuffer* sound = new sf::SoundBuffer;

            if(!sound->loadFromFile(audioDir + name))
                std::cout<<"Could not load audio file "<<audioDir+name;
            else
                soundBuffers[name] = sound;
            return *sound;
        }
    }

    sf::Font& ResourceManager::getFont(const std::string& name)
    {
        if(fonts.find(name) != fonts.end())
            return(*fonts[name]);
        else
        {
            sf::Font* font = new sf::Font;

            if(!font->loadFromFile(fontDir + name))
                std::cout<<"Could not load font file "<<fontDir+name;
            else
                fonts[name] = font;
            return *font;
        }
    }

    void ResourceManager::releaseAllResources()
    {
        for(auto itr = textures.begin(); itr != textures.end(); itr++)
        {
            //delete the resource pointer
            delete (*itr).second;
            itr = textures.erase(itr);
        }

        for(auto itr = soundBuffers.begin(); itr != soundBuffers.end(); itr++)
        {
            //delete the resource pointer
            delete (*itr).second;
            itr = soundBuffers.erase(itr);
        }

        for(auto itr = fonts.begin(); itr != fonts.end(); itr++)
        {
            //delete the resource pointer
            delete (*itr).second;
            itr = fonts.erase(itr);
        }
    }

    void ResourceManager::setTextureDir(const std::string& dir)
    {
        textureDir = dir;
    }

    void ResourceManager::setFontDir(const std::string& dir)
    {
        fontDir = dir;
    }

    void ResourceManager::setAudioDir(const std::string& dir)
    {
        audioDir = dir;
    }
}
