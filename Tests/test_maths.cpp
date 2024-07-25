#include <gtest/gtest.h>

#include <Engine/Core/Maths/Vector3.hpp>
#include <Engine/Core/Maths/Matrix44.hpp>

#include <Engine/Core/Maths/MathsIO.hpp>

/* ================== MATRIX44 ================== */

TEST(Core_Maths, Matrix44_Init)
{

    // Default initialization = Identity matrix
    Matrix44 mat;
    EXPECT_EQ(mat.a00, kOne);
    EXPECT_EQ(mat.a01, kZero);
    EXPECT_EQ(mat.a02, kZero);
    EXPECT_EQ(mat.a03, kZero);
    EXPECT_EQ(mat.a10, kZero);
    EXPECT_EQ(mat.a11, kOne);
    EXPECT_EQ(mat.a12, kZero);
    EXPECT_EQ(mat.a13, kZero);
    EXPECT_EQ(mat.a20, kZero);
    EXPECT_EQ(mat.a21, kZero);
    EXPECT_EQ(mat.a22, kOne);
    EXPECT_EQ(mat.a23, kZero);
    EXPECT_EQ(mat.a30, kZero);
    EXPECT_EQ(mat.a31, kZero);
    EXPECT_EQ(mat.a32, kZero);
    EXPECT_EQ(mat.a33, kOne);

    // Passing individual components to initializer
    Matrix44 matA{
        static_cast<Scalar>(0.0), static_cast<Scalar>(1.0), static_cast<Scalar>(2.0), static_cast<Scalar>(3.0),
        static_cast<Scalar>(4.0), static_cast<Scalar>(5.0), static_cast<Scalar>(6.0), static_cast<Scalar>(7.0),
        static_cast<Scalar>(8.0), static_cast<Scalar>(9.0), static_cast<Scalar>(10.0), static_cast<Scalar>(11.0),
        static_cast<Scalar>(12.0), static_cast<Scalar>(13.0), static_cast<Scalar>(14.0), static_cast<Scalar>(15.0)};

    EXPECT_EQ(matA.a00, static_cast<Scalar>(0.0));
    EXPECT_EQ(matA.a01, static_cast<Scalar>(1.0));
    EXPECT_EQ(matA.a02, static_cast<Scalar>(2.0));
    EXPECT_EQ(matA.a03, static_cast<Scalar>(3.0));
    EXPECT_EQ(matA.a10, static_cast<Scalar>(4.0));
    EXPECT_EQ(matA.a11, static_cast<Scalar>(5.0));
    EXPECT_EQ(matA.a12, static_cast<Scalar>(6.0));
    EXPECT_EQ(matA.a13, static_cast<Scalar>(7.0));
    EXPECT_EQ(matA.a20, static_cast<Scalar>(8.0));
    EXPECT_EQ(matA.a21, static_cast<Scalar>(9.0));
    EXPECT_EQ(matA.a22, static_cast<Scalar>(10.0));
    EXPECT_EQ(matA.a23, static_cast<Scalar>(11.0));
    EXPECT_EQ(matA.a30, static_cast<Scalar>(12.0));
    EXPECT_EQ(matA.a31, static_cast<Scalar>(13.0));
    EXPECT_EQ(matA.a32, static_cast<Scalar>(14.0));
    EXPECT_EQ(matA.a33, static_cast<Scalar>(15.0));

    // Initializing with vector4s
    Matrix44 matB{
        Vector4{static_cast<Scalar>(10.0), static_cast<Scalar>(11.0), static_cast<Scalar>(12.0), static_cast<Scalar>(13.0)},
        Vector4{static_cast<Scalar>(14.0), static_cast<Scalar>(15.0), static_cast<Scalar>(16.0), static_cast<Scalar>(17.0)},
        Vector4{static_cast<Scalar>(18.0), static_cast<Scalar>(19.0), static_cast<Scalar>(20.0), static_cast<Scalar>(21.0)},
        Vector4{static_cast<Scalar>(22.0), static_cast<Scalar>(23.0), static_cast<Scalar>(24.0), static_cast<Scalar>(25.0)}};
    EXPECT_EQ(matB.a00, static_cast<Scalar>(10.0));
    EXPECT_EQ(matB.a01, static_cast<Scalar>(11.0));
    EXPECT_EQ(matB.a02, static_cast<Scalar>(12.0));
    EXPECT_EQ(matB.a03, static_cast<Scalar>(13.0));
    EXPECT_EQ(matB.a10, static_cast<Scalar>(14.0));
    EXPECT_EQ(matB.a11, static_cast<Scalar>(15.0));
    EXPECT_EQ(matB.a12, static_cast<Scalar>(16.0));
    EXPECT_EQ(matB.a13, static_cast<Scalar>(17.0));
    EXPECT_EQ(matB.a20, static_cast<Scalar>(18.0));
    EXPECT_EQ(matB.a21, static_cast<Scalar>(19.0));
    EXPECT_EQ(matB.a22, static_cast<Scalar>(20.0));
    EXPECT_EQ(matB.a23, static_cast<Scalar>(21.0));
    EXPECT_EQ(matB.a30, static_cast<Scalar>(22.0));
    EXPECT_EQ(matB.a31, static_cast<Scalar>(23.0));
    EXPECT_EQ(matB.a32, static_cast<Scalar>(24.0));
    EXPECT_EQ(matB.a33, static_cast<Scalar>(25.0));

    // Copy init
    Matrix44 matC{matB};
    EXPECT_EQ(matC.a00, static_cast<Scalar>(10.0));
    EXPECT_EQ(matC.a01, static_cast<Scalar>(11.0));
    EXPECT_EQ(matC.a02, static_cast<Scalar>(12.0));
    EXPECT_EQ(matC.a03, static_cast<Scalar>(13.0));
    EXPECT_EQ(matC.a10, static_cast<Scalar>(14.0));
    EXPECT_EQ(matC.a11, static_cast<Scalar>(15.0));
    EXPECT_EQ(matC.a12, static_cast<Scalar>(16.0));
    EXPECT_EQ(matC.a13, static_cast<Scalar>(17.0));
    EXPECT_EQ(matC.a20, static_cast<Scalar>(18.0));
    EXPECT_EQ(matC.a21, static_cast<Scalar>(19.0));
    EXPECT_EQ(matC.a22, static_cast<Scalar>(20.0));
    EXPECT_EQ(matC.a23, static_cast<Scalar>(21.0));
    EXPECT_EQ(matC.a30, static_cast<Scalar>(22.0));
    EXPECT_EQ(matC.a31, static_cast<Scalar>(23.0));
    EXPECT_EQ(matC.a32, static_cast<Scalar>(24.0));
    EXPECT_EQ(matC.a33, static_cast<Scalar>(25.0));

    // Copy assign init
    Matrix44 matD = matB;
    EXPECT_EQ(matD.a00, static_cast<Scalar>(10.0));
    EXPECT_EQ(matD.a01, static_cast<Scalar>(11.0));
    EXPECT_EQ(matD.a02, static_cast<Scalar>(12.0));
    EXPECT_EQ(matD.a03, static_cast<Scalar>(13.0));
    EXPECT_EQ(matD.a10, static_cast<Scalar>(14.0));
    EXPECT_EQ(matD.a11, static_cast<Scalar>(15.0));
    EXPECT_EQ(matD.a12, static_cast<Scalar>(16.0));
    EXPECT_EQ(matD.a13, static_cast<Scalar>(17.0));
    EXPECT_EQ(matD.a20, static_cast<Scalar>(18.0));
    EXPECT_EQ(matD.a21, static_cast<Scalar>(19.0));
    EXPECT_EQ(matD.a22, static_cast<Scalar>(20.0));
    EXPECT_EQ(matD.a23, static_cast<Scalar>(21.0));
    EXPECT_EQ(matD.a30, static_cast<Scalar>(22.0));
    EXPECT_EQ(matD.a31, static_cast<Scalar>(23.0));
    EXPECT_EQ(matD.a32, static_cast<Scalar>(24.0));
    EXPECT_EQ(matD.a33, static_cast<Scalar>(25.0));
}

