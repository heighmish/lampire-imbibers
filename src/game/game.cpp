#include "game/game.hpp"

#include <cstddef>
#include <memory>

#include "engine/collider_component.hpp"
#include "engine/entity.hpp"
#include "engine/entity_types.hpp"
#include "engine/event_bus.hpp"
#include "engine/lifetime_handler.hpp"
#include "engine/renderable_component.hpp"
#include "engine/shapes.hpp"
#include "engine/transform_component.hpp"
#include "engine/velocity_component.hpp"
#include "game/death_event.hpp"
#include "game/health_component.hpp"
#include "game/input.hpp"
#include "game/weapon_component.hpp"
#include "raylib.h"

namespace lampire {
constexpr int PLAYER_WIDTH = 25;
constexpr int PLAYER_HEIGHT = 25;

Game::Game() {
    m_weaponsHandler.registerEvents(m_eventBus, m_entityManager);
    m_damageHandler.registerHandlers(m_eventBus);
    m_eventBus.subscribe<DeathEvent>([this](DeathEvent event) {
        if (event.entity->getType() == engine::Enemy) {
            m_score++;
        }

        if (event.entity->getType() == engine::Player) {
            m_isGameOver = true;
        }
    });
    restart();
}

void Game::restart() {
    m_entityManager.clear();

    auto player = m_entityManager.addEntity(engine::Player);
    auto rect = engine::Rect{.height = PLAYER_HEIGHT, .width = PLAYER_WIDTH};
    player->renderable =
        std::make_unique<engine::RenderableComponent>(rect, GREEN);
    player->transform = std::make_unique<engine::TransformComponent>(
        GetScreenWidth() / 2, GetScreenHeight() / 2);
    player->velocity = std::make_unique<engine::VelocityComponent>(0, 0);
    player->collider = std::make_unique<engine::ColliderComponent>(rect);
    player->weapon = std::make_unique<WeaponComponent>(0, 1, 1, 50);
    player->health = std::make_unique<HealthComponent>(10.0);
    m_isGameOver = false;
    m_score = 0;
}

void Game::update(Input inputs, double dt) {
    m_entityManager.update();

    m_inputHandler.handleInputs(m_entityManager, m_eventBus, dt, inputs);

    if (!m_isPaused && !m_isGameOver) {
        auto entities = m_entityManager.getEntities();
        m_aiHandler.UpdateBehaviour(
            m_entityManager.getEntities(engine::Player).front(),
            m_entityManager.getEntities(engine::EntityType::Enemy));
        m_movementSystem.updatePosition(entities, dt);
        m_collisionHandler.handleCollisions(entities, m_eventBus);
        m_weaponsHandler.handleWeapons(m_entityManager, dt);
        m_damageHandler.updateTimers(m_entityManager, dt);

        m_lifetimeHandler.UpdateLifetimes(m_entityManager, dt);
        m_enemySpawner.spawnEnemy(m_entityManager, dt);
        m_eventBus.handleEvents();
    }
}

void Game::render() {
    auto entities = m_entityManager.getEntities();
    m_renderer.renderEntities(entities, m_score);
    if (m_isGameOver) {
        m_renderer.drawGameOverScreen();
    } else if (m_isPaused) {
        m_renderer.drawPauseScreen();
    }
}
void Game::shutdown() {}

void Game::togglePause() { m_isPaused = !m_isPaused; }

lampire::Input checkInputs() {
    auto inputs = Input{};

    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        inputs.moveDown = true;
    }

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        inputs.moveUp = true;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        inputs.moveLeft = true;
    }

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        inputs.moveRight = true;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        inputs.isMouseDown = true;
    }
    return inputs;
}

}  // namespace lampire
