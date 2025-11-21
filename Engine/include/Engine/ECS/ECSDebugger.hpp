#pragma once

#include "World.hpp"
#include "Components.hpp"
#include <imgui.h>
#include <vector>
#include <string>
#include <cstring>

namespace Engine::ECS {

/**
 * @brief ImGui-based ECS debugger
 * 
 * Provides visualization and debugging tools for the ECS:
 * - Entity browser
 * - Component inspector
 * - System statistics
 */
class ECSDebugger {
public:
    ECSDebugger(World& world) : m_world(world) {}

    /**
     * @brief Render the ECS debugger window
     */
    void Render() {
        if (!m_showWindow) return;

        ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("ECS Debugger", &m_showWindow)) {
            if (ImGui::BeginTabBar("ECSDebuggerTabs")) {
                if (ImGui::BeginTabItem("Entities")) {
                    RenderEntitiesTab();
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Systems")) {
                    RenderSystemsTab();
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Statistics")) {
                    RenderStatsTab();
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }

    /**
     * @brief Show or hide the debugger window
     */
    void SetVisible(bool visible) {
        m_showWindow = visible;
    }

    bool IsVisible() const {
        return m_showWindow;
    }

    /**
     * @brief Register an entity for tracking in the debugger
     */
    void TrackEntity(Entity entity, const char* name = nullptr) {
        EntityInfo info;
        info.entity = entity;
        if (name) {
            strncpy(info.name, name, sizeof(info.name) - 1);
            info.name[sizeof(info.name) - 1] = '\0';
        } else {
            snprintf(info.name, sizeof(info.name), "Entity %u", entity);
        }
        m_trackedEntities.push_back(info);
    }

    /**
     * @brief Clear all tracked entities
     */
    void ClearTrackedEntities() {
        m_trackedEntities.clear();
    }

private:
    struct EntityInfo {
        Entity entity;
        char name[64];
    };

    World& m_world;
    bool m_showWindow = true;
    std::vector<EntityInfo> m_trackedEntities;
    Entity m_selectedEntity = NULL_ENTITY;

    void RenderEntitiesTab() {
        ImGui::Text("Total Entities: %u", m_world.GetEntityCount());
        ImGui::Separator();

        if (ImGui::BeginChild("EntityList", ImVec2(0, 0))) {
            for (const auto& info : m_trackedEntities) {
                bool selected = (m_selectedEntity == info.entity);
                if (ImGui::Selectable(info.name, selected)) {
                    m_selectedEntity = info.entity;
                }

                if (selected && m_selectedEntity != NULL_ENTITY) {
                    ImGui::Indent();
                    
                    // Show entity signature
                    auto signature = m_world.GetEntitySignature(m_selectedEntity);
                    ImGui::Text("Signature: %s", signature.to_string().c_str());
                    
                    // Show components
                    ImGui::Text("Components:");
                    
                    // Check for common components
                    if (m_world.HasComponent<Components::Position>(m_selectedEntity)) {
                        auto& pos = m_world.GetComponent<Components::Position>(m_selectedEntity);
                        ImGui::BulletText("Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
                        
                        // Allow editing
                        if (ImGui::TreeNode("Edit Position")) {
                            ImGui::DragFloat("X", &pos.x, 0.1f);
                            ImGui::DragFloat("Y", &pos.y, 0.1f);
                            ImGui::DragFloat("Z", &pos.z, 0.1f);
                            ImGui::TreePop();
                        }
                    }
                    
                    if (m_world.HasComponent<Components::Velocity>(m_selectedEntity)) {
                        auto& vel = m_world.GetComponent<Components::Velocity>(m_selectedEntity);
                        ImGui::BulletText("Velocity: (%.2f, %.2f, %.2f)", vel.x, vel.y, vel.z);
                        
                        if (ImGui::TreeNode("Edit Velocity")) {
                            ImGui::DragFloat("VX", &vel.x, 0.1f);
                            ImGui::DragFloat("VY", &vel.y, 0.1f);
                            ImGui::DragFloat("VZ", &vel.z, 0.1f);
                            ImGui::TreePop();
                        }
                    }
                    
                    if (m_world.HasComponent<Components::Rotation>(m_selectedEntity)) {
                        auto& rot = m_world.GetComponent<Components::Rotation>(m_selectedEntity);
                        ImGui::BulletText("Rotation: (%.2f, %.2f, %.2f)", rot.pitch, rot.yaw, rot.roll);
                        
                        if (ImGui::TreeNode("Edit Rotation")) {
                            ImGui::DragFloat("Pitch", &rot.pitch, 1.0f);
                            ImGui::DragFloat("Yaw", &rot.yaw, 1.0f);
                            ImGui::DragFloat("Roll", &rot.roll, 1.0f);
                            ImGui::TreePop();
                        }
                    }
                    
                    if (m_world.HasComponent<Components::Name>(m_selectedEntity)) {
                        auto& name = m_world.GetComponent<Components::Name>(m_selectedEntity);
                        ImGui::BulletText("Name: %s", name.name);
                    }
                    
                    ImGui::Unindent();
                }
            }
        }
        ImGui::EndChild();
    }

    void RenderSystemsTab() {
        ImGui::Text("Registered Systems:");
        ImGui::Separator();

        const auto& systems = m_world.GetSystemManager().GetSystems();
        
        if (ImGui::BeginChild("SystemList")) {
            for (size_t i = 0; i < systems.size(); ++i) {
                const auto& system = systems[i];
                if (ImGui::TreeNode((void*)(intptr_t)i, "%s", system->GetName())) {
                    ImGui::Text("Entities: %zu", system->GetEntities().size());
                    
                    if (system->GetEntities().size() > 0 && ImGui::TreeNode("Entity List")) {
                        for (Entity entity : system->GetEntities()) {
                            ImGui::BulletText("Entity %u", entity);
                        }
                        ImGui::TreePop();
                    }
                    
                    ImGui::TreePop();
                }
            }
        }
        ImGui::EndChild();
    }

    void RenderStatsTab() {
        ImGui::Text("ECS Statistics");
        ImGui::Separator();
        
        ImGui::Text("Total Entities: %u", m_world.GetEntityCount());
        ImGui::Text("Tracked Entities: %zu", m_trackedEntities.size());
        ImGui::Text("Systems: %zu", m_world.GetSystemManager().GetSystems().size());
        
        ImGui::Separator();
        ImGui::Text("Memory Usage (estimated):");
        ImGui::Indent();
        ImGui::Text("Entity overhead: ~%zu bytes", m_world.GetEntityCount() * sizeof(Signature));
        ImGui::Unindent();
    }
};

} // namespace Engine::ECS