TEST(Core_Maths, Matrix44_Equality)
{
    Matrix44 mat;
    Matrix44 identity = {
        kOne, kZero, kZero, kZero,
        kZero, kOne, kZero, kZero,
        kZero, kZero, kOne, kZero,
        kZero, kZero, kZero, kOne};

    EXPECT_TRUE(mat == identity);
    EXPECT_EQ(mat, identity);

    Matrix44 matA{
        static_cast<Scalar>(0.0), static_cast<Scalar>(1.0), static_cast<Scalar>(2.0), static_cast<Scalar>(3.0),
        static_cast<Scalar>(4.0), static_cast<Scalar>(5.0), static_cast<Scalar>(6.0), static_cast<Scalar>(7.0),
        static_cast<Scalar>(8.0), static_cast<Scalar>(9.0), static_cast<Scalar>(10.0), static_cast<Scalar>(11.0),
        static_cast<Scalar>(12.0), static_cast<Scalar>(13.0), static_cast<Scalar>(14.0), static_cast<Scalar>(15.0)};
    auto matB{matA};
    EXPECT_EQ(matA, matB);
}

TEST(Core_Maths, Matrix44_FromPosition)
{
    Vector4 vec{2.0, 3.0, 4.0, 5.0};
    Matrix44 matA = Matrix44::FromPosition(Vector4(2.0, 3.0, 4.0, 5.0));
    Matrix44 matB{1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2.0, 3.0, 4.0, 5.0};
    EXPECT_EQ(matA, matB);
}

