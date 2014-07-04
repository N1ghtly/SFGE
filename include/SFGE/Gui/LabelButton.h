#ifndef LABELBUTTON_H
#define LABELBUTTON_H
#include <functional>
#include <SFGE/Gui/Label.h>


namespace sfge
{
    /// \brief This is a label that the user can click.
    class LabelButton : public sfge::Label
    {
        typedef std::function<void ()> callback;

        public:
            /// \brief Constructor.
            LabelButton(const std::string& labelText = "", int x=0, int y=0);
            ~LabelButton();

            /// \brief Set the object method to be called when the label is clicked.
            template<class T>
            void setOnClickCallback(void (T::*func)(void), T* object)
            {
                onClickCallback = std::bind(func, object);
            }
            /// \brief Set the function to be called when the label is clicked.
            void setOnClickCallback(callback func)
            {
                onClickCallback = func;
            }

            /// \brief Handle events and call appropriate callbacks
            virtual void onHandle(const sf::Event& event);


        private:
            callback onClickCallback;
    };
}

#endif // LABELBUTTON_H
