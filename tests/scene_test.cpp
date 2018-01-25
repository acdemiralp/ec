#include "catch.hpp"

#include <string>

#include <ec/entity.hpp>
#include <ec/scene.hpp>

TEST_CASE("Scene test.", "[scene]")
{
  ec::scene<ec::entity<std::string, int, float>> scene;

  // scene::entities.
  REQUIRE(scene.entities().size() == 0);

  // scene::add_entity and entity::scene/id/bitset.
  auto entity_1 = scene.add_entity();
  auto entity_2 = scene.add_entity();
  auto entity_3 = scene.add_entity();
  REQUIRE(entity_1->scene () == &scene);
  REQUIRE(entity_1->id    () == 0     );
  REQUIRE(entity_1->bitset() == 0     ); 
  REQUIRE(entity_2->scene () == &scene);
  REQUIRE(entity_2->id    () == 1     );
  REQUIRE(entity_2->bitset() == 0     );
  REQUIRE(entity_3->scene () == &scene);
  REQUIRE(entity_3->id    () == 2     );
  REQUIRE(entity_3->bitset() == 0     );

  // scene::entities.
  auto entities_1 = scene.entities();
  REQUIRE(entities_1.size() == 3);
  REQUIRE(entities_1[0] == *entity_1);
  REQUIRE(entities_1[1] == *entity_2);
  REQUIRE(entities_1[2] == *entity_3);

  // scene::entities<required_types...>.
  auto entities_2 = scene.entities<std::string>            ();
  auto entities_3 = scene.entities<int>                    ();
  auto entities_4 = scene.entities<float>                  ();
  auto entities_5 = scene.entities<std::string, int>       ();
  auto entities_6 = scene.entities<std::string, int, float>();
  auto entities_7 = scene.entities<int, std::string>       ();
  auto entities_8 = scene.entities<float, int, std::string>();
  REQUIRE(entities_2.size() == 0);
  REQUIRE(entities_3.size() == 0);
  REQUIRE(entities_4.size() == 0);
  REQUIRE(entities_5.size() == 0);
  REQUIRE(entities_6.size() == 0);
  REQUIRE(entities_7.size() == 0);
  REQUIRE(entities_8.size() == 0);

  // entity::has_components<required_types...>.
  REQUIRE(!entity_1->has_components<std::string>());
  REQUIRE(!entity_2->has_components<std::string>());
  REQUIRE(!entity_2->has_components<int>        ());
  REQUIRE(!entity_3->has_components<std::string>());
  REQUIRE(!entity_3->has_components<int>        ());
  REQUIRE(!entity_3->has_components<float>      ());

  // entity::add_component<type, argument_types...> and entity::has_components<required_types...>.
  auto component_1 = entity_1->add_component<std::string>("Entity 1");
  auto component_2 = entity_2->add_component<std::string>("Entity 2");
  auto component_3 = entity_2->add_component<int>        (2);
  auto component_4 = entity_3->add_component<std::string>("Entity 3");
  auto component_5 = entity_3->add_component<int>        (3);
  auto component_6 = entity_3->add_component<float>      (3.0F);
  REQUIRE(entity_1->has_components<std::string>());
  REQUIRE(entity_2->has_components<std::string>());
  REQUIRE(entity_2->has_components<int>        ());
  REQUIRE(entity_3->has_components<std::string>());
  REQUIRE(entity_3->has_components<int>        ());
  REQUIRE(entity_3->has_components<float>      ());
  
  // entity::has_components<required_types...>.
  auto compound_has_components_1 = entity_2->has_components<std::string, int>();
  auto compound_has_components_2 = entity_2->has_components<int, std::string>();
  auto compound_has_components_3 = entity_3->has_components<std::string, int, float>();
  auto compound_has_components_4 = entity_3->has_components<float, int, std::string>();
  REQUIRE(compound_has_components_1);
  REQUIRE(compound_has_components_2);
  REQUIRE(compound_has_components_3);
  REQUIRE(compound_has_components_4);

  // entity::get_component.
  REQUIRE( entity_1->get_component<std::string>() == component_1);
  REQUIRE( entity_2->get_component<std::string>() == component_2);
  REQUIRE( entity_2->get_component<int>        () == component_3);
  REQUIRE( entity_3->get_component<std::string>() == component_4);
  REQUIRE( entity_3->get_component<int>        () == component_5);
  REQUIRE( entity_3->get_component<float>      () == component_6);
  REQUIRE(*entity_1->get_component<std::string>() == "Entity 1" );
  REQUIRE(*entity_2->get_component<std::string>() == "Entity 2" );
  REQUIRE(*entity_2->get_component<int>        () == 2          );
  REQUIRE(*entity_3->get_component<std::string>() == "Entity 3" );
  REQUIRE(*entity_3->get_component<int>        () == 3          );
  REQUIRE(*entity_3->get_component<float>      () == 3.0F       );

  // entity::get_components.
  auto compound_components_1 = entity_2->get_components<std::string, int>();
  auto compound_components_2 = entity_2->get_components<int, std::string>();
  auto compound_components_3 = entity_3->get_components<std::string, int, float>();
  auto compound_components_4 = entity_3->get_components<float, int, std::string>();
  REQUIRE(*std::get<0>(compound_components_1) == "Entity 2");
  REQUIRE(*std::get<1>(compound_components_1) == 2         );
  REQUIRE(*std::get<0>(compound_components_2) == 2         );
  REQUIRE(*std::get<1>(compound_components_2) == "Entity 2");
  REQUIRE(*std::get<0>(compound_components_3) == "Entity 3");
  REQUIRE(*std::get<1>(compound_components_3) == 3         );
  REQUIRE(*std::get<2>(compound_components_3) == 3.0F      );
  REQUIRE(*std::get<0>(compound_components_4) == 3.0F      );
  REQUIRE(*std::get<1>(compound_components_4) == 3         );
  REQUIRE(*std::get<2>(compound_components_4) == "Entity 3");

  // scene::entities<required_types...>.
  entities_2 = scene.entities<std::string>            ();
  entities_3 = scene.entities<int>                    ();
  entities_4 = scene.entities<float>                  ();
  entities_5 = scene.entities<std::string, int>       ();
  entities_6 = scene.entities<std::string, int, float>();
  entities_7 = scene.entities<int, std::string>       ();
  entities_8 = scene.entities<float, int, std::string>();
  REQUIRE(entities_2.size() == 3);
  REQUIRE(entities_3.size() == 2);
  REQUIRE(entities_4.size() == 1);
  REQUIRE(entities_5.size() == 2);
  REQUIRE(entities_6.size() == 1);
  REQUIRE(entities_7.size() == 2);
  REQUIRE(entities_8.size() == 1);

  // entity::remove_component and entity::has_components<required_types...>.
  entity_3->remove_component<float>();
  REQUIRE( entity_1->has_components<std::string>());
  REQUIRE( entity_2->has_components<std::string>());
  REQUIRE( entity_2->has_components<int>        ());
  REQUIRE( entity_3->has_components<std::string>());
  REQUIRE( entity_3->has_components<int>        ());
  REQUIRE(!entity_3->has_components<float>      ());

  // scene::entities<required_types...>.
  entities_2 = scene.entities<std::string>            ();
  entities_3 = scene.entities<int>                    ();
  entities_4 = scene.entities<float>                  ();
  entities_5 = scene.entities<std::string, int>       ();
  entities_6 = scene.entities<std::string, int, float>();
  entities_7 = scene.entities<int, std::string>       ();
  entities_8 = scene.entities<float, int, std::string>();
  REQUIRE(entities_2.size() == 3);
  REQUIRE(entities_3.size() == 2);
  REQUIRE(entities_4.size() == 0);
  REQUIRE(entities_5.size() == 2);
  REQUIRE(entities_6.size() == 0);
  REQUIRE(entities_7.size() == 2);
  REQUIRE(entities_8.size() == 0);
  
  // entity::get_component.
  REQUIRE( entity_1->get_component<std::string>() == component_1);
  REQUIRE( entity_2->get_component<std::string>() == component_2);
  REQUIRE( entity_2->get_component<int>        () == component_3);
  REQUIRE( entity_3->get_component<std::string>() == component_4);
  REQUIRE( entity_3->get_component<int>        () == component_5);
  REQUIRE(!entity_3->get_component<float>      ()               );
  REQUIRE(*entity_1->get_component<std::string>() == "Entity 1" );
  REQUIRE(*entity_2->get_component<std::string>() == "Entity 2" );
  REQUIRE(*entity_2->get_component<int>        () == 2          );
  REQUIRE(*entity_3->get_component<std::string>() == "Entity 3" );
  REQUIRE(*entity_3->get_component<int>        () == 3          );

  // entity::get_components.
  compound_components_1 = entity_2->get_components<std::string, int>();
  compound_components_2 = entity_2->get_components<int, std::string>();
  compound_components_3 = entity_3->get_components<std::string, int, float>();
  compound_components_4 = entity_3->get_components<float, int, std::string>();
  REQUIRE(*std::get<0>(compound_components_1) == "Entity 2");
  REQUIRE(*std::get<1>(compound_components_1) == 2         );
  REQUIRE(*std::get<0>(compound_components_2) == 2         );
  REQUIRE(*std::get<1>(compound_components_2) == "Entity 2");
  REQUIRE(*std::get<0>(compound_components_3) == "Entity 3");
  REQUIRE(*std::get<1>(compound_components_3) == 3         );
  REQUIRE( std::get<2>(compound_components_3) == nullptr   );
  REQUIRE( std::get<0>(compound_components_4) == nullptr   );
  REQUIRE(*std::get<1>(compound_components_4) == 3         );
  REQUIRE(*std::get<2>(compound_components_4) == "Entity 3");

  // scene::remove_entity and scene::entities.
  scene.remove_entity(entity_3);
  entities_1 = scene.entities();
  REQUIRE(entities_1.size() == 2);
  REQUIRE(entities_1[0] == *entity_1);
  REQUIRE(entities_1[1] == *entity_2);
}