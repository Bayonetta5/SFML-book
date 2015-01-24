#ifndef BOOK_SYSTEM_HPP
#define BOOK_SYSTEM_HPP

#include <SFML-utils/ES.hpp>

#include <SFML-Book/Entity.hpp>

namespace book
{
    struct SysSkin : sfutils::System<SysSkin,Entity>
    {
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
    };
}
#endif