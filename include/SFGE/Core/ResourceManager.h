#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <list>

#define rm sfge::ResourceManager::instance()

namespace sfge
{
    /// \brief A resource manager that guarantees no resource is loaded twice.
    ///
    /// This class manages the SFML resources and ensures that every resource is loaded into memory only once.\n
    /// This class is a singleton, to guarantee only one instance is loaded into memory at any given time.\n
    ///
    /// When requesting a resource, it will first check if is already loaded. If it is, a reference is returned.
    /// If not, it will load the resource and subsequently return a reference.
    class ResourceManager
    {
        public:
            ~ResourceManager();

            /// \brief Returns the singleton instance
            static ResourceManager* instance();

            /// \brief Releases all the stored resources
            void releaseAllResources();

            /// \brief Releases a specific resource
            /// @param name The filename of the resource to be released
            void releaseResource(const std::string& name);

            /// \brief Get a texture
            /// @param name The filename of the texture
            sf::Texture& getTexture(const std::string& name);

            /// \brief Get a soundbuffer
            /// @param name The filename of the sound
            sf::SoundBuffer& getSoundBuffer(const std::string& name);

            /// \brief Get a font
            /// @param name The filename of the font
            sf::Font& getFont(const std::string& name);

            /// \brief Sets the directory where the textures are located
            void setTextureDir(const std::string& dir);

            /// \brief Sets the directory where audio is located
            void setAudioDir(const std::string& dir);

            /// \brief Sets the directory where the fonts are located
            void setFontDir(const std::string& dir);

        protected:
            ResourceManager();

        private:
            static ResourceManager* mgr;

            std::string textureDir;
            std::string audioDir;
            std::string fontDir;

            std::map<std::string, sf::Texture*> textures;
            std::map<std::string, sf::SoundBuffer*> soundBuffers;
            std::map<std::string, sf::Font*> fonts;
    };
}
#endif // RESOURCEMANAGER_H
