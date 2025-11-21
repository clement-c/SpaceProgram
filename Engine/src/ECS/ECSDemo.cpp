#include <Engine/ECS/ECS.hpp>
#include <Engine/ECS/Components.hpp>
#include <Engine/ECS/ECSDebugger.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

using namespace Engine::ECS;
using namespace Engine::ECS::Components;

/**
 * @brief Physics system that updates positions based on velocities
 */
class PhysicsSystem : public System {
public:
    void Init() override {
        std::cout << "[PhysicsSystem] Initialized" << std::endl;
    }

    void Update(float deltaTime) override {
        for (Entity entity : m_entities) {
            auto& pos = m_world->GetComponent<Position>(entity);
            auto& vel = m_world->GetComponent<Velocity>(entity);
            
            pos.x += vel.x * deltaTime;
            pos.y += vel.y * deltaTime;
            pos.z += vel.z * deltaTime;
        }
    }

    void Shutdown() override {
        std::cout << "[PhysicsSystem] Shutdown" << std::endl;
    }

    const char* GetName() const override {
        return "PhysicsSystem";
    }

    void SetWorld(World* world) {
        m_world = world;
    }

private:
    World* m_world = nullptr;
};

/**
 * @brief Rotation system
 */
class RotationSystem : public System {
public:
    void Update(float deltaTime) override {
        for (Entity entity : m_entities) {
            auto& rot = m_world->GetComponent<Rotation>(entity);
            rot.yaw += rotationSpeed * deltaTime;
            
            if (rot.yaw > 360.0f) {
                rot.yaw -= 360.0f;
            }
        }
    }

    const char* GetName() const override {
        return "RotationSystem";
    }

    void SetWorld(World* world) {
        m_world = world;
    }

    float rotationSpeed = 45.0f;

private:
    World* m_world = nullptr;
};

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ECS Demo with ImGui Debugger", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Create ECS World
    World world;
    
    // Register components
    world.RegisterComponent<Position>();
    world.RegisterComponent<Velocity>();
    world.RegisterComponent<Rotation>();
    world.RegisterComponent<Name>();
    
    // Register and configure PhysicsSystem
    auto physicsSystem = world.RegisterSystem<PhysicsSystem>();
    physicsSystem->SetWorld(&world);
    {
        Signature signature;
        signature.set(world.GetComponentType<Position>());
        signature.set(world.GetComponentType<Velocity>());
        world.SetSystemSignature<PhysicsSystem>(signature);
    }
    
    // Register and configure RotationSystem
    auto rotationSystem = world.RegisterSystem<RotationSystem>();
    rotationSystem->SetWorld(&world);
    {
        Signature signature;
        signature.set(world.GetComponentType<Rotation>());
        world.SetSystemSignature<RotationSystem>(signature);
    }
    
    // Create entities
    Entity box = world.CreateEntity();
    world.AddComponent(box, Position{0.0f, 0.0f, 0.0f});
    world.AddComponent(box, Velocity{2.0f, 1.0f, 0.0f});
    world.AddComponent(box, Rotation{0.0f, 0.0f, 0.0f});
    world.AddComponent(box, Name{"Moving Box"});
    
    Entity sphere = world.CreateEntity();
    world.AddComponent(sphere, Position{5.0f, 2.0f, 0.0f});
    world.AddComponent(sphere, Rotation{0.0f, 0.0f, 0.0f});
    world.AddComponent(sphere, Name{"Rotating Sphere"});
    
    Entity particle = world.CreateEntity();
    world.AddComponent(particle, Position{-5.0f, 0.0f, 0.0f});
    world.AddComponent(particle, Velocity{3.0f, -1.0f, 0.5f});
    world.AddComponent(particle, Name{"Fast Particle"});
    
    // Create ECS Debugger
    ECSDebugger debugger(world);
    debugger.TrackEntity(box, "Moving Box");
    debugger.TrackEntity(sphere, "Rotating Sphere");
    debugger.TrackEntity(particle, "Fast Particle");
    
    // Initialize systems
    world.InitSystems();
    
    // Main loop
    float lastTime = static_cast<float>(glfwGetTime());
    bool showDemo = true;
    
    std::cout << "\n=== ECS Demo with ImGui Running ===" << std::endl;
    std::cout << "Press ESC to exit" << std::endl;
    std::cout << "Use the ImGui window to inspect and modify entities" << std::endl;
    
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        // Poll events
        glfwPollEvents();
        
        // Check for ESC key
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        
        // Update ECS
        world.UpdateSystems(deltaTime);
        
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Show demo window
        if (showDemo) {
            ImGui::ShowDemoWindow(&showDemo);
        }
        
        // Render ECS Debugger
        debugger.Render();
        
        // Additional info window
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(300, 120), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("ECS Demo Info")) {
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            ImGui::Text("Delta Time: %.3f ms", deltaTime * 1000.0f);
            ImGui::Separator();
            ImGui::Text("Entities: %u", world.GetEntityCount());
            ImGui::Text("Systems: 2 (Physics, Rotation)");
            if (ImGui::Button("Reset Positions")) {
                world.GetComponent<Position>(box) = Position{0.0f, 0.0f, 0.0f};
                world.GetComponent<Position>(sphere) = Position{5.0f, 2.0f, 0.0f};
                world.GetComponent<Position>(particle) = Position{-5.0f, 0.0f, 0.0f};
            }
        }
        ImGui::End();
        
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
    }
    
    // Cleanup
    world.ShutdownSystems();
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    std::cout << "\n=== ECS Demo Complete ===" << std::endl;
    
    return 0;
}
