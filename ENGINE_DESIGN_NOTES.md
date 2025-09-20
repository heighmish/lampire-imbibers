# Game Engine Design Principles (Rewrite Guide)

This document summarizes the core architectural ideas for a robust game engine, based on our discussions.

### 1. The Core Architecture: Engine vs. Game

*   **Principle:** Separate generic code from game-specific code.
*   **Litmus Test:** Ask "Could I use this file in a completely different game?" If yes, it belongs in the `engine` namespace. If no, it belongs in the `game` namespace.
*   **Engine:** Contains reusable, generic systems like the ECS core (`EntityManager`, components like `TransformComponent`), the renderer, the event bus, and the main game loop. It knows nothing about "players" or "enemies."
*   **Game:** Contains the specific logic that makes your game unique: `AiHandler`, `WeaponsHandler`, and components like `WeaponComponent`.

### 2. The ECS Design: Data-Oriented Approach

*   **Principle:** Stop thinking of an Entity as an object that owns its components. Instead, the `EntityManager` (or "Registry") owns all the components in tightly packed, contiguous arrays.
*   **Entities are just IDs:** An `Entity` is just a lightweight identifier (a number), not a container.
*   **Centralize "Recipes" with Archetypes:** Don't let systems like `EnemySpawner` build entities from scratch. Define Archetypes (or Prefabs) that describe the list of components for an entity type (e.g., "base_enemy"). Systems then just ask the `EntityManager` to `createEntity("base_enemy", position)`. Use `std::string` for archetype names to enable loading them from data files later.

### 3. System Communication: Decoupling is Key

*   **Principle:** Systems should be self-contained and not know about each other.
*   **Use an Event Bus:** Instead of passing data (like `ShootAction`) between systems, use an event bus.
    *   An `InputHandler` publishes a `PlayerShotEvent`.
    *   A `WeaponsHandler` and an `AudioSystem` can both subscribe to `PlayerShotEvent` and react independently. This is a flexible, scalable way to handle communication.
*   **Orchestrate with Phases:** To manage the order of execution, group your systems into phases (`Input`, `Gameplay`, `Physics`, `Cleanup`) and run them in a fixed sequence each frame.

### 4. The Game Loop: Stability is Everything

*   **Principle:** Decouple game logic from rendering to ensure a stable and deterministic simulation.
*   **Use a Fixed Timestep:** Implement an accumulator-based game loop. Your game logic should always update in fixed time increments (e.g., 1/60th of a second), regardless of how fast the game is rendering. This prevents physics instability and makes behavior consistent across all hardware.

### 5. Core C++ Patterns: Testability and Flexibility

*   **Favor Dependency Injection over Singletons:** Avoid global state. If a system needs a service (like a `RandomNumberGenerator`), pass it into the system's constructor. This makes dependencies explicit and your code vastly easier to test.
*   **Be Data-Driven:** This is the theme that connects everything. Move hard-coded values (move speeds, fire rates, projectile counts, damage) out of your system logic and into component data. Your systems provide the *behavior*, but the components provide the *data* that drives that behavior. This allows you to create new content and tune your game without recompiling code.
*   **Manage Dependencies with Forward Declarations:** Use forward declarations (`class MyClass;`) in header files whenever you only need a pointer or reference to a type. This drastically reduces compile times and prevents circular dependency errors.
