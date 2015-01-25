#include <SFML-Book/Helpers.hpp>
#include <SFML-Book/Configuration.hpp>

#include <SFML-Book/Component.hpp>
#include <SFML-Book/Team.hpp>

namespace book
{
    
    void makeAsMain(Entity& entity,Team* team)
    {
        //add animation
        setAnimation(entity,Configuration::AnimMainStand,CompSkin::Stand,0.5,0.7,0.17,0.17);

        //add team
        setTeam(entity,team);
        team->setQgId(entity.id());

        //add AI
        entity.add<CompAIMain>(100,sf::seconds(10));
        entity.add<CompHp>(5000);


        entity.name = "QG";
    }

    void makeAsEye(Entity& entity,Team* team)
    {
        //add animation
        setAnimation(entity,Configuration::AnimEyeLeft,CompSkin::MoveLeft,0.5,0.8,0.5,0.5);
        setAnimation(entity,Configuration::AnimEyeRight,CompSkin::MoveRight,0.5,0.8,0.5,0.5);

        //add team
        setTeam(entity,team);

        //add AI
        entity.add<CompAIWarrior>(50,sf::seconds(0.5));
        entity.add<CompHp>(500);
        entity.add<CompAIFlyer>(100);

        entity.name = "Fly Eye";
    }

    void makeAsWormEgg(Entity& entity,Team* team)
    {
        setAnimation(entity,Configuration::AnimWormEggBirth,CompSkin::Spawn,0.5,1,0.3,0.3);
        setAnimation(entity,Configuration::AnimWormEggStand,CompSkin::Stand,0.5,1,0.3,0.3);

        setTeam(entity,team);
        entity.add<CompAISpawner>(makeAsWorm,1,sf::seconds(15));
        entity.add<CompHp>(200);

        entity.name = "Worm Egg";
    }

    void makeAsWorm(Entity& entity,Team* team)
    {
        makeAsEye(entity,team); //TODO
        entity.name = "Worm";
    }

    void setTeam(Entity& entity,Team* team)
    {
        if(team)
        {
            entity.add<CompTeam>(team);
            entity.component<CompSkin>()->_sprite.setColor(team->gui.getColor());
        }
    }

    void setAnimation(Entity& entity,int animationId,int animationMap,float ox,float oy,float sx,float sy)
    {
        CompSkin& skin = *entity.component<CompSkin>().get();
        sfutils::Animation& animation = Configuration::animations.get(animationId);

        skin._animations.emplace(animationMap,&animation);
        skin._sprite.setAnimation(skin._animations.at(animationMap));

        //resize to map size
        sf::IntRect rec = animation.getRect(0);
        skin._sprite.setOrigin(rec.width*ox,rec.height*oy);
        skin._sprite.setScale(sx,sy);
    }
}
