#include "Engine/Core/Maths/Euler.hpp"
#include "Engine/Core/Maths/Matrix33.hpp"
#include "Engine/Core/Maths/Quaternion.hpp"

namespace Engine::ECS
{

    struct CRotation
    {
        Quaternion rotation = Quaternion::Identity();
        CRotation() = default;
        CRotation(Euler const &);
        CRotation(Matrix33 const &);

        CRotation &SetEuler();
        CRotation &SetMatrix();
    };

}