TEST(Core_Maths, Matrix44_AimMatrix)
{
    Vector4 src{8.2, 3.5, -2.2};
    Vector4 tgt{2.65, -0.56, 5.9};
    Matrix44 a = Matrix44::AimMatrix(src, tgt);
    Matrix44 b{-0.522340298, -0.38210839, 0.762334526, 0.0, -0.21597968, 0.924117565, 0.315213591, 0.0, -0.824932396, 0, -0.565231442, 0.0, 8.2, 3.5, -2.2, 1.0};
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    EXPECT_TRUE(a == b);
}

// ===================== VECTOR3 ================== //

TEST(Core_Maths, Vec3_Init)
{
    Vector3 vec;
    EXPECT_EQ(vec.x, 0.0);
    EXPECT_EQ(vec.y, 0.0);
    EXPECT_EQ(vec.z, 0.0);

    auto vec_x = Vector3::X();
    EXPECT_EQ(vec_x.x, 1.0);
    EXPECT_EQ(vec_x.y, 0.0);
    EXPECT_EQ(vec_x.z, 0.0);

    auto vec_y = Vector3::Y();
    EXPECT_EQ(vec_y.x, 0.0);
    EXPECT_EQ(vec_y.y, 1.0);
    EXPECT_EQ(vec_y.z, 0.0);

    auto vec_z = Vector3::Z();
    EXPECT_EQ(vec_z.x, 0.0);
    EXPECT_EQ(vec_z.y, 0.0);
    EXPECT_EQ(vec_z.z, 1.0);

    Vector3 vec_init_with_values{1.0, 2.0, 3.0};
    EXPECT_EQ(vec_init_with_values.x, 1.0);
    EXPECT_EQ(vec_init_with_values.y, 2.0);
    EXPECT_EQ(vec_init_with_values.z, 3.0);

    Vector3 copy_init = vec_init_with_values;
    EXPECT_EQ(copy_init.x, 1.0);
    EXPECT_EQ(copy_init.y, 2.0);
    EXPECT_EQ(copy_init.z, 3.0);

    constexpr Vector3 static_vec{4.0, 5.0, 6.0};
    static_assert(static_vec.x == 4.0 && static_vec.y == 5.0 && static_vec.z == 6.0, "Constexpr initializer failed");
}

TEST(Core_Maths, Vector3_Normalize)
{
    Vector3 startVec = Vector3{1.0, 2.0, -3.0};
    Vector3 normalized = startVec.Normalized();
    Vector3 expected = Vector3{0.2672612369, 0.5345224738, -0.8017836809};
    EXPECT_EQ(normalized, expected);
    startVec.Normalize();
    EXPECT_EQ(startVec, expected);
}
