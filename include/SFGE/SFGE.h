#ifndef SFGE_H_INCLUDED
#define SFGE_H_INCLUDED

/// @mainpage
/// SFGE (Simple & Fast Game Engine) is a framework specifically tailored for developing games in.\n
/// It's design goals are flexibility, simplicity and usability.\n
/// SFGE is currently in a very early state is not stable.\n\n
/// A simple code example:
/// @code
/// #include <SFML/Graphics.hpp>
/// #include <SFGE/Director.h>
/// #include <SFGE/Core/MenuState.h>
///
/// int main()
/// {
///     sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML program");
///
///     sfge::Director director;
///     director.run(new MenuState(&window, &director));
/// }
/// @endcode
/// It's as simple as that!


#endif // SFGE_H_INCLUDED
