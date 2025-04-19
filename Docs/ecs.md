
# ECS

## Basic entity instanciation

```cpp

auto& main_entity_pool = engine.MainEntityPool();
Entity i_camera = main_entity_pool.GetEntity<Transform, Data>();
Entity i_player = main_entity_pool.GetEntity<Transform, Controllable>();

Scene scene;
scene.AddEntity("camera", i_camera); // Scene does not own camera
auto i_mesh = scene.NewEntity<Transform, Mesh>("main_mesh"); // mesh owned by the scene

// same as:
auto i_mesh_b = scene.MainEntityPool().GetEntity<Transform, Mesh>();
scene.GetEntity(i_mesh_b.ID).SetName("other_mesh");

System anim;

```

## Serialized entity

```cpp
entities {
    camera {
        name: "Camera"
        components {
            Transform {
                euler: 0 0.0 90.0 0.0 // 0=XYZ
            }
            Data {}
        }
    },
    main_mesh {
        name: "Main mesh"
        components {
            Transform {}
            Mesh @file="./main.geo"
        }
    },
    other_mesh {
        name: "Main mesh"
        components {
            Transform {}
            Mesh {
                @buffer="./all_geos.geo":1056,2500,0 // Bits start,end,endianness
            }
        }
    }
}
```

## Adding/removing components

Like, adding render and physics components to a game-logic entity (something from an inventory gets added to the scene)

Remove components


## Example code

```cpp
auto& engine = Engine.Instance();
auto& mng = engine.ResourcesManager();

// mng.RegisterResource<FontRsc>("font");

uint32_t vehicleTypeId = mng.RegisterResource("Vehicle", "path/to/description.json"); // When resource is an aggregate of other resources or components
// Resgister a bunch of resources at once
mng.RegisterResources("path/to/index.json");

uint32_t car_rsc = mng.LoadResource(vehicleTypeId, "rsc/vehicles/generic_car.json", true /* lazy load, imports description, loads data only when instantiated */);

Scene scene;
scene.Instantiate(car_rsc);

```
